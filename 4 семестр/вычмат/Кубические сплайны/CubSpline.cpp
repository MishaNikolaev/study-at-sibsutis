#include <iostream>
#include <cmath>
#include <iomanip>
#include <graphics.h>

using namespace std;

double custom_function(double x) {
    return sqrt(x); 
}

const int MAX_POINTS = 10;
int n;
double x0;
double step;
double x_arr[MAX_POINTS];
double y_arr[MAX_POINTS];
double x;

void calc_y() {
    for (int i = 0; i < n; i++) {
        y_arr[i] = custom_function(x_arr[i]);
    }
}

double h[MAX_POINTS-1];
double M[MAX_POINTS];

void printMatrix(double mat[][MAX_POINTS], int size) {
    cout << "Matrix:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(10) << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printVector(double vec[], int size) {
    cout << "Vector:" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(10) << vec[i] << " ";
    }
    cout << endl << endl;
}

void gauss(double mat[][MAX_POINTS+1], int size, double solution[]) {
    for (int i = 0; i < size; i++) {
        int maxRow = i;
        for (int k = i + 1; k < size; k++) {
            if (abs(mat[k][i]) > abs(mat[maxRow][i])) {
                maxRow = k;
            }
        }
        
        for (int k = i; k <= size; k++) {
            swap(mat[i][k], mat[maxRow][k]);
        }
        
        for (int k = i + 1; k < size; k++) {
            double factor = mat[k][i] / mat[i][i];
            for (int j = i; j <= size; j++) {
                mat[k][j] -= factor * mat[i][j];
            }
        }
    }
    
    for (int i = size - 1; i >= 0; i--) {
        solution[i] = mat[i][size];
        for (int j = i + 1; j < size; j++) {
            solution[i] -= mat[i][j] * solution[j];
        }
        solution[i] /= mat[i][i];
    }
}

double cubicSpline(double x_val) {
    int i = 0;
    while (i < n-1 && x_val > x_arr[i+1]) {
        i++;
    }
    
    if (i >= n-1) i = n-2;
    
    double dx = x_val - x_arr[i];
    double term1 = M[i] * pow(x_arr[i+1] - x_val, 3) / (6.0 * h[i]);
    double term2 = M[i+1] * pow(x_val - x_arr[i], 3) / (6.0 * h[i]);
    double term3 = (y_arr[i] - M[i] * h[i]*h[i] / 6.0) * (x_arr[i+1] - x_val) / h[i];
    double term4 = (y_arr[i+1] - M[i+1] * h[i]*h[i] / 6.0) * (x_val - x_arr[i]) / h[i];
    
    return term1 + term2 + term3 + term4;
}

void computeSteps() {
    cout << "Calculating steps h:" << endl;
    for (int i = 0; i < n-1; i++) {
        h[i] = x_arr[i+1] - x_arr[i];
        cout << "h[" << i << "] = " << h[i] << endl;
    }
    cout << endl;
}

void setupSplineSystem(double mat[][MAX_POINTS+1]) {
    for (int i = 0; i < n-2; i++) {
        for (int j = 0; j < n-1; j++) {
            mat[i][j] = 0.0;
        }
    }
    
    for (int i = 0; i < n-2; i++) {
        if (i > 0) mat[i][i-1] = h[i] / 6.0;
        mat[i][i] = (h[i] + h[i+1]) / 3.0;
        if (i < n-3) mat[i][i+1] = h[i+1] / 6.0;
        
        mat[i][n-1] = ((y_arr[i+2] - y_arr[i+1]) / h[i+1]) - 
                      ((y_arr[i+1] - y_arr[i]) / h[i]);
    }
}

void solveForM() {
    M[0] = 0;
    M[n-1] = 0;
    
    if (n <= 2) return; 
    
    double mat[MAX_POINTS][MAX_POINTS+1];
    setupSplineSystem(mat);
    
    cout << "Extended matrix before solving:" << endl;
    for (int i = 0; i < n-2; i++) {
        for (int j = 0; j < n-1; j++) {
            cout << setw(10) << mat[i][j] << " ";
        }
        cout << " | " << setw(10) << mat[i][n-1] << endl;
    }
    cout << endl;
    
    double solution[MAX_POINTS];
    gauss(mat, n-2, solution);
    
    for (int i = 0; i < n-2; i++) {
        M[i+1] = solution[i];
    }
    
    cout << "Vector M:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "M[" << i << "] = " << M[i] << endl;
    }
    cout << endl;
}

void draw_graph() {
    int win_width = 1200;
    int win_height = 800;
    initwindow(win_width, win_height, "Cubic Spline Interpolation");
    
    setbkcolor(WHITE);
    cleardevice();

    const int margin_left = 100;
    const int margin_right = 50;
    const int margin_top = 50;
    const int margin_bottom = 100;

    int graph_width = win_width - margin_left - margin_right;
    int graph_height = win_height - margin_top - margin_bottom;

    double x_min = x_arr[0];
    double x_max = x_arr[n-1];
    double x_range = x_max - x_min;
    x_min -= x_range * 0.2;
    x_max += x_range * 0.2;
    if (x_min < 0) x_min = 0;

    double y_min = 0.0;
    double y_max = 0.0;
    
    for (int i = 0; i < n; i++) {
        if (y_arr[i] > y_max) y_max = y_arr[i];
    }
    
    double step_size = (x_max - x_min) / 100;
    for (double xi = x_min; xi <= x_max; xi += step_size) {
        double yi = cubicSpline(xi);
        if (yi > y_max) y_max = yi;
    }
    
    y_max *= 1.1; 

    double scaleX = graph_width / (x_max - x_min);
    double scaleY = graph_height / (y_max - y_min);

    int originX = margin_left;
    int originY = win_height - margin_bottom;

    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 2);
    line(originX, originY, originX + graph_width, originY);
    line(originX, originY, originX, originY - graph_height);

    outtextxy(originX + graph_width - 20, originY + 20, "X");
    outtextxy(originX - 30, originY - graph_height + 10, "Y");

    setcolor(LIGHTGRAY);
    setlinestyle(DOTTED_LINE, 0, 1);
    
    for (double x_val = ceil(x_min); x_val <= floor(x_max); x_val += max(1.0, (x_max-x_min)/10)) {
        int px = originX + (x_val - x_min) * scaleX;
        line(px, originY, px, originY - graph_height);
        
        char label[20];
        sprintf(label, "%.1f", x_val);
        outtextxy(px - 15, originY + 10, label);
    }
    
    for (double y_val = ceil(y_min); y_val <= floor(y_max); y_val += max(1.0, (y_max-y_min)/10)) {
        int py = originY - (y_val - y_min) * scaleY;
        line(originX, py, originX + graph_width, py);
        
        char label[20];
        sprintf(label, "%.1f", y_val);
        outtextxy(originX - 50, py - 5, label);
    }

    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, 2);
    step_size = (x_max - x_min) / 200;
    int prev_px = -1, prev_py = -1;
    
    for (double xi = x_min; xi <= x_max; xi += step_size) {
        double yi = custom_function(xi);
        if (!isnan(yi)) {
            int px = originX + (xi - x_min) * scaleX;
            int py = originY - (yi - y_min) * scaleY;
            
            if (prev_px != -1) {
                line(prev_px, prev_py, px, py);
            }
            prev_px = px;
            prev_py = py;
        }
    }

    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, 2);
    prev_px = -1; prev_py = -1;
    
    for (double xi = x_min; xi <= x_max; xi += step_size) {
        double yi = cubicSpline(xi);
        if (!isnan(yi)) {
            int px = originX + (xi - x_min) * scaleX;
            int py = originY - (yi - y_min) * scaleY;
            
            if (prev_px != -1) {
                line(prev_px, prev_py, px, py);
            }
            prev_px = px;
            prev_py = py;
        }
    }

    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    for (int i = 0; i < n; i++) {
        int px = originX + (x_arr[i] - x_min) * scaleX;
        int py = originY - (y_arr[i] - y_min) * scaleY;
        circle(px, py, 5);
        floodfill(px, py, GREEN);
    }

    setcolor(BLUE);
    outtextxy(50, 30, "Original function (sqrt(x))");
    setcolor(RED);
    outtextxy(50, 50, "Cubic spline");
    setcolor(GREEN);
    outtextxy(50, 70, "Interpolation points");

    setcolor(BLACK);
    char info[100];
    sprintf(info, "Number of points: %d", n);
    outtextxy(50, 100, info);
    sprintf(info, "Step size: %.2f", step);
    outtextxy(50, 120, info);

    getch();
    closegraph();
}

int main() {
    cout << "Enter initial x0: ";
    cin >> x0;
    cout << "Enter step h: ";
    cin >> step;
    cout << "Enter number of nodes n (>=2): ";
    cin >> n;
    
    if (n < 2) {
        cout << "n must be >= 2." << endl;
        return 1;
    }
    if (n > MAX_POINTS) {
        cout << "n must be <= " << MAX_POINTS << endl;
        return 1;
    }

    for (int i = 0; i < n; i++) {
        x_arr[i] = x0 + i * step;
    }
    calc_y();

    computeSteps();
    solveForM();

    cout << fixed << setprecision(6);
    for (int i = 0; i < n; i++) {
        double xi = x_arr[i];
        double si = cubicSpline(xi);
        cout << "S(" << xi << ") = " << si << " (exact: " << y_arr[i] << ")" << endl;
    }

    draw_graph();

    return 0;
}

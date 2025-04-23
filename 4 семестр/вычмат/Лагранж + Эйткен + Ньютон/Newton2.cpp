#include <iostream>
#include <cmath>
#include <graphics.h>
using namespace std;

double custom_function(double x) {
    return sqrt(x); 
}

int n;
double x0;
double step;
double* x_arr;
double* y_arr;
double** delta_y;
double x;

void calc_y() {
    for (int i = 0; i < n; i++) {
        y_arr[i] = custom_function(x_arr[i]);
    }
}

void calculate_deltas() {
    delta_y = new double*[n-1];
    for (int i = 0; i < n-1; i++) {
        delta_y[i] = new double[n-1-i];
    }
    
    for (int i = 0; i < n-1; i++) {
        delta_y[0][i] = y_arr[i+1] - y_arr[i];
    }
    
    for (int j = 1; j < n-1; j++) {
        for (int i = 0; i < n-1-j; i++) {
            delta_y[j][i] = delta_y[j-1][i+1] - delta_y[j-1][i];
        }
    }
}

double factorial(int k) {
    double result = 1.0;
    for (int i = 2; i <= k; i++) {
        result *= i;
    }
    return result;
}

double NewtonSecondFormula(double x_val) {
    double h = x_arr[1] - x_arr[0];
    double q = (x_val - x_arr[n-1]) / h;
    
    double result = y_arr[n-1];
    double term = q;
    
    for (int i = 1; i < n; i++) {
        result += term * delta_y[i-1][n-1-i] / factorial(i);
        term *= (q + i);
    }
    
    return result;
}

void draw_graph(double interpolated_y) {
    setbkcolor(WHITE);
    cleardevice();

    const int margin_left = 100;
    const int margin_right = 50;
    const int margin_top = 50;
    const int margin_bottom = 100;

    int graph_width = getmaxx() - margin_left - margin_right;
    int graph_height = getmaxy() - margin_top - margin_bottom;

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
        double yi = custom_function(xi);
        if (yi > y_max) y_max = yi;
    }
    
    y_max *= 1.1;

    double scaleX = graph_width / (x_max - x_min);
    double scaleY = graph_height / (y_max - y_min);

    int originX = margin_left;
    int originY = getmaxy() - margin_bottom;


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
        } else {
            prev_px = -1;
        }
    }

    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, 2);
    prev_px = -1; prev_py = -1;
    
    for (double xi = x_min; xi <= x_max; xi += step_size) {
        double yi = NewtonSecondFormula(xi);
        if (!isnan(yi)) {
            int px = originX + (xi - x_min) * scaleX;
            int py = originY - (yi - y_min) * scaleY;
            
            if (prev_px != -1) {
                line(prev_px, prev_py, px, py);
            }
            prev_px = px;
            prev_py = py;
        } else {
            prev_px = -1;
        }
    }

    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    for (int i = 0; i < n; i++) {
        if (!isnan(y_arr[i])) {
            int px = originX + (x_arr[i] - x_min) * scaleX;
            int py = originY - (y_arr[i] - y_min) * scaleY;
            circle(px, py, 4);
            floodfill(px, py, BLUE);
        }
    }

    setcolor(BLACK);
    char info[100];
    sprintf(info, "Number of points: %d", n);
    outtextxy(20, 20, info);
    sprintf(info, "X: %.2f", x);
    outtextxy(20, 40, info);
    sprintf(info, "P%d(X): %.4f", n-1, interpolated_y);
    outtextxy(20, 60, info);
    sprintf(info, "f(X): %.4f", custom_function(x));
    outtextxy(20, 80, info);
}

int main() {
    cout << "Enter initial x0: ";
    cin >> x0;
    if (x0 < 0) {
        cout << "x0 must be >= 0." << endl;
        return 1;
    }
    
    cout << "Enter step h: ";
    cin >> step;
    cout << "Enter number of nodes n (>=2): ";
    cin >> n;
    if (n < 2) {
        cout << "n must be >= 2." << endl;
        return 1;
    }

    x = x0 + (n - 1) * step / 2.0; 

    int gd = DETECT, gm;
    initwindow(1200, 800, "Newton Interpolation Graph");

    x_arr = new double[n];
    y_arr = new double[n];

    for (int i = 0; i < n; i++) {
        x_arr[i] = x0 + i * step;
    }

    calc_y();
    calculate_deltas();
    double y = NewtonSecondFormula(x);

    cout << "P_" << n-1 << "(x) = " << y << endl;

    draw_graph(y);

    while (!kbhit()) {
        delay(100);
    }

    for (int i = 0; i < n-1; i++) {
        delete[] delta_y[i];
    }
    delete[] delta_y;
    delete[] x_arr;
    delete[] y_arr;
    closegraph();
    return 0;
}

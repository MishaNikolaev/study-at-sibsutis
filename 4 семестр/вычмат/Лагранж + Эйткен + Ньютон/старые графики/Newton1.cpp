#include <iostream>
#include <cmath>
#include <iomanip>
#include <graphics.h>

using namespace std;

double custom_function(double x) {
    //if (fabs(x) < 1e-10) return NAN;
    //return (1.0 / x);
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

double NewtonFirstFormula(double x_val) {
    double h = x_arr[1] - x_arr[0];
    double q = (x_val - x_arr[0]) / h;
    
    double result = y_arr[0];
    double term = q;
    
    for (int i = 1; i < n; i++) {
        result += term * delta_y[i-1][0] / tgamma(i+1);
        term *= (q - i);
    }
    
    return result;
}

double offsetX = 0.0;
double offsetY = 0.0;

void draw_graph(double interpolated_y) {
    setbkcolor(WHITE);
    cleardevice();

    double x_min = x_arr[0];
    double x_max = x_arr[n-1];
    
    double x_margin = (x_max - x_min) * 0.1;
    x_min = x_min - x_margin;
    x_max = x_max + x_margin;

    double y_min = +1e10;
    double y_max = -1e10;
    
    for (int i = 0; i < n; i++) {
        if (!isnan(y_arr[i])) {
            y_min = min(y_min, y_arr[i]);
            y_max = max(y_max, y_arr[i]);
        }
    }
    
    for (double xi = x_min; xi <= x_max; xi += 0.1) {
        double yi = custom_function(xi);
        if (!isnan(yi)) {
            y_min = min(y_min, yi);
            y_max = max(y_max, yi);
        }
    }
    
    double y_margin = (y_max - y_min) * 0.1;
    y_min = y_min - y_margin;
    y_max = y_max + y_margin;
    
    if (isinf(y_min) || isinf(y_max) || isnan(y_min) || isnan(y_max)) {
        y_min = -10;
        y_max = 10;
    }

    double scaleX = (getmaxx() * 0.9) / (x_max - x_min);
    double scaleY = (getmaxy() * 0.9) / (y_max - y_min);
    
    int centerX = getmaxx() * 0.05 + offsetX;
    int centerY = getmaxy() * 0.95 + offsetY;

    setcolor(LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, 1);
    for (double i = floor(x_min); i <= ceil(x_max); i += 1.0) {
        int px = centerX + (i - x_min) * scaleX;
        line(px, 0, px, getmaxy());
    }
    for (double i = floor(y_min); i <= ceil(y_max); i += 1.0) {
        int py = centerY - (i - y_min) * scaleY;
        line(0, py, getmaxx(), py);
    }

    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 3);
    
    int x_axis_y = centerY - (0 - y_min) * scaleY;
    if (y_min <= 0 && y_max >= 0) {
        line(0, x_axis_y, getmaxx(), x_axis_y);
    } else {
        x_axis_y = centerY;
        line(0, x_axis_y, getmaxx(), x_axis_y);
    }
    
    int y_axis_x = centerX + (0 - x_min) * scaleX;
    if (x_min <= 0 && x_max >= 0) {
        line(y_axis_x, 0, y_axis_x, getmaxy());
    } else {
        y_axis_x = centerX;
        line(y_axis_x, 0, y_axis_x, getmaxy());
    }

    outtextxy(getmaxx() - 30, x_axis_y - 20, (char*)"X");
    outtextxy(y_axis_x + 10, 10, (char*)"Y");

    setcolor(BLACK);
    for (double i = floor(x_min); i <= ceil(x_max); i += max(1.0, floor((x_max - x_min)/10))) {
        int px = centerX + (i - x_min) * scaleX;
        if (px >= 0 && px <= getmaxx()) {
            char label[10];
            sprintf(label, "%.0f", i);
            outtextxy(px - 10, x_axis_y + 5, label);
        }
    }
    for (double i = floor(y_min); i <= ceil(y_max); i += max(1.0, floor((y_max - y_min)/10))) {
        int py = centerY - (i - y_min) * scaleY;
        if (py >= 0 && py <= getmaxy()) {
            char label[10];
            sprintf(label, "%.0f", i);
            outtextxy(y_axis_x + 10, py - 5, label);
        }
    }

    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, 2);
    double plot_step = 0.1;
    int prev_px = -1, prev_py = -1;
    for (double xi = 0; xi <= x_max; xi += plot_step) {
        double yi = custom_function(xi);
        if (!isnan(yi)) {
            int px = centerX + (xi - x_min) * scaleX;
            int py = centerY - (yi - y_min) * scaleY;
            
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
    for (double xi = x_min; xi <= x_max; xi += plot_step) {
        double yi = NewtonFirstFormula(xi);
        if (!isnan(yi)) {
            int px = centerX + (xi - x_min) * scaleX;
            int py = centerY - (yi - y_min) * scaleY;
            
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
            int px = centerX + (x_arr[i] - x_min) * scaleX;
            int py = centerY - (y_arr[i] - y_min) * scaleY;
            circle(px, py, 5);
            floodfill(px, py, BLUE);
        }
    }

    char info[100];
    setcolor(BLACK);
    sprintf(info, "Number of points: %d", n);
    outtextxy(20, 20, info);
    sprintf(info, "X: %.2f", x);
    outtextxy(20, 40, info);
    sprintf(info, "P%d(X): %.4f", n-1, interpolated_y);
    outtextxy(20, 60, info);
    sprintf(info, "f(X): %.4f", custom_function(x));
    outtextxy(20, 80, info);
    sprintf(info, "Error: %.4f", fabs(interpolated_y - custom_function(x)));
    outtextxy(20, 100, info);

    setcolor(BLACK);
    outtextxy(20, getmaxy() - 120, (char*)"  X     |     Y");
    outtextxy(20, getmaxy() - 110, (char*)"----------------");
    for (int i = 0; i < min(n, 10); i++) { 
        char coord[30];
        sprintf(coord, " %.2f  |  %.4f", x_arr[i], y_arr[i]);
        outtextxy(20, getmaxy() - 100 + i * 15, coord);
    }
    if (n > 10) {
        outtextxy(20, getmaxy() - 100 + 10 * 15, (char*)"... more points ...");
    }

}

int main() {
    cout << "Enter initial x0: ";
    cin >> x0;
    cout << "Enter h: ";
    cin >> step;
    cout << "Enter number of nodes n (>=2): ";
    cin >> n;
    if (n < 2) {
        cout << "n must be >= 2." << endl;
        return 1;
    }

    x = x0 + (n - 1) * step / 2.0;  

    int gd = DETECT, gm;
    initwindow(1600, 800, "Newton Interpolation Graph");

    x_arr = new double[n];
    y_arr = new double[n];

    for (int i = 0; i < n; i++) {
        x_arr[i] = x0 + i * step;
    }

    calc_y();
    calculate_deltas();
    double y = NewtonFirstFormula(x);

    cout << fixed << setprecision(4);
    cout << "P_" << n-1 << "(x) = " << y << endl;
    cout << "f(x) = " << custom_function(x) << endl;

    draw_graph(y);

    while (true) {
        if (kbhit()) {
            int key = getch();
            if (key == 27) break; 
            if (key == 0 || key == 224) {
                key = getch();
                switch (key) {
                    case 72: offsetY += 50; break;  
                    case 80: offsetY -= 50; break;  
                    case 75: offsetX += 50; break;  
                    case 77: offsetX -= 50; break;  
                }
            }
            cleardevice();
            draw_graph(y);
        }
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

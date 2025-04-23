#include <iostream>
#include <complex>
#include <cmath>
#include <iomanip>
#include <graphics.h>

using namespace std;

double custom_function(double x) {
    return sqrt(x);
}

complex<double> TrigInterpolate(double X, const double x_arr[], const double y_arr[], int n) {
    const double pi = M_PI;
    complex<double> A0(0, 0), A1(0, 0), A_1(0, 0), A2(0, 0);
    
    for (int k = 0; k < n; k++) {
        double angle = 2 * pi * k / n;
        A0 += y_arr[k];
        A1 += y_arr[k] * complex<double>(cos(angle), -sin(angle));
        A_1 += y_arr[k] * complex<double>(cos(angle), sin(angle));
        A2 += y_arr[k] * complex<double>(cos(2*angle), -sin(2*angle));
    }

    double t = (X - x_arr[0]) / (n * (x_arr[1] - x_arr[0]));

    complex<double> result = (A0 + 
                            A1 * exp(complex<double>(0, 2*pi*1*t)) + 
                            A_1 * exp(complex<double>(0, -2*pi*1*t)) + 
                            A2 * exp(complex<double>(0, 2*pi*2*t))) / double(n);

    return result;
}

void draw_graph(const double x_arr[], const double y_arr[], int n, double x_interp) {
    setbkcolor(WHITE);
    cleardevice();

    const int margin_left = 100;
    const int margin_right = 50;
    const int margin_top = 50;
    const int margin_bottom = 100;

    int graph_width = getmaxx() - margin_left - margin_right;
    int graph_height = getmaxy() - margin_top - margin_bottom;

    double x_min = x_arr[0] - 1.0;
    double x_max = x_arr[n-1] + 1.0;
    
    double y_min = 0.0;
    double y_max = 0.0;
    for (int i = 0; i < n; i++) {
        if (y_arr[i] < y_min) y_min = y_arr[i];
        if (y_arr[i] > y_max) y_max = y_arr[i];
    }
    
    y_min -= 1.0;
    y_max += 1.0;

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
    for (double x_val = ceil(x_min); x_val <= floor(x_max); x_val += 1.0) {
        int px = originX + (x_val - x_min) * scaleX;
        line(px, originY, px, originY - graph_height);
        char label[20];
        sprintf(label, "%.0f", x_val);
        outtextxy(px - 5, originY + 10, label);
    }
    
    for (double y_val = ceil(y_min); y_val <= floor(y_max); y_val += 1.0) {
        int py = originY - (y_val - y_min) * scaleY;
        line(originX, py, originX + graph_width, py);
        char label[20];
        sprintf(label, "%.0f", y_val);
        outtextxy(originX - 30, py - 5, label);
    }

    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, 2);
    double step_size = (x_max - x_min) / 200;
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

    complex<double>* interp_results = new complex<double>[n];
    for (int i = 0; i < n; i++) {
        interp_results[i] = TrigInterpolate(x_arr[i], x_arr, y_arr, n);
    }

    double slope_re = (interp_results[n-1].real() - interp_results[0].real()) / (x_arr[n-1] - x_arr[0]);
    double x_start = x_arr[0] - (x_arr[n-1] - x_arr[0]) * 0.2;
    double x_end = x_arr[n-1] + (x_arr[n-1] - x_arr[0]) * 0.2;
    double y_start = interp_results[0].real() - slope_re * (x_arr[0] - x_start);
    double y_end = interp_results[0].real() + slope_re * (x_end - x_arr[0]);

    int px1_ext = originX + (x_start - x_min) * scaleX;
    int py1_ext = originY - (y_start - y_min) * scaleY;
    int px2_ext = originX + (x_end - x_min) * scaleX;
    int py2_ext = originY - (y_end - y_min) * scaleY;

    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, 2);
    line(px1_ext, py1_ext, px2_ext, py2_ext);

    setcolor(GREEN);
    setlinestyle(SOLID_LINE, 0, 2);
    int py1_im = originY - (interp_results[0].imag() - y_min) * scaleY;
    int py2_im = originY - (interp_results[n-1].imag() - y_min) * scaleY;
    int px1 = originX + (x_arr[0] - x_min) * scaleX;
    int px2 = originX + (x_arr[n-1] - x_min) * scaleX;
    line(px1, py1_im, px2, py2_im);

    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    for (int i = 0; i < n; i++) {
        int px = originX + (x_arr[i] - x_min) * scaleX;
        int py = originY - (y_arr[i] - y_min) * scaleY;
        circle(px, py, 4);
        floodfill(px, py, BLUE);
    }

    setcolor(BLUE);
    outtextxy(getmaxx() - 200, 50, "Custom function (sqrt(x))");
    setcolor(RED);
    outtextxy(getmaxx() - 200, 70, "Real part (ReZ)");
    setcolor(GREEN);
    outtextxy(getmaxx() - 200, 90, "Imaginary part (ImZ)");
    setcolor(BLACK);
    outtextxy(getmaxx() - 200, 110, "Original points");

    complex<double> interp_result = TrigInterpolate(x_interp, x_arr, y_arr, n);
    char info[100];
    sprintf(info, "Interpolation at x = %.2f", x_interp);
    outtextxy(20, 20, info);
    sprintf(info, "ReZ = %.4f", interp_result.real());
    outtextxy(20, 40, info);
    sprintf(info, "ImZ = %.4f", interp_result.imag());
    outtextxy(20, 60, info);

    delete[] interp_results;
}

int main() {
    double x0, h;
    int n;
    
    cout << "Enter initial x0: ";
    cin >> x0;
    cout << "Enter step h: ";
    cin >> h;
    cout << "Enter number of points n: ";
    cin >> n;
    
    double* x_arr = new double[n];
    double* y_arr = new double[n];
    
    for (int i = 0; i < n; i++) {
        x_arr[i] = x0 + i * h;
        y_arr[i] = custom_function(x_arr[i]);
    }
    
    double x_interp = x0 + (n - 1) * h / 2.0;
    
    complex<double> result = TrigInterpolate(x_interp, x_arr, y_arr, n);
    
    cout << fixed << setprecision(4);
    cout << "Interpolation at x = " << x_interp << endl;
    cout << "ReZ = " << result.real() << endl;
    cout << "ImZ = " << result.imag() << endl;

    int gd = DETECT, gm;
    initwindow(1200, 800, "Trigonometric Interpolation Graph");
    
    draw_graph(x_arr, y_arr, n, x_interp);
    
    while (!kbhit()) {
        delay(100);
    }
    
    delete[] x_arr;
    delete[] y_arr;
    closegraph();
    
    return 0;
}


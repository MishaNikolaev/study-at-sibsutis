#include <iostream>
#include <cmath>
#include <iomanip>
  
using namespace std;

double func(double x) {
    return pow(x, 2) - 2;
}

double diff_func(double x) {
    return 2 * x;
}

double epsilon = 1e-8;
int step = 44;

double MPD(double a, double b) {
    double c;

    for (int i = 0; i < step; i++) {
        c = (a + b)/2;
        double fc = func(c);
        double fa = func(a);
        double fb = func(b);

        cout << "Step " << i + 1 << " [" << a << "; " << b << "]:" << endl;
        cout << "c = " << fixed << setprecision(3) << c << "  f(c) = " << fc << endl;
        cout << "in intervals [" << a << "; " << c << "]  f(a) * f(c) = " << fa * fc << endl;
        cout << "             [" << c << "; " << b << "]  f(c) * f(b) = " << fc * fb << endl;
        cout << "----------------------------------------------------" << endl;

        if (abs(fc) < epsilon) {
            return c;
        }

        if (fa * fc < 0) {
            b = c;
        }
        if (fc * fb < 0) {
            a = c;
        }
    }
    return c;
}

double Hord(double a, double b) {
    double c, c_old = 0.0;

    for (int i = 0; i < step; i++) {
        c = (a * func(b) - b * func(a)) / (func(b) - func(a));
        double fc = func(c);
        double fa = func(a);
        double fb = func(b);

        cout << "Step " << i + 1 << " [" << a << "; " << b << "]:" << endl;
        cout << "c = " << fixed << setprecision(3) << c << "  f(c) = " << fc << endl;
        cout << "in intervals [" << a << "; " << c << "]  f(a) * f(c) = " << fa * fc << endl;
        cout << "             [" << c << "; " << b << "]  f(c) * f(b) = " << fc * fb << endl;
        cout << "----------------------------------------------------" << endl;

        if (abs(c - c_old) < epsilon) {
            return c;
        }

        if (func(a) * func(c) < 0) {
            b = c;
        } else {
            a = c;
        }

        c_old = c;
    }
    return c;
}

double Newton(double x0) {
    double x = x0;
    cout << "Method Newton:" << endl;
    cout << "x0 = " << fixed << setprecision(3) << x << "  f(x0) = " << func(x) << "  diff_func(x0) =" << diff_func(x) << endl;

    for (int i = 0; i < step; i++) {
        double x_next = x - func(x) / diff_func(x);
        cout << "x" << i + 1 << " = " << fixed << setprecision(3) << x_next << "  f(x" << i + 1 << ") = " << func(x_next) << "  diff_func(x" << i + 1 << ") = " << diff_func(x_next) << endl;
  
        if (abs(x_next - x) < epsilon) {
            return x_next;
        }

        x = x_next;
    }
    return x;
}

int main() {
    double a = 1, b = 2;
    cout << "Method polovinnogo delenia:" << endl;
    double result = MPD(a, b);
    cout << "Result: " << result << endl;
    cout << endl; 

    cout << "Method Hord:" << endl;
    double result2 = Hord(a, b);
    cout << "Result: " << result2 << endl;
    cout << endl;

    double x0 = 2.0;
    double result3 = Newton(x0);
    cout << "Result: " << result3 << endl;

    return 0;
}

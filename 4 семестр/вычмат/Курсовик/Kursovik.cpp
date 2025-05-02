#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double epsilon = 1e-8;
const double h = 0.1;
const double a = 0.0;
const double b = 1.0;
const double Y0 = 1.0;
const double DY0 = 1.0; 

void f(double x, double y, double dy, double F[2]) {
    F[0] = dy;
    F[1] = (exp(x) + y + dy) / 3.0;
}

void Runge_Kutta(double a, double b, double h, double y, double dy, bool flag, double result[2]) {
    int n = static_cast<int>(round((b - a) / h)) + 1;
    double* X = new double[n];
    double Y[2] = {y, dy};
    
    for (int i = 0; i < n; i++) {
        X[i] = a + i * h;
    }
    
    if (flag) {
        cout << fixed << setprecision(6) << X[0] << "     " 
             << setprecision(9) << Y[0] << "     " << Y[1] << endl;
    }
    
    for (int i = 1; i < n; i++) {
        double K1[2], K2[2], K3[2], K4[2];
        
        f(X[i-1], Y[0], Y[1], K1);
        f(X[i-1] + h/2, Y[0] + h/2 * K1[0], Y[1] + h/2 * K1[1], K2);
        f(X[i-1] + h/2, Y[0] + h/2 * K2[0], Y[1] + h/2 * K2[1], K3);
        f(X[i-1] + h, Y[0] + h * K3[0], Y[1] + h * K3[1], K4);
        
        Y[0] = Y[0] + h/6 * (K1[0] + 2*K2[0] + 2*K3[0] + K4[0]);
        Y[1] = Y[1] + h/6 * (K1[1] + 2*K2[1] + 2*K3[1] + K4[1]);
        
        if (flag) {
            cout << fixed << setprecision(6) << X[i] << "     " 
                 << setprecision(9) << Y[0] << "     " << Y[1] << endl;
        }
    }
    
    result[0] = Y[0];
    result[1] = Y[1];
    delete[] X;
}

double dv_peresch(double eps, double h, double a, double b, double y0, double dy0) {
    double Y1[2], Y2[2];
    
    Runge_Kutta(a, b, h, y0, dy0, false, Y1);
    Runge_Kutta(a, b, h/2, y0, dy0, false, Y2);
    
    while (fabs(Y1[0] - Y2[0]) > eps) {
        h /= 2.0;
        Y1[0] = Y2[0];
        Y1[1] = Y2[1];
        Runge_Kutta(a, b, h/2, y0, dy0, false, Y2);
    }
    
    cout << "--------------------" << endl;
    cout << "h = " << h/2 << endl;
    return h/2;
}

int main() {
    double h_new = dv_peresch(epsilon, h, a, b, Y0, DY0);
    
    double Y[2];
    Runge_Kutta(a, b, h_new, Y0, DY0, true, Y);
    
    return 0;
}

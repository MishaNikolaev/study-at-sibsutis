#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void gauss(double a[3][3], double y[3], double answers[3]) {
    const int n = 3;
    
    for (int i = 0; i < n; i++) {
        double diagonal = a[i][i];
        for (int j = i; j < n; j++) {
            a[i][j] /= diagonal;
        }
        y[i] /= diagonal;
        
        for (int k = i + 1; k < n; k++) {
            double factor = a[k][i];
            for (int j = i; j < n; j++) {
                a[k][j] -= factor * a[i][j];
            }
            y[k] -= factor * y[i];
        }
    }
    
    for (int i = n - 1; i >= 0; i--) {
        answers[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            answers[i] -= a[i][j] * answers[j];
        }
    }
}

void least_squares(double x[], double y[], int n, double &a, double &b, double &c) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0, sum_xxx = 0, sum_xxxx = 0, sum_xxy = 0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += x[i] * x[i];
        sum_xxx += x[i] * x[i] * x[i];
        sum_xxxx += x[i] * x[i] * x[i] * x[i];
        sum_xxy += x[i] * x[i] * y[i];
    }

    cout << "\nSum for system of uravnenyi:\n";
    cout << "Sum(x) = " << fixed << setprecision(4) << sum_x << endl;
    cout << "Sum(y) = " << sum_y << endl;
    cout << "Sum(xy) = " << sum_xy << endl;
    cout << "Sum(x^2) = " << sum_xx << endl;
    cout << "Sum(x^3)= " << sum_xxx << endl;
    cout << "Sum(x^4 )= " << sum_xxxx << endl;
    cout << "Sum(x^2*y) = " << sum_xxy << endl;

    double matrix[3][3] = {
        {static_cast<double>(n), sum_x, sum_xx},
        {sum_x, sum_xx, sum_xxx},
        {sum_xx, sum_xxx, sum_xxxx}
    };
    double col[3] = {sum_y, sum_xy, sum_xxy};

    cout << "\nMatrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nVector:\n";
    for (int i = 0; i < 3; i++) {
        cout << col[i] << " ";
    }
    cout << endl;

    double coef[3];
    gauss(matrix, col, coef);
    a = coef[0];
    b = coef[1];
    c = coef[2];

    cout << "\nAfter pryamoi hod:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nCoefficients:\n";
    cout << "a = " << fixed << setprecision(6) << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
}

int main() {
    const int n = 4;
    double x[n] = {0, 1, 2, 3};
    double y[n] = {0, 1, 4, 9};

    cout << "initial X and Y:\n";
    cout << "X:";
    for (int i = 0; i < n; i++) {
        cout << " " << fixed << setprecision(3) << x[i];
    }
    cout << "\nY:";
    for (int i = 0; i < n; i++) {
        cout << " " << y[i];
    }
    cout << endl;

    double a, b, c;
    least_squares(x, y, n, a, b, c);

    cout << "\nUravnenye:\n";
    cout << "y = " << fixed << setprecision(4) << a << " + " << b << "x + " << c << "x^2" << endl;

    return 0;
}

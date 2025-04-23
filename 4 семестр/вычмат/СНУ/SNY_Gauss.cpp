#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double epsilon = 1e-8;
const int size = 2;

double x = 2.0;
double y = 1.0;
double f[size];
double W[size][size];
double x_vector[size];

void F() {
    f[0] = x * x + y * y - 6;
    f[1] = x - y - 2;
}

void Wmatrix() {
    W[0][0] = 2 * x;
    W[0][1] = 2 * y;
    W[1][0] = 1;
    W[1][1] = -1;
}

void gauss() {
    double matrix[size][size + 1] = {
        {W[0][0], W[0][1], f[0]},
        {W[1][0], W[1][1], f[1]}
    };

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            double coef = matrix[j][i] / matrix[i][i];
            for (int k = i; k <= size; k++) {
                matrix[j][k] -= coef * matrix[i][k];
            }
        }
    }

    for (int i = size - 1; i >= 0; i--) {
        x_vector[i] = matrix[i][size];
        for (int j = i + 1; j < size; j++) {
            x_vector[i] -= matrix[i][j] * x_vector[j];
        }
        x_vector[i] /= matrix[i][i];
    }
}

int main() {
    cout << fixed << setprecision(6);

    while (true) {
        F(); 
        Wmatrix(); 

        cout << "F(x,y) = [" << f[0] << ", " << f[1] << "]" << endl;

        if (fabs(f[0]) < epsilon && fabs(f[1]) < epsilon) {
            cout << "Finded: x = " << x << ", y = " << y << endl;
            break;
        }

        gauss();

        x -= x_vector[0];
        y -= x_vector[1];

        cout << "New epsilon: x = " << x << ", y = " << y << endl << endl;
    }

    return 0;
}

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int matrix_size = 3;
float answers[matrix_size];

float matrix[matrix_size][matrix_size + 1] = {
        {2, 3, 1, 7},
        {-4, 2, -3, 1},
        {-5, 2, -3, 1}
};

void printMatrix() {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size + 1; j++) {
            cout << fixed << setprecision(1) << matrix[i][j] << " "; 
        }
        cout << endl;
    }
}

void leadEl(int &leadString) {
    int maxRow = leadString;
    float maxElement = fabs(matrix[leadString][leadString]);
    
    for (int i = leadString + 1; i < matrix_size; i++) {
        if (fabs(matrix[i][leadString]) > maxElement) {
            maxElement = fabs(matrix[i][leadString]);
            maxRow = i;
        }
    }

    if (maxRow != leadString) {
        for (int j = 0; j <= matrix_size; j++) {
            float temp = matrix[leadString][j];
            matrix[leadString][j] = matrix[maxRow][j];
            matrix[maxRow][j] = temp;
        }
    }
}

void gaussLeadEl() {
    int leadingRow = 0;
    leadEl(leadingRow);
    for (int i = 0; i < matrix_size; i++) {
        for (int j = i + 1; j < matrix_size; j++) {
            float flag = matrix[j][i] / matrix[i][i];
            for (int k = i; k < matrix_size + 1; k++) {
                matrix[j][k] -= matrix[i][k] * flag;
            }
        }
        for (int i = matrix_size - 1; i >= 0; i--) {
            answers[i] = matrix[i][matrix_size];
            for (int j = i + 1; j < matrix_size; j++) {
                answers[i] -= matrix[i][j] * answers[j];
            }
            answers[i] /= matrix[i][i];
        }
    }
}

int main() {

    cout << "Initial matrix " << endl;
    printMatrix();
    cout << endl;

    cout << "Matrix choice element" << endl;
    printMatrix();
    cout << endl;
    gaussLeadEl();
    printMatrix();
    for (int i = 0; i < matrix_size; i++) {
        cout << "x" << i + 1 << "=" << fixed << setprecision(1) << answers[i] << endl; 
    }

    return 0;
}


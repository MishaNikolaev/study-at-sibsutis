#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int size = 3;
double answers[size];

double matrix[size][size + 1] = {
    {2, -1, 3, 5},
    {-1, 2, 1, 4},
    {3, 0, 1, 2}
};

void printMatrix() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size + 1; j++) {
            cout << setw(10) << setprecision(6) << matrix[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;
}

void chooseLeadingElement(int leadingRow) {
    int maxRow = leadingRow; 
    double maxElement = fabs(matrix[leadingRow][leadingRow]); 

    for (int i = leadingRow + 1; i < size; i++) {
        if (fabs(matrix[i][leadingRow]) > maxElement) {
            maxElement = fabs(matrix[i][leadingRow]);
            maxRow = i;
        }
    }

    if (maxRow != leadingRow) {
        for (int j = 0; j <= size; j++) { 
            double temp = matrix[leadingRow][j];
            matrix[leadingRow][j] = matrix[maxRow][j];
            matrix[maxRow][j] = temp;
        }
    }
}

void gauss() {
    
    cout << "Matrix after choosing leading element:" << endl;
    printMatrix();
	for(int j = 0; j < size - 1; j++) {
		chooseLeadingElement(j);
	    for (int i = j + 1; i < size; i++) {
	        double coef = matrix[i][j] / matrix[j][j]; 
	        for (int k = j; k <= size; k++) {
	            matrix[i][k] -= coef * matrix[j][k];
	        }
		}
    }

    cout << "Matrix in triangular form:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size + 1; j++) {
            if (fabs(matrix[i][j]) < 1e-6) {
                matrix[i][j] = 0.0;
            }
        }
    }
    printMatrix();

    for (int i = size - 1; i >= 0; i--) {
        answers[i] = matrix[i][size];
        for (int j = i + 1; j < size; j++) {
            answers[i] -= matrix[i][j] * answers[j];
        }
        answers[i] /= matrix[i][i]; 
    }
}

int main() {
    cout << "Initial Matrix:" << endl;
    printMatrix();

    gauss();

    cout << "Solutions:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "x[" << i << "] = " << fixed << setprecision(6) << answers[i] << endl;
    }

    return 0;
}


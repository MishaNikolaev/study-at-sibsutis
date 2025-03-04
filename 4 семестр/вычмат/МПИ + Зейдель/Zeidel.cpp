#include <iostream>
#include <cmath>

using namespace std;

const int matrix_size = 3;
const double Epsilon = 1e-6;

float matrix[matrix_size][matrix_size + 1] = {
        {5, -1, 1, 9},
        {4, 10, -1, 18},
        {2, -3, -10, 1}
};

float A[matrix_size][matrix_size] = {};
float B[matrix_size] = {};
float C[matrix_size][matrix_size] = {};
float E[matrix_size][matrix_size] = {};
float x[matrix_size] = {};

void printMatrix(const float matrix[][matrix_size + 1]) {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            printf(" %6.2f ", matrix[i][j]);
        }
        printf(" | %6.2f \n", matrix[i][matrix_size]);
    }
    cout << endl;
}

void printMatrix(const float matrix[][matrix_size]) {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            printf(" %6.2f ", matrix[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

void printVector(const float vector[], int size) {
	cout << "\n";
    for (int i = 0; i < size; i++) {
        printf(" %6.2f \n", vector[i]);
    }
    cout << endl;
}

void divideMatrix() {
    for (int i = 0; i < matrix_size; i++) {
        float diagonalElement = matrix[i][i];
        for (int j = 0; j < matrix_size + 1; j++) {
            matrix[i][j] = matrix[i][j] / diagonalElement;
        }
    }
}

void getMatrixAB() {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            A[i][j] = matrix[i][j];
        }
    }

    for (int k = 0; k < matrix_size; k++) {
        B[k] = matrix[k][matrix_size];
    }
}

double maxB(const float odnomer[], int size) {
    double maxVal = fabs(odnomer[0]);
    for (int i = 1; i < size; i++) {
        if (fabs(odnomer[i]) > maxVal) {
            maxVal = fabs(odnomer[i]);
        }
    }
    return maxVal;
}

double maxC(const float matrix[][matrix_size], int size) {
    double maxVal = 0;
    for (int i = 0; i < size; i++) {
        double rowSum = 0;
        for (int j = 0; j < size; j++) {
            rowSum += fabs(matrix[i][j]);
        }
        if (rowSum > maxVal) {
            maxVal = rowSum;
        }
    }
    return maxVal;
}


void matrixE() {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            if (i == j) {
                E[i][j] = 1;
            } else {
                E[i][j] = 0;
            }
        }
    }
}

void zeidelIterate() {
    double temp = 0;
    double Cmax = maxC(C, matrix_size);
    double Bmax = maxB(B, matrix_size);

    double N = ceil(log((Epsilon * (1 - Cmax)) / Bmax) / log(Cmax));

    cout << "Calculated number of steps: " << N-1 << endl;

    cout << "-----------------------" << endl;
    cout << "Seidel Iteration Method Results:" << endl;
    cout << "-----------------------" << endl;

    for (int i = 0; i < matrix_size; i++) {
        x[i] = 0;
    }

    cout << "Initial vector x:" << endl;
    printVector(x, matrix_size);

    int steps = min(static_cast<int>(N), 3); 

    for (int j = 0; j < steps; j++) {
        cout << "Step " << j + 1 << ":" << endl;
        
        for (int i = 0; i < matrix_size; i++) {
            temp = 0;

            cout << "x before update (step " << j + 1 << "): ";
            printVector(x, matrix_size);

            for (int k = 0; k < i; k++) {
                temp += C[i][k] * x[k];
            }
            for (int k = i + 1; k < matrix_size; k++) {
                temp += C[i][k] * x[k];
            }

            x[i] = B[i] - temp;

            cout << "Updated x[" << i + 1 << "] = " << x[i] << endl;
        }
        

        cout << "Resulting vector after step " << j + 1 << ":" << endl;
        printVector(x, matrix_size);
    }
}


int main() {
    setlocale(LC_ALL, "RUS");

    cout << "Initial matrix:" << endl;
    printMatrix(matrix);

    divideMatrix();

    cout << "matrix after delenie:" << endl;
    printMatrix(matrix);

    getMatrixAB();

    cout << "Matrix A:" << endl;
    printMatrix(A);

    cout << "Matrix B:" << endl;
    printVector(B, matrix_size);

    cout << "Matrix E:" << endl;
    matrixE();
    printMatrix(E);

    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            C[i][j] = A[i][j] - E[i][j];
        }
    }

    cout << "Matrix C (A - E):" << endl;
    printMatrix(C);

    zeidelIterate();

    cout << "Answers:" << endl;
    printVector(x, matrix_size);

    return 0;
}

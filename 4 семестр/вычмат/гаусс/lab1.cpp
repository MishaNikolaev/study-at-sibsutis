#include <iostream>

using namespace std;

const int size = 3;
float answers[size];

float matrix[size][size + 1] = {
    {2, -1, 3, 5},
    {-1, 2, 1, 4},
    {3, 0, 1, 2}
};

void printMatrix() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size + 1; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void gauss() {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            float coef = matrix[j][i] / matrix[i][i];
            for (int k = i; k <= size; k++) {
                matrix[j][k] -= coef * matrix[i][k];
            }
        }
        for(int i = size - 1; i>=0; i--){
        	answers[i] = matrix[i][size];
        	//for(int j + 1; j<si)
        	for(int j = i +1; j<size; j++){
        		answers[i] -= matrix[i][j] * answers[j];
			}
			answers[i] /= matrix[i][i];
		}
    }
}

int main() {
    cout << "Matrix:" << endl;
    printMatrix();
    gauss();
    cout << "Matrix after priamoi hod:" << endl;
    printMatrix();
    cout << "Answers:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "x[" << i << "] = " << answers[i] << endl;
    }
	
    return 0;
}



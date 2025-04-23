#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double epsilon = 1e-8;
const int size = 2;

double x = 2.0, y = 1.0; 
double f[size];           
double W[size][size];     
double W_obr[size][size]; 
double Vector[size];    
double opredelitel;   

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

void obrMatrix() {
    opredelitel = W[0][0] * W[1][1] - W[0][1] * W[1][0];

    W_obr[0][0] = W[1][1] / opredelitel;
    W_obr[0][1] = -W[0][1] / opredelitel;
    W_obr[1][0] = -W[1][0] / opredelitel;
    W_obr[1][1] = W[0][0] / opredelitel;
}

void computeVectorX() {
    Vector[0] = W_obr[0][0] * f[0] + W_obr[0][1] * f[1];
    Vector[1] = W_obr[1][0] * f[0] + W_obr[1][1] * f[1];
}

int main() {
    cout << fixed << setprecision(6);

    while (true) {
        F();         
        Wmatrix();   
        obrMatrix(); 
        computeVectorX();  

        cout << "F(x,y) = [" << f[0] << ", " << f[1] << "]" << endl;
         cout << "opredelitel W = " << opredelitel << endl;

        if (fabs(f[0]) < epsilon && fabs(f[1]) < epsilon) {
            cout << "Find: x = " << x << ", y = " << y << endl;
            break;
        }

        x -= Vector[0];
        y -= Vector[1];

        cout << "epsilon: x = " << x << ", y = " << y << endl << endl;
    }

    return 0;
}


#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double epsilon = pow(10, -12);
    
double* compute_y(int n, double* x) {
    double* y = new double[n];
    for (int i = 0; i < n; i++)  
    {
        y[i] = 1 / x[i];
    }
    return y;
}

void printTable(int n, double* x, double* y) {
    cout << "\tX\t\tY";
    cout << "\n-----------------------------------\n";
    for (int i = 0; i < n; i++)  
    {
        cout << "\t" << x[i] << "\t|";
        cout << "   " << y[i] << endl;
        cout << "-----------------------------------\n";
    }
}

double trapecia(int n, double* x, double* y) {
    double result = 0;
    for (int i = 0; i < n - 1; i++) { 
        double chasticnya_sum = (x[i + 1] - x[i]) * (y[i] + y[i + 1]) * 0.5; 
        result += chasticnya_sum;
    }
    cout << "\nresult = " << result << endl;
    return result;
}


double simpson(int n, double* x, double* y) {
    if ((n-1) % 2 != 0) {
        cout << "intervals should be chetnimi" << endl;
        return -1;
    }
    
    double result = 0;
    for (int i = 0; i < n - 1; i += 2) {
        double h = x[i+1] - x[i];
        double chasticnya_sum = h/3 * (y[i] + 4*y[i+1] + y[i+2]);
        result += chasticnya_sum;
    }
    cout << "\nresult = " << result << endl;
    return result;
}



int main() {
    setlocale(LC_ALL, "ru");
    double a, b, h;

    cout << "Enter a (lower limit): "; cin >> a;
    cout << "Enter b (upper limit: "; cin >> b;
    cout << "Enter h: "; cin >> h;

    int n = (b - a) / h + 1;
    cout << "n = " << n << endl;

    double* x = new double[n];
    x[0] = a;
    for (int i = 1; i < n; i++) {
        x[i] = x[i - 1] + h;
    }

    double* y = compute_y(n, x);
    //printTable(n, x, y);

    cout << "\n\n---------------------- Trapecia ----------------------\n";
    double prevResult = 0;
    double result = trapecia(n, x, y);

    double newH = h;
    int iteration = 1;
    while (true) {
        newH /= 2;
        int newN = (b - a) / newH + 1;
        if (newN <= 1) break;

        double* newX = new double[newN];
        newX[0] = a;
        for (int i = 1; i < newN; i++) {
            newX[i] = newX[i - 1] + newH;
        }

        double* newY = compute_y(newN, newX);
        prevResult = result;
        cout << "\nFor h = " << newH;
        result = trapecia(newN, newX, newY);

        delete[] newX;
        delete[] newY;

        if (abs(result - prevResult) < epsilon) {
            cout << "\n\nTochnost dostignyta at h = " << newH << " (iteration " << iteration << ")" << endl;
            cout << "Final result: " << result << endl;
            break;
        }
        iteration++;
    }

    cout << "\n\n---------------------- Simpson ----------------------\n";
    double simpsonResult = simpson(n, x, y);
    newH = h;
    iteration = 1;
    while (true) {
        newH /= 2;
        int newN = (b - a) / newH + 1;
        if (newN <= 1) break;

        double* newX = new double[newN];
        newX[0] = a;
        for (int i = 1; i < newN; i++) {
            newX[i] = newX[i - 1] + newH;
        }

        double* newY = compute_y(newN, newX);
        prevResult = simpsonResult;
        cout << "\nFor h = " << newH;
        simpsonResult = simpson(newN, newX, newY);

        delete[] newX;
        delete[] newY;

        if (abs(simpsonResult - prevResult) < epsilon) {
            cout << "\n\nTochnost dostignyta at h = " << newH << " (iteration " << iteration << ")" << endl;
            cout << "Final result: " << simpsonResult << "\n\n\n\n";
            break;
        }
        iteration++;
    }

    delete[] x;
    delete[] y;

    return 0;
}

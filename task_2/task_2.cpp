#define _USE_MATH_DEFINES 
#include <iostream>
#include <cmath>
#include <Windows.h>

using namespace std;

double calculateAverage(double arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

double calculateStandardDeviation(double arr[], int n, double x_cp) {
    double sum_squares = 0;
    for (int i = 0; i < n; i++) {
        sum_squares += pow(arr[i], 2);
    }

    double term1 = (1.0 / (n - 1)) * sum_squares;
    double term2 = (double(n) / (n - 1)) * pow(x_cp, 2);

    return sqrt(term1 - term2);
}

double calculateY(double x, double x_cp, double sigma, int n) {
    double exponent = -pow(x - x_cp, 2) / (2 * pow(sigma, 2));
    double coefficient = 1.0 / (sigma * sqrt(M_PI * n));
    double correctionFactor = 1.0 + 1.0 / (12 * n);

    return coefficient * exp(exponent) * correctionFactor;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    const int n = 10;
    double X[n] = { 22.0, 21.0, 10.0, 19.0, 22.0, 13.0, 21.0, 18.0, 14.0, 25.0 };

    cout << "Вхідні дані:" << endl;
    cout << "{ ";
    for (int i = 0; i < n; i++) {
        cout << X[i] << (i < n - 1 ? ", " : " }\n");
    }
    cout << endl;

    double x_cp = calculateAverage(X, n);
    cout << "Середнє значення = " << x_cp << endl;

    double sigma = calculateStandardDeviation(X, n, x_cp);
    cout << "Середньо-квадратичне відхилення = " << sigma << endl;

    cout << "\nРезультати розрахунку y для кожного x:" << endl;
    for (int i = 0; i < n; i++) {
        double y = calculateY(X[i], x_cp, sigma, n);
        cout << "y(" << X[i] << ") = " << y << endl;
    }

    return 0;
}
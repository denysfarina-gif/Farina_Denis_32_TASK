#include <iostream>
#include <vector>
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

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    const int n = 10;
    double X[n] = { 20, 11, 10, 19, 22, 23, 11, 18, 14, 25 };

    double x_cp = calculateAverage(X, n);
    double y = calculateStandardDeviation(X, n, x_cp);

    cout << "Результати експерименту:" << endl;
    cout << "Середнє значення (x_cp) = " << x_cp << endl;
    cout << "Середньо-квадратичне відхилення (y) = " << y << endl;

    return 0;
}
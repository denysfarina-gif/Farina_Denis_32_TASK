#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double calculateAverage(double arr[], int n);
double calculateStdDev(double arr[], int n, double avg);

int main() {
    const int n = 10;
    double X[n] = { 20, 11, 10, 19, 22, 23, 11, 18, 14, 25 };

    double x_cp = calculateAverage(X, n);
    double y = calculateStdDev(X, n, x_cp);

    cout << fixed << setprecision(2);
    cout << "Середне значення (x_cp): " << x_cp << endl;
    cout << "Середньо-квадратичне відхилення (y): " << y << endl;

    return 0;
}

double calculateAverage(double arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

double calculateStdDev(double arr[], int n, double avg) {
    double sumOfSquares = 0;
    for (int i = 0; i < n; i++) {
        sumOfSquares += pow(arr[i], 2);
    }

    double part1 = (1.0 / (n - 1)) * sumOfSquares;
    double part2 = (static_cast<double>(n) / (n - 1)) * pow(avg, 2);

    return sqrt(part1 - part2);
}
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <Windows.h>
using namespace std;

int** createMatrix(int n);
void fillMatrix(int** matrix, int n, int v);
void printMatrix(int** matrix, int n);
int findMaxAbs(int** matrix, int n);
void processSectors(int** matrix, int n, int maxAbs);
void freeMemory(int** matrix, int n);

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    srand(static_cast<unsigned int>(time(0)));
    int n;
    int variant = 33; 

    cout << "Введіть розмір квадратної матриці n: ";
    cin >> n;

    if (n <= 0) {
        cout << "Помилка! Розмір має бути більшим за нуль." << endl;
        return 1;
    }

    int** matrix = createMatrix(n);

    fillMatrix(matrix, n, variant);

    cout << "\nЗгенерована матриця:" << endl;
    printMatrix(matrix, n);

    int maxAbs = findMaxAbs(matrix, n);
    cout << "\nМаксимальне значення за модулем у всій матриці: " << maxAbs << endl;

    processSectors(matrix, n, maxAbs);

    cout << "\nМатриця після заміни елементів у 7 секторі:" << endl;
    printMatrix(matrix, n);

    freeMemory(matrix, n);

    return 0;
}

int** createMatrix(int n) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    return matrix;
}

void fillMatrix(int** matrix, int n, int v) {
    int limit = 10 + v; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % (2 * limit + 1) - limit;
        }
    }
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int findMaxAbs(int** matrix, int n) {
    int maxAbs = abs(matrix[0][0]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(matrix[i][j]) > maxAbs) {
                maxAbs = abs(matrix[i][j]);
            }
        }
    }
    return maxAbs;
}

void processSectors(int** matrix, int n, int maxAbs) {
    int evenCountS4 = 0;
    int elementsInS7 = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= n / 2 && j >= n / 2 && i < j) {
                if (matrix[i][j] % 2 == 0) {
                    evenCountS4++;
                }
            }
            if (i >= n / 2 && j < n / 2 && (i + j) < (n - 1)) {
                elementsInS7++;
                matrix[i][j] = maxAbs; 
            }
        }
    }

    cout << "Знайдено парних чисел у 4 секторі: " << evenCountS4 << endl;
    cout << "Замінено елементів у 7 секторі: " << elementsInS7 << endl;
}

void freeMemory(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
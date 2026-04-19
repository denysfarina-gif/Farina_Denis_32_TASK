#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <windows.h>

using namespace std;

void findFirstInSector3(int** matrix, int n, int k) {
    bool found = false;
    cout << "\n1. Пошук у секторі 3 (правий трикутник + головна діагональ):" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j >= i && j > n - 1 - i) {
                if (matrix[i][j] % k == 0) {
                    cout << "Перший елемент, що ділиться на " << k << ": " << matrix[i][j];
                    cout << " (знаходиться в рядку " << i << ", стовпці " << j << ")" << endl;
                    found = true;
                    return; 
                }
            }
        }
    }
    if (!found) {
        cout << "Елементів, що діляться на " << k << " без остачі, не знайдено." << endl;
    }
}

void processSector8(int** matrix, int n, int minAbsValue) {
    int count = 0;
    cout << "\n2. Робота у секторі 8 (нижче побічної діагоналі):" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j > n - 1) {
                count++;
                matrix[i][j] = minAbsValue;
            }
        }
    }
    cout << "Кількість елементів у секторі 8: " << count << endl;
    cout << "Всі вони були замінені на мінімальне за модулем значення: " << minAbsValue << endl;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n, k, variant = 32;
    cout << "Введіть розмірність матриці n: ";
    cin >> n;
    cout << "Введіть число k для перевірки подільності: ";
    cin >> k;

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    int minAbs = 1000; 
    int minValWithMinAbs = 0; 

    int rangeMin = -10 - variant;
    int rangeMax = 10 + variant;  

    cout << "\nПочаткова матриця (діапазон від " << rangeMin << " до " << rangeMax << "):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % (rangeMax - rangeMin + 1) + rangeMin;
            cout << setw(5) << matrix[i][j];

            if (abs(matrix[i][j]) < minAbs) {
                minAbs = abs(matrix[i][j]);
                minValWithMinAbs = matrix[i][j];
            }
        }
        cout << endl;
    }

    findFirstInSector3(matrix, n, k);
    processSector8(matrix, n, minValWithMinAbs);

    cout << "\nМатриця після змін у секторі 8:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
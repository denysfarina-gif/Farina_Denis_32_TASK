#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <future>
#include <random>
#include <iomanip>
#include <string>
#include <windows.h> 

using namespace std;
using namespace std::chrono;

void printArray(const vector<int>& arr) {
    if (arr.size() <= 10) {
        for (size_t i = 0; i < arr.size(); ++i) {
            cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
        }
    }
    else {
        for (int i = 0; i < 5; ++i) cout << arr[i] << ", ";
        cout << "... [пропущено елементів: " << (arr.size() - 10) << "] ...";
        for (size_t i = arr.size() - 5; i < arr.size(); ++i) cout << ", " << arr[i];
    }
    cout << endl;
}

vector<int> generateArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 120000);
    for (int& x : arr) x = dis(gen);
    return arr;
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[minIdx], arr[i]);
    }
}

void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++; j--;
        }
    }
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

int binarySearch(const vector<int>& arr, int target) {
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == target) return m;
        if (arr[m] < target) l = m + 1; else r = m - 1;
    }
    return -1;
}

template<typename Func>
long long measureTime(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto stop = high_resolution_clock::now();
    return duration_cast<milliseconds>(stop - start).count();
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    vector<int> sizes = { 10, 100, 1000, 8000, 50000, 150000 };
    const int runsCount = 5;

    for (int n : sizes) {
        cout << " РОБОТА З МАСИВОМ РОЗМІРОМ n = " << n << endl;

        vector<int> originalArray = generateArray(n);
        cout << "Початковий масив:" << endl;
        printArray(originalArray);

        double avgBubbleSync = 0, avgBubbleAsync = 0;
        for (int i = 0; i < runsCount; ++i) {
            vector<int> t1 = originalArray, t2 = originalArray;
            avgBubbleSync += measureTime([&]() { bubbleSort(t1); });
            avgBubbleAsync += measureTime([&]() {
                auto f = async(launch::async, [&]() { bubbleSort(t2); });
                f.get();
                });
        }
        cout << "Бульбашка (середнє): Синхронно = " << fixed << setprecision(2) << (avgBubbleSync / runsCount) << " мс | Асинхронно = " << (avgBubbleAsync / runsCount) << " мс" << endl;

        double avgSelectSync = 0, avgSelectAsync = 0;
        for (int i = 0; i < runsCount; ++i) {
            vector<int> t1 = originalArray, t2 = originalArray;
            avgSelectSync += measureTime([&]() { selectionSort(t1); });
            avgSelectAsync += measureTime([&]() {
                auto f = async(launch::async, [&]() { selectionSort(t2); });
                f.get();
                });
        }
        cout << "Вибором   (середнє): Синхронно = " << (avgSelectSync / runsCount) << " мс | Асинхронно = " << (avgSelectAsync / runsCount) << " мс" << endl;

        double avgQuickSync = 0, avgQuickAsync = 0;
        vector<int> lastSorted;
        for (int i = 0; i < runsCount; ++i) {
            vector<int> t1 = originalArray, t2 = originalArray;
            avgQuickSync += measureTime([&]() { quickSort(t1, 0, n - 1); });
            avgQuickAsync += measureTime([&]() {
                auto f = async(launch::async, [&]() { quickSort(t2, 0, n - 1); });
                f.get();
                });
            lastSorted = t2;
        }
        cout << "QuickSort (середнє): Синхронно = " << (avgQuickSync / runsCount) << " мс | Асинхронно = " << (avgQuickAsync / runsCount) << " мс" << endl;

        cout << "\nРезультат після QuickSort:" << endl;
        printArray(lastSorted);

        if (n == sizes[0]) {
            cout << "\n= Бінарний пошук =" << endl;
            cout << "Введіть число: ";
            int target;
            if (cin >> target) {
                int idx = binarySearch(lastSorted, target);
                if (idx != -1) cout << "Знайдено на індексі: " << idx << endl;
                else cout << "Не знайдено!" << endl;
            }
        }
        cout << "\nНатисніть Enter" << endl;
        cin.ignore(); cin.get();
    }
    return 0;
}
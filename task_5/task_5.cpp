#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Country {
    string name;
    string area;
    string population;
    string gdp;
    string governmentForm;
};
void out(string s, int width) {
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        if ((unsigned char)s[i] < 128 || (unsigned char)s[i] >= 192) {
            count++;
        }
    }
    cout << s;
    for (int i = 0; i < (width - count); i++) {
        cout << " ";
    }
}

string cleanString(string str) {
    while (!str.empty() && (isspace((unsigned char)str.back()) || str.back() == '\r' || str.back() == '\n')) {
        str.pop_back();
    }
    while (!str.empty() && isspace((unsigned char)str.front())) {
        str.erase(0, 1);
    }
    return str;
}

void printHeader() {
    cout << "\n";
    out("Назва", 20);
    out("Площа", 15);
    out("Населення", 20);
    out("ВВП", 15);
    cout << "Форма влади" << endl;
    cout << string(85, '-') << endl;
}

void printCountry(const Country& c) {
    out(c.name, 20);
    out(c.area, 15);
    out(c.population, 20);
    out(c.gdp, 15);
    cout << c.governmentForm << endl;
}


void addCountryToFile(string filename) {
    Country c;
    cout << "\nВведення даних про нову країну\n";
    cin.ignore(MAXSHORT, '\n');

    cout << "Назва країни: ";
    getline(cin, c.name);
    cout << "Площа: ";
    getline(cin, c.area);
    cout << "Населення: ";
    getline(cin, c.population);
    cout << "ВВП ($): ";
    getline(cin, c.gdp);
    cout << "Форма влади (напр. democracy): ";
    getline(cin, c.governmentForm);

    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        outFile << c.name << "|" << c.area << "|" << c.population << "|" << c.gdp << "|" << c.governmentForm << endl;
        outFile.close();
        cout << "Країну успішно додано до бази!\n";
    }
}

void viewAllCountries(string filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Файл поки що порожній.\n";
        return;
    }

    printHeader();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        Country c;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);

        if (p1 != string::npos && p2 != string::npos && p3 != string::npos && p4 != string::npos) {
            c.name = line.substr(0, p1);
            c.area = line.substr(p1 + 1, p2 - p1 - 1);
            c.population = line.substr(p2 + 1, p3 - p2 - 1);
            c.gdp = line.substr(p3 + 1, p4 - p3 - 1);
            c.governmentForm = cleanString(line.substr(p4 + 1));
            printCountry(c);
        }
    }
    inFile.close();
}

void showDemocraticCountries(string filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) return;

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        size_t p4 = line.rfind('|');
        if (p4 == string::npos) continue;

        string gov = cleanString(line.substr(p4 + 1));

        if (gov.find("Democracy") != string::npos || gov.find("democracy") != string::npos) {
            if (!found) {
                cout << "\nТільки демократичні країни\n";
                printHeader();
            }

            Country c;
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);

            c.name = line.substr(0, p1);
            c.area = line.substr(p1 + 1, p2 - p1 - 1);
            c.population = line.substr(p2 + 1, p3 - p2 - 1);
            c.gdp = line.substr(p3 + 1, p4 - p3 - 1);
            c.governmentForm = gov;

            printCountry(c);
            found = true;
        }
    }
    if (!found) cout << "\nДемократичних країн не знайдено.\n";
    inFile.close();
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    string filename = "countries.txt";
    int choice;

    do {
        cout << "1. Додати нову країну\n";
        cout << "2. Показати весь список\n";
        cout << "3. Знайти демократичні країни\n";
        cout << "0. Вийти\n";
        cout << "Твій вибір: ";
        cin >> choice;

        if (choice == 1) addCountryToFile(filename);
        else if (choice == 2) viewAllCountries(filename);
        else if (choice == 3) showDemocraticCountries(filename);

    } while (choice != 0);

    return 0;
}
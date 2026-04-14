#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>

using namespace std;

struct Planet {
    string name;
    double size;
    bool isHabitable;
    double orbitDuration;
    string starName;
};

void addPlanet();
void showAllPlanets();
void showHabitablePlanets();

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;
    while (true) {
        cout << "\nМеню програми:" << endl;
        cout << "1. Додати нову планету в базу" << endl;
        cout << "2. Вивести список усіх планет" << endl;
        cout << "3. Показати тільки придатні для життя" << endl;
        cout << "4. Вийти" << endl;
        cout << "Твій вибір: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 4) break;

        switch (choice) {
        case 1: addPlanet(); break;
        case 2: showAllPlanets(); break;
        case 3: showHabitablePlanets(); break;
        default: cout << "Немає такого пункту!" << endl;
        }
    }
    return 0;
}

void addPlanet() {
    Planet p;
    string habitableInput;

    cout << "Назва планети: ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Розмір (діаметр у км): ";
    cin >> p.size;

    cout << "Придатна для життя? (так/ні): ";
    cin >> habitableInput;
    p.isHabitable = (habitableInput == "так" || habitableInput == "Так" || habitableInput == "yes" || habitableInput == "y");
    cout << "Оберт навколо зорі (днів): ";
    cin >> p.orbitDuration;

    cout << "Назва зорі: ";
    cin.ignore();
    getline(cin, p.starName);

    ofstream fout("planets.txt", ios::app);
    if (fout.is_open()) {
        fout << p.name << "|" << p.size << "|" << (p.isHabitable ? "1" : "0") << "|"
            << p.orbitDuration << "|" << p.starName << endl;
        fout.close();
        cout << "Все збережено у файл!" << endl;
    }
}

void showAllPlanets() {
    ifstream fin("planets.txt");
    if (!fin.is_open()) {
        cout << "Файл ще не створено або він порожній." << endl;
        return;
    }

    string line;
    cout << "\nУсі планети в базі:" << endl;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string n, s, h, o, st;

        getline(ss, n, '|');
        getline(ss, s, '|');
        getline(ss, h, '|');
        getline(ss, o, '|');
        getline(ss, st, '|');

        cout << "* " << n << " (Зоря: " << st << ", Життя: " << (h == "1" ? "Є" : "Немає") << ")" << endl;
    }
    fin.close();
}

void showHabitablePlanets() {
    ifstream fin("planets.txt");
    if (!fin.is_open()) {
        cout << "Файл не знайдено." << endl;
        return;
    }

    string line;
    bool found = false;
    cout << "\nСписок придатних для життя планет:" << endl;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string n, s, h, o, st;

        getline(ss, n, '|');
        getline(ss, s, '|');
        getline(ss, h, '|');
        getline(ss, o, '|');
        getline(ss, st, '|');

        if (h == "1") {
            cout << "-> " << n << " біля зорі " << st << " (Орбіта: " << o << " дн.)" << endl;
            found = true;
        }
    }

    if (!found) cout << "На жаль, придатних планет поки немає." << endl;
    fin.close();
}
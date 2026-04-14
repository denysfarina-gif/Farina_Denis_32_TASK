#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct SentenceInfo {
    string text;
    int words;
};

int countWordsInSentence(const string& s) {
    stringstream ss(s);
    string word;
    int count = 0;
    while (ss >> word) {
        count++;
    }
    return count;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cout << "Помилка: не вдалося знайти файл input.txt" << endl;
        return 1;
    }

    vector<SentenceInfo> list;
    string line;

    while (getline(fin, line)) {
        if (!line.empty()) {
            SentenceInfo si;
            si.text = line;
            si.words = countWordsInSentence(line);
            list.push_back(si);
        }
    }
    fin.close();

    sort(list.begin(), list.end(), [](const SentenceInfo& a, const SentenceInfo& b) {
        return a.words > b.words;
        });

    ofstream fout("output.txt");
    if (!fout.is_open()) {
        cout << "Помилка: не вдалося створити файл output.txt" << endl;
        return 1;
    }

    for (const auto& s : list) {
        fout << s.text << endl;
    }
    fout.close();

    cout << "Успішно! Речення відсортовані та записані в output.txt" << endl;

    return 0;
}
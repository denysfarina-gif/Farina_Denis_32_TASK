#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Файл input.txt не знайдено!" << endl;
        return 1;
    }

    vector<string> allWords;
    string word;
    map<string, int> charFreq;

    while (inputFile >> word) {
        if (!word.empty() && (word.back() == '.' || word.back() == ',')) {
            word.pop_back();
        }
        allWords.push_back(word);

        for (int i = 0; i < word.length(); ) {
            string symbol;
            unsigned char c = (unsigned char)word[i];

            if (c >= 128) {
                symbol = word.substr(i, 2);
                i += 2;
            }
            else {
                symbol = word.substr(i, 1);
                i += 1;
            }
            charFreq[symbol]++;
        }
    }
    inputFile.close();

    if (charFreq.empty()) {
        cout << "Файл порожній!" << endl;
        return 0;
    }

    string rarestSymbol;
    int minCount = -1;

    for (auto const& [sym, count] : charFreq) {
        if (minCount == -1 || count < minCount) {
            minCount = count;
            rarestSymbol = sym;
        }
    }

    string targetWord;
    for (const string& w : allWords) {
        if (w.find(rarestSymbol) != string::npos) {
            targetWord = w;
            break;
        }
    }

    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        outputFile << (unsigned char)0xEF << (unsigned char)0xBB << (unsigned char)0xBF;

        outputFile << "Символ, що зустрічається найрідше: '" << rarestSymbol << "'" << endl;
        outputFile << "Кількість повторень: " << minCount << endl;
        outputFile << "Слово з цим символом: " << targetWord << endl;

        outputFile.close();
        cout << "Готово! Перевір файл output.txt" << endl;
    }

    return 0;
}
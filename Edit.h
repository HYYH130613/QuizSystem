//U2410237 Soy Yeakaterina
#ifndef EDIT_H
#define EDIT_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // для remove и rename
using namespace std;

const int LINE_SIZE = 100;
const int LINES_PER_QUESTION = 6;

class Edit {
public:
    void editQuiz(const string& filename) {
        int questionNum;
        char partChoice;
        string newText;

        // Запрос номера вопроса
        cout << "Which question would you like to change? (number): ";
        cin >> questionNum;
        cin.ignore();

        int baseLine = 2 + (questionNum - 1) * LINES_PER_QUESTION;

        // Чтение и вывод нужного вопроса
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Failed to open file for reading.\n";
            return;
        }

        string line;
        int lineIndex = 0;
        int printStart = baseLine;

        cout << "\nCurrent Question No." << questionNum << ":\n";
        while (getline(inFile, line)) {
            if (lineIndex >= printStart && lineIndex < printStart + LINES_PER_QUESTION)
                cout << line << endl;
            ++lineIndex;
        }
        inFile.close();

        // Запрос выбора части для редактирования
        cout << "\nWhat do you want to change?\n> q - Question\n> a - a)\n> b - b)\n> c - c)\n> d - d)\n> r - Correct answer\n> x - back to main menu\n> ";
        cin >> partChoice;
        cin.ignore();

        int offset = -1;
        switch (partChoice) {
            case 'q': offset = 0; break;
            case 'a': offset = 1; break;
            case 'b': offset = 2; break;
            case 'c': offset = 3; break;
            case 'd': offset = 4; break;
            case 'r': offset = 5; break;
            case 'x':
                cout << "\n";
                return;
                break;
            default:
                cout << "Wrong choice.\n";
                return;
        }

        cout << "Enter new text: ";
        getline(cin, newText);
        if (newText.length() > LINE_SIZE)
            newText = newText.substr(0, LINE_SIZE);

        // Создание временного файла
        ifstream original(filename);
        ofstream temp("temp.txt");
        if (!original || !temp) {
            cout << "Error opening files.\n";
            return;
        }

        lineIndex = 0;
        int targetLine = baseLine + offset;
        while (getline(original, line)) {
            // Если мы находим строку для редактирования, добавляем метку и выравниваем
            if (lineIndex == targetLine) {
                string label;
                if (partChoice == 'a') label = "  a) ";
                else if (partChoice == 'b') label = "  b) ";
                else if (partChoice == 'c') label = "  c) ";
                else if (partChoice == 'd') label = "  d) ";
                else if (partChoice == 'r') label = "Correct answer: ";

                // Ручное добавление пробелов для выравнивания
                while (newText.length() + label.length() < LINE_SIZE) {
                    newText += " ";  // Добавляем пробелы, пока строка не станет нужной длины
                }

                // Записываем строку в файл
                temp << label << newText << '\n';
            }
            else {
                temp << line << '\n';
            }
            ++lineIndex;
        }


        original.close();
        temp.close();

        // Удаление старого и переименование
        if (remove(filename.c_str()) != 0) {
            cout << "Failed to delete original file.\n";
            return;
        }
        if (rename("temp.txt", filename.c_str()) != 0) {
            cout << "Failed to rename temp file.\n";
            return;
        }

        cout << "\nData updated successfully.\n";
    }
};

#endif

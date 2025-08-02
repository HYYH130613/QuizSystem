//u2410234 Sofina Adelina
#ifndef DELETE_H
#define DELETE_H

#include <iostream>
#include <fstream>
#include <string>
#include "Quiz.h"

using namespace std;

Quiz quiz;

//process of deleting one quiz
class Delete {
public:

    static void deleteQuiz(const string& quizName) {
        string filename = quizName + ".txt";
        //check if we have this quiz
        ifstream testFile(filename);
        if (!testFile) {
            cout << "\n------------------------\n";
            cout << "Quiz not found!\n";
            return;
        }
        testFile.close();
        //ask if the user really wants to delete the quiz
        cout << "\n------------------------\n";
        cout << "Are you sure you want to delete '" << quizName << "'? (y/n): ";
        char confirm;
        cin >> confirm;
        cin.ignore();

        if (tolower(confirm) != 'y') {
            cout << "\n------------------------\n";
            cout << "Deletion cancelled.\n";
            return;
        }

        if (remove(filename.c_str()) != 0) {
            cout << "\n------------------------\n";
            cerr << "Error deleting quiz file\n";
        } else {
            cout << "\n------------------------\n";
            cout << "Quiz deleted successfully\n";
            quiz.deletedFromQuizzes(quizName);
            //-1 from quiz counter
            Quiz::decrementTotalQuizzes();
        }
    }
};

#endif
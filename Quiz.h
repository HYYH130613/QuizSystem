//U2410234 Sofina Adelina
#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <fstream>
#include <string>
#include "Create.h"

using namespace std;

//collecting everything into the one quiz
class Quiz{
protected:
    static int totalQuizzes;
    static int activeQuizzes;
    int quizId;
    string quizName;
    Create create;

  public:
    //memory capacity
    static const int MAX_QUIZZES = 100;

    //creating quiz
    Quiz() {
        quizName = "Unknown";
        if (totalQuizzes >= MAX_QUIZZES) {
            throw runtime_error("Maximum quiz capacity reached");
        }
        //add one quiz to quiz counter
        quizId = ++totalQuizzes;
        activeQuizzes++;
    }

    void addQuiz() {
        cout << "Enter your quiz name: ";
        getline(cin, quizName);

        create.getQuestionCount();
        create.createQuiz();
    }
    void saveToFile() {
        try {
            string filename = quizName + ".txt";
            ofstream file(filename);
            ofstream quizzesFile("quizzList.txt");

            if (!file.is_open())
                throw runtime_error("Cannot open file for writing.");

            file << "Quiz Name: " << quizName << "\n\n";
            quizzesFile << quizName << "\n\n";

            for (int i = 0; i < create.getTotalQuestions(); ++i) {
                file << "Q" << (i + 1) << ": ";
                file << create.getQuestion(i).display();
            }

            file.close();
            cout << "====================\n";
            cout << "Quiz saved to: " << filename << "\n";


        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    void loadFromFile(const string& filename) {
        cin.ignore();

        try {
            ifstream file;
            //file.exceptions(ifstream::failbit | ifstream::badbit);
            file.open(filename);

            string line;
            while (!file.eof()) {
                getline(file, line);
                cout << line << "\n";
            }

            file.close();

        }
        catch (const exception& e) {
            cerr << "Unexpected error: " << e.what() << endl;
        }
    }
    //create a list of names to show later what quizzes we have
    void quizzesList() {
        try {
            ifstream file("quizzList.txt");
            string line;

            if(file){
                while (!file.eof()) {
                    getline(file, line);
                    cout << line << "\n";
                }
                file.close();
            }
            else
            {
                throw invalid_argument("Sorry, there are no quizzes here yet!");
            }

        }
        catch (const ifstream::failure& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    //remove name of quiz from list if it deletes
    bool deletedFromQuizzes(const string& quizNameToDelete) {

        string tempFilename = "temp.txt";
        string quizFilename = "quizzList.txt";
        ifstream inFile(quizFilename);
        if (!inFile.is_open()) {
            return false;
        }

        ofstream tempFile(tempFilename);
        if (!tempFile.is_open()) {
            inFile.close();
            return false;
        }

        string line;
        bool found = false;
        bool firstLine = true;
        while (getline(inFile, line)) {
            if (line == quizNameToDelete) {
                found = true;
                continue;
            }
            if (!firstLine) {
                tempFile << '\n';
            }
            tempFile << line;
            firstLine = false;
        }

        inFile.close();
        tempFile.close();

        if (!found) {
            remove(tempFilename.c_str());
            return false;
        }

        if (remove(quizFilename.c_str()) != 0 || rename(tempFilename.c_str(), quizFilename.c_str()) != 0) {
            return false;
        }

        return true;
    }

    //add quiz counter in memory capacity

    static void saveTotalToFile() {
        ofstream quizzesCountFile("quizCount.dat");
        if (quizzesCountFile) {quizzesCountFile << totalQuizzes;}
    }

    static void loadTotalFromFile() {
        ifstream quizzesCountFile("quizCount.dat");
        if (quizzesCountFile) {quizzesCountFile >> totalQuizzes;}
    }

    //remove quiz counter if quiz was deleted

    static void decrementTotalQuizzes() {
        if (totalQuizzes > 0) {
            totalQuizzes--;
            saveTotalToFile();
        }
    }

    static int getTotalQuizzes() { return totalQuizzes; }
    static int getActiveQuizzes() { return activeQuizzes; }
    static int getRemainingCapacity() { return MAX_QUIZZES - totalQuizzes; }

    ~Quiz() {
        activeQuizzes--;
    }

};

int Quiz::totalQuizzes = 0;
int Quiz::activeQuizzes = 0;
#endif
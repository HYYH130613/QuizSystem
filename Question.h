//U2410244 Ten Alexandr
#ifndef QUESTION_H
#define QUESTION_H
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstring>

using namespace std;

class Question {
protected:
    string question;
    string options[2][4];
    string correctAnswer;

public:
    //Creating only one question
    Question() {
        question = "Unknown";

        string opt[4] = { "n/a", "n/a", "n/a", "n/a" };
        for (int i = 0; i < 4; ++i) {
            options[1][i] = opt[i];
        }

        options[0][0] = "a";
        options[0][1] = "b";
        options[0][2] = "c";
        options[0][3] = "d";

        correctAnswer = "Unknown";
    }

    void getQuestionData(){

        cout << "Enter Question:  ";
        getline(cin, question);

        for (int i = 0; i < 4; i++) {
            cout << "Enter Option  " << options[0][i] << ": ";
            getline(cin, options[1][i]);
        }

        cout << "Enter Correct Answer:  ";
        getline(cin, correctAnswer);
    }

    //get correct option

    string getCorrectAnswer() const {
        return correctAnswer;
    }

    //check correct option

    friend bool operator==(const Question& q, const string& s);

    bool isCorrect() {
        try {
            if (!((*this == "a") || (*this == "b") || (*this == "c") || (*this == "d"))) {
                throw invalid_argument("Error: valid answers - a, b, c, d.");
            }
            return true;
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            return false;
        }
    }

    //format of one question
    string display() const {
        string output = question + "\n";
        for (int i = 0; i < 4; ++i) {
            output += "  " + options[0][i] + ") " + options[1][i] + "\n";
        }
        output += "Correct answer: " + correctAnswer + "\n" + "\n" ;
        return output;
    }

    ~Question() = default;
};

bool operator==(const Question& q, const string& s) {
    return strcmp(q.correctAnswer.c_str(), s.c_str()) == 0;
}

#endif
// U2410238 Stepanov Dmitriy
#ifndef CREATE_H
#define CREATE_H

#include "Question.h"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

class Create {
private:
    //how many questions will be in the quiz
    int questionCount;
    //limit
    Question questions[100];

public:
    Create() {
        questionCount = 0;
    }
    //get how many questions there will be
    void getQuestionCount() {
        while (true) {
            cout << "How many questions your quiz would have (1 - 100): ";
            if (!(cin >> questionCount)) {
                cin.clear(); // clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "\nInvalid input. Please enter a numeric value.\n";
                continue;
            }

            if (questionCount <= 0 || questionCount > 100) {
                cout << "\nInvalid number of questions. Must be between 1 and 100.\n";
                continue;
            }

            cin.ignore(); // flush newline
            break; // valid input
        }
    }

    //collect questions from the class question
    void createQuiz() {
        for (int i = 0; i < questionCount; i++) {
            while (true) {
                cout << "\n--- Question " << i + 1 << " ---\n";
                questions[i].getQuestionData();

                if (!questions[i].isCorrect()) {
                    cout << "Incorrect answer format! Please re-enter the question.\n";
                }
                else {
                    break; // valid question
                }
            }
        }
    }
    //for further use in the class quiz
    int getTotalQuestions() const {
        return questionCount;
    }

    //for further use in the classroom quiz
    const Question& getQuestion(int index) const {
        if (index < 0 || index >= questionCount) {
            throw out_of_range("Invalid question index.");
        }
        return questions[index];
    }
};

#endif
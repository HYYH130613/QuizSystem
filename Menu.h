//u2410234 Sofina Adelina
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "Quiz.h"
#include "Edit.h"
#include "Person.h"
#include "Delete.h"

using namespace std;

//clear terminal
void clearScreen() {
    cout << "\x1B[2J\x1B[H";
    cout.flush();
}

class MainMenu { //abstract menu class
  protected:
  Person* person;

  public:

  MainMenu(Person* person) : person(person) {};

  virtual ~MainMenu() { delete person; }

  virtual void displayMenu() = 0;
};

class AdminMenu : public MainMenu { //admin menu class
  public:

    AdminMenu(string name) : MainMenu(new Admin(name)) {}

    void displayMenu() final {
      string filename;
      string id;
      Edit edit;
      Quiz quizAdmin;
      int option;
      bool isRunning = true;

      while (isRunning) {
        cout<<"\n====================\n";
        cout << "     Admin Menu    \n";
        cout << "====================\n";
        cout << "Logged in as: " << person->getName() << endl;
        cout << "\n------------------------\n"<< "1. Create Quiz\n";
        cout << "\n------------------------\n"<< "2. Edit Quiz\n";
        cout << "\n------------------------\n"<< "3. Delete Quiz\n";
        cout << "\n------------------------\n"<< "4. Logout\n";
        cout << "\n------------------------\n"<< "Choose an option: ";

        cin >> option;
        cin.ignore();
        try{
          switch (option) {
            case 1:
              try {
                quizAdmin.addQuiz();
                quizAdmin.saveToFile();
                Quiz::saveTotalToFile();
                cout << "\n------------------------\n";
                cout << "\nQuiz created successfully!\n";
                cout << "\n------------------------\n";
                cout << "\nRemaining capacity: " << Quiz::MAX_QUIZZES - Quiz::getTotalQuizzes() << "\n";
                cout << "\n------------------------\n";
                //simulating loading process
                cout << "\nPress Enter to return to the Admin Menu..." << endl;
                cin.get();
                clearScreen();

              }
            catch (const exception& e) {
              cerr << "Error: " << e.what() << endl;
            }
            break;

            case 2:
              cout << "====================\n";
            cout<<"List of existing quizzes:\n";
            quizAdmin.quizzesList();
            cout << "====================\n";
            cout << "\nEnter your quiz name: ";
            getline(cin, id);
            cout << "\n====================\n";
            cin.ignore();
            filename = id + ".txt";

            try {
              cout << "====================\n";
              edit.editQuiz(filename);
              cout << "====================\n";

              cout << "\n------------------------\n";
              cout << "\nPress Enter to return the Admin Menu..." << endl;
              cin.get();
              clearScreen();

            } catch (const exception& e) {
              cerr << "Error editing quiz: " << e.what() << endl;
            }
            break;

            case 3: {
              string quizName;
              cout << "====================\n";
              cout<<"List of existing quizzes:\n";
              quizAdmin.quizzesList();
              cout << "====================\n";
              cout << "Enter quiz name to delete: ";
              getline(cin, quizName);
              cout << "====================\n";
              Delete::deleteQuiz(quizName);
              cout << "\n------------------------\n";
              cout << "Remaining capacity: "
                   << Quiz::MAX_QUIZZES - Quiz::getTotalQuizzes() << "\n";

              cout << "\n------------------------\n";
              cout << "\nPress Enter to return to the Admin Menu..." << endl;
              cin.get();
              clearScreen();

              break;
            }

            case 4: {
              isRunning = false;
              break;

              default:
                throw invalid_argument( "Invalid input! Please try again.");
            }
          }
        } catch (const exception& e) {
          cerr << "Error: " << e.what() << endl;
        }
      }
    }

    ~AdminMenu() {
        //clear terminal
        clearScreen();
    };

};

class UserMenu : public MainMenu { //user menu class
  public:

    UserMenu(string name) : MainMenu(new User(name)) {}

    void displayMenu()final{
      string name, filename;
      int option;
      bool isRunning = true;
      while (isRunning) {
        Quiz quizUser;
        cout<<"\n====================\n";
        cout << "     User Menu    \n";
        cout << "====================\n";
        cout << "Logged in as: " << person->getName() << endl;
        cout << "\n------------------------\n" << "1. Load Quiz\n";
        cout << "\n------------------------\n" << "2. Logout\n";
        cout << "\n------------------------\n"<< "Enter an option: ";

        cin >> option;
        try {
          switch (option) {
            case 1:
                cin.ignore();
          		quizUser.quizzesList();
				cout << "====================\n";
				cout << "Enter your quiz name: ";
				getline(cin, name);
				//cin.ignore();
				filename = name + ".txt";
				try {
				cout << "====================\n";
				quizUser.loadFromFile(filename);

                //simulating loading process
                clearScreen();
                cout << "\n------------------------\n";
                cout << "\nPress Enter to continue..." << endl;
                cin.get();
                clearScreen();
				}
            catch (const exception& e) {
              cout << "====================\n";
              cerr << "Error loading quiz: " << e.what() << endl;
            }
            break;

            case 2:
            isRunning = false;
            break;

            default:
              throw invalid_argument( "Invalid input! Please try again.");
          }
        } catch (const exception& e) {
          cerr << "Error: " << e.what() << endl;
        }
      }
    }

  ~UserMenu(){
      clearScreen();
  };

};

//acces to admin menu
string admins [7] = {"Adelina", "Yekaterina", "Xurshida", "Alexandr", "Dmitriy", "Suvanov Sharof", "Anvarov Akobirkhuja"};

void runMenuSystem() { // run all menues and login for access
  int inputRole;
  bool isRunning = true;
  string name;

  while (isRunning) {
    cout<<"\n====================\n";
    cout << "     Main Menu    \n";
    cout << "====================\n";
    cout << "\n------------------------\n" << "1. Admin Menu\n";
    cout << "\n------------------------\n" << "2. User Menu\n";
    cout << "\n------------------------\n" << "3. Logout\n";
    cout << "\n------------------------\n"<< "Enter an option: ";
    cin >> inputRole;
    cin.ignore();

    MainMenu* menu = nullptr;

    try {
      switch (inputRole) {

        case 1: {
          cout<<"\n====================\n";
          cout << "Enter admin name: ";
          getline(cin, name);

          try {
            for (int i = 0; i<=6; i++) {
              if (name == admins[i]) {

                //simulating loading process
              	clearScreen();
                cout << "\n------------------------\n";
                cout << "\nPress Enter to continue..." << endl;
                cin.get();
                clearScreen();

                menu = new AdminMenu(name);
                menu->displayMenu();
                delete menu;
                break;

              }else {
                throw invalid_argument("Invalid Name! Please try again.");
              }
            }
          }catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
          }
          cout << "\n------------------------\n";
          cout << "\nPress Enter to continue..."<<endl;
          cin.get();
          clearScreen();
          break;
      }
        case 2: {
          cout<<"\n====================\n";
          cout << "Enter user name: ";
          getline(cin, name);
          //simulating loading process
          clearScreen();
          cout << "\n------------------------\n";
          cout << "\nPress Enter to continue...";
          cin.get();
          clearScreen();

          menu = new UserMenu(name);
          menu->displayMenu();
          delete menu;
          break;
      }
        case 3: {
          cout << "==========================\n";
          cout<<"\tGoodbye!\n";
          cout << "==========================\n";
          isRunning = false;
          break;
      }
        default: {
          throw invalid_argument( "Invalid input! Please try again.");
      }
      }
    }
    catch (const exception& ex) {
      cerr << "Error: " << ex.what() << endl;
      if (menu) {
        delete menu;
      }
    }
  }
}

#endif


#include "Menu.h"
#include "Quiz.h"

using namespace std;

int main(){

    Quiz::loadTotalFromFile();
    runMenuSystem();

    return 0;
}

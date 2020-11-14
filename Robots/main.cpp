#include <iostream>
#include <string>
#include "optionparser.h"
#include "GameView.h"

using namespace std;

enum class Cell { EMPTY, ROCK, BOMB, APPLE };

int main(int argc, char* argv[]) {
    ConsoleView gameView;
    string cmd;
    getline(cin, cmd);
    while (cmd != "exit") {
        cout << gameView.getWidth() << "x" << gameView.getHeight() << endl;
        getline(cin, cmd);
    }
    return 0;
}

#include <iostream>
#include "Interface.h"

using namespace std;

Interface::Interface(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    game = new GameModel(rows, cols);
    updateUI();
}

Interface::~Interface() {
    delete game;
    game = nullptr;
}

void Interface::run() {
    string cmd;
    getline(cin, cmd);

    while (cmd != "exit") {
        auto result = CommandParser::parseCommand(cmd, rows, cols);
        if (result.first == CommandType::HELP) printHelp();
        else if (!game->invokeCommand(result.first, result.second)) {
            cout << "Invalid command or arguments. Use <help> to see available commands" << endl;
            cout << "(If you tried to execute <save> or <load>, make sure file name is valid or file exists and has valid content)" << endl;
        }
        else updateUI();
        getline(cin, cmd);
    }
}

void Interface::updateUI() {
    clearUI();
    cout << (*game) << endl;
    cout << "Moves made: " << game->getMoves() << endl;
}

void Interface::clearUI() {
    system("cls");
}

void Interface::printHelp() {
    cout << "List of available commands:" << endl;
    cout << "\t" << "help - show this list" << endl;
    cout << "\t" << "exit - exit application" << endl;
    cout << "\t" << "reset - clear field and reset moves" << endl;
    cout << "\t" << "" << R"(set XY - 'A' <= X <= 'J', 0 <= Y <= 9, set cell XY to ALIVE state)" << endl;
    cout << "\t" << "" << R"(clear XY - 'A' <= X <= 'J', 0 <= Y <= 9, set cell XY to DEAD state)" << endl;
    cout << "\t" << "step [N] - cycle game N times forward (1, if N not specified)" << endl;
    cout << "\t" << "back - cycle game 1 time backward (only one time after step command)" << endl;
    cout << "\t" << R"(save "filename" - save game state (no history of moves))" << endl;
    cout << "\t" << R"(load "filename" - load game from file (no history of moves))" << endl;
}
#include <iostream>
#include <fstream>
#include "CommandParser.h"

CommandParser::CommandParser(Field *field) {
    this->field = field;
}

ParseResult CommandParser::parseCommand(string& cmd) {
    vector<string> split = StringUtils::split(cmd, ' ');
    if (split.empty()) return INVALID_CMD;

    if (split[0] == "help") {
        if (split.size() > 1) return INVALID_ARG;
        return HELP;
    }
    else if (split[0] == "reset") {
        if (split.size() > 1) return INVALID_ARG;
        field->reset();
    }
    else if (split[0] == "set") {
        if (split.size() != 2 && split[1].size() != 2) return INVALID_ARG;

        int r = ROWS - 1 + '0' - split[1][1], c = split[1][0] - 'A';
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return INVALID_ARG;

        field->setCell(r, c);
    }
    else if (split[0] == "clear") {
        if (split.size() != 2 || split[1].size() != 2) return INVALID_ARG;

        int r = ROWS - 1 + '0' - split[1][1], c = split[1][0] - 'A';
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return INVALID_ARG;

        field->clearCell(r, c);
    }
    else if (split[0] == "step") {
        if (split.size() > 2) return INVALID_ARG;

        int n = 1;
        if (split.size() == 2) n = stoi(cmd.substr(5));
        if (n <= 0) return INVALID_ARG;

        for (int i = 0; i < n - 1; i++) field->makeMove(false);
        field->makeMove();
    }
    else if (split[0] == "back") {
        if (split.size() > 1) return INVALID_ARG;
        field->revertMove();
    }
    else if (split[0] == "save") {
        if (split.size() != 2) return INVALID_ARG;
        string fl_name = StringUtils::trim(split[1], "\"");
        ofstream sv_file(fl_name + ".txt");
        for (int i = 0; i < ROWS * COLS; i++)
            sv_file << (field->getCell(i) == DEAD ? UI_DEAD : UI_ALIVE);
        sv_file.close();
    }
    else if (split[0] == "load") {
        if (split.size() != 2) return INVALID_ARG;
        string fl_name = StringUtils::trim(split[1], "\"");
        ifstream ld_file(fl_name + ".txt");
        if (!ld_file.is_open()) return NO_FILE;
        string in;
        getline(ld_file, in);
        if (!field->load(in)) return INVALID_FILE;
    }
    else return INVALID_CMD;

    return OK;
}

void CommandParser::printHelp() {
    cout << "List of available commands:" << endl;
    cout << "help - show this list" << endl;
    cout << "exit - exit application" << endl;
    cout << "reset - clear field and reset moves" << endl;
    cout << R"(set XY - 'A' <= X <= 'J', 0 <= Y <= 9, set cell XY to ALIVE state)" << endl;
    cout << R"(clear XY - 'A' <= X <= 'J', 0 <= Y <= 9, set cell XY to DEAD state)" << endl;
    cout << "step [N] - cycle game N times forward (1, if N not specified)" << endl;
    cout << "back - cycle game 1 time backward" << endl;
    cout << R"(save "filename" - save game state (no history of moves))" << endl;
    cout << R"(load "filename" - load game from file (no history of moves))" << endl;
}
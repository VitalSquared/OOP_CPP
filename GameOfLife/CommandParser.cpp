#include <iostream>
#include <fstream>
#include "CommandParser.h"
#include "Interface.h"

using namespace std;

ParseResult CommandParser::parseCommand(string& cmd, Field *field) {
    vector<string> split = splitString(cmd, ' ');

    if (split.empty()) return INVALID_CMD;

    if (split[0] == "help") {
        if (split.size() > 1) return INVALID_ARG;
        return HELP;
    }
    else if (split[0] == "reset") {
        if (split.size() > 1) return INVALID_ARG;
        if (field != nullptr) field->reset();
    }
    else if (split[0] == "set") {
        if (split.size() != 2 || split[1].size() != 2) return INVALID_ARG;

        int r = ROWS - 1 + '0' - split[1][1], c = split[1][0] - 'A';
        if (!validateCoords(r, c)) return INVALID_ARG;

        if (field != nullptr) field->setCell(r, c, ALIVE);
    }
    else if (split[0] == "clear") {
        if (split.size() != 2 || split[1].size() != 2) return INVALID_ARG;

        int r = ROWS - 1 + '0' - split[1][1], c = split[1][0] - 'A';
        if (!validateCoords(r, c)) return INVALID_ARG;

        if (field != nullptr) field->setCell(r, c, DEAD);
    }
    else if (split[0] == "step") {
        if (split.size() > 2) return INVALID_ARG;

        int n = 1;
        if (split.size() == 2) {
            try {
                n = stoi(cmd.substr(5));
            }
            catch (std::exception&) {
                return INVALID_ARG;
            }
        }
        if (n <= 0) return INVALID_ARG;

        if (field != nullptr) {
            for (int i = 0; i < n - 1; i++) field->makeMove(false);
            field->makeMove();
        }
    }
    else if (split[0] == "back") {
        if (split.size() > 1) return INVALID_ARG;
        if (field != nullptr) field->revertMove();
    }
    else if (split[0] == "save") {
        if (split.size() != 2) return INVALID_ARG;
        if (split[1].front() != '\"' && split[1].back() != '\"') return INVALID_ARG;

        if (field != nullptr) {
            string fl_name = trimString(split[1], "\"");
            ofstream sv_file(fl_name + ".txt");
            for (int i = 0; i < ROWS * COLS; i++)
                sv_file << (field->getCell(i) == DEAD ? UI_DEAD : UI_ALIVE);
            sv_file.close();
        }
    }
    else if (split[0] == "load") {
        if (split.size() != 2) return INVALID_ARG;
        if (split[1].front() != '\"' && split[1].back() != '\"') return INVALID_ARG;
        string fl_name = trimString(split[1], "\"");
        ifstream ld_file(fl_name + ".txt");
        if (!ld_file.is_open()) return NO_FILE;
        string in;
        getline(ld_file, in);
        if (field != nullptr) {
            if (!field->load(in)) {
                ld_file.close();
                return INVALID_FILE;
            }
        }
        ld_file.close();
    }
    else return INVALID_CMD;

    return OK;
}

void CommandParser::printHelp() {
    cout << "List of available commands:" << endl;
    cout << "\t" << "help - show this list" << endl;
    cout << "\t" << "exit - exit application" << endl;
    cout << "\t" << "reset - clear field and reset moves" << endl;
    cout << "\t" << "" << R"(set XY - 'A' <= X <= 'J', 0 <= Y <= 9, set cell XY to ALIVE state)" << endl;
    cout << "\t" << "" << R"(clear XY - 'A' <= X <= 'J', 0 <= Y <= 9, set cell XY to DEAD state)" << endl;
    cout << "\t" << "step [N] - cycle game N times forward (1, if N not specified)" << endl;
    cout << "\t" << "back - cycle game 1 time backward" << endl;
    cout << "\t" << R"(save "filename" - save game state (no history of moves))" << endl;
    cout << "\t" << R"(load "filename" - load game from file (no history of moves))" << endl;
}

bool CommandParser::validateCoords(int r, int c) {
    return 0 <= r && r < ROWS && 0 <= c && c < COLS;
}

vector<string> CommandParser::splitString(const string &str, char ch) {
    vector<string> v;
    size_t pos = str.find(ch);
    size_t initialPos = 0;
    string substr;
    while (pos != string::npos) {
        substr = str.substr(initialPos, pos - initialPos);
        if (!substr.empty()) v.push_back(substr);
        initialPos = pos + 1;
        pos = str.find(ch, initialPos);
    }
    substr = str.substr(initialPos, min(pos, str.size()) - initialPos + 1);
    if (!substr.empty()) v.push_back(substr);
    return v;
}

string& CommandParser::ltrimString(string &str, const string &chars) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

string& CommandParser::rtrimString(std::string &str, const string &chars) {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

string& CommandParser::trimString(std::string &str, const string &chars) {
    return ltrimString(rtrimString(str, chars), chars);
}
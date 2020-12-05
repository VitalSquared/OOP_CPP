#include <iostream>
#include "CommandParser.h"
#include "Utils.h"

using namespace std;

pair<CommandType, vector<string>> CommandParser::parseCommand(const string& cmd, int rows, int cols) {
    vector<string> split = splitString(cmd, ' ');

    CommandType cmdType = CommandType::NONE;
    vector<string> args(split);

    if (!args.empty()) args.erase(args.begin());

    if (!split.empty()) {
        if (split[0] == "help" || split[0] == "reset" || split[0] == "back") {
            if (split.size() == 1) cmdType = split[0] == "help" ? CommandType::HELP : split[0] == "back" ? CommandType::BACK : CommandType::RESET;
        }
        else if (split[0] == "set" || split[0] == "clear") {
            if (split.size() == 2 && split[1].size() == 2) {
                int r = rows - 1 + '0' - split[1][1], c = split[1][0] - 'A';
                if (0 <= r && r < rows && 0 <= c && c < cols) {
                    cmdType = split[0] == "set" ? CommandType::SET : CommandType::CLEAR;
                    args.clear();
                    args.emplace_back(to_string(r));
                    args.emplace_back(to_string(c));
                }
            }
        }
        else if (split[0] == "step") {
            if (!split.empty() && split.size() <= 2) {
                int n = 1;
                if (split.size() == 2) {
                    try {
                        n = stoi(split[1]);
                    }
                    catch (std::exception &) {
                        n = 0;
                    }
                }
                if (n > 0) cmdType = CommandType::STEP;
            }
        }
        else if (split[0] == "save" || split[0] == "load") {
            if (split.size() == 2) {
                string fl_name = trimString(split[1], "\"");
                if (split[0] == "save") cmdType = CommandType::SAVE;
                else cmdType = CommandType::LOAD;
            }
        }
    }

    return make_pair(cmdType, args);
}

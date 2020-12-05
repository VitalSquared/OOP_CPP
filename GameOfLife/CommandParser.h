#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <vector>

using namespace std;

enum class CommandType { NONE, HELP, RESET, SET, CLEAR, STEP, BACK, SAVE, LOAD };

class CommandParser {
public:
    static pair<CommandType, vector<string>> parseCommand(const string& cmd, int rows, int cols);
};

#endif

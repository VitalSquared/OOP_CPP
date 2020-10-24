#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include "GameModel.h"

using namespace std;

enum ParseResult { OK, HELP, INVALID_CMD, INVALID_ARG, NO_FILE, INVALID_FILE };

class CommandParser {
public:
    CommandParser(Field *field);
    ParseResult parseCommand(string& cmd);
    static void printHelp();

private:
    Field *field;
};

#endif

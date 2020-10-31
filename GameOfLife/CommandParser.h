#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <vector>
#include "GameModel.h"

using namespace std;

enum ParseResult { OK, HELP, INVALID_CMD, INVALID_ARG, NO_FILE, INVALID_FILE };

class CommandParser {
public:
    static ParseResult parseCommand(string& cmd, Field *field = nullptr);
    static void printHelp();
private:
    static bool validateCoords(int r, int c);
    static vector<string> splitString(const string& str, char ch = ' ');
    static string& ltrimString(string& str, const string& chars = "\t\n\v\f\r ");
    static string& rtrimString(string& str, const string& chars = "\t\n\v\f\r ");
    static string& trimString(string& str, const string& chars = "\t\n\v\f\r ");
};

#endif

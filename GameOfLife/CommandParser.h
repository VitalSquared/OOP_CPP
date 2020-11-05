#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <vector>
#include "GameModel.h"

using namespace std;

enum ParseResult { OK, HELP, INVALID_CMD, INVALID_ARG, FILE_CANT_BE_CREATED, FILE_DOESNT_EXIST, INVALID_FILE_CONTENT };

class CommandParser {
public:
    static ParseResult parseCommand(const string& cmd, Field *field = nullptr);
    static void printHelp();
private:
    static bool validateCoords(int r, int c);
    static vector<string> splitString(const string& str, char ch = ' ');
    static string& ltrimString(string& str, const string& chars = "\t\n\v\f\r ");
    static string& rtrimString(string& str, const string& chars = "\t\n\v\f\r ");
    static string& trimString(string& str, const string& chars = "\t\n\v\f\r ");
};

#endif

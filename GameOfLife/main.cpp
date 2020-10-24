#include <iostream>
#include "GameModel.h"
#include "CommandParser.h"

using namespace std;

int main() {
    Field field;
    CommandParser cmdParser(&field);

    string cmd = "";
    getline(cin, cmd);

    while (cmd != "exit") {
        ParseResult result = cmdParser.parseCommand(cmd);
        switch(result) {
            case OK: break;
            case HELP: CommandParser::printHelp(); break;
            case INVALID_CMD: cout << "Invalid command. Use help to see available commands" << endl; break;
            case INVALID_ARG: cout << "Invalid argument(s). Use help to see available commands" << endl; break;
            case NO_FILE: cout << "File doesn't exist" << endl; break;
            case INVALID_FILE: cout << "Invalid contents of file" << endl; break;
        }
        getline(cin, cmd);
    }

    return 0;
}

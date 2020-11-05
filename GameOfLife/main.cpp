#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameModel.h"
#include "CommandParser.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc > 1) {
        if (string(argv[1]) == "-run_google_tests") {
            testing::InitGoogleTest();
            int res = RUN_ALL_TESTS();
            return 0;
        }
    }

    Field field;
    string cmd;
    getline(cin, cmd);

    while (cmd != "exit") {
        ParseResult result = CommandParser::parseCommand(cmd, &field);
        switch(result) {
            case OK: break;
            case HELP: CommandParser::printHelp(); break;
            case INVALID_CMD: cout << "Invalid command. Use help to see available commands" << endl; break;
            case INVALID_ARG: cout << "Invalid argument(s). Use help to see available commands" << endl; break;
            case FILE_CANT_BE_CREATED: cout << "File can't be created" << endl; break;
            case FILE_DOESNT_EXIST: cout << "File doesn't exist" << endl; break;
            case INVALID_FILE_CONTENT: cout << "Invalid contents of file" << endl; break;
        }
        getline(cin, cmd);
    }

    return 0;
}

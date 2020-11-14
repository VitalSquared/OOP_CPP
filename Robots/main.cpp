#include <iostream>
#include <string>
#include "optionparser.h"
#include "ConsoleView.h"
#include "Command.h"
#include "Field.h"
#include "Utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    argc -= (argc>0); //  \/
    argv += (argc>0); //   skip program name argv[0] if present

    ifstream ld_file;

    if (argc >= 1) {
        if ("-generate" == string(argv[0])) {
            if (argc != 4) {
                printError(ErrorType::INVALID_ARGS);
                return 0;
            }
            int w, h;
            try {
                w = stoi(argv[1]);
                h = stoi(argv[2]);
            }
            catch (exception&) {
                printError(ErrorType::INVALID_ARGS);
                return 0;
            }
            if (w < 1000 || h < 1000) {
                printError(ErrorType::WH1000);
                return 0;
            }
            string fl_name(argv[3]);
            fl_name = trimString(fl_name, "\"");
            ofstream sv_file(fl_name);
            if (!sv_file.is_open()) {
                printError(ErrorType::CANT_CREATE_FILE);
                return 0;
            }
            cout << "Generating..." << endl;
            generateMap(w, h, sv_file);
            sv_file.close();
            cout << "Generation completed. Exiting..." << endl;
            cout << "Press ENTER to continue." << endl;
            cin.get();
            return 0;
        }
        else {
            if (argc > 1) {
                printError(ErrorType::INVALID_ARGS);
                return 0;
            }
            string fl_name(argv[0]);
            fl_name = trimString(fl_name, "\"");
            ld_file.open(fl_name);
            if (!ld_file.is_open()) {
                printError(ErrorType::NO_FILE);
                return 0;
            }
        }
    }
    else {
        printError(ErrorType::INVALID_ARGS);
        return 0;
    }

    try {
        Field field(ld_file);
        ld_file.close();

        Collector collector(field);
        ConsoleView consoleView(&field, &collector);
        consoleView.renderField();

        string cmd;
        getline(cin, cmd);
        while (cmd != "exit") {
            if (!collector.getDeadState()) {
                if (cmd == "MOVE U") {
                    collector.move(Direction::UP, field);
                } else if (cmd == "MOVE D") {
                    collector.move(Direction::DOWN, field);
                } else if (cmd == "MOVE L") {
                    collector.move(Direction::LEFT, field);
                } else if (cmd == "MOVE R") {
                    collector.move(Direction::RIGHT, field);
                } else if (cmd == "GRAB") {
                    collector.grab(field);
                } else if (cmd == "SCAN") {
                    collector.scan();
                }
                string msg = collector.retrievePendingMessage();
                if (!msg.empty()) {
                    consoleView.showMessage(msg);
                }
                consoleView.renderField();
            }
            getline(cin, cmd);
        }
    }
    catch (exception&) {
        if (ld_file.is_open()) ld_file.close();
        printError(ErrorType::OTHER);
    }
    return 0;
}

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
        Sapper sapper(field, collector.getScanned());

        ConsoleView gameView(&field, &collector, &sapper);
        gameView.renderField();

        Mode *mode = new ManualMode(&field, &collector, &sapper, &gameView);

        Command *command = nullptr;

        string cmd;
        getline(cin, cmd);
        while (cmd != "exit") {
            if (!collector.getDeadState()) {
                delete command;
                command = nullptr;

                if (cmd == "MOVE U") {
                    command = new MoveCommand(mode, Direction::UP);
                }
                else if (cmd == "MOVE D") {
                    command = new MoveCommand(mode, Direction::DOWN);
                }
                else if (cmd == "MOVE L") {
                    command = new MoveCommand(mode, Direction::LEFT);
                }
                else if (cmd == "MOVE R") {
                    command = new MoveCommand(mode, Direction::RIGHT);
                }
                else if (cmd == "GRAB") {
                    command = new GrabCommand(mode);
                }
                else if (cmd == "SCAN") {
                    command = new ScanCommand(mode);
                }
                else if (cmd == "SET_MODE manual") {
                    command = new ChangeModeCommand(&mode, new ManualMode(&field, &collector, &sapper, &gameView));
                }
                else if (cmd.substr(0, 13) == "SET_MODE scan") {
                    try {
                        int n = stoi(cmd.substr(13));
                        command = new ChangeModeCommand(&mode, new ScanMode(&field, &collector, &gameView, n));
                    }
                    catch (exception&) {}
                }
                else if (cmd == "SET_MODE auto") {
                    command = new ChangeModeCommand(&mode,new AutoMode(&field, &collector, &sapper, &gameView));
                }
                else if (cmd == "SAPPER ON") {
                    command = new SapperCommand(mode, true);
                }
                else if (cmd == "SAPPER OFF") {
                    command = new SapperCommand(mode, false);
                }
                if (command) command->execute();
                string msg = mode->getPendingMessage();
                if (!msg.empty()) gameView.showMessage(msg);
                gameView.renderField();
            }
            getline(cin, cmd);
        }

        delete command;
        delete mode;
    }
    catch (exception&) {
        if (ld_file.is_open()) ld_file.close();
        printError(ErrorType::OTHER);
    }
    return 0;
}

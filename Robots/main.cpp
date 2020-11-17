#include <iostream>
#include <vector>
#include <string>
#include "optionparser.h"
#include "Collector.h"
#include "Sapper.h"
#include "ConsoleView.h"
#include "ManualMode.h"
#include "ScanMode.h"
#include "AutoMode.h"
#include "Command.h"
#include "Utils.h"

enum  optionIndex { LOAD, GENERATE };
const option::Descriptor usage[] =
        {
            {LOAD, 0,"l", "load",option::Arg::None, "  --load, -l \"file\"  \tLoad map from file." },
            {GENERATE, 0,"g","generate",option::Arg::None, "  --generate, -g  width height \"file\" \tGenerate map file <width x height>." },
            {0,0,nullptr,nullptr,nullptr,nullptr}
        };

using namespace std;

int main(int argc, char* argv[]) {
    argc -= (argc>0); argv += (argc>0); // skip program name argv[0] if present

    option::Stats  stats(usage, argc, argv);
    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

    if (parse.error()) {
        printError(ErrorType::OTHER);
        return 1;
    }

    ifstream ld_file;

    if (options[GENERATE]) {
        if (parse.nonOptionsCount() != 3) {
            option::printUsage(std::cout, usage);
            printError(ErrorType::INVALID_ARGS);
            return 0;
        }
        int w, h;
        try {
            w = stoi(parse.nonOption(0));
            h = stoi(parse.nonOption(1));
        }
        catch (exception&) {
            printError(ErrorType::INVALID_ARGS);
            return 0;
        }
        if (w < 1000 || h < 1000) {
            printError(ErrorType::WH1000);
            return 0;
        }

        ofstream sv_file(parse.nonOption(2));
        if (!sv_file.is_open()) {
            printError(ErrorType::CANT_CREATE_FILE);
            return 0;
        }
        cout << "Generating..." << endl;
        generateMap(w, h, sv_file);
        sv_file.close();
        cout << "Generation completed. Exiting...\nPress ENTER to continue." << endl;
        cin.get();
        return 0;
    }
    else if (options[LOAD]) {
        if (parse.nonOptionsCount() != 1) {
            option::printUsage(std::cout, usage);
            printError(ErrorType::INVALID_ARGS);
            return 0;
        }
        ld_file.open(parse.nonOption(0));
        if (!ld_file.is_open()) {
            printError(ErrorType::NO_FILE);
            return 0;
        }
    }
    else {
        option::printUsage(std::cout, usage);
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

        string cmd, msg;

        getline(cin, cmd);
        while (cmd != "exit") {
            vector<string> args = splitString(cmd, ' ');

            if (!collector.getDeadState()) {
                delete command;
                command = nullptr;
                bool success = true;
                if (!args.empty()) {
                    if (args[0] == "MOVE") {
                        if (args.size() != 2 || args[1].size() != 1) success = false;
                        else {
                            switch(args[1][0]) {
                                case 'U': command = new MoveCommand(mode, Direction::UP); break;
                                case 'D': command = new MoveCommand(mode, Direction::DOWN); break;
                                case 'L': command = new MoveCommand(mode, Direction::LEFT); break;
                                case 'R': command = new MoveCommand(mode, Direction::RIGHT); break;
                                default: success = false;
                            }
                        }
                    }
                    else if (args[0] == "GRAB") {
                        if (args.size() != 1) success = false;
                        else command = new GrabCommand(mode);
                    }
                    else if (args[0] == "SCAN") {
                        if (args.size() != 1) success = false;
                        else command = new ScanCommand(mode);
                    }
                    else if (args[0] == "SET_MODE") {
                        if (args.size() < 2) success = false;
                        else {
                            if (args[1] == "manual") {
                                if (args.size() != 2) success = false;
                                else command = new ChangeModeCommand(&mode, new ManualMode(&field, &collector, &sapper, &gameView));
                            }
                            else if (args[1] == "scan") {
                                if (args.size() != 3) success = false;
                                else {
                                    try {
                                        int n = stoi(args[2]);
                                        command = new ChangeModeCommand(&mode, new ScanMode(&field, &collector, &gameView, n));
                                    }
                                    catch (exception &) {
                                        success = false;
                                    }
                                }
                            }
                            else if (args[1] == "auto") {
                                if (args.size() != 2) success = false;
                                else command = new ChangeModeCommand(&mode, new AutoMode(&field, &collector, &sapper, &gameView));
                            }
                            else success = false;
                        }
                    }
                    else if (args[0] == "SAPPER") {
                        if (args.size() != 2) success = false;
                        else {
                            if (args[1] == "ON") command = new SapperCommand(mode, true);
                            else if (args[1] == "OFF") command = new SapperCommand(mode, false);
                            else success = false;
                        }
                    }
                    else success = false;
                }

                if (command) command->execute();
                msg = success ? mode->getPendingMessage() : "Invalid command.";
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

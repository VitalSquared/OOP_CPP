#include <iostream>
#include <ctime>
#include "optionparser.h"
#include "Utils.h"
#include "IGameView.h"
#include "ConsoleView.h"

const option::Descriptor usage[] =
        {
                {0,0,nullptr,nullptr,nullptr,nullptr}
        };

int main(int argc, char** argv) {
    srand(std::time(nullptr));

    int cnt_collectors = 1;
    argc -= (argc>0); argv += (argc>0);

    option::Stats  stats(usage, argc, argv);
    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

    if (parse.error()) {
        std::cout <<"Error while parsing arguments" << std::endl;
        return 0;
    }

    if (parse.nonOptionsCount() != 1 && parse.nonOptionsCount() != 2) {
        option::printUsage(std::cout, usage);
        std::cout << "Invalid amount of arguments." << std::endl;
        return 0;
    }
    if (!fileExists(parse.nonOption(0))) {
        std::cout << "File doesn't exist" << std::endl;
        return 0;
    }
    if (parse.nonOptionsCount() == 2) {
        if (!convertStringToInt(parse.nonOption(1), cnt_collectors) || cnt_collectors <= 0) {
            std::cout <<"Invalid amount of collectors" << std::endl;
            return 0;
        }
    }

    std::cout << "Booting up..." << std::endl;
    std::cout << "Loading map " + std::string(parse.nonOption(0)) << std::endl;

    IGameView* gameView = new ConsoleView(parse.nonOption(0), cnt_collectors);
    gameView->run();
    delete gameView;

    return 0;
}

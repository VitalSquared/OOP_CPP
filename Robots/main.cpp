#include <iostream>
#include <ctime>
#include "optionparser.h"
#include "Utils.h"
#include "IGameView.h"
#include "ConsoleView.h"

enum  optionIndex { LOAD, GENERATE };
const option::Descriptor usage[] =
        {
                {LOAD, 0,"l", "load",option::Arg::None, "  --load, -l <\"file\"> [collectors count]  \tLoad map from file with collectors count (>=1, defaults to 1 if not present)." },
                {GENERATE, 0,"g","generate",option::Arg::None, "  --generate, -g  width height \"file\" \tGenerate map file <width x height>." },
                {0,0,nullptr,nullptr,nullptr,nullptr}
        };

void completeExecution(const std::string& message) {
    if (!message.empty()) std::cout << message << std::endl;
    std::cout << "Press ENTER to continue" << std::endl;
    std::cin.get();
    exit(0);
}

int main(int argc, char** argv) {
    srand(std::time(nullptr));

    int cnt_collectors = 1;
    argc -= (argc>0); argv += (argc>0);

    option::Stats  stats(usage, argc, argv);
    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

    if (parse.error()) completeExecution("Error while parsing arguments");

    if (options[GENERATE]) {
        if (parse.nonOptionsCount() != 3) {
            option::printUsage(std::cout, usage);
            completeExecution("Invalid amount of arguments.");
        }
        int w, h;
        if (!convertStringToInt(parse.nonOption(0), w) || !convertStringToInt(parse.nonOption(1), h)) {
            completeExecution("Invalid WIDTH and HEIGHT parameters");
        }
        if (w < 1000 || h < 1000) completeExecution("WIDTH and HEIGHT must be at least 1000");
        if (fileExists(parse.nonOption(2))) {
            std::cout << "File already exists. Do you want to override it? Y/N" << std::endl;
            char ch;
            std::cin.get(ch);
            if (ch != 'Y' && ch != 'y') completeExecution("");
        }
        std::ofstream sv_file(parse.nonOption(2));
        if (!sv_file.is_open()) {
            completeExecution("Can't create file");
            return 0;
        }
        std::cout << "Generating map..." << std::endl;
        generateMap(w, h, sv_file);
        sv_file.close();
        completeExecution("Generation completed. Exiting...");
    }
    else if (options[LOAD]) {
        if (parse.nonOptionsCount() != 1 && parse.nonOptionsCount() != 2) {
            option::printUsage(std::cout, usage);
            completeExecution("Invalid amount of arguments.");
            return 0;
        }
        if (!fileExists(parse.nonOption(0))) {
            completeExecution("File doesn't exist");
            return 0;
        }
        if (parse.nonOptionsCount() == 2) {
            if (!convertStringToInt(parse.nonOption(1), cnt_collectors) || cnt_collectors <= 0) {
                completeExecution("Invalid amount of collectors");
                return 0;
            }
        }
    }
    else {
        option::printUsage(std::cout, usage);
        completeExecution("Invalid arguments.");
        return 0;
    }

    std::cout << "Booting up..." << std::endl;
    std::cout << "Loading map " + std::string(parse.nonOption(0)) << std::endl;

    IGameView* gameView = new ConsoleView(parse.nonOption(0), cnt_collectors);
    gameView->run();
    delete gameView;

    return 0;
}

#include <iostream>
#include "IGameView.h"
#include "ConsoleView.h"

int main(int argc, char** argv) {
    std::cout << "Booting up..." << std::endl;
    IGameView* gameView = new ConsoleView("map1.txt");
    gameView->run();
    delete gameView;
    return 0;
}

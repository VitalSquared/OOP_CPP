#ifndef INTERFACE_H
#define INTERFACE_H

#include "CommandParser.h"
#include "GameModel.h"

class Interface {
public:
    Interface(int rows, int cols);
    ~Interface();

    void run();

private:
    int rows;
    int cols;
    GameModel *game;

    void clearUI();
    void updateUI();
    void printHelp();
};

#endif

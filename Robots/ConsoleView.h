#ifndef ROBOTS_CONSOLEVIEW_H
#define ROBOTS_CONSOLEVIEW_H

#include <string>
using namespace std;

class ConsoleView {
public:
    ConsoleView() = default;
    void clearScreen();
    int getWidth();
    int getHeight();

    const string colorBlack = "\x1B[30m";
    const string colorRed = "\x1B[31m";
    const string colorGreen = "\x1B[32m";
    const string colorYellow = "\x1B[33m";
    const string colorBlue = "\x1B[34m";
    const string colorMagenta = "\x1B[35m";
    const string colorCyan = "\x1B[36m";
    const string colorWhite = "\x1B[37m";
    const string colorGrey = "\x1B[30;1m";
    const string colorDarkGrey = "\x1B[38;5;238m";
};

#endif

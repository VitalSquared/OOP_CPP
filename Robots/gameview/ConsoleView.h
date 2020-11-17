#ifndef ROBOTS_CONSOLE_VIEW_H
#define ROBOTS_CONSOLE_VIEW_H

#include <iostream>
#include <string>
#include "Field.h"
#include "Collector.h"
#include "Sapper.h"
#include "Utils.h"
#include "GameView.h"

using namespace std;

class ConsoleView : GameView {
public:
    ConsoleView(Field *field, Collector *collector, Sapper *sapper);
    int getWidth() override;
    int getHeight() override;
    void renderField() override;
    static void showMessage(string& msg);
    void setModeName(const string& str);

    //const string colorBlack = "\x1B[30m";
    const string colorRed = "\x1B[31m";
    const string colorGreen = "\x1B[32m";
    //const string colorYellow = "\x1B[33m";
    //const string colorBlue = "\x1B[34m";
    const string colorMagenta = "\x1B[35m";
    const string colorCyan = "\x1B[36m";
    const string colorWhite = "\x1B[37m";
    const string colorGrey = "\x1B[30;1m";
    const string colorDarkGrey = "\x1B[38;5;238m";
    const string* getIconFromCell(int r, int c, bool bIgnoreCollector = false);

private:
    Field *field;
    Collector *collector;
    Sapper *sapper;
    string currentMode;

    static void clearScreen();

    const int ICON_SIZE = 2;

    const string APPLE_ICON[2] = { colorRed + "/|",
                                   colorRed + "oo" };
    const string BOMB_ICON[2] = { colorMagenta + "()",
                                  colorMagenta + "()"};
    const string DEFUSED_BOMB_ICON[2] = { colorGrey + "()",
                                          colorGrey + "()"};
    const string ROCK_ICON[2] = { colorGrey + "{/",
                                  colorGrey + "/}"};
    const string EMPTY_ICON[2] = { colorWhite + "  ",
                                   colorWhite + "  "};
    const string COLLECTOR_ICON[2] = { colorGreen + "Ro",
                                       colorGreen + "bo"};
    const string SAPPER_ICON[2] = { colorCyan + "Sa",
                                    colorCyan + "pp"};
    const string UNKNOWN_ICON[2] = { colorDarkGrey + "??",
                                     colorDarkGrey + "??"};
};

#endif

#ifndef ROBOTS_GAMEVIEW_H
#define ROBOTS_GAMEVIEW_H

#include "ConsoleView.h"
#include "Field.h"
#include "Robot.h"

class GameView : public ConsoleView {
public:
    GameView(Field *field, Collector *collector);
    void renderField();
private:
    Field *field;
    Collector *collector;
    const string* getIconFromCell(int r, int c);

    const int ICON_SIZE = 2;

    const string APPLE_ICON[2] = { colorRed + "/|",
                                   colorRed + "oo" };
    const string BOMB_ICON[2] = { colorMagenta + "()",
                                  colorMagenta + "/\\"};
    const string ROCK_ICON[2] = { colorGrey + "{/",
                                  colorGrey + "/}"};
    const string EMPTY_ICON[2] = { colorWhite + "  ",
                                   colorWhite + "  "};
    const string COLLECTOR_ICON[2] = { colorGreen + "Ro",
                                       colorGreen + "bo"};
    const string SAPPER_ICON[2] = { colorCyan + "SS",
                                    colorCyan + "SS"};
    const string UNKNOWN_ICON[2] = { colorDarkGrey + "??",
                                     colorDarkGrey + "??"};
};

#endif

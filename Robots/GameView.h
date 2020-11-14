#ifndef ROBOTS_GAMEVIEW_H
#define ROBOTS_GAMEVIEW_H

#include <windows.h>

class ConsoleView {
public:
    ConsoleView() = default;
    void clearScreen() {
        system("cls");
    }
    int getWidth() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        return columns;
    }
    int getHeight() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int rows;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        return rows;
    }
private:

};

class GameView : public ConsoleView {
public:

private:

};

#endif //ROBOTS_GAMEVIEW_H

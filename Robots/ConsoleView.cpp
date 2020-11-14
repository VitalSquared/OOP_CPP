#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <windows.h>

#define GET_SCREEN_WIDTH \
    CONSOLE_SCREEN_BUFFER_INFO csbi; \
    int columns; \
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); \
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

#define GET_SCREEN_HEIGHT \
    CONSOLE_SCREEN_BUFFER_INFO csbi; \
    int rows; \
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); \
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

#else

#include <sys/ioctl.h>
#include <unistd.h>

#define GET_SCREEN_WIDTH \
    struct winsize size; \
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); \
    int columns = size.ws_col;

#define GET_SCREEN_HEIGHT \
    struct winsize size; \
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); \
    int rows = size.ws_row;

#endif
#include "ConsoleView.h"

void ConsoleView::clearScreen() {
    system("cls");
}

int ConsoleView::getWidth() {
    GET_SCREEN_WIDTH;
    return columns;
}

int  ConsoleView::getHeight() {
    GET_SCREEN_HEIGHT;
    return rows;
}
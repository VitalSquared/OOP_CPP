#include <iostream>
#include <string>
#include "ConsoleView.h"
#include "Utils.h"

using namespace std;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <windows.h>

#define GET_SCREEN_WIDTH \
    CONSOLE_SCREEN_BUFFER_INFO csbi; \
    int columns; \
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); \
    columns = max(csbi.srWindow.Right - csbi.srWindow.Left + 1, 100);

#define GET_SCREEN_HEIGHT \
    CONSOLE_SCREEN_BUFFER_INFO csbi; \
    int rows; \
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); \
    rows = max(csbi.srWindow.Bottom - csbi.srWindow.Top + 1, 50);

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

ConsoleView::ConsoleView(Field *field, Collector *collector) {
    this->field = field;
    this->collector = collector;
}

void ConsoleView::renderField() {
    //check if collector robot is dead
    if (collector->getDeadState()) {
        clearScreen();
        ifstream deathmsg("robot_has_exploded.txt");
        if (deathmsg.is_open()) {
            while (!deathmsg.eof()) {
                string row;
                getline(deathmsg, row);
                cout << row << endl;
            }
            deathmsg.close();
        }
        else cout << "ROBOT HAS EXPLODED" << endl;
        cout << "Apples collected: " << collector->getApples() << endl;
        cout << "Use <exit> to quit application" << endl;
        return;
    }

    int width = getWidth();
    int height = getHeight();

    clearScreen();
    cout << endl; //empty line on top
    string apples_collected = "Apples: " + to_string(collector->getApples());

    string legend[] = {
            APPLE_ICON[0],
            APPLE_ICON[1] + colorWhite + " - Apple",
            BOMB_ICON[0],
            BOMB_ICON[1] + colorWhite + " - Bomb",
            ROCK_ICON[0],
            ROCK_ICON[1] + colorWhite + " - Rock",
            COLLECTOR_ICON[0],
            COLLECTOR_ICON[1] + colorWhite + " - Collector",
    };

    //calculate offset that is required from the right side to fit in legend
    int right_offset = legend[0].length();
    for (int i = 1; i < 5; i++)
        if (legend[i].length() > right_offset)
            right_offset = legend[i].length();

    //calculate field width (how many cells can fit in the row)
    int field_width = width - right_offset - 1;
    while (field_width % ICON_SIZE != 0 && (field_width / ICON_SIZE) % 2 != 0) field_width -= 1;
    field_width -= field_width / ICON_SIZE;
    field_width /= ICON_SIZE;

    //calculate field height (how many cells can fit in the column)
    int field_height = height - 4;
    while (field_height % ICON_SIZE != 0 && (field_height / ICON_SIZE) % 2 != 0) field_height -= 1;
    field_height -= field_height / ICON_SIZE;
    field_height /= ICON_SIZE;

    //total field width
    int field_screen_width = field_width * ICON_SIZE + field_width;

    //put "Apples: {num}" in the center
    int apples_coll_len = apples_collected.length();
    int left_offset1 = (field_screen_width - apples_coll_len) / 2;
    for (int i = 0; i < left_offset1; i++) cout << " ";
    cout << apples_collected;

    //put "Legend" after that
    for (int i = left_offset1 + apples_coll_len - 1; i < field_screen_width; i++) cout << " ";
    cout << "Legend" << endl;

    //get coordinates of collector
    int coll_r = collector->getRow();
    int coll_c = collector->getCol();

    //by placing collector in the center of screen, we calculate the coordinates of top left corner
    int top_r = coll_r - field_height / 2;
    int left_c = coll_c - field_width / 2;

    //print first rows and legend
    for (int i = 0; i < 4; i++) {
        for (int icon = 0; icon < ICON_SIZE; icon++) {
            for (int j = 0; j < field_width; j++) {
                cout << getIconFromCell(top_r + i, left_c + j)[icon] << colorDarkGrey + "|";
            }
            cout << " " << legend[i * ICON_SIZE + icon] << endl;
        }
        for (int j = 0; j < field_screen_width; j++) cout << colorDarkGrey + ((j + 1) % (ICON_SIZE + 1) == 0 ? "+" : "-");
        if (i == 3) cout << colorWhite + " Current cell:";
        cout << endl;
    }

    for (int i = 4; i < 5; i++) {
        for (int icon = 0; icon < ICON_SIZE; icon++) {
            for (int j = 0; j < field_width; j++) {
                cout << getIconFromCell(top_r + i, left_c + j)[icon] << colorDarkGrey + "|";
            }
            cout << " " << getIconFromCell(coll_r, coll_c, true)[icon] << endl;
        }
        for (int j = 0; j < field_screen_width; j++) cout << colorDarkGrey + ((j + 1) % (ICON_SIZE + 1) == 0 ? "+" : "-");
        cout << endl;
    }

    //print the rest of the rows
    for (int i = 5; i < field_height; i++) {
        for (int icon = 0; icon < ICON_SIZE; icon++) {
            for (int j = 0; j < field_width; j++) {
                cout << getIconFromCell(top_r + i, left_c + j)[icon] << colorDarkGrey + "|";
            }
            cout << endl;
        }
        for (int j = 0; j < field_screen_width; j++) cout << colorDarkGrey + ((j + 1) % (ICON_SIZE + 1) == 0 ? "+" : "-");
        cout << endl;
    }
    cout << colorWhite << endl;
}

const string* ConsoleView::getIconFromCell(int r, int c, bool bIgnoreCollector) {
    if (!bIgnoreCollector && r == collector->getRow() && c == collector->getCol()) return COLLECTOR_ICON; //collector
    if (!collector->hasScanned(r, c)) return UNKNOWN_ICON; //not scanned
    if (r < 0 || c < 0 || c >= field->getCols() || r >= field->getRows()) return ROCK_ICON; //out of bounds

    Cell cell = field->getCell(r, c);
    switch(cell) {
        case Cell::EMPTY: return EMPTY_ICON;
        case Cell::ROCK: return ROCK_ICON;
        case Cell::BOMB: return BOMB_ICON;
        case Cell::APPLE: return APPLE_ICON;
    }

    return EMPTY_ICON;
}

void ConsoleView::showMessage(string& msg) {
    cout << msg << endl;
    delay(1000);
}

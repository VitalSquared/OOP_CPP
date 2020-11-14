#include <iostream>
#include <string>
#include "GameView.h"

using namespace std;

GameView::GameView(Field *field, Collector *collector) {
    this->field = field;
    this->collector = collector;
}

void GameView::renderField() {
    if (collector->getDeadState()) {
        clearScreen();
        ifstream deathmsg("robot_has_exploded.txt");
        if (deathmsg.is_open()) {
            while (!deathmsg.eof()) {
                string row;
                getline(deathmsg, row);
                cout << row << endl;
            }
        }
        else {
            cout << "ROBOT HAS EXPLODED" << endl;
        }
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
    int right_offset = legend[0].length();
    for (int i = 1; i < 5; i++)
        if (legend[i].length() > right_offset)
            right_offset = legend[i].length();

    int field_width = width - right_offset - 1;
    while (field_width % ICON_SIZE != 0 && (field_width / ICON_SIZE) % 2 == 0) field_width -= 1;
    field_width -= field_width / ICON_SIZE - 1;
    field_width /= ICON_SIZE;
    int field_screen_width = field_width * ICON_SIZE + field_width;
    int field_height = height - 4;
    while (field_height % ICON_SIZE != 0 && (field_height / ICON_SIZE) % 2 == 0) field_height -= 1;
    field_height -= field_height / ICON_SIZE - 1;
    field_height /= ICON_SIZE;

    int apples_coll_len = apples_collected.length();
    int left_offset1 = (field_screen_width - apples_coll_len) / 2;
    for (int i = 0; i < left_offset1; i++) cout << " ";
    cout << apples_collected;
    for (int i = left_offset1 + apples_coll_len - 1; i < field_screen_width; i++) cout << " ";
    cout << "Legend" << endl;

    int coll_r = collector->getRow();
    int coll_c = collector->getCol();

    int top_r = coll_r - field_height / 2;
    int left_c = coll_c - field_width / 2;

    for (int i = 0; i < 4; i++) {
        for (int icon = 0; icon < ICON_SIZE; icon++) {
            for (int j = 0; j < field_width; j++) {
                cout << getIconFromCell(top_r + i, left_c + j)[icon] << colorDarkGrey + "|";
            }
            cout << " " << legend[i * ICON_SIZE + icon] << endl;
        }
        for (int j = 0; j < field_screen_width; j++) cout << colorDarkGrey + ((j + 1) % (ICON_SIZE + 1) == 0 ? "+" : "-");
        cout << endl;
    }
    for (int i = 4; i < field_height; i++) {
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

const string* GameView::getIconFromCell(int r, int c) {
    if (r == collector->getRow() && c == collector->getCol())
        return COLLECTOR_ICON;
    if (!collector->hasScanned(r, c)) return UNKNOWN_ICON;
    if (r < 0 || c < 0 || c >= field->getCols() || r >= field->getRows())
        return ROCK_ICON;
    Cell cell = field->getCell(r, c);
    switch(cell) {
        case Cell::EMPTY: return EMPTY_ICON;
        case Cell::ROCK: return ROCK_ICON;
        case Cell::BOMB: return BOMB_ICON;
        case Cell::APPLE: return APPLE_ICON;
    }
    return EMPTY_ICON;
}

#ifndef ROBOTS_ROBOT_H
#define ROBOTS_ROBOT_H

#include <iostream>
#include <set>
#include <ctime>
//#include <synchapi.h>
#include "Mode.h"
#include "Field.h"

using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Robot {

};

class Collector : public Robot {
public:
    Collector(Field &field) {
        isDead = false;
        apples = 0;
        srand(time(0));
        r = rand() % field.getRows();
        c = rand() % field.getCols();
        scanned = new set<pair<int, int>>();
        scanned->insert({r, c});
    }
    ~Collector() {
        scanned->clear();
        delete scanned;
        scanned = nullptr;
    }
    void changeMode(Mode *newMode) {

    }
    void move(Direction dir, Field &field) {
        int dr = 0, dc = 0;
        switch(dir) {
            case Direction::UP: dr = -1; break;
            case Direction::DOWN: dr = 1; break;
            case Direction::LEFT: dc = -1; break;
            case Direction::RIGHT: dc = 1; break;
        }
        int new_r = r + dr, new_c = c + dc;
        if (new_r < 0 || new_r >= field.getRows() || new_c < 0 || new_c >= field.getCols()) {
            cout << "I can't go there." << endl;
            //Sleep(2000);
        }
        else if (!hasScanned(new_r, new_c)) {
            cout << "I can't go there." << endl;
            //Sleep(2000);
        }
        else if (field.getCell(new_r, new_c) == Cell::ROCK) {
            cout << "I can't go there." << endl;
            //Sleep(2000);
        }
        else {
            r += dr;
            c += dc;
            if (field.getCell(r, c) == Cell::BOMB) isDead = true;
        }
    }
    void scan() {
        scanned->insert({r, c - 1});
        scanned->insert({r, c + 1});
        scanned->insert({r - 1, c});
        scanned->insert({r + 1, c});
    }
    bool hasScanned(int r_, int c_) {
        return scanned->find({r_, c_}) != scanned->end();
    }
    void grab(Field &field) {
        if (field.getCell(r, c) == Cell::APPLE) {
            apples++;
            field.setCell(r, c, Cell::EMPTY);
        }
        else {
            cout << "There are no apples here." << endl;
            //Sleep(2000);
        }
    }
    int getApples() {
        return apples;
    }
    int getRow() {
        return r;
    }
    int getCol() {
        return c;
    }
    bool getDeadState() {
        return isDead;
    }
private:
    bool isDead;
    size_t apples;
    int r, c;
    set<pair<int, int>> *scanned;
};

class Sapper : public Robot {

};

#endif

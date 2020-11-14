#ifndef ROBOTS_ROBOT_H
#define ROBOTS_ROBOT_H

#include <iostream>
#include <set>
#include <ctime>
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
        pendingMessage = "";
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
        if (new_r < 0 || new_r >= field.getRows() || new_c < 0 || new_c >= field.getCols() ||
                !hasScanned(new_r, new_c) || field.getCell(new_r, new_c) == Cell::ROCK) {
            pendingMessage = "I can't go there.";
        }
        else {
            r = new_r;
            c = new_c;
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
        else pendingMessage = "There are no apples here.";
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

    string retrievePendingMessage() {
        string msg = pendingMessage;
        pendingMessage = "";
        return msg;
    }

private:
    bool isDead;
    int apples;
    int r, c;
    string pendingMessage;
    set<pair<int, int>> *scanned;
};

class Sapper : public Robot {

};

#endif

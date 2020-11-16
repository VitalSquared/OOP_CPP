#ifndef ROBOTS_ROBOT_H
#define ROBOTS_ROBOT_H

#include <iostream>
#include <set>
#include <ctime>
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
        srand(time(nullptr));
        r = rand() % field.getRows();
        c = rand() % field.getCols();
        scanned = new set<pair<int, int>>();
        scanned->insert({r, c});
        this->field = &field;
    }

    ~Collector() {
        scanned->clear();
        delete scanned;
        scanned = nullptr;
    }

    void setNewPosition(int new_r, int new_c) {
        r = new_r;
        c = new_c;
        if (field->getCell(new_r, new_c) == Cell::BOMB) isDead = true;
    }

    bool hasScanned(int r_, int c_) {
        return scanned->find({r_, c_}) != scanned->end();
    }

    void scan() {
        scanned->insert({r, c - 1});
        scanned->insert({r, c + 1});
        scanned->insert({r - 1, c});
        scanned->insert({r + 1, c});
    }

    bool collectApple() {
        if (field->getCell(r, c) == Cell::APPLE) {
            apples++;
            field->setCell(r, c, Cell::EMPTY);
            return true;
        }
        return false;
    }

    set<pair<int,int>> *getScanned() {
        return scanned;
    }

    void addScanned(int r_, int c_) {
        scanned->insert({r_, c_});
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
    int apples;
    int r, c;
    Field *field;
    set<pair<int, int>> *scanned;
};

class Sapper : public Robot {
public:
    Sapper(Field &field, set<pair<int,int>> *collectorScanned) {
        this->field = &field;
        this->collectorScanned = collectorScanned;
        active = false;
    }

    ~Sapper() {}

    void setNewPosition(int new_r, int new_c) {
        if (active) {
            r = new_r;
            c = new_c;
            if (field->getCell(new_r, new_c) == Cell::BOMB) {
                field->setCell(new_r, new_c, Cell::DEFUSED_BOMB);
            }
        }
    }

    void toggleSapper(bool newActive) {
        active = newActive;
        if (active) {
            srand(time(nullptr));
            int i = 0, req = rand() % collectorScanned->size();
            for (auto coord : *collectorScanned) {
                if (i == req) {
                    r = coord.first;
                    c = coord.second;
                    break;
                }
                i++;
            }
            setNewPosition(r, c);
        }
    }

    bool getActive() {
        return active;
    }

    int getRow() {
        return r;
    }

    int getCol() {
        return c;
    }

private:
    bool active;
    int r, c;
    Field *field;
    set<pair<int,int>> *collectorScanned;
};

#endif

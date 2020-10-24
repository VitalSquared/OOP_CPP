#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "Utils.h"

#define ROWS 10
#define COLS 10
#define IDX(R, C) ((R) * (ROWS) + (C))

#define UI_DEAD '.'
#define UI_ALIVE '*'

enum State { DEAD, ALIVE };

class Cell {
public:
    Cell();
    State getState();
    void setState(State newState);
private:
    State state;
};

class Field {
public:
    Field();
    ~Field();
    void makeMove(bool updateUI = true);
    void revertMove();
    State getCell(int i);
    void setCell(int r, int c);
    void clearCell(int r, int c);
    void reset();
    bool load(string& in);

private:
    int moves;
    Cell *field;
    vector<Cell*> history;

    int normalizeRow(int r);
    int normalizeCol(int c);
    void updateUI();
};

#endif

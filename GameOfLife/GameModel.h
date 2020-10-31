#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <string>
#include <vector>

#define ROWS 10
#define COLS 10
#define IDX(R, C) ((R) * (ROWS) + (C))

using namespace std;

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
    void makeMove(bool bUpdateUI = true);
    void revertMove();
    State getCell(int i);
    void setCell(int r, int c, State state);
    void reset();
    bool load(string& in);
    int getMoves();

private:
    int moves;
    Cell *field;
    vector<Cell*> history;

    int normalizeRow(int r);
    int normalizeCol(int c);
};

#endif

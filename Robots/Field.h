#ifndef ROBOTS_FIELD_H
#define ROBOTS_FIELD_H

#include <fstream>
#include <list>

using namespace std;

enum class Cell { EMPTY, ROCK, BOMB, APPLE, DEFUSED_BOMB };

class Field {
public:
    explicit Field(ifstream &file);
    ~Field();
    Cell getCell(int r, int c);
    void setCell(int r, int c, Cell cell);
    int getRows() const;
    int getCols() const;

private:
    int rows;
    int cols;
    Cell *field;
    int getIndex(int r, int c) const;
};

#endif

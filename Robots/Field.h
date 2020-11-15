#ifndef ROBOTS_FIELD_H
#define ROBOTS_FIELD_H

#include <fstream>
#include <list>

using namespace std;

enum class Cell { EMPTY, ROCK, BOMB, APPLE };

class Field {
public:
    Field(ifstream &file);
    ~Field();
    Cell getCell(int r, int c);
    void setCell(int r, int c, Cell cell);
    int getRows();
    int getCols();

private:
    int rows;
    int cols;
    Cell *field;
    int getIndex(int r, int c);
};

#endif

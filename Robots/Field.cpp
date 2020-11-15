#include <iostream>
#include <string>
#include "Field.h"
#include "Utils.h"
#include <queue>
#include <list>
#include <set>

using namespace std;

Field::Field(ifstream &file) {
    rows = 0;
    cols = 0;
    field = nullptr;

    file >> rows >> cols;
    string tmp;
    getline(file, tmp);
    if (rows < 1000 || cols < 1000)
        throw exception();

    field = new Cell[rows * cols];
    for (int r = 0; r < rows; r++) {
        string row;
        getline(file, row);
        trimString(row, "\r");
        if (row.length() != cols) {
            delete [] field;
            field = nullptr;
            throw exception();
        }
        for (int c = 0; c < cols; c++) {
            switch(row[c]) {
                case 'A':
                    field[getIndex(r, c)] = Cell::APPLE;
                    break;
                case 'B':
                    field[getIndex(r, c)] = Cell::BOMB;
                    break;
                case 'R':
                    field[getIndex(r, c)] = Cell::ROCK;
                    break;
                default:
                    field[getIndex(r, c)] = Cell::EMPTY;
                    break;
            }
        }
    }
}

Field::~Field() {
    delete [] field;
    field = nullptr;
}

Cell Field::getCell(int r, int c) {
    if (r < 0 || r >= rows || c < 0 || c >= rows) return Cell::ROCK;
    return field[getIndex(r, c)];
}

void Field::setCell(int r, int c, Cell cell) {
    field[getIndex(r, c)] = cell;
}

int Field::getIndex(int r, int c) {
    return r * cols + c;
}

int Field::getRows() {
    return rows;
}

int Field::getCols() {
    return cols;
}

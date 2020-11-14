#include <iostream>
#include <string>
#include "Field.h"

using namespace std;

Field::Field(ifstream &file) {
    rows = 0;
    cols = 0;
    field = nullptr;

    file >> rows >> cols;
    string tmp;
    getline(file, tmp);
    if (rows < 1000 || cols < 1000)
        throw exception("Invalid file");

    field = new Cell[rows * cols];
    for (int r = 0; r < rows; r++) {
        string row;
        getline(file, row);
        if (row.length() != cols) {
            delete [] field;
            field = nullptr;
            throw exception("Invalid file");
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
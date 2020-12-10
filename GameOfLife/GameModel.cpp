#include <iostream>
#include <fstream>
#include "GameModel.h"

using namespace std;

GameModel::GameModel(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    moves = 0;
    undidMove = false;
    cur_field = new bool[rows * cols];
    prev_field = new bool[rows * cols];
    for (int i = 0; i < rows * cols; i++) cur_field[i] = false;
}

GameModel::~GameModel() {
    delete [] cur_field;
    cur_field = nullptr;

    delete [] prev_field;
    prev_field = nullptr;
}

bool GameModel::invokeCommand(CommandType cmd, const vector<string>& args) {
    int r, c, n;
    switch(cmd) {
        case CommandType::SET:
            r = stoi(args[0]);
            c = stoi(args[1]);
            setCell(r, c, true);
            break;
        case CommandType::CLEAR:
            r = stoi(args[0]);
            c = stoi(args[1]);
            setCell(r, c, false);
            break;
        case CommandType::RESET:
            reset();
            break;
        case CommandType::BACK:
            undoMove();
            break;
        case CommandType::STEP:
            if (args.empty()) n = 1;
            else n = stoi(args[0]);
            for (int i = 0; i < n; i++) makeMove();
            break;
        case CommandType::LOAD:
            load(args[0]);
            break;
        case CommandType::SAVE:
            save(args[0]);
            break;
        default: return false;
    }
    return true;
}

void GameModel::makeMove() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            pair<int, int> neighbours[8] =
                    {
                            {r - 1, c - 1}, {r - 1, c}, {r - 1, c + 1},
                                {r, c - 1},                     {r, c + 1},
                            {r + 1, c - 1}, {r + 1, c}, {r + 1, c + 1}
                    };
            int alive = 0;
            for (auto pair : neighbours) {
                int nr = normalizeRow(pair.first), nc = normalizeCol(pair.second);
                if (cur_field[pairToIndex(nr, nc)]) alive++;
            }

            if(cur_field[pairToIndex(r, c)]) {
                if (alive < 2 || alive > 3) prev_field[pairToIndex(r, c)] = false;
                else prev_field[pairToIndex(r, c)] = true;
            }
            else {
                if (alive == 3) prev_field[pairToIndex(r, c)] = true;
                else prev_field[pairToIndex(r, c)] = false;
            }
        }
    }

    undidMove = false;
    moves++;

    bool* tmp = prev_field;
    prev_field = cur_field;
    cur_field = tmp;
}

void GameModel::undoMove() {
    if (moves == 0 || undidMove) return;

    undidMove = true;
    moves--;

    bool* tmp = cur_field;
    cur_field = prev_field;
    prev_field = tmp;
}

bool GameModel::getCell(int r, int c) const {
    return cur_field[pairToIndex(r, c)];
}

void GameModel::setCell(int r, int c, bool state) {
    cur_field[pairToIndex(r, c)] = state;
}

void GameModel::reset() {
    for (int i = 0; i < rows * cols; i++)
        cur_field[i] = false;
    moves = 0;
}

bool GameModel::load(const string &fl_name) {
    ifstream file(fl_name);
    if (!file.is_open()) return false;
    string in;
    getline(file, in);
    file.close();

    if (in.size() != rows * cols) return false;

    for (int i = 0; i < rows * cols; i++) {
        if (in[i] != '.' && in[i] != '*') return false;
    }

    for (int i = 0; i < rows * cols; i++) {
        cur_field[i] = in[i] == '*';
    }

    moves = 0;
    return true;
}

bool GameModel::save(const string &fl_name) {
    ofstream file(fl_name);
    if (!file.is_open()) return false;
    for (int i = 0; i < rows * cols; i++) {
        file << (cur_field[i] ? '*' : '.');
    }
    file.close();
    return true;
}

int GameModel::getMoves() const {
    return moves;
}

int GameModel::normalizeRow(int r) const {
    while (r < 0) r += rows;
    while (r >= rows) r -= rows;
    return r;
}

int GameModel::normalizeCol(int c) const {
    while (c < 0) c += rows;
    while (c >= rows) c -= rows;
    return c;
}

int GameModel::pairToIndex(int r, int c) const {
    return r * cols + c;
}

ostream& operator<<(ostream& stream, const GameModel& game) {
    for (int r = 0; r < game.rows; r++) {
        stream << game.rows - 1 - r << " ";
        for (int c = 0; c < game.cols; c++) {
            bool state = game.getCell(r, c);
            stream << (state ? '*' : '.') << " ";
        }
        stream << endl;
    }
    stream << "  ";
    for (char i = 'A'; i < 'A' + game.cols; i++) cout << i << " ";
    stream << endl;
    return stream;
}
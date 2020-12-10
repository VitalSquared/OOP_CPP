#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <string>
#include <vector>
#include "CommandParser.h"

using namespace std;

class GameModel {
public:
    GameModel(int rows, int cols);
    ~GameModel();

    bool invokeCommand(CommandType cmd, const vector<string>& args);
    int getMoves() const;

    friend ostream& operator<<(ostream& stream, const GameModel& game);

private:
    int rows;
    int cols;
    int moves;
    bool undidMove;
    bool *cur_field;
    bool *prev_field;

    void makeMove();
    void undoMove();

    bool getCell(int r, int c) const;
    void setCell(int r, int c, bool state);
    void reset();

    bool load(const string& fl_name);
    bool save(const string& fl_name);

    int normalizeRow(int r) const;
    int normalizeCol(int c) const;

    int pairToIndex(int r, int c) const;
};

#endif

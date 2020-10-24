#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define ROWS 10
#define COLS 10
#define IDX(R, C) ((R) * (ROWS) + (C))

#define UI_DEAD '.'
#define UI_ALIVE '*'

class Cell {
public:
    enum State { DEAD, ALIVE };
    Cell() { state = DEAD; }
    State getState() { return state; }
    void setState(State newState) { state = newState; }
private:
    State state;
};

class Field {
public:
    Field() {
        moves = 0;
        field = new Cell[ROWS * COLS];
        updateUI();
    }

    ~Field() {
        delete field;
    }

    void makeMove(bool update = true) {
        Cell *new_field = new Cell[ROWS * COLS];
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                pair<int, int> neighbours[8] =
                    {
                        {r - 1, c - 1}, {r - 1, c}, {r - 1, c + 1},
                        {r, c - 1},  {r, c + 1},
                        {r + 1, c - 1}, {r + 1, c}, {r + 1, c + 1}
                    };
                int alive = 0;
                for (auto pair : neighbours) {
                    int nr = getNormalRow(pair.first), nc = getNormalCol(pair.second);
                    if (field[IDX(nr, nc)].getState() == Cell::ALIVE) alive++;
                }
                switch(field[IDX(r, c)].getState()) {
                    case Cell::ALIVE:
                        if (alive < 2 || alive > 3) new_field[IDX(r, c)].setState(Cell::DEAD);
                        else new_field[IDX(r, c)].setState(field[IDX(r, c)].getState());
                        break;
                    case Cell::DEAD:
                        if (alive == 3) new_field[IDX(r, c)].setState(Cell::ALIVE);
                        else new_field[IDX(r, c)].setState(field[IDX(r, c)].getState());
                        break;
                }
            }
        }
        moves++;
        history.push_back(field);
        field = new_field;
        if (update) updateUI();
    }

    void revertMove() {
        if (moves == 0 || history.empty()) return;
        moves--;
        delete [] field;
        field = history.back();
        history.pop_back();
        updateUI();
    }

    Cell::State getCell(int i) {
        return field[i].getState();
    }

    void setCell(int r, int c) {
        field[IDX(r, c)].setState(Cell::ALIVE);
        updateUI();
    }

    void clearCell(int r, int c) {
        field[IDX(r, c)].setState(Cell::DEAD);
        updateUI();
    }

    void reset() {
        for (int i = 0; i < ROWS * COLS; i++)
            field[i].setState(Cell::DEAD);
        moves = 0;
        history.clear();
        updateUI();
    }

    void load(string in) {
        for (int i = 0; i < ROWS * COLS; i++)
            field[i].setState(in[i] == UI_DEAD ? Cell::DEAD : Cell::ALIVE);
        moves = 0;
        history.clear();
        updateUI();
    }

private:
    int moves;
    Cell *field;
    vector<Cell*> history;

    int getNormalRow(int r) {
        while (r < 0) r += ROWS;
        while (r >= ROWS) r -= ROWS;
        return r;
    }

    int getNormalCol(int c) {
        while (c < 0) c += ROWS;
        while (c >= ROWS) c -= ROWS;
        return c;
    }

    void updateUI() {
        system("cls");
        for (int r = 0; r < ROWS; r++) {
            cout << (char) ('J' - r) << " ";
            for (int c = 0; c < COLS; c++) {
                Cell::State state = field[IDX(r, c)].getState();
                switch(state) {
                    case Cell::ALIVE: cout << UI_ALIVE; break;
                    case Cell::DEAD: cout << UI_DEAD; break;
                }
            }
            cout << endl;
        }
        cout << "  ";
        for (int i = 0; i < 10; i++) cout << i;
        cout << endl;
        cout << "Moves made: " << moves << endl;
    }
};

class CommandParser {
public:
    enum ParseResult { OK, HELP, INVALID_CMD, INVALID_ARG, NO_FILE };

    CommandParser(Field *field) {
        this->field = field;
    }

    ParseResult parseCommand(string cmd) {
        if (cmd == "help") return HELP;
        else if (cmd == "reset") {
            field->reset();
        }
        else if (cmd.substr(0, 3) == "set" && cmd[3] == ' ' && cmd.length() == 6) {
            int r = 'J' - cmd[4], c = cmd[5] - '0';
            if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return INVALID_ARG;
            field->setCell(r, c);
        }
        else if (cmd.substr(0, 5) == "clear" && cmd[5] == ' ' && cmd.length() == 8) {
            int r = 'J' - cmd[6], c = cmd[7] - '0';
            if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return INVALID_ARG;
            field->clearCell(r, c);
        }
        else if (cmd == "step" || (cmd.substr(0, 4) == "step" && cmd[4] == ' ')) {
            int n = 1;
            if (cmd.length() >= 6) n = stoi(cmd.substr(5));
            if (n <= 0) return INVALID_ARG;
            for (int i = 0; i < n - 1; i++) field->makeMove(false);
            field->makeMove();
        }
        else if (cmd == "back") {
            field->revertMove();
        }
        else if (cmd.substr(0, 4) == "save" && cmd[4] == ' ' && cmd[5] == '\"') {
            string fl_name = cmd.substr(6);
            if (fl_name.length() == 0) return INVALID_ARG;
            fl_name.pop_back();
            if (fl_name.length() == 0) return INVALID_ARG;
            ofstream sv_file(fl_name + ".txt");
            for (int i = 0; i < ROWS * COLS; i++)
                sv_file << (field->getCell(i) == Cell::DEAD ? UI_DEAD : UI_ALIVE);
            sv_file.close();
        }
        else if (cmd.substr(0, 4) == "load" && cmd[4] == ' ' && cmd[5] == '\"') {
            string fl_name = cmd.substr(6);
            if (fl_name.length() == 0) return INVALID_ARG;
            fl_name.pop_back();
            if (fl_name.length() == 0) return INVALID_ARG;
            ifstream ld_file(fl_name + ".txt");
            if (!ld_file.is_open()) return NO_FILE;
            string in;
            getline(ld_file, in);
            field->load(in);
        }
        else return INVALID_CMD;
        return OK;
    }

private:
    Field *field;
};

void printHelp() {
    cout << "List of available commands:" << endl;
    cout << "help - show this list" << endl;
    cout << "exit - exit application" << endl;
    cout << "reset - clear field and reset moves" << endl;
    cout << R"(set XY - 'A' <= X <= 'J', 0 <= Y <= 9, set cell XY to ALIVE state)" << endl;
    cout << R"(clear XY - 'A' <= X <= 'J', 0 <= Y <= 9, set cell XY to DEAD state)" << endl;
    cout << "step [N] - cycle game N times forward (1, if N not specified)" << endl;
    cout << "back - cycle game 1 time backward" << endl;
    cout << R"(save "filename" - save game state (no history of moves))" << endl;
    cout << R"(load "filename" - load game from file (no history of moves))" << endl;
}

int main() {
    Field field;
    CommandParser cmdParser(&field);
    string cmd;
    getline(cin, cmd);
    while (cmd != "exit") {
        CommandParser::ParseResult result = cmdParser.parseCommand(cmd);
        switch(result) {
            case CommandParser::OK: break;
            case CommandParser::HELP: printHelp(); break;
            case CommandParser::INVALID_CMD: cout << "Invalid command. Use help to see available commands" << endl; break;
            case CommandParser::INVALID_ARG: cout << "Invalid argument(s). Use help to see available commands" << endl; break;
            case CommandParser::NO_FILE: cout << "File doesn't exist" << endl; break;
        }
        getline(cin, cmd);
    }
    return 0;
}

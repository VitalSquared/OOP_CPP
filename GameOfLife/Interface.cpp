#include <iostream>
#include "Interface.h"

using namespace std;

void Interface::updateUI(Field &field) {
    clearUI();
    for (int r = 0; r < ROWS; r++) {
        cout << ROWS - 1 - r << " ";
        for (int c = 0; c < COLS; c++) {
            State state = field.getCell(IDX(r, c));
            switch(state) {
                case ALIVE: cout << UI_ALIVE; break;
                case DEAD: cout << UI_DEAD; break;
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << "  ";
    for (char i = 'A'; i < 'A' + COLS; i++) cout << i << " ";
    cout << endl;
    cout << "Moves made: " << field.getMoves() << endl;
}

void Interface::clearUI() {
    system("cls");
}
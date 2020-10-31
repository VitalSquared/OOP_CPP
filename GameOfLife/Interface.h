#ifndef INTERFACE_H
#define INTERFACE_H

#include "GameModel.h"

#define UI_DEAD '.'
#define UI_ALIVE '*'

class Interface {
public:
    static void updateUI(Field &field);
private:
    static void clearUI();
};

#endif

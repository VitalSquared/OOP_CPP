#ifndef ROBOTS_SAPPER_H
#define ROBOTS_SAPPER_H

#include <iostream>
#include <set>
#include <ctime>
#include "Field.h"
#include "Utils.h"
#include "Robot.h"

class Sapper : public Robot {
public:
    Sapper(Field &field, set<pair<int,int>> *collectorScanned);
    ~Sapper() override = default;

    void setNewPosition(pair<int, int> new_pos) override;
    pair<int, int> getPosition() override;

    void toggleSapper(bool newActive);
    bool getActive() const;

private:
    bool active;
    int pos_r, pos_c;
    Field *field;
    set<pair<int,int>> *collectorScanned;
};

#endif

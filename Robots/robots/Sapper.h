#ifndef ROBOTS_SAPPER_H
#define ROBOTS_SAPPER_H

#include <iostream>
#include <set>
#include <ctime>
#include "Field.h"
#include "Utils.h"
#include "Robot.h"
#include "Collector.h"

class Sapper : public Robot {
public:
    Sapper(Field &field, Collector *collector);
    ~Sapper() override = default;

    void setNewPosition(pair<int, int> new_pos) override;
    pair<int, int> getPosition() override;
    bool isActive() const override;

    void toggleSapper(bool newActive);

private:
    bool active;
    int pos_r, pos_c;
    Field *field;
    Collector *collector;

    pair<int, int> findSuitablePos() override;
};

#endif

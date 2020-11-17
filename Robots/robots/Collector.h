#ifndef ROBOTS_COLLECTOR_H
#define ROBOTS_COLLECTOR_H

#include <iostream>
#include <set>
#include <ctime>
#include "Field.h"
#include "Utils.h"
#include "Robot.h"

using namespace std;

class Collector : public Robot {
public:
    explicit Collector(Field &field);
    ~Collector() override;

    void setNewPosition(pair<int, int> new_pos) override;
    pair<int, int> getPosition() override;

    bool hasScanned(int r_, int c_);
    void scan();
    bool collectApple();
    set<pair<int,int>> *getScanned();
    int getApples() const;
    bool getDeadState() const;

private:
    bool isDead;
    int apples;
    int pos_r, pos_c;
    Field *field;
    set<pair<int, int>> *scanned;
};

#endif

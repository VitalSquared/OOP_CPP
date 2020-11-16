#ifndef ROBOTS_ROBOT_H
#define ROBOTS_ROBOT_H

#include <iostream>
#include <set>
#include <ctime>
#include "Field.h"

using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Robot {
public:
    virtual ~Robot() = default;
    virtual void setNewPosition(pair<int, int> new_pos) = 0;
    virtual pair<int, int> getPosition() = 0;
};

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

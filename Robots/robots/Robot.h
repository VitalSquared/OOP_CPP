#ifndef ROBOTS_ROBOT_H
#define ROBOTS_ROBOT_H

#include <iostream>

using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Robot {
public:
    virtual ~Robot() = default;
    virtual void setNewPosition(pair<int, int> new_pos) = 0;
    virtual pair<int, int> getPosition() = 0;
};

#endif

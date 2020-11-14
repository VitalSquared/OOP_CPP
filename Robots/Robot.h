#ifndef ROBOTS_ROBOT_H
#define ROBOTS_ROBOT_H

#include "Mode.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Robot {

};

class Collector : public Robot {
public:
    Collector();
    void changeMode(Mode *newMode) {
        mode = newMode;
    }
    void move(Direction dir) {

    }
private:
    Mode *mode;
};

class Sapper : public Robot {

};

#endif //ROBOTS_ROBOT_H

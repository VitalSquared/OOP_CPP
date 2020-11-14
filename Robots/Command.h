#ifndef ROBOTS_COMMAND_H
#define ROBOTS_COMMAND_H

#include "Robot.h"
#include "Mode.h"

class Command {
public:
    Command(Collector *robot) {
        this->robot = robot;
    }
    virtual int execute() = 0;
protected:
    Collector *robot;
};

class ManualModeCommand : public Command {
public:
    int execute() override = 0;
private:
};

class MoveCommand : public ManualModeCommand {
public:
    MoveCommand();
    void setDirection(Direction new_dir) {
        dir = new_dir;
    }
    int execute() override {
        robot->move(dir);
        return 0;
    }
private:
    Direction dir;
};

class GrabCommand : public ManualModeCommand {

};

class ScanCommand : public ManualModeCommand {

};

class SapperCommand : public ManualModeCommand {

};

class ChangeModeCommand : public Command {
public:
    ChangeModeCommand();
    void setMode(Mode *new_mode) {
        this->mode = new_mode;
    }
    int execute() override {
        robot->changeMode(mode);
        return 0;
    }
private:
    Mode *mode;
};

#endif //ROBOTS_COMMAND_H

#ifndef ROBOTS_COMMAND_H
#define ROBOTS_COMMAND_H

#include "Robot.h"
#include "Mode.h"

enum class ModeType { MANUAL, SCAN, AUTO };

class Command {
public:
    virtual ~Command() = default;
    virtual int execute() = 0;
};

class ManualModeCommand : public Command {
public:
    virtual ~ManualModeCommand() = default;
    int execute() override = 0;
private:
};

class MoveCommand : public ManualModeCommand {
public:
    MoveCommand(Mode *mode, Direction dir) {
        this->mode = mode;
        this->dir = dir;
    }
    int execute() override {
        mode->move(dir);
        return 0;
    }
private:
    Direction dir;
    Mode *mode;
};

class GrabCommand : public ManualModeCommand {
public:
    GrabCommand(Mode *mode) {
        this->mode = mode;
    }
    int execute() override {
        mode->grab();
        return 0;
    }
private:
    Mode *mode;
};

class ScanCommand : public ManualModeCommand {
public:
    ScanCommand(Mode *mode) {
        this->mode = mode;
    }
    int execute() override {
        mode->scan();
        return 0;
    }
private:
    Mode *mode;
};

class SapperCommand : public ManualModeCommand {
public:
    SapperCommand(Mode *mode) {
        this->mode = mode;
    }
    int execute() override {
        return 0;
    }
private:
    Mode *mode;
};

class ChangeModeCommand : public Command {
public:
    ChangeModeCommand(Mode **mode, ModeType type, Field *field, Collector *collector, ConsoleView *gameView) {
        this->mode = mode;
        this->type = type;
        this->field = field;
        this->collector = collector;
        this->gameView = gameView;
    }
    int execute() override {
        delete *mode;
        switch (type) {
            case ModeType::MANUAL:
                *mode = new ManualMode(field, collector, gameView);
                break;
            case ModeType::SCAN:
                *mode = new ScanMode(field, collector, gameView);
                break;
            case ModeType::AUTO:
                *mode = new AutoMode(field, collector, gameView);
                break;
        }
        return 0;
    }
private:
    ModeType type;
    Mode **mode;
    Field *field;
    Collector *collector;
    ConsoleView *gameView;
};

#endif

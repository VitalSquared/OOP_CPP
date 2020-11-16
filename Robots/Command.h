#ifndef ROBOTS_COMMAND_H
#define ROBOTS_COMMAND_H

#include "Robot.h"
#include "Mode.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class ManualModeCommand : public Command {
public:
    ~ManualModeCommand() override = default;
    void execute() override = 0;
};

class MoveCommand : public ManualModeCommand {
public:
    MoveCommand(Mode *mode, Direction dir);
    void execute() override;
private:
    Direction dir;
    Mode *mode;
};

class GrabCommand : public ManualModeCommand {
public:
    GrabCommand(Mode *mode) ;
    void execute() override;
private:
    Mode *mode;
};

class ScanCommand : public ManualModeCommand {
public:
    ScanCommand(Mode *mode);
    void execute() override;
private:
    Mode *mode;
};

class SapperCommand : public ManualModeCommand {
public:
    SapperCommand(Mode *mode, bool enable);
    void execute() override;
private:
    Mode *mode;
    bool enable;
};

class ChangeModeCommand : public Command {
public:
    ChangeModeCommand(Mode **mode, Mode *new_mode);
    void execute() override;
private:
    Mode **mode;
    Mode *new_mode;
};

#endif

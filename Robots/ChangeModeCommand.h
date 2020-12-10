#ifndef ROBOTS_CHANGE_MODE_COMMAND_H
#define ROBOTS_CHANGE_MODE_COMMAND_H

#include "ICommand.h"
#include "IMode.h"


class ChangeModeCommand : public ICommand {
public:
    ChangeModeCommand(IMode** mode);
    ~ChangeModeCommand() override = default;

    bool validateArgs(std::vector<std::string> args) override;
    bool execute(std::vector<std::string> args) override;

private:
    IMode** mode;
};

#endif

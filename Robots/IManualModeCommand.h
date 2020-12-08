#ifndef ROBOTS_IMANUALMODECOMMAND_H
#define ROBOTS_IMANUALMODECOMMAND_H

#include "ICommand.h"

class IManualModeCommand : public ICommand {
public:
    IManualModeCommand(std::map<IRobot*, std::pair<int, int>>* _robots, int* _id, Repeater* _repeater) {
        this->robots = _robots;
        this->activeCollectorID = _id;
        this->repeater = _repeater;
    }
    ~IManualModeCommand() override = default;

    CommandType validateArgs(std::vector<std::string> args) override = 0;
    bool execute(std::vector<std::string> args) override = 0;

protected:
    std::map<IRobot*, std::pair<int, int>>* getRobots() { return robots; }
    IRobot* getActiveCollector() {
        for (auto robot : *robots) {
            if (robot.first->getRobotID().second == *activeCollectorID) {
                return robot.first;
            }
        }
        return nullptr;
    }
    int* getActiveCollectorID() { return activeCollectorID; }
    Repeater* getRepeater() { return repeater; }

private:
    std::map<IRobot*, std::pair<int, int>>* robots;
    int* activeCollectorID;
    Repeater* repeater;
};

#endif

#ifndef ROBOTS_MANUAL_MODE_H
#define ROBOTS_MANUAL_MODE_H

#include "Mode.h"
#include "Collector.h"
#include "Sapper.h"
#include "ConsoleView.h"
#include "Utils.h"

class ManualMode : public Mode {
public:
    ManualMode(Field *field, Collector *collector, Sapper *sapper, ConsoleView *gameView);
    ~ManualMode() override = default;
    void move(Direction dir) override;
    void grab() override;
    void scan() override;
    void toggleSapper(bool enable) override;
    string getPendingMessage() override;

private:
    string pendingMessage;
    Field *field;
    Collector *collector;
    Sapper *sapper;
    ConsoleView *gameView;

    bool validateCell(int r, int c, const set<Cell>& canWalkOn) override;
};

#endif

#ifndef ROBOTS_AUTO_MODE_H
#define ROBOTS_AUTO_MODE_H

#include "Mode.h"
#include "Field.h"
#include "Collector.h"
#include "Sapper.h"
#include "ConsoleView.h"
#include "Utils.h"

class AutoMode : public Mode {
public:
    AutoMode(Field *field, Collector *collector, Sapper *sapper, ConsoleView *gameView);
    ~AutoMode() override = default;
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

    void startAutoCollecting();
    bool validateCell(int r, int c, Cell ignore) override;
    bool findClosestPoint(set<pair<int,int>> *scanned, set<pair<int,int>>& unreachable, int& rr, int& cr, int &rp, int &cp, Cell point);
};

#endif

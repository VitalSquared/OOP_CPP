#ifndef ROBOTS_SCAN_MODE_H
#define ROBOTS_SCAN_MODE_H

#include "Mode.h"
#include "Collector.h"
#include "ConsoleView.h"
#include "Utils.h"

class ScanMode : public Mode {
public:
    ScanMode(Field *field, Collector *collector, Sapper *sapper, ConsoleView *gameView, int n);
    ~ScanMode() override = default;
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

    void startAutoScanning(int n);
    bool validateCell(int r, int c, const set<Cell>& canWalkOn) override;
};

#endif

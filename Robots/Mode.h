#ifndef ROBOTS_MODE_H
#define ROBOTS_MODE_H

#include <vector>
#include "ConsoleView.h"
#include "Robot.h"
#include "Field.h"

using namespace std;

class Mode {
public:
    virtual ~Mode() = default;
    virtual void move(Direction dir) = 0;
    virtual void grab() = 0;
    virtual void scan() = 0;
    virtual void toggleSapper(bool enable) = 0;
    virtual string getPendingMessage() = 0;

private:
    virtual bool validateCell(int r, int c, Cell ignore) = 0;

protected:
    vector<pair<int,int>> buildPath(int rs, int cs, int rf, int cf, Cell ignore = Cell::EMPTY);
};

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

    bool validateCell(int r, int c, Cell ignore) override;
};

class ScanMode : public Mode {
public:
    ScanMode(Field *field, Collector *collector, ConsoleView *gameView, int n);
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
    ConsoleView *gameView;

    void startAutoScanning(int n);
    bool validateCell(int r, int c, Cell ignore) override;
};

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

#ifndef ROBOTS_MODE_H
#define ROBOTS_MODE_H

#include <list>
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
    virtual void startAutoScanning(int n) = 0;
    virtual string getPendingMessage() = 0;
    virtual string getModeName() = 0;
private:
    virtual bool validateCell(int r, int c) = 0;

protected:
    list<pair<int,int>> buildPath(int rs, int cs, int rf, int cf);
};

class ManualMode : public Mode {
public:
    ManualMode(Field *field, Collector *collector, ConsoleView *gameView);
    ~ManualMode() override = default;
    void move(Direction dir) override;
    void grab() override;
    void scan() override;
    void startAutoScanning(int n) override;
    string getPendingMessage() override;
    string getModeName() override;
private:
    string pendingMessage;
    Field *field;
    Collector *collector;
    ConsoleView *gameView;

    bool validateCell(int r, int c) override;
};

class ScanMode : public Mode {
public:
    ScanMode(Field *field, Collector *collector, ConsoleView *gameView);
    ~ScanMode() override = default;
    void move(Direction dir) override;
    void grab() override;
    void scan() override;
    void startAutoScanning(int n) override;
    string getPendingMessage() override;
    string getModeName() override;
private:
    string pendingMessage;
    Field *field;
    Collector *collector;
    ConsoleView *gameView;

    bool validateCell(int r, int c) override;
};

class AutoMode : public Mode {
public:
    AutoMode(Field *field, Collector *collector, ConsoleView *gameView);
    ~AutoMode() override = default;
    void move(Direction dir) override;
    void grab() override;
    void scan() override;
    void startAutoScanning(int n) override;
    string getPendingMessage() override;
    string getModeName() override;
private:
    string pendingMessage;
    Field *field;
    Collector *collector;
    ConsoleView *gameView;

    void startAutoCollecting();
    bool validateCell(int r, int c) override;
};

#endif

#ifndef ROBOTS_MODE_H
#define ROBOTS_MODE_H

#include <vector>
#include <queue>
#include <set>
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

#endif

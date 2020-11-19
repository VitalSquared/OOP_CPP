#ifndef ROBOTS_MODE_H
#define ROBOTS_MODE_H

#include <vector>
#include <queue>
#include <set>
#include "Robot.h"
#include "Field.h"
#include "Utils.h"

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
    virtual bool validateCell(int r, int c, const set<Cell>& canWalkOn) = 0;

protected:
    vector<pair<int,int>> buildPath(int rs, int cs, int rf, int cf, const set<Cell>& canWalkOn);
    bool findClosestPoint(Field *field,set<pair<int,int>> *scanned, set<pair<int,int>>& unreachable,
                          int& rr, int& cr, int &rp, int &cp, Cell point);
};

#endif

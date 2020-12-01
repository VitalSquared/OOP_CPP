#ifndef ROBOTS_IGAMEVIEW_H
#define ROBOTS_IGAMEVIEW_H

class IGameView {
public:
    virtual ~IGameView() = default;
    virtual void run() = 0;
};

#endif

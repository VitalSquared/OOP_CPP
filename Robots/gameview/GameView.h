#ifndef ROBOTS_GAME_VIEW_H
#define ROBOTS_GAME_VIEW_H

class GameView {
public:
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual void renderField() = 0;
};

#endif

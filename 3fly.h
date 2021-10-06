#ifndef FLY_H
#define FLY_H

#include "3brick.h"

class Fly : public Brick2
{
public:
    Fly(int, int, bool);
    ~Fly();
    int getMoveCount(){ return moveCount; }
    void setmoveCount(int mc){ this->moveCount = mc; }
    bool getUp(){ return up; }
    void setUp(bool upDown){ this->up = upDown; }

private:
    int moveCount = 37;
    bool up = true;

};

#endif // FLY_H

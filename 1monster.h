#ifndef MONSTER_H
#define MONSTER_H

#include "1brick.h"

class Monster : public Brick
{
public:
    Monster(int, int);
    static int currentFrame;
    void accept(PaintVisitor *p){ p->visitPixmap(this); }
    ~Monster();
};

#endif // MONSTER_H

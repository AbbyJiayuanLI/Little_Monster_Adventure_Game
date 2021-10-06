#ifndef FLAME2_H
#define FLAME2_H

#include "3brick.h"

class Flame2 : public Brick2
{
public:
    Flame2(int, int);
    static int currentFrame;
    void accept(PaintVisitor2 *p){ p->visitPixmap(this); }


};

#endif // FLAME2_H

#ifndef MOVEFLOOR_H
#define MOVEFLOOR_H
#include "3brick.h"
class MoveFloor : public Brick2
{
public:
    MoveFloor(int, int);
    static int currentFrame;
    void accept(PaintVisitor2 *p){ p->visitPixmap(this); }
    ~MoveFloor();
};

#endif // MOVEFLOOR_H

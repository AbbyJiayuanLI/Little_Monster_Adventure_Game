#ifndef MOVEVERTICAL_H
#define MOVEVERTICAL_H
#include "3brick.h"
class MoveVertical : public Brick2
{
public:
    MoveVertical(int, int);
    static int currentFrame;
    void accept(PaintVisitor2 *p){ p->visitPixmap(this); }
    ~MoveVertical();
};

#endif // MOVEVERTICAL_H

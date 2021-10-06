#ifndef BACKGROUND2_H
#define BACKGROUND2_H

#include "3brick.h"

class Background2 : public Brick2
{
public:
    Background2(int, int);
    ~Background2();
    void moveBrick();
};

#endif // BACKGROUND2_H

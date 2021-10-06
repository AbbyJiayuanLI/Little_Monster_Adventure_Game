#ifndef BLOOD2_H
#define BLOOD2_H

#include "3brick.h"
class Blood2 : public Brick2
{
public:
    Blood2(int, int);
    bool getStopBlood(){ return show; }
    void setStopBlood(bool show){ this->show = show; }

    bool show = false;
};

#endif // BLOOD2_H

#ifndef SHIELD_VISUAL_H
#define SHIELD_VISUAL_H

#include "1brick.h"

class shield_visual : public Brick
{
public:
    shield_visual(int x, int y, QString);
    ~shield_visual();
    inline void setShield_S(bool is){ this->shield_s = is; }
    inline bool getShield_S(){ return shield_s; }
//    bool getIsDestroyed() {return isDestroyed; }
//    bool setIsDestroyed(bool x) {this->isDestroyed = x; }
//private:
//    bool isDestroyed = true;
    bool shield_s;

};

#endif // SHIELD_VISUAL_H

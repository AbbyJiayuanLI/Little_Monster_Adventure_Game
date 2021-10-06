#ifndef ROLE2_H
#define ROLE2_H

#include <QDebug>
#include "3player.h"

class Role2 : public Player2
{
public:

    Role2(int, int);
    ~Role2();
    int getGoldNumber(){ return goldNumber; }
    void setGoldNumber(int goldNumber){ this->goldNumber = goldNumber; }
    bool intersectTop(QRect );
    bool intersectBottom(QRect );
    bool intersectRight(QRect );
    bool intersectLeft(QRect );
    bool getIsFlying(){ return isFlying; }
    void setIsFlying(int flying){ this->isFlying = flying; }
    inline bool getIsHurted(){ return isHurted; }
    inline void setIsHurted(bool hurt){ this->isHurted = hurt; }
    int getGoldNumberWhenFly(){ return goldNumberWhenfly; }
    void setGoldNumberWhenFly(int goldNumber){ this->goldNumberWhenfly = goldNumber; }


private:
    int goldNumber;
    int goldNumberWhenfly;
    int flying = false;
    bool isFlying = false;
    bool isHurted = false;
    bool hurt = false;

};

#endif // ROLE2_H

#ifndef ROLE_H
#define ROLE_H

#include <QDebug>
#include "1player.h"

class Role : public Player
{
public:

    Role(int, int);
    ~Role();
    int getGoldNumber(){ return goldNumber; }
    int getBulletNumber(){ return bulletNumber; }
    int getWalkedDistance(){ return walkedDistance; }
    void setGoldNumber(int goldNumber){ this->goldNumber = goldNumber; }
    void setBulletNumber(int bulletNumber){ this->bulletNumber = bulletNumber; }
    void setWalkedDistance(int walkedDistance){ this->walkedDistance = walkedDistance; }
    bool intersectTop(QRect );
    bool intersectBottom(QRect );
    bool intersectRight(QRect );
    bool intersectLeft(QRect );
    bool getIsLittle(){ return isLittle; }
    bool getIsShielded(){ return isShielded; }

    void setIsLittle(bool little){ this->isLittle = little; }
    void setIsShielded(bool shield){ this->isShielded = shield; }

    inline bool getIsHurted(){ return isHurted; }
    inline void setIsHurted(bool hurt){ this->isHurted = hurt; }
    int getGoldNumberWhenMushroom(){ return goldNumberWhenMushroom; }
    void setGoldNumberWhenMushroom(int goldNumber){ this->goldNumberWhenMushroom = goldNumber; }


private:
    int goldNumber;
    int bulletNumber;
    int walkedDistance;
    int goldNumberWhenMushroom;
    bool isLittle = false;
    bool isShielded = false;
    int isJeted = 0;
    bool isHurted = false;
    bool hurt = false;

};

#endif // ROLE_H

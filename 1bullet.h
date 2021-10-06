#ifndef BULLET_H
#define BULLET_H

#include "1brick.h"

class Bullet : public Brick
{
public:
    Bullet(int, int, QString);
    ~Bullet();
    void setShow(bool show){ this->show = show; }
    bool getShow(){ return show; }
    inline void setBulletR(bool is){ this->bulletR = is; }
    inline bool getBulletR(){ return bulletR; }
private:
    bool show = false;
    bool bulletR;
};


#endif // BULLET_H

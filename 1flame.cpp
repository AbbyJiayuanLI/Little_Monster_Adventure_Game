#include "1flame.h"

Flame::Flame(int x, int y) : Brick(x,y)
{
    this->setSprite(QString(":land/fire.png"));
    this->rect = QRect(x, y-10, getSprite().width()/9, getSprite().height());
}


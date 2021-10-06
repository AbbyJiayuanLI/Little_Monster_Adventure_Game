#include "3flame.h"

Flame2::Flame2(int x, int y) : Brick2(x,y)
{
    this->setSprite(QString(":magma/fire.png"));
    this->rect = QRect(x, y-10, getSprite().width()/9, getSprite().height());
}


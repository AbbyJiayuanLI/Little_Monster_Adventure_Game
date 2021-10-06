#include "3movevertical.h"
#include <iostream>

MoveVertical::MoveVertical(int x, int y): Brick2(x,y)
{
    this->setSprite(QString(":magma/movebrick.png"));
    this->rect = QRect(x, y+5, getSprite().width(), getSprite().height());
}

MoveVertical::~MoveVertical(){
    std::cout <<"move floor deleted.";
}

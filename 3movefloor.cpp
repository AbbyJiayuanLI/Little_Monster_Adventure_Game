#include "3movefloor.h"
#include <iostream>

MoveFloor::MoveFloor(int x, int y): Brick2(x,y)
{
    this->setSprite(QString(":magma/movebrick.png"));
    this->rect = QRect(x, y+5, getSprite().width()/3, getSprite().height());
}

MoveFloor::~MoveFloor(){
    std::cout <<"move floor deleted.";
}

#include "1monster.h"
#include <iostream>

Monster::Monster(int x, int y) : Brick(x,y)
{
    this->setSprite(QString(":land/dark_eater.png"));
    this->rect = QRect(x, y+5, getSprite().width()/3, getSprite().height());
}

Monster::~Monster(){
    std::cout << "Dark Eater deleted";
}

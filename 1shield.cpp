#include "1shield.h"
#include <iostream>

Shield::Shield(int x, int y ) : Brick(x,y, ":land/shield.png")
{
    this->sprite = QPixmap(":land/shield.png");
    this->setRect(QRect(x, y, sprite.width(), sprite.height()));
}

Shield::~Shield()
{
     std::cout << ("Shield deleted\n");
}

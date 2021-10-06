#include "1gold.h"
#include <iostream>

Gold::Gold(int x, int y ) : Brick(x,y, ":land/gold_sprites.png")
{
    this->sprite = QPixmap(":land/gold_sprites.png");
    this->setRect(QRect(x, y, sprite.width()/3, sprite.height()));
}

Gold::~Gold()
{
     std::cout << ("Gold deleted\n");
}

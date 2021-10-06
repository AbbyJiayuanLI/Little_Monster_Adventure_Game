#include "3gold.h"
#include <iostream>

Gold2::Gold2(int x, int y ) : Brick2(x,y, ":magma/gold_sprites.png")
{
    this->sprite = QPixmap(":magma/gold_sprites.png");
    this->setRect(QRect(x, y, sprite.width()/3, sprite.height()));
}

Gold2::~Gold2()
{
     std::cout << ("Gold deleted\n");
}

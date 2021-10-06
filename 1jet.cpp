#include "1jet.h"
#include <iostream>

Jet::Jet(int x, int y ) : Brick(x,y, ":land/jet.png")
{
    this->sprite = QPixmap(":land/jet.png");
    this->setRect(QRect(x, y, sprite.width(), sprite.height()));
}

Jet::~Jet()
{
     std::cout << ("Jet deleted\n");
}

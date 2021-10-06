#include "3background.h"
#include <iostream>


Background2::Background2(int x, int y ) : Brick2(x,y, ":magma/backgroundfire1.png")
{
     this->rect.setSize(QSize(getImage().width()+4,getImage().height()));
}

Background2::~Background2()
{
    std::cout << ("Background deleted\n");
}

void Background2::moveBrick()
{
    rect.moveTo(rect.left() - Brick2::speed/2, rect.top());
}

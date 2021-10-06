#include "3floor.h"
#include <iostream>

Floor2::Floor2(int x, int y , QString picture) : Brick2(x,y, picture)
{
}

Floor2::~Floor2()
{
    std::cout << ("Floor deleted\n");
}

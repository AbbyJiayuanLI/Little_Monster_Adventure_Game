#include "3safe.h"
#include <iostream>

Safe2::Safe2(int x, int y ) : Brick2(x,y, ":magma/safegold.png")
{
}

Safe2::~Safe2()
{
    std::cout << ("Safe deleted\n");
}

#include "1safe.h"
#include <iostream>

Safe::Safe(int x, int y ) : Brick(x,y, ":land/safegold.png")
{
}

Safe::~Safe()
{
    std::cout << ("Safe deleted\n");
}

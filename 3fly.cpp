#include "3fly.h"
#include <QString>
#include <iostream>

Fly::Fly(int x, int y , bool up) : Brick2(x,y, ":magma/fly.png")
{
    std::cout << "Fly created\n";
    this->up = up;
}

Fly::~Fly()
{
    std::cout << ("Fly deleted\n");
}




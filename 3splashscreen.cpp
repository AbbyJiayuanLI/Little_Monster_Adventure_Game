#include "3splashscreen.h"
#include <iostream>

SplashScreen2::SplashScreen2(int x, int y, QString image ) : Brick2(x,y, image)
{
    std::cout << ("SplashScreen created\n");
}

SplashScreen2::~SplashScreen2()
{
    std::cout << ("SplashScreen deleted\n");
}

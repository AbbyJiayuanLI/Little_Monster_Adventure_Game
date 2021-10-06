#include "3player.h"
#include <iostream>
#include <QDebug>
#include <QRect>

Player2::Player2(int x, int y)
{
    rect.translate(x, y);
    dead = false;
    isMovingR=false;
    isMovingL=false;
    isJumping=false;
}

Player2::~Player2()
{
    std::cout << ("Player deleted\n");
}


void Player2::move(int x ,int y)
{
    rect.moveTo(x, y);
}

void Player2::moveDie(int x ,int y)
{
    dieRect.moveTo(x, y);
}

bool Player2::intersect(QRect r)
{
    if(r.intersects(getRect()))
       return true;
    else
        return false;
}

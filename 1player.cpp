#include "1player.h"
#include <iostream>
#include <QDebug>
#include <QRect>
#include <QList>
#include "1shield.h"

Player::Player(int x, int y)
{
    rect.translate(x, y);
    dead = false;
    isMovingR=false;
    isMovingL=false;
    isJumping=false;
}

Player::~Player()
{
    std::cout << ("Player deleted\n");
}


void Player::move(int x ,int y)
{
    rect.moveTo(x, y);
}

void Player::moveDie(int x ,int y)
{
    dieRect.moveTo(x, y);
}

bool Player::intersect(QRect r)
{
    if(r.intersects(getRect()))
       return true;
    else
        return false;
}

int Player::intersectOneOf(QList<Shield*> *L)
{
    bool result = -1;
    for(int i = 0; i<(*L).size(); i++)
        if((*L)[i]->getRect().intersects(getRect())) {
            result = i;
            break;
        }
    return result;
}

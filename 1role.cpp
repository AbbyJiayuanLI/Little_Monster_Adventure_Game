#include "1role.h"
#include <iostream>
#include <QDebug>

Role::Role(int x, int y ) : Player(x,y)
{
    this->moveRSprite = QPixmap(":land/role.png");
    this->moveLSprite = QPixmap(":land/role_left.png");
    this->stopSprite = QPixmap(":land/role.png");
    this->goldNumber = 0;
    this->bulletNumber = 0;
    this->walkedDistance = 0;
    this->rect = QRect(x, y, 45, moveRSprite.height() - 7);
    this->dieRect = QRect(x, y, 50, stopSprite.height()-7);
}

Role::~Role()
{
    std::cout << ("Role deleted\n");
}

bool Role::intersectTop(QRect r)
{
    if(r.intersected(getRect()).width() > 7 && getRect().y() > r.y())
    {
        move(getRect().x(),r.y() + 49);
        return true;
    }
    return false;
}

bool Role::intersectBottom(QRect r)
{
    if(r.intersected(getRect()).width() > 5 && getRect().y() < r.y())
    {
        move(getRect().x(),r.y() - getRect().height() + 1);
        return true;
    }
    return false;
}

bool Role::intersectRight(QRect r)
{
    if(r.intersected(getRect()).height() > 5 && getRect().x() < r.x() )
        return true;
    return false;
}

bool Role::intersectLeft(QRect r)
{
    if(r.intersected(getRect()).height() > 5 && getRect().x() > r.x())
        return true;
    return false;
}


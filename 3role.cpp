#include "3role.h"
#include <iostream>
#include <QDebug>

Role2::Role2(int x, int y ) : Player2(x,y)
{
    this->moveRSprite = QPixmap(":magma/role.png");
    this->moveLSprite = QPixmap(":magma/role_left.png");
    this->stopSprite = QPixmap(":magma/role.png");
    this->goldNumber = 0;
    this->rect = QRect(x, y, 45, moveRSprite.height() - 7);
    this->dieRect = QRect(x, y, 50, stopSprite.height()-7);
}

Role2::~Role2()
{
    std::cout << ("Role deleted\n");
}

bool Role2::intersectTop(QRect r)
{
    if(r.intersected(getRect()).width() > 7 && getRect().y() > r.y())
    {
        move(getRect().x(),r.y() + 49);
        return true;
    }
    return false;
}

bool Role2::intersectBottom(QRect r)
{
    if(r.intersected(getRect()).width() > 5 && getRect().y() < r.y())
    {
        move(getRect().x(),r.y() - getRect().height() + 1);
        return true;
    }
    return false;
}

bool Role2::intersectRight(QRect r)
{
    if(r.intersected(getRect()).height() > 5 && getRect().x() < r.x() )
        return true;
    return false;
}

bool Role2::intersectLeft(QRect r)
{
    if(r.intersected(getRect()).height() > 5 && getRect().x() > r.x())
        return true;
    return false;
}


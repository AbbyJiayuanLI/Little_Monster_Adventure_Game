#include "1brick.h"
#include <iostream>
#include <QDebug>

Brick::Brick(int x,int y){
    destroyed = false;
    rect.translate(x, y);
    rect.setSize(QSize(50,50));
}

Brick::Brick(int x, int y, QString picture)
{
    image.load(picture);
    destroyed = false;
    rect = image.rect();
    rect.translate(x, y);
}

Brick::~Brick()
{
    std::cout << ("Brick deleted\n");
}

QRect Brick::getRect()
{
    return rect;
}

void Brick::setRect(QRect rct)
{
    rect = rct;
}

QImage & Brick::getImage()
{
    return image;
}

void Brick::moveBrick()
{
    rect.moveTo(rect.left() - Brick::speed, rect.top());
}

void Brick::automoveBrick()
{
    rect.moveTo(rect.left() - Brick::speed + 2, rect.top());
}

void Brick::jetmoveBrick()
{
    rect.moveTo(rect.left() - 2 * Brick::speed, rect.top());
}

void Brick::move(int x ,int y)
{
    rect.moveTo(x, y);
}

bool Brick::intersectBottom(QRect r)
{
    if(r.intersected(getRect()).width() > 5 && getRect().y() < r.y())
    {
        move(getRect().x(),r.y() - getRect().height() + 1);
        return true;
    }
    return false;
}

bool Brick::intersectRight(QRect r)
{
    if(r.intersected(getRect()).height() > 5 && getRect().x() < r.x() )
        return true;
    return false;
}

bool Brick::intersectLeft(QRect r)
{
    if(r.intersected(getRect()).height() > 5 && getRect().x() > r.x())
        return true;
    return false;
}

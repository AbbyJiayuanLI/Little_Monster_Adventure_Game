#include "3brick.h"
#include <iostream>
#include <QDebug>

Brick2::Brick2(int x,int y){
    destroyed = false;
    rect.translate(x, y);
    rect.setSize(QSize(50,50));
}

Brick2::Brick2(int x, int y, QString picture)
{
    image.load(picture);
    destroyed = false;
    rect = image.rect();
    rect.translate(x, y);
}

Brick2::~Brick2()
{
    std::cout << ("Brick2 deleted\n");
}

QRect Brick2::getRect()
{
    return rect;
}

void Brick2::setRect(QRect rct)
{
    rect = rct;
}

QImage & Brick2::getImage()
{
    return image;
}

void Brick2::moveBrick()
{
    rect.moveTo(rect.left() - Brick2::speed, rect.top());
}

void Brick2::move(int x ,int y)
{
    rect.moveTo(x, y);
}

bool Brick2::intersectBottom(QRect r)
{
    if(r.intersected(getRect()).width() > 5 && getRect().y() < r.y())
    {
        move(getRect().x(),r.y() - getRect().height() + 1);
        return true;
    }
    return false;
}

bool Brick2::intersectRight(QRect r)
{
    if(r.intersected(getRect()).height() > 5 && getRect().x() < r.x() )
        return true;
    return false;
}

bool Brick2::intersectLeft(QRect r)
{
    if(r.intersected(getRect()).height() > 5 && getRect().x() > r.x())
        return true;
    return false;
}

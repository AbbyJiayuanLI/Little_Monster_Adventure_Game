#include "1bullet_item.h"
#include <iostream>

BulletItem::BulletItem(int x, int y ) : Brick(x,y, ":land/bullet_item.png")
{
    this->sprite = QPixmap(":land/bullet_item.png");
    this->setRect(QRect(x, y, sprite.width(), sprite.height()));
}

BulletItem::~BulletItem()
{
     std::cout << ("Bullet_item deleted\n");
}

#include "1bullet.h"
#include <QString>

Bullet::Bullet(int x, int y, QString image) : Brick(x, y, image)
{
    setShow(true);
}

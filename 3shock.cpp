#include "3shock.h"

Shock2::Shock2(int x, int y) : Brick2(x,y)
{
    this->sprite = QPixmap(":magma/shock.png");
    this->setRect(QRect(x, y, sprite.width(), sprite.height() / 3));
}

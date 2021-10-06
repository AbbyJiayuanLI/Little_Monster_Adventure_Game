#ifndef BULLET_ITEM_H
#define BULLET_ITEM_H

#include <QPixmap>
#include <QRect>
#include <QString>

#include "1brick.h"
class BulletItem : public Brick
{

public:
  BulletItem(int, int);
  void accept(PaintVisitor *p){ p->visitPixmap(this); }
  ~BulletItem();

};

#endif // BULLET_ITEM_H

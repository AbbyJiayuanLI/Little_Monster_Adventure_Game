#ifndef SHIELD_H
#define SHIELD_H

#include <QPixmap>
#include <QRect>
#include <QString>

#include "1brick.h"

class Shield : public Brick
{
public:
  Shield(int, int);
  void accept(PaintVisitor *p){ p->visitPixmap(this); }
  static int currentFrame;
  ~Shield();
};

#endif // SHIELD_H

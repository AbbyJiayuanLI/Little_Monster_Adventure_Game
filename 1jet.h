#ifndef JET_H
#define JET_H

#include <QPixmap>
#include <QRect>
#include <QString>

#include "1brick.h"

class Jet : public Brick
{
public:
  Jet(int, int);
  void accept(PaintVisitor *p){ p->visitPixmap(this); }
  static int currentFrame;
  ~Jet();
};

#endif // JET_H

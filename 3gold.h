#ifndef GOLD2_H
#define GOLD2_H

#include <QPixmap>
#include <QRect>
#include <QString>

#include "3brick.h"
class Gold2 : public Brick2
{

public:
  Gold2(int, int);
  void accept(PaintVisitor2 *p){ p->visitPixmap(this); }
  static int currentFrame;
  ~Gold2();

};

#endif // GOLD2_H

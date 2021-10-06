#ifndef PAINTVISITOR2_H
#define PAINTVISITOR2_H

#include <QPainter>
#include <QPaintDevice>
#include <QPaintEngine>

class Player2;
class Brick2;

class PaintVisitor2
{
public:
    PaintVisitor2(QPainter *painter);
    ~PaintVisitor2();
    void visitImage(Brick2 *e);
    void visitPixmap(Brick2 *e);
    void visitPixmap(Player2 *e);
    QPainter *getPainter(){ return painter; }


private:
    QPainter *painter;
};

#endif // PAINTVISITOR2_H

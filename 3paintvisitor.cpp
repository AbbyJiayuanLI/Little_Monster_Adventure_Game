#include "3paintvisitor.h"
#include "3player.h"
#include "3brick.h"
#include <QDebug>

PaintVisitor2::PaintVisitor2(QPainter *painter)
{
    this->painter = painter;
}

void PaintVisitor2::visitImage(Brick2 *e){
    getPainter()->drawImage(e->getRect(),e->getImage());
}

void PaintVisitor2::visitPixmap(Player2 *e){
    if(e->getIsMovingR())
        getPainter()->drawPixmap(e->getRect(), e->getMoveRSprite(), e->getSrcRect());
    else if(e->getIsMovingL())
        getPainter()->drawPixmap(e->getRect(), e->getMoveLSprite(), e->getSrcRect());
    else
        getPainter()->drawPixmap(e->getRect(), e->getStopSprite(), e->getSrcRect());
}

void PaintVisitor2::visitPixmap(Brick2 *e){
        getPainter()->drawPixmap(e->getRect(), e->getSprite(), e->getSrcRect());
}

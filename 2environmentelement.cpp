#include "2environmentelement.h"

double environmentElement::speedX = 2;

environmentElement::environmentElement(QObject *parent):
    QObject(parent)
{
    this->clearAllFrame();
    this->bindRect.setRect(0,0,0,0);
    this->enabledLogic = false;
    this->enabledDraw = false;
}

void environmentElement::addFrame(QPixmap pixmap)
{
    if(pixmap.isNull())
        return;
    this->pixmapList.append(pixmap);
    this->frameCount++;
}

void environmentElement::clearAllFrame()
{
    this->pixmapList.clear();
    this->frameCount = 0;
}

QRectF& environmentElement::getBindRect()
{
    return this->bindRect;
}

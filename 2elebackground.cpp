#include "2elebackground.h"

EleBackground::EleBackground(QObject *parent) :
    GameElement(parent)
{
    this->addFrame(QPixmap(":sea/bg_day.png"));
    this->init();
}

void EleBackground::init()
{
    this->bindRect.setRect(0,0,288,512);
    this->currentFrame = 0;
    this->enabledDraw = true;
}

void EleBackground::logic()
{
    if(!this->enabledLogic)
        return;
}

void EleBackground::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),
                        this->bindRect.width(),this->bindRect.height(),
                        this->pixmapList[this->currentFrame]);
}


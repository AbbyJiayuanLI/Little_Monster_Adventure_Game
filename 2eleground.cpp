#include "2eleground.h"

EleGround::EleGround(QObject *parent) :
    environmentElement(parent)
{
    this->addFrame(QPixmap(":sea/land.png"));
    this->init();
}

void EleGround::init()
{
    this->bindRect.setRect(0,400.0,288,112.0 );
    this->currentFrame = 0;
//    this->speedX = 2.5;
    this->positionX = 0;
}

void EleGround::logic()
{
    if( !this->enabledLogic )
        return;

    this->positionX -= this->speedX;
    if(positionX < -this->bindRect.width() )
        this->positionX = 0;
//    this->speedX += 0.003;
}

void EleGround::draw(QPainter *painter)
{
    painter->drawPixmap(this->positionX,
                        this->bindRect.topLeft().y(),
                        this->bindRect.width(),this->bindRect.height(),
                        this->pixmapList[this->currentFrame]);
    painter->drawPixmap(this->positionX + this->bindRect.width()-2,
                        this->bindRect.topLeft().y(),
                        this->bindRect.width(),this->bindRect.height(),
                        this->pixmapList[this->currentFrame]);
}

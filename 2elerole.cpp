#include "2elerole.h"

EleRole::EleRole(QObject *parent) :
    GameElement(parent)
{
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
}

void EleRole::init()
{
    this->loadFrame();
    this->lastFrame = 0;
    this->currentFrame = 1;
    this->angle = 0;
    this->speedX = 7.0;
    this->speedY = -7.2;
    this->increaseY = 0.43;
    this->bindRect.setRect(58,220.0,36.0,40.0);
    this->timer.start(150);
}

void EleRole::logic()
{
    if( !this->enabledLogic )
    {
        return;
    }
            //Angle
            this->angle = qAtan2(this->speedY,this->speedX)*180.0/3.14;
            if(this->angle < -10)
                this->angle = -25;
            else if(this->angle > 60)
                this->angle = 90;

            //Y
            this->speedY += this->increaseY;
            if(this->speedY > 14.0)
            {
                this->speedY = 14.0;
                this->angle = 90;
            }
            this->bindRect.translate(0,this->speedY);

            //limit
            if(this->bindRect.top() < -this->bindRect.height()) //limit to the top
                this->bindRect.moveTop(-this->bindRect.height());
            if(this->bindRect.bottom() > 415.0) //limit to the bottom and stop game
            {
                this->bindRect.moveBottom(415.0);
                this->timer.stop();
            }
            return;
}

void EleRole::draw(QPainter *painter)
{
    if( !this->enabledDraw )
        return;
        painter->save();
        painter->translate(this->bindRect.center());
        painter->rotate(this->angle);
        painter->translate(-this->bindRect.center());
        painter->drawPixmap(this->bindRect.x(),
                            this->bindRect.y(),
                            this->bindRect.width(),this->bindRect.height(),
                            this->pixmapList[this->currentFrame]);
        painter->restore();
}

void EleRole::loadFrame()
{
    switch(qrand()%3)
    {
    case 0:
        this->clearAllFrame();
        this->addFrame(QPixmap(":sea/bird0_0.png"));
        this->addFrame(QPixmap(":sea/bird0_1.png"));
        this->addFrame(QPixmap(":sea/bird0_2.png"));
        break;
    case 1:
        this->clearAllFrame();
        this->addFrame(QPixmap(":sea/bird1_0.png"));
        this->addFrame(QPixmap(":sea/bird1_1.png"));
        this->addFrame(QPixmap(":sea/bird1_2.png"));
        break;
    case 2:
        this->clearAllFrame();
        this->addFrame(QPixmap(":sea/bird2_0.png"));
        this->addFrame(QPixmap(":sea/bird2_1.png"));
        this->addFrame(QPixmap(":sea/bird2_2.png"));
        break;
    }
}

void EleRole::roleUp()
{
    this->speedY = -6.6;
}

void EleRole::updateFrame()
{
    if( !this->enabledDraw )
        return;

    if(this->currentFrame > this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame++;
    }
    else if(this->currentFrame < this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame--;
    }

    if(this->currentFrame<0 || this->currentFrame>2)
        this->currentFrame = 1;
}


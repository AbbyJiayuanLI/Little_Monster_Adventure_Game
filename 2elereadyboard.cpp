#include "2elereadyboard.h"

EleReadyBoard::EleReadyBoard(QObject *parent) :
    GameElement(parent)
{
    this->addFrame(QPixmap(":sea/text_ready.png"));
    this->addFrame(QPixmap(":sea/tutorial.png"));
    this->init();
}

void EleReadyBoard::init()
{
}

void EleReadyBoard::logic()
{
    if(!this->enabledLogic)
        return;
}

void EleReadyBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;
    painter->drawPixmap(55.0,145.0,180.0,63.0,
                        this->pixmapList[0]);
    painter->drawPixmap(86.5,290.0,115.0,100.0,
                        this->pixmapList[1]);
}

#include "2elescoreboard.h"

EleScoreBoard::EleScoreBoard(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void EleScoreBoard::init()
{
    this->bindRect.setRect(131.5,80.0,20.0,50.0);
    this->score = 0;

    this->tempUnit = 0;
    this->tempDecade = 0;
    this->tempHundred = 0;
}

void EleScoreBoard::logic()
{
    if(!this->enabledLogic)
    {
        return;
    }
    else
    {
        this->tempUnit = this->score%10;
        this->tempDecade = (this->score%100)/10;
        this->tempHundred = (this->score%1000)/100;
    }
}

void EleScoreBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
    {
        return;
    }
    else
    {
        if(this->tempDecade == 0 && this->tempHundred == 0)
        {
            painter->drawPixmap(this->bindRect.x(),
                                this->bindRect.y(),
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempUnit]);
        }
        else if(this->tempHundred == 0)
        {
            painter->drawPixmap(this->bindRect.x()-10.0,
                                this->bindRect.y(),
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempDecade]);
            painter->drawPixmap(this->bindRect.x()+10.0,
                                this->bindRect.y(),
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempUnit]);
        }
        else
        {
            painter->drawPixmap(this->bindRect.x()-20.0,
                                this->bindRect.y(),
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempHundred]);
            painter->drawPixmap(this->bindRect.x(),
                                this->bindRect.y(),
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempDecade]);
            painter->drawPixmap(this->bindRect.x()+19.0,
                                this->bindRect.y(),
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempUnit]);
        }
    }
}

void EleScoreBoard::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":sea/font_048.png"));
    this->addFrame(QPixmap(":sea/font_049.png"));
    this->addFrame(QPixmap(":sea/font_050.png"));
    this->addFrame(QPixmap(":sea/font_051.png"));
    this->addFrame(QPixmap(":sea/font_052.png"));
    this->addFrame(QPixmap(":sea/font_053.png"));
    this->addFrame(QPixmap(":sea/font_054.png"));
    this->addFrame(QPixmap(":sea/font_055.png"));
    this->addFrame(QPixmap(":sea/font_056.png"));
    this->addFrame(QPixmap(":sea/font_057.png"));
}

void EleScoreBoard::setScore(int _score)
{
    this->score = _score;
}

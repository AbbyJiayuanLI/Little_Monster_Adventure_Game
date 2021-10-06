#include "2eleoverboard.h"

EleOverBoard::EleOverBoard(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void EleOverBoard::init()
{
    this->score = 0;
    this->highestScore = 0;
    this->medal = NONE;
    this->scoreLabelArrived = false;
    this->overTextRect.setRect(54.0,-500.0,180.0,60.0);
    this->scoreLabelRect.setRect(44.0,1300,200.0,170.0);
}

void EleOverBoard::logic()
{
    if(!this->enabledLogic)
        return;

    if(this->overTextRect.y() < 100.0)
        this->overTextRect.translate(0,15.0);
    else
        this->overTextRect.setY(100.0);

    if(this->scoreLabelRect.y() > 160.0)
    {
        this->scoreLabelRect.translate(0,-20.0);
    }
    else
    {
        this->scoreLabelRect.setY(160.0);
        this->scoreLabelArrived = true;
    }
}

void EleOverBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(this->overTextRect.x(),
                        this->overTextRect.y(),
                        this->overTextRect.width(),
                        this->overTextRect.height(),
                        this->pixmapList[10]);
    painter->drawPixmap(this->scoreLabelRect.x(),
                        this->scoreLabelRect.y(),
                        this->scoreLabelRect.width(),
                        this->scoreLabelRect.height(),
                        this->pixmapList[11]);

    if( !this->scoreLabelArrived )
        return;

    //score
    if((this->score%1000)/100 != 0)
    {
        painter->drawPixmap(185.0, 210.0, 17.0, 21.0,
                            this->pixmapList[(this->score%1000)/100]);
        painter->drawPixmap(202.0, 210.0, 17.0, 21.0,
                            this->pixmapList[(this->score%100)/10]);
    }
    else if((this->score%100)/10 != 0)
    {
        painter->drawPixmap(185.0,210.0,16.0,24.0,
                            this->pixmapList[(this->score%100)/10]);
    }
    painter->drawPixmap(202.0,210.0,16.0,24.0,
                        this->pixmapList[this->score%10]);

    //best score

    if((this->highestScore%1000)/100 != 0)
    {
        painter->drawPixmap(185.0,270.0,16.0,24.0,
                            this->pixmapList[(this->highestScore%1000)/100]);
        painter->drawPixmap(202.0,270.0,16.0,24.0,
                            this->pixmapList[(this->highestScore%100)/10]);
    }
    else if((this->highestScore%100)/10 != 0)
    {
        painter->drawPixmap(185.0,270.0,16.0,24.0,
                            this->pixmapList[(this->highestScore%100)/10]);
    }
    painter->drawPixmap(202.0,270.0,16.0,24.0,
                        this->pixmapList[this->highestScore%10]);

    //Medal
    if(this->medal != NONE)
    {
        painter->drawPixmap(55.0,248.0,45.0,45.0,
                         this->pixmapList[this->medal]);
    }
    //Button
    emit this->buttonVisible(true,true,false);
}

void EleOverBoard::setScore(int _score)
{
    this->score = _score;
    this->highestScore = this->getHighestScore();
    switch(this->score/10)
    {
    case    0:
        this->medal = NONE; break;
    case    1:
        this->medal = COPPERMEDAL;  break;
    case    2:
        this->medal = SILVERMEDAL;  break;
    case    3:
        this->medal = GOLDMEDAL;  break;
    default:
        this->medal = PLATINICMEDAL; break;
    }
}

int EleOverBoard::getHighestScore()
{
    int highestScore;
    if( !QFile::exists("./HighestScore.sc"))
    {
        QFile file;
        file.setFileName("./HighestScore.sc");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream txtStrm(&file);
        txtStrm << this->score <<endl;
        highestScore = this->score;
        file.close();
    }
    else
    {
        QFile file;
        file.setFileName("./HighestScore.sc");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream txtStrm(&file);
        txtStrm >> highestScore ;
        file.close();
        file.remove();

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        if( this->score > highestScore)
        {
            txtStrm << this->score <<endl;
            highestScore = this->score;
        }
        else
        {
            txtStrm << highestScore << endl;
        }
        file.close();
    }
    return highestScore;
}

void EleOverBoard::loadFrame()
{
    this->clearAllFrame();

    this->addFrame(QPixmap(":sea/number_score_00.png"));
    this->addFrame(QPixmap(":sea/number_score_01.png"));
    this->addFrame(QPixmap(":sea/number_score_02.png"));
    this->addFrame(QPixmap(":sea/number_score_03.png"));
    this->addFrame(QPixmap(":sea/number_score_04.png"));
    this->addFrame(QPixmap(":sea/number_score_05.png"));
    this->addFrame(QPixmap(":sea/number_score_06.png"));
    this->addFrame(QPixmap(":sea/number_score_07.png"));
    this->addFrame(QPixmap(":sea/number_score_08.png"));
    this->addFrame(QPixmap(":sea/number_score_09.png"));

    this->addFrame(QPixmap(":sea/text_game_over.png"));
    this->addFrame(QPixmap(":sea/score_panel.png"));

    this->addFrame(QPixmap(":sea/medals_0.png"));
    this->addFrame(QPixmap(":sea/medals_1.png"));
    this->addFrame(QPixmap(":sea/medals_2.png"));
    this->addFrame(QPixmap(":sea/medals_3.png"));
}

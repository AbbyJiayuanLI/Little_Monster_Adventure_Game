#ifndef HEADER2_H
#define HEADER2_H

#include <QRect>
#include <QColor>
#include <QString>
#include <QImage>

class Header2
{
public:
    Header2();
    QRect getRect(){ return rect; }
    QColor getColor(){ return color; }
    QString getText(){ return text; }
    QImage getHeart(){ return heart; }
    QRect getHeartSize(){ return heartSize; }
    QImage getGold(){ return gold; }
    QRect getGoldSize(){ return goldSize; }
    QPoint getGoldPosition(){ return goldPosition; }
private:
    QRect rect;
    QColor color;
    QString text;
    QImage heart;
    QImage gold;
    QRect heartSize;
    QRect goldSize;
    QPoint goldPosition;
};

#endif // HEADER2_H

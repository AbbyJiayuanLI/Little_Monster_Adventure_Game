#ifndef HEADER_H
#define HEADER_H

#include <QRect>
#include <QColor>
#include <QString>
#include <QImage>

class Header
{
public:
    Header();
    QRect getRect(){ return rect; }
    QColor getColor(){ return color; }
    QString getText(){ return text; }
    QImage getHeart(){ return heart; }
    QRect getHeartSize(){ return heartSize; }
    QImage getGold(){ return gold; }
    QRect getGoldSize(){ return goldSize; }
    QPoint getGoldPosition(){ return goldPosition; }
    QImage getBullet(){ return bullet; }
    QRect getBulletSize(){ return bulletSize; }
    QPoint getBulletPosition(){ return bulletPosition; }
    QImage getWalked(){ return walked; }
    QRect getWalkedSize(){ return walkedSize; }
    QPoint getWalkedPosition(){ return walkedPosition; }
private:
    QRect rect;
    QColor color;
    QString text;
    QImage heart;
    QImage gold;
    QImage bullet;
    QImage walked;
    QRect heartSize;
    QRect goldSize;
    QRect bulletSize;
    QRect walkedSize;
    QPoint goldPosition;
    QPoint bulletPosition;
    QPoint walkedPosition;
};

#endif // HEADER_H

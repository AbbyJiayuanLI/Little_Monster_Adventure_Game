#ifndef ELEGROUND_H
#define ELEGROUND_H

#include "2environmentelement.h"

class EleGround : public environmentElement
{
    Q_OBJECT
private:
    int currentFrame;
    int positionX;
//    float speedX;
public:
    explicit EleGround(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
};

#endif // ELEGROUND_H

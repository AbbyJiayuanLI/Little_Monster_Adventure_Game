#ifndef ELEBACKGROUND_H
#define ELEBACKGROUND_H

#include "2gameelement.h"

class EleBackground : public GameElement
{
    Q_OBJECT
private:
    int currentFrame;
public:
    explicit EleBackground(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
};

#endif // ELEBACKGROUND_H

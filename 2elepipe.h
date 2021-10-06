#ifndef ELEPIPE_H
#define ELEPIPE_H

#include "2environmentelement.h"

enum PipeType{above=0,
              following=1};

class ElePipe : public environmentElement
{
    Q_OBJECT
private:
    int currentFrame;
//    int speedX;
    int startPosition;
    QRectF pipeRect[2];
    bool pipePassEmited;

    void loadFrame();
public:
    explicit ElePipe(int pos = 0,QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

    QRectF &getRect(PipeType);
signals:
    void pipePass();

};

#endif // ELEPIPE_H

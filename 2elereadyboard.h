#ifndef ELEREADYBOARD_H
#define ELEREADYBOARD_H

#include "2gameelement.h"

class EleReadyBoard : public GameElement
{
    Q_OBJECT
public:
    explicit EleReadyBoard(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
signals:

public slots:

};

#endif // ELEREADYBOARD_H

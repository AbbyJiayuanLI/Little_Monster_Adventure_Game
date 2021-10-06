#ifndef ELEROLE_H
#define ELEROLE_H

#include <QTimer>
#include <qmath.h>
#include "2gameelement.h"

class EleRole : public GameElement
{
    Q_OBJECT
private:
    int lastFrame;
    int currentFrame;
    float speedY;
    float increaseY;
    float speedX;
    int angle;
    QTimer timer;

    void loadFrame();

public:
    explicit EleRole(QObject *parent = 0);
    void init();
    void logic();
    void draw(QPainter *);
    void roleUp();

signals:

public slots:
    void updateFrame();
};

#endif // ELEROLE_H

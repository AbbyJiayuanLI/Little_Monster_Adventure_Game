#ifndef ENVIRONMENTELEMENT_H
#define ENVIRONMENTELEMENT_H

#include <QObject>
#include <QVector>
#include <QPainter>
#include <QPixmap>

class environmentElement : public QObject
{
    Q_OBJECT
public:
    explicit environmentElement(QObject *parent = 0);

    bool enabledLogic;
    bool enabledDraw;

    static double speedX;//不安全？？？

    virtual void init()=0;
    virtual void draw(QPainter *)=0;
    virtual void logic()=0;

    QRectF& getBindRect();



protected:
    int frameCount;
    QVector<QPixmap> pixmapList;
    QRectF bindRect;

    void addFrame(QPixmap);
    void clearAllFrame();
signals:

public slots:

};


#endif // ENVIRONMENTELEMENT_H

#ifndef BRICK2_H
#define BRICK2_H

#include <QImage>
#include <QRect>
#include <QString>
#include "3paintvisitor.h"

class Brick2
{

  public:
    static int speed;
    Brick2(int ,int );
    Brick2(int, int , QString );
    ~Brick2();
    inline bool isDestroyed(){ return destroyed;}
    inline void setDestroyed(bool d){this->destroyed=d;}
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();
    void setImage(QString i){ image.load(i); }
    void move(int ,int );
    void moveBrick();
    void accept(PaintVisitor2 *p){ p->visitImage(this); }
    inline QPixmap getSprite(){ return sprite; }
    inline void setSprite(QString sprite){ this->sprite.load(sprite); }
    inline QRect getSrcRect(){ return srcRect; }
    inline void setSrcRect(QRect srcRect){ this->srcRect = srcRect; }
    inline QRect getDieRect(){ return dieRect; }
    inline void setDieRect(QRect dieRect){ this->dieRect = dieRect; }
    bool intersectBottom(QRect );
    bool intersectRight(QRect );
    bool intersectLeft(QRect );
    bool getMoveX(){return moveX;}
    bool getMoveUp(){return moveUp;}
    void setMoveX(bool mx){this->moveX=mx;}
    void setMoveUp(bool value){this->moveUp = value;}
    void setXR(int x){this->xR=x;}
    void setYR(int y){this->yR=y;}
    void setStartY(int s){this->startY=s;}
    int getXR(){return xR;}
    int getYR(){return yR;}
    int getStartY(){return startY;}

  private:
    QImage image;
    bool destroyed;
    bool moveX=true;
    bool moveUp=true;
    int xR=0;
    int yR=0;
    int startY;
protected:
    QRect rect;
    QRect dieRect;
    QPixmap sprite;
    QRect srcRect;

};

#endif // BRICK2_H

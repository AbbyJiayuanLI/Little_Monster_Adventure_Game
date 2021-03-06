#ifndef PLAYER2_H
#define PLAYER2_H

#include <QPixmap>
#include <QImage>
#include <QRect>
#include <QString>
#include "3paintvisitor.h"

class Player2
{

  public:
    Player2(int, int);
    ~Player2();
    bool isDead(){return dead;}
    inline void setDead(bool destr){ dead = destr; }
    inline QRect getRect(){ return rect; }
    inline void setSrcRect(QRect srcRect){ this->srcRect = srcRect; }
    inline QRect getSrcRect(){ return srcRect; }
    inline void setRect(QRect rect){ this->rect = rect; }
    inline QRect getDieRect(){ return dieRect; }
    inline void setDieRect(QRect dieRect){ this->dieRect = dieRect; }
    inline QPixmap getMoveRSprite(){ return moveRSprite; }
    inline QPixmap getMoveLSprite(){ return moveLSprite; }
    inline QPixmap getStopSprite(){ return stopSprite; }
    inline void setMoveRSprite(QString m){ moveRSprite.load(m); }
    inline void setMoveLSprite(QString m){ moveLSprite.load(m); }
    inline void setStopSprite(QString m){ stopSprite.load(m); }
    inline bool getIsMovingR(){ return isMovingR; }
    inline bool getIsMovingL(){ return isMovingL; }
    inline bool getIsJumping(){ return isJumping; }
    inline void setIsMovingR(bool is){ this->isMovingR = is; }
    inline void setIsMovingL(bool is){ this->isMovingL = is; }
    inline void setIsJumping(bool is){ this->isJumping = is; }
    inline bool getIsAttacking(){ return isAttacking; }
    inline bool getIsFiring(){ return isFiring; }
    inline void setIsAttacking(bool is){ this->isAttacking = is; }
    inline void setIsFiring(bool is){ this->isFiring = is; }
    void move(int , int);
    void moveDie(int ,int );
    inline int getLife(){ return life; }
    inline void setLife(int life){ this->life = life; }
    inline int getInvicible(){ return invicible; }
    inline void setInvicible(int invicible){ this->invicible = invicible; }
    bool intersect(QRect );
    void accept(PaintVisitor2 *p){ p->visitPixmap(this); }
    void setUntouchable(bool touch){ this->unTouchable = touch; }
    bool getUntouchable(){ return this->unTouchable; }
    inline int getCurrentFrame(){ return currentFrame; }
    inline void setCurrentFrame(int frame){ this->currentFrame = frame; }
    QPixmap moveRSprite;
    QPixmap moveLSprite;
    QPixmap stopSprite;
    QPixmap jumpSprite;

protected:
    QRect rect;
    QRect dieRect;
    QRect srcRect;
    bool isMovingR;
    bool isMovingL;
    bool isJumping;
    bool isFiring = false;
    bool isAttacking = false;
    bool dead = false;
    int currentFrame = 0;
 private:
    bool unTouchable = false;
    int life = 5;
    int invicible = 0;

};

#endif // Player2_H

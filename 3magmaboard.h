#ifndef MAGMABOARD_H
#define MAGMABOARD_H

#include <QWidget>
#include <QObject>

#include "3safe.h"
#include "3floor.h"
#include "3role.h"
#include "3model.h"


class View2;


class MagmaBoard : QObject
{
    Q_OBJECT

public:
    MagmaBoard(Model2 *m, View2 *v);
    ~MagmaBoard();
    void stopGame();
    void movementRole();
    void moveXRole(int );
    void movementBackground();
    void movementFly(int );
    void movementBullet(int );
    void moveBrick(int ,Brick2 *);
    void movefloor(int , Brick2 *);
    void movevertical(int, Brick2 *);
    void movementMap(int );
    void splashScreen();
    bool GameOver();
    bool Completed();
    void hurted();
    void flying();
    bool intersectBottomRole(int );
    bool intersectTopRole(int );
    bool intersectRightRole(int );
    bool intersectLeftRole(int );
    void intersectGoldRole(int );
    void intersectFlyRole(int );
    void intersectYMonsterRole(int );
    void intersectYMoveFloorRole(int );
    void intersectYMoveVerticalRole(int );
    void intersectXMonsterRole(int );
    void intersectFlameRole(int );
    bool intersectBottomBrick(Brick2 *);
    bool intersectRightBrick(Brick2 *);
    bool intersectLeftBrick(Brick2 *);
    void goldAnim();
    void flameAnim();
    void MonsterAnim(int );
    void MoveFloorAnim(int );
    void MoveVerticalAnim(int );
    void BackgroundAnim(int );
    void fantom();
    inline bool getIsMovingR(){ return getModel()->getRole()->getIsMovingR(); }
    inline bool getIsMovingL(){ return getModel()->getRole()->getIsMovingL(); }
    inline bool getIsJumping(){ return getModel()->getRole()->getIsJumping(); }
//    inline bool getIsAttacking(){ return getModel()->getRole()->getIsAttacking(); }
    inline bool getIsFiring(){ return getModel()->getRole()->getIsFiring(); }
    inline void setIsMovingR(bool is){ getModel()->getRole()->setIsMovingR(is); }
    inline void setIsMovingL(bool is){ getModel()->getRole()->setIsMovingL(is); }
    inline void setBulletR(bool is){ getModel()->setBulletR(is); }
    inline void setIsJumping(bool is){ getModel()->getRole()->setIsJumping(is); }
//    inline void setIsAttacking(bool is){ getModel()->getRole()->setIsAttacking(is); }
    inline void setIsFiring(bool is){ getModel()->getRole()->setIsFiring(is); }
    inline void setIsGameOver(bool is){ this->isGameOver = is; }
    inline bool getIsGameOVer(){ return isGameOver; }
    bool getMoveMap(){return moveMap;}
    inline std::tuple<> getAllObjects();
    inline Model2 *getModel(){ return this->model; }
    inline qreal getOpacity(){ return opacity; }
    inline void setOpacity(qreal opacity){this->opacity = opacity; }
    inline int getXRelatif(){ return xRelatif; }
    inline void setXRelatif(int x){this->xRelatif = x; }

private:
    void timerEvent(QTimerEvent *event);

    Model2 *model;
    View2 *view;
    bool gameStarted;
    int xRelatif;
    int yRelatif;
    int startJumpY;
    int iterBackground;
    int tempMove = 0;
    int RoleSize;
    int tempMonster = 0;
    int tempMoveFloor = 0;
    int tempMoveVertical = 0;
    int tempBullet = 0;
    int tempGold = 0;
    int tempFlame = 0;
    qreal opacity = 1;
    bool isFlying;
    bool isGameOver = false;
    bool moveMap=false;
    int showBloodCount = 0;
    int timerId=0;
};
#endif // MAGMABOARD_H

#ifndef LANDBOARD_H
#define LANDBOARD_H

#include <QWidget>
#include <QObject>

#include "1safe.h"
#include "1floor.h"
#include "1role.h"
#include "1model.h"


class View;


class LandBoard : QObject
{
    Q_OBJECT

public:
    LandBoard(Model *m, View *v);
    ~LandBoard();
    void stopGame();
    void movementRole();
    void moveXRole(int );
    void movementBackground();
    void movementMushroom(int );
    void movementBullet(int );
    void movementPeach();
    void moveBrick(int ,Brick *);
    void movementMysticTree(int );
    void movementBullet();
    void movementMap(int );
    void splashScreen();
    bool GameOver();
    void hurted();
    void Jeted();
    void Peach();
    bool intersectBottomRole(int );
    bool intersectTopRole(int );
    bool intersectRightRole(int );
    bool intersectLeftRole(int );
    void intersectGoldRole(int );
    void intersectShieldRole(int );
    void intersectJetRole(int );
    void intersectBulletitemRole(int );
    void intersectMushroomRole(int );
    void intersectBullet(int );
    void intersectShield_Visual(int i);
    void intersectYMonsterRole(int );
    void intersectXMonsterRole(int );
    void intersectFlameRole(int );
    bool intersectBottomBrick(Brick *);
    bool intersectRightBrick(Brick *);
    bool intersectLeftBrick(Brick *);
    void intersectMysticTreeRole(int i);
    void intersectPeachRole();
    void attackMysticTree(int i);
    void goldAnim();
    void shieldAnim();
    void flameAnim();
    void MonsterAnim(int );
    void BackgroundAnim(int );
    void autoBackgroundAnim(int );
    void timeElaspe();
    inline bool getIsMovingR(){ return getModel()->getRole()->getIsMovingR(); }
    inline bool getIsMovingL(){ return getModel()->getRole()->getIsMovingL(); }
    inline bool getIsJumping(){ return getModel()->getRole()->getIsJumping(); }
    inline bool getIsFiring(){ return getModel()->getRole()->getIsFiring(); }
    inline void setIsMovingR(bool is){ getModel()->getRole()->setIsMovingR(is); }
    inline void setIsMovingL(bool is){ getModel()->getRole()->setIsMovingL(is); }
    inline void setBulletR(bool is){ getModel()->setBulletR(is); }
    inline void setIsJumping(bool is){ getModel()->getRole()->setIsJumping(is); }
    inline void setIsFiring(bool is){ getModel()->getRole()->setIsFiring(is); }
    inline void setIsGameOver(bool is){ this->isGameOver = is; }
    inline bool getIsGameOVer(){ return isGameOver; }
    bool getMoveMap(){return moveMap;}
    inline std::tuple<> getAllObjects();
    inline Model *getModel(){ return this->model; }
    inline qreal getOpacity(){ return opacity; }
    inline void setOpacity(qreal opacity){this->opacity = opacity; }
    inline int getXRelatif(){ return xRelatif; }
    inline void setXRelatif(int x){this->xRelatif = x; }

private:
    void timerEvent(QTimerEvent *event);

    Model *model;
    View *view;
    bool gameStarted;
    int xRelatif;
    int yRelatif;
    int startJumpY;
    int iterBackground;
    int tempMove = 0;
    int RoleSize;
    int tempMonster = 0;
    int tempBullet = 0;
    int peachTempo = 0;
    int tempGold = 0;
    int tempShield = 0;
    int tempJet = 0;
    int tempFlame = 0;
    qreal opacity = 1;
    bool isLittle;
    bool isGameOver = false;
    bool moveMap=false;
    bool automoveMap=true;
    int showBloodCount = 0;
    int bulletTime = 0;
    int timerId=0;
};
#endif // LANDBOARD_H

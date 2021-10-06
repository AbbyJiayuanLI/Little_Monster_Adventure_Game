#ifndef MODEL2_H
#define MODEL2_H

#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QChar>

#include "3splashscreen.h"
#include "3header.h"
#include "3background.h"
#include "3fly.h"
#include "3movefloor.h"
#include "3movevertical.h"
#include "3flame.h"

class Safe2;
class Floor2;
class Role2;
class Brick2;
class Gold2;
class Fly;
class Blood2;

class Model2
{
public:
    Model2();
    ~Model2();
    void createBrick(QList<QChar> ,int ,int );
    void brickOrganisation();
    inline Role2 *getRole(){ return role; }
    SplashScreen2 *getSplashScreen(){ return splashScreen; }
    Header2 *getHeader(){ return header; }
    QList<Brick2*> *getCompteur(){ return compteur; }
    inline QList<Safe2*> *getSafes(){ return safes; }
    inline QList<Floor2*> *getFloors(){ return floors; }
    inline QList<Background2*> *getBackground(){ return background; }
    inline QList<Fly*> *getFly(){ return fly; }
    inline QList<Gold2*> *getGold(){ return golds; }
    inline QList<Flame2*> *getFlame(){ return flames; }
    inline QList<MoveFloor*> *getMoveFLoor() {return movefloor;}
    inline QList<MoveVertical*> *getMoveVertical(){return movevertical;}
    inline Blood2 *getBlood(){ return blood; }
    inline int getSpeed(){ return speed; }
    inline void setSpeed(int speed){ this->speed = speed; }
    void createFly(int, int, bool);
    bool getMonsterBool(){ return monsterBool; }
    bool getMoveFloorBool(){ return movefloorBool;}
    bool getMoveVerticalBool(){ return moveverticalBool;}
    void setMonsterBool(bool value){ this->monsterBool = value; }
    void setMoveFloorBool(bool value){this -> movefloorBool = value;}
    void setMoveVerticalBool(bool value){this->moveverticalBool = value;}
    bool getBulletR(){ return bulletR; }
    void setBulletR(bool value) { bulletR = value; }
    void createGameOver(int x, int y);
    void createPeach(int x, int y);
    void createEncart(int x, int y, QString image);
    void createCompleted(int x, int y);
    void createBullet(int x, int y, QString image);
    static int const brickSize = 50;
    static int const Hauteur = 500;
    static int const Longueur = 1000;
    static int const NbrBrickVisible = 20;

private:
    QList<Safe2*> *safes;
    QList<Fly*> *fly;
    QList<Floor2*> *floors;
    QList<Brick2*> *compteur;
    QList<Background2*> *background;
    QList<Gold2*> *golds;
    QList<Flame2*> *flames;
    QList<MoveFloor *> *movefloor;
    QList<MoveVertical *> *movevertical;
    Role2 *role;
    SplashScreen2 *splashScreen;
    Header2 *header;
    Blood2 *blood;
    QList<QChar> ligne1;
    QList<QChar> ligne2;
    QList<QChar> ligne3;
    QList<QChar> ligne4;
    QList<QChar> ligne5;
    QList<QChar> ligne6;
    QList<QChar> ligne7;
    int backgroundCount=0;
    int mapPosition = 7;
    int speed = 4;
    bool movefloorBool;
    bool moveverticalBool;
    bool monsterBool;
    bool bulletR = true;
};

#endif // MODEL2_H

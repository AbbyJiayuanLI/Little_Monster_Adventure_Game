#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QChar>

#include "1splashscreen.h"
#include "1header.h"
#include "1background.h"
#include "1monster.h"
#include "1flame.h"
#include "1bullet.h"
#include "1shield_visual.h"
#include "1bullet_item.h"

class Safe;
class Floor;
class Role;
class Brick;
class Gold;
class Shield;
class Jet;
class BulletItem;
class Blood;

class Model
{
public:
    Model();
    ~Model();
    void createBrick(QList<QChar> ,int ,int );
    void brickOrganisation();
    inline Role *getRole(){ return role; }
    SplashScreen *getSplashScreen(){ return splashScreen; }
    Header *getHeader(){ return header; }
    QList<Brick*> *getCompteur(){ return compteur; }
    inline QList<Safe*> *getSafes(){ return safes; }
    inline QList<Floor*> *getFloors(){ return floors; }
    inline QList<Background*> *getBackground(){ return background; }
    inline QList<Gold*> *getGold(){ return golds; }
    inline QList<Shield*> *getShield(){ return shields; }
    inline QList<Jet*> *getJet(){ return jets; }
    inline QList<BulletItem*> *getBulletItem(){ return bulletItems; }
    inline QList<shield_visual*> *getShield_Visual(){ return shields_visual; }
    inline QList<Flame*> *getFlame(){ return flames; }
    inline QList<Monster*> *getMonster(){ return monster; }
    inline Blood *getBlood(){ return blood; }
    inline QList<Bullet*> *getBullet(){ return bullets; }
    inline int getSpeed(){ return speed; }
    inline void setSpeed(int speed){ this->speed = speed; }
    bool getBulletR(){ return bulletR; }
    void setBulletR(bool value) { bulletR = value; }
    bool getShield_S(){ return shield_s; }
    void setShield_S(bool value) { shield_s = value; }
    void createGameOver(int x, int y);
    void createBullet(int x, int y, QString image);
    void createShield(int x, int y, QString image);
    static int const brickSize = 50;
    static int const Hauteur = 500;
    static int const Longueur = 1000;
    static int const NbrBrickVisible = 20;

private:
    QList<Safe*> *safes;
    QList<Floor*> *floors;
    QList<Brick*> *compteur;
    QList<Background*> *background;
    QList<Gold*> *golds;
    QList<Shield*> *shields;
    QList<Jet*> *jets;
    QList<BulletItem*> *bulletItems;
    QList<shield_visual*> *shields_visual;
    QList<Flame*> *flames;
    QList<Monster *> *monster;
    Role *role;
    SplashScreen *splashScreen;
    Header *header;
    Blood *blood;
    QList<Bullet*> *bullets;

    QList<QChar> ligne1;
    QList<QChar> ligne2;
    QList<QChar> ligne3;
    QList<QChar> ligne4;
    QList<QChar> ligne5;
    QList<QChar> ligne6;
    int backgroundCount=0;
    int mapPosition = 7;
    int speed = 4;
    bool bulletR = true;
    bool shield_s = false;
};

#endif // MODEL_H

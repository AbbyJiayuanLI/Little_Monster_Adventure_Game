#include "1model.h"
#include "1brick.h"
#include "1gold.h"
#include "1shield.h"
#include "1jet.h"
#include <1role.h>
#include <1safe.h>
#include <1floor.h>
#include "1monster.h"
#include "1blood.h"
#include <1splashscreen.h>
#include <1header.h>
#include "1flame.h"
#include "1bullet.h"
#include "1shield_visual.h"
#include "1bullet_item.h"
#include <QDebug>

Model::Model()
{
    this->background = new QList<Background *>;
    this->floors = new QList<Floor *>;
    this->safes = new QList<Safe*>;
    this->golds = new QList<Gold *>;
    this->shields = new QList<Shield *>;
    this->jets = new QList<Jet *>;
    this->bulletItems = new QList<BulletItem *>;
    this->flames = new QList<Flame *>;
    this->bullets = new QList<Bullet *>;
    this->splashScreen = new SplashScreen(330, 170, ":land/go2.png");
    this->monster=new QList<Monster *>;
    this->background = new QList<Background *>;
    this->header = new Header();
    this->compteur = new QList<Brick*> ;
    this->role = new Role(200, 340);
    this->blood = new Blood(0,0);
    QFile fichier(":land/ModelMap.txt");

    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream in (&fichier);
        while(!in.atEnd())
        {
            QString stock = in.readLine();
            if (stock.left(6)=="LIGNEa")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne1.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEb")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne2.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEc")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne3.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEd")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne4.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEe")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne5.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEf")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne6.append(stock.at(i));
                    }
                }
            }
        }
        fichier.close();
    }

    for (int i=0; i<NbrBrickVisible; i++) {
        Floor *k= new Floor(i*brickSize, Hauteur-brickSize, QString(":land/floor_bottom.jpg"));
        floors->append(k);
        Floor *k2= new Floor(i*brickSize, Hauteur-2*brickSize, QString(":land/floor_grass.png"));
        floors->append(k2);
    }
    for (int i=0; i<NbrBrickVisible; i++) {
        Brick *b=new Brick(i*brickSize,Hauteur+brickSize);
        compteur->append(b);
    }
    for (int i=0; i<2; i++) {
        Background* b = new Background(i*Model::Longueur, 0);
        background->append(b);
    }
}

//--------------------------------------------------------------------------------------------------------//

Model::~Model()
{
    floors->clear();
    delete floors;
    safes->clear();
    delete safes;
    compteur->clear();
    delete compteur;
    background->clear();
    delete background;
    monster->clear();
    delete monster;
    delete flames;
    golds->clear();
    delete golds;
    shields->clear();
    delete shields;
    jets->clear();
    delete jets;
    bulletItems->clear();
    delete bulletItems;
    delete role;
    delete splashScreen;
}

//-----------------------------------------------------------------------------------------------------------------//

void Model::createBrick(QList<QChar> l ,int num ,int x){
    QChar myChar = l.at(mapPosition);

    if(myChar == '0')
        return;
    else if(myChar == '1'){
        Floor *k= new Floor(x+brickSize,Hauteur-num*brickSize, QString(":land/floor_bottom.jpg"));
        floors->append(k);
        return;
    }
    else if(myChar == '2'){
        Safe* t= new Safe(x+brickSize, Hauteur-num*brickSize);
        safes->append(t);
        return;
    }
    else if(myChar == '3'){
        Gold* g= new Gold(x+brickSize, Hauteur-num*brickSize);
        golds->append(g);
        return;
    }
    else if(myChar == '4'){
        Monster* d= new Monster(x+brickSize, Hauteur-num*brickSize);
        d->setMoveX(false);
        monster->append(d);
        return;
    }
    else if(myChar == '5'){
        Flame* f = new Flame(x+brickSize, Hauteur-num*brickSize);
        f->setMoveX(false);
        flames->append(f);
        return;
    }
    else if(myChar == '6'){
        Safe* t= new Safe(x+brickSize, Hauteur-num*brickSize);
        t->setCapacity(2);
        safes->append(t);
        return;
    }
    else if(myChar == '7'){
        Floor *k= new Floor(x+brickSize,Hauteur-num*brickSize , QString(":land/floor_grass.png"));
        floors->append(k);
        return;
    }
    else if(myChar == '8'){
        Floor *k= new Floor(x+brickSize,Hauteur-num*brickSize , QString(":land/floor_right.png"));
        floors->append(k);
        return;
    }
    else if(myChar == '9'){
        Floor *k= new Floor(x+brickSize,Hauteur-num*brickSize , QString(":land/floor_left.png"));
        floors->append(k);
        return;
    }  
    else if(myChar == 'b'){
        BulletItem* b= new BulletItem(x+brickSize, Hauteur-num*brickSize);
        bulletItems->append(b);
        return;
    }
    else if(myChar == 's'){
        Shield* s= new Shield(x+brickSize, Hauteur-num*brickSize);
        shields->append(s);
        return;
    }
    else if(myChar == 'j'){
        Jet* j= new Jet(x+brickSize, Hauteur-num*brickSize);
        jets->append(j);
        return;
    }
}

//----------------------------------------------------------------------------------------------------------------//

void Model::brickOrganisation()
{
    for(int i = 0; i<background->size(); i++){
        if(background->at(i)->getRect().x() < -background->at(i)->getRect().width() + 2){
            background->removeAt(i);
            Background* b = new Background(1000,0);
            background->append(b);
        }
    }
    if(compteur->last()->getRect().x()<((NbrBrickVisible)*brickSize)){
        Brick *b=new Brick(compteur->last()->getRect().x()+brickSize,Hauteur+brickSize);
        createBrick(ligne1,1,compteur->last()->getRect().x());
        createBrick(ligne2,2,compteur->last()->getRect().x());
        createBrick(ligne3,3,compteur->last()->getRect().x());
        createBrick(ligne4,4,compteur->last()->getRect().x());
        createBrick(ligne5,5,compteur->last()->getRect().x());
        createBrick(ligne6,6,compteur->last()->getRect().x());
        compteur->append(b);
        mapPosition++;
    }

    if (compteur->first()->getRect().x()<=-brickSize){
        compteur->removeAt(compteur->indexOf(compteur->first()));
    }

    for(int i = 0; i<floors->size(); i++){
        if (floors->at(i)->getRect().x()<=-brickSize || floors->at(i)->isDestroyed()){
            floors->removeAt(i);
        }
    }

    for(int i = 0; i<safes->size(); i++){
        if (safes->at(i)->getRect().x()<=-brickSize || safes->at(i)->isDestroyed()){
            safes->removeAt(i);
        }
    }

    for(int i = 0; i<golds->size(); i++){
        if (golds->at(i)->getRect().x()<=-brickSize || golds->at(i)->isDestroyed()){
            golds->removeAt(i);
        }
    }

    for(int i = 0; i<shields->size(); i++){
        if (shields->at(i)->getRect().x()<=-brickSize || shields->at(i)->isDestroyed()){
            shields->removeAt(i);
        }
    }

    for(int i = 0; i<jets->size(); i++){
        if (jets->at(i)->getRect().x()<=-brickSize || jets->at(i)->isDestroyed()){
            jets->removeAt(i);
        }
    }

    for(int i = 0; i<bulletItems->size(); i++){
        if (bulletItems->at(i)->getRect().x()<=-brickSize || bulletItems->at(i)->isDestroyed()){
            bulletItems->removeAt(i);
        }
    }

    for(int i = 0; i<flames->size(); i++){
        if (flames->at(i)->getRect().x()<=-brickSize || flames->at(i)->isDestroyed()){
            flames->removeAt(i);
        }
    }

    for(int i = 0; i<monster->size(); i++){
        if (monster->at(i)->getRect().x()<=-brickSize ){
            monster->removeAt(i);
        }
    }
}

void Model::createGameOver(int x, int y){
    this->splashScreen = new SplashScreen(x, y, ":land/gameover.png");
}

void Model::createBullet(int x, int y, QString image){
    Bullet *b = new Bullet(x, y, image);
    bullets->append(b);
}

void Model::createShield(int x, int y, QString image){
    shield_visual *s = new shield_visual(x, y, image);
    shields_visual->append(s);
}

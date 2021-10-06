#include "3model.h"
#include "3brick.h"
#include "3gold.h"
#include <3role.h>
#include <3safe.h>
#include <3floor.h>
#include "3movefloor.h"
#include "3movevertical.h"
#include "3blood.h"
#include <3splashscreen.h>
#include <3header.h>
#include "3flame.h"
#include <QDebug>

Model2::Model2()
{
    this->background = new QList<Background2 *>;
    this->floors = new QList<Floor2 *>;
    this->safes = new QList<Safe2*>;
    this->fly = new QList<Fly *>;
    this->golds = new QList<Gold2 *>;
    this->flames = new QList<Flame2 *>;
    this->splashScreen = new SplashScreen2(330, 170, ":magma/go2.png");
    this->movefloor = new QList<MoveFloor *>;
    this->movevertical = new QList<MoveVertical *>;
    this->background = new QList<Background2 *>;
    this->header = new Header2();
    this->compteur = new QList<Brick2*> ;
    this->role = new Role2(200, 340);
    this->blood = new Blood2(0,0);

    QFile fichier(":magma/ModelMap.txt");

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
            else if (stock.left(6)=="LIGNEg")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne7.append(stock.at(i));
                    }
                }
            }
        }
        fichier.close();
    }

    for (int i=0; i<NbrBrickVisible; i++) {
        Floor2 *k= new Floor2(i*brickSize, Hauteur-brickSize, QString(":magma/magma_land_nothing.jpg"));
        floors->append(k);
        Floor2 *k2= new Floor2(i*brickSize, Hauteur-2*brickSize, QString(":magma/magma_land_center.png"));
        floors->append(k2);
    }
    for (int i=0; i<NbrBrickVisible; i++) {
        Brick2 *b=new Brick2(i*brickSize,Hauteur+brickSize);
        compteur->append(b);
    }
    for (int i=0; i<2; i++) {
        Background2* b = new Background2(i*Model2::Longueur, 0);
        background->append(b);
    }
}

//--------------------------------------------------------------------------------------------------------//

Model2::~Model2()
{
    floors->clear();
    delete floors;
    safes->clear();
    delete safes;
    compteur->clear();
    delete compteur;
    background->clear();
    delete background;
    fly->clear();
    delete fly;
    movefloor->clear();
    delete movefloor;
    movevertical -> clear();
    delete movevertical;
    delete flames;
    golds->clear();
    delete golds;
    delete role;
    delete splashScreen;
}

//-----------------------------------------------------------------------------------------------------------------//

void Model2::createBrick(QList<QChar> l ,int num ,int x){
    QChar myChar = l.at(mapPosition);

    if(myChar == '0')
        return;
    else if(myChar == '1'){
        Floor2 *k= new Floor2(x+brickSize,Hauteur-num*brickSize, QString(":magma/magma_land_nothing.jpg"));
        floors->append(k);
        return;
    }
    else if(myChar == '2'){
        Safe2* t= new Safe2(x+brickSize, Hauteur-num*brickSize);
        safes->append(t);
        return;
    }
    else if(myChar == '3'){
        Gold2* g= new Gold2(x+brickSize, Hauteur-num*brickSize);
        golds->append(g);
        return;
    }
    else if(myChar == '5'){
        Flame2* f = new Flame2(x+brickSize, Hauteur-num*brickSize);
        f->setMoveX(false);
        flames->append(f);
        return;
    }
    else if(myChar == '6'){
        Safe2* t= new Safe2(x+brickSize, Hauteur-num*brickSize);
        t->setCapacity(2);
        safes->append(t);
        return;
    }
    else if(myChar == '7'){
        Floor2 *k= new Floor2(x+brickSize,Hauteur-num*brickSize , QString(":magma/magma_land_center.png"));
        floors->append(k);
        return;
    }
    else if(myChar == '8'){
        Floor2 *k= new Floor2(x+brickSize,Hauteur-num*brickSize , QString(":magma/magma_land_right.png"));
        floors->append(k);
        return;
    }
    else if(myChar == '9'){
        Floor2 *k= new Floor2(x+brickSize,Hauteur-num*brickSize , QString(":magma/magma_land_left.png"));
        floors->append(k);
        return;
    }
    else if(myChar == 'A'){
        Floor2 *k= new Floor2(x+brickSize,Hauteur-num*brickSize , QString(":magma/invisible.png"));
        floors->append(k);
        return;
    }
    else if(myChar == 'D'){
        MoveFloor * d = new MoveFloor(x+brickSize, Hauteur-num*brickSize);
        d->setMoveX(false);
        movefloor->append(d);
        return;
    }
    else if(myChar == 'F'){
        MoveVertical * d = new MoveVertical(x+brickSize, Hauteur-num*brickSize);
        d->setMoveX(false);
        movevertical->append(d);
        return;
    }}
//----------------------------------------------------------------------------------------------------------------//

void Model2::brickOrganisation()
{
    for(int i = 0; i<background->size(); i++){
        if(background->at(i)->getRect().x() < -background->at(i)->getRect().width() + 2){
            background->removeAt(i);
            Background2* b = new Background2(1000,0);
            background->append(b);
        }
    }
    if(compteur->last()->getRect().x()<((NbrBrickVisible)*brickSize)){
        Brick2 *b=new Brick2(compteur->last()->getRect().x()+brickSize,Hauteur+brickSize);
        createBrick(ligne1,1,compteur->last()->getRect().x());
        createBrick(ligne2,2,compteur->last()->getRect().x());
        createBrick(ligne3,3,compteur->last()->getRect().x());
        createBrick(ligne4,4,compteur->last()->getRect().x());
        createBrick(ligne5,5,compteur->last()->getRect().x());
        createBrick(ligne6,6,compteur->last()->getRect().x());
        createBrick(ligne7,7,compteur->last()->getRect().x());
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

    for(int i = 0; i<fly->size(); i++){
        if (fly->at(i)->getRect().x()<=-brickSize || fly->at(i)->isDestroyed()){
            fly->removeAt(i);
        }
    }

    for(int i = 0; i<flames->size(); i++){
        if (flames->at(i)->getRect().x()<=-brickSize || flames->at(i)->isDestroyed()){
            flames->removeAt(i);
        }
    }
    for(int i = 0; i < movefloor->size(); i++){
        if (movefloor->at(i)->getRect().x() <= -brickSize ){
            movefloor->removeAt(i);
        }
    }
    for(int i = 0; i < movevertical->size(); i++){
        if (movevertical->at(i)->getRect().x() <= -brickSize ){
            movevertical->removeAt(i);
        }
    }
}

void Model2::createFly(int x, int y, bool up){
    Fly *m = new Fly(x+9, y+10, up);
    m->setYR(0);
    m->setXR(0);
    m->setStartY(m->getRect().y() + 50);
    fly->append(m);
}

void Model2::createGameOver(int x, int y){
    this->splashScreen = new SplashScreen2(x, y, ":magma/gameover.png");
}

void Model2::createCompleted(int x, int y){
    this->splashScreen = new SplashScreen2(x, y, ":magma/level_complete.png");
}




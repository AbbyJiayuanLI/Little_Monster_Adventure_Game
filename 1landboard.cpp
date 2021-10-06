#include "1landboard.h"
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <QTimer>

#include "1model.h"
#include "1view.h"
#include <iostream>
using namespace std;

LandBoard::LandBoard(Model *m, View *v) : QObject()
{
    this->model = m;
    this->view = v;
    this->view->setControl(this);
    gameStarted = true;
    xRelatif = -100;
    yRelatif = 0;
    iterBackground=0;
    timerId = startTimer(15);
}

int Gold::currentFrame = 0;
int Shield::currentFrame = 0;
int Jet::currentFrame = 0;
int Flame::currentFrame = 0;
int Monster::currentFrame = 0;
double Brick::speed = 3;
//----------------------------------------------------------------------------------------------------------------//

LandBoard::~LandBoard()
{
    killTimer(timerId);
}

//----------------------------------------------------------------------------------------------------------------//


void LandBoard::timerEvent(QTimerEvent *)
{
    flameAnim();
    splashScreen();
    movementRole();
    getModel()->brickOrganisation();
    goldAnim();
    hurted();
    Jeted();
    GameOver();
    timeElaspe();
    view->repaint();
}


void LandBoard::stopGame()
{
    gameStarted = false;
}

void LandBoard::timeElaspe(){
    if (!GameOver()) {
        Brick::speed += 0.001;
        model->getRole()->setWalkedDistance(model->getRole()->getWalkedDistance()+int(Brick::speed));
    }
}

//----------------------------------------------------------------------------------------------------------------//

void LandBoard::movementRole()
{
    int y=model->getRole()->getRect().y();
    if(model->getRole()->getIsJeted() == 0 && getIsJumping()){
        xRelatif += 4;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = startJumpY-yRelatif;
        moveXRole(y);
        model->getRole()->setCurrentFrame(0);
        if(intersectTopRole(0)){
            xRelatif=0;
            yRelatif=0;
            startJumpY=model->getRole()->getRect().y();
            setIsJumping(false);
        }
    }

    if(intersectBottomRole(0)){
        xRelatif=0;
        yRelatif=0;
        startJumpY=model->getRole()->getRect().y();
        setIsJumping(false);
        moveXRole(y);

        if(getIsMovingR() && tempMove == 1){
            model->getRole()->setCurrentFrame(model->getRole()->getCurrentFrame());
            tempMove = 0;
        }
        else if(getIsMovingR())
            tempMove++;
        else if(getIsMovingL() && tempMove == 1){
            model->getRole()->setCurrentFrame(model->getRole()->getCurrentFrame());
            tempMove = 0;
        }
        else if(getIsMovingL())
            tempMove++;
        else
            model->getRole()->setCurrentFrame(0);
    }

    if((model->getRole()->getIsJeted() == 0 && !intersectBottomRole(0) && !getIsJumping())){
        yRelatif=(-0.02*(xRelatif*xRelatif));
        for(int i=0;i<4;++i){xRelatif += 1;}
        y = startJumpY-yRelatif;
        moveXRole(y);
        model->getRole()->setCurrentFrame(0);
    }
}

void LandBoard::movementBullet(int i)
{
    int y = model->getBullet()->at(i)->getRect().y();
    if (getModel()->getBullet()->at(i)->getBulletR()) {
        if (moveMap) model->getBullet()->at(i)->move(model->getBullet()->at(i)->getRect().x() + int(0.5 * Brick::speed) , y);
        else model->getBullet()->at(i)->move(model->getBullet()->at(i)->getRect().x() + int(Brick::speed), y);
    } else {
        if (moveMap) model->getBullet()->at(i)->move(model->getBullet()->at(i)->getRect().x() - int(1.8*Brick::speed), y);
        else model->getBullet()->at(i)->move(model->getBullet()->at(i)->getRect().x() - int(1.5*Brick::speed), y);
    }
}

void LandBoard::moveBrick(int x ,Brick * b)
{
    int speed;
    if(moveMap)
        speed = int(Brick::speed);
    else
        speed = int(Brick::speed)-2;


    if(intersectBottomBrick(b)){
        if(b->getMoveX()){
            b->move(x-speed+2, b->getRect().y());
            if(intersectRightBrick(b))
                b->setMoveX(false);
        }
        else if(!b->getMoveX()){
            b->move(x-speed-3, b->getRect().y());
            if( intersectLeftBrick(b) || b->getRect().x()<3)
                b->setMoveX(true);
        }
        b->setYR(0);
        b->setXR(0);
        b->setStartY(b->getRect().y());
    }
    else{
        b->setYR(-0.02*(b->getXR()*b->getXR()));
        b->setXR(b->getXR()+3);
        int y = b->getStartY()- b->getYR();
        if(b->getMoveX()){
            b->move(x-speed+2, y);
            if(intersectRightBrick(b))
                b->setMoveX(false);
        }
        else if(!b->getMoveX()){
            b->move(x-speed-2,y);
            if( intersectLeftBrick(b))
                b->setMoveX(true);
        }
    }
}

void LandBoard::moveXRole(int y)
{
    int x=model->getRole()->getRect().x();
    if (model->getRole()->getIsJeted() == 0) {
        if(!intersectLeftRole(0) && model->getRole()->getRect().x()>=2 && getIsMovingL() ) {
            x -= Brick::speed;
            x -= (Brick::speed-2);
        } else if( !intersectRightRole(0) && model->getRole()->getRect().x()<=600  && getIsMovingR()) {
            x += Brick::speed;
            x -= (Brick::speed-2);
        } else if( !intersectRightRole(0) && model->getRole()->getRect().x()>600  && getIsMovingR()) {
        } else {
            x -= (Brick::speed-2);
        }

        if( !intersectRightRole(0)&& model->getRole()->getRect().x()>=600  && getIsMovingR() ){
            moveMap=true;
        }
        else
            moveMap=false;
    } else {
        moveMap = true;
    }
    model->getRole()->move(x,y);
}

//----------------------------------------------------------------------------------------------------------------//

bool LandBoard::intersectTopRole(int i)
{
    if(i<model->getFloors()->size() || i<model->getSafes()->size()){
        if(!model->getFloors()->empty() && i<model->getFloors()->size()){
            if(model->getRole()->intersectTop(model->getFloors()->at(i)->getRect()))
                return true;
        }
        if(!model->getSafes()->empty() && i<model->getSafes()->size()){
            if(model->getRole()->intersectTop(model->getSafes()->at(i)->getRect())){
                if(model->getSafes()->at(i)->getCapacity()){
                    if(model->getSafes()->at(i)->getCapacity() == 2){
                        model->getSafes()->at(i)->setCapacity(1);
                    }
                }else
                    model->getSafes()->at(i)->setDestroyed(true);
            return true;
            }
        }
    intersectTopRole(i+1);
    }
    else
        return false;
}

bool LandBoard::intersectBottomRole(int i)
{
    if(i<model->getFloors()->size()
            || i<model->getSafes()->size()){
        if(!model->getFloors()->empty() && i<model->getFloors()->size()){
            if(model->getRole()->intersectBottom(model->getFloors()->at(i)->getRect()))
                return true;
        }
        if(!model->getSafes()->empty() && i<model->getSafes()->size()){
            if(model->getRole()->intersectBottom(model->getSafes()->at(i)->getRect())){
                return true;
            }
        }
        intersectBottomRole(i+1);
    }
    else
        return false;
}

bool LandBoard::intersectLeftRole(int i)
{
    if(i<model->getFloors()->size()
            || i<model->getSafes()->size()
            || i<model->getMonster()->size()){
    if(!model->getFloors()->empty() && i<model->getFloors()->size()){
        if(model->getRole()->intersectLeft(model->getFloors()->at(i)->getRect()))
            return true;
    }
    if(!model->getSafes()->empty() && i<model->getSafes()->size()){
        if(model->getRole()->intersectLeft(model->getSafes()->at(i)->getRect()))
            return true;
    }
    if(!model->getMonster()->empty() && i<model->getMonster()->size()){
        if(model->getRole()->intersectLeft(model->getMonster()->at(i)->getRect()))
            return true;
        }
    intersectLeftRole(i+1);
    }
    else
        return false;
}

bool LandBoard::intersectRightRole(int i)
{
    if(i<model->getFloors()->size()
            || i<model->getSafes()->size()
            || i<model->getMonster()->size()){
        if(!model->getFloors()->empty() && i<model->getFloors()->size() ){
            if(model->getRole()->intersectRight(model->getFloors()->at(i)->getRect()))
                return true;

        }
        if(!model->getSafes()->empty() && i<model->getSafes()->size()){
            if(model->getRole()->intersectRight(model->getSafes()->at(i)->getRect()))
                return true;
        }
        if(!model->getMonster()->empty() && i<model->getMonster()->size()){
            if(model->getRole()->intersectRight(model->getMonster()->at(i)->getRect()))
                return true;
        }
        intersectRightRole(i+1);
    }
    else
        return false;
}

void LandBoard::intersectGoldRole(int i)
{
    if(model->getRole()->intersect(model->getGold()->at(i)->getRect())){
        model->getGold()->at(i)->setDestroyed(true);
        model->getRole()->setGoldNumber(model->getRole()->getGoldNumber()+1);
    }
}

void LandBoard::intersectShieldRole(int i)
{
    if(model->getRole()->intersect(model->getShield()->at(i)->getRect())){
        model->getShield()->at(i)->setDestroyed(true);
        model->getRole()->setIsShielded(true);
    }
}

void LandBoard::intersectJetRole(int i)
{
    if(model->getRole()->intersect(model->getJet()->at(i)->getRect())){
        model->getJet()->at(i)->setDestroyed(true);
        model->getRole()->setIsJeted(300);
    }

}

void LandBoard::Jeted()
{
    if (getModel()->getRole()->getIsJeted() != 0) {
        getModel()->getRole()->setIsJeted(getModel()->getRole()->getIsJeted() - 1);
        cout << getModel()->getRole()->getIsJeted() << endl;
    }
    if (getModel()->getRole()->getIsJeted() == 1) {
        getModel()->getRole()->setIsShielded(true);
    }
}

void LandBoard::intersectBulletitemRole(int i)
{
    if(model->getRole()->intersect(model->getBulletItem()->at(i)->getRect())){
        model->getBulletItem()->at(i)->setDestroyed(true);
        model->getRole()->setBulletNumber(model->getRole()->getBulletNumber()+1);
    }
}

void LandBoard::intersectFlameRole(int i)
{
        if(model->getRole()->intersect(model->getFlame()->at(i)->getRect()) && !model->getRole()->getUntouchable()){
            showBloodCount = 0;
            this->model->getRole()->setIsHurted(true);
        }
}

void LandBoard::intersectXMonsterRole(int i)
{
    if(model->getRole()->intersect(model->getMonster()->at(i)->getRect())
       && !model->getRole()->getUntouchable()
       && !model->getMonster()->at(i)->isDestroyed()){
        if( !model->getRole()->getIsMovingR()&& !model->getRole()->getIsMovingL())
            model->getMonster()->at(i)->setMoveX(!model->getMonster()->at(i)->getMoveX());
        if(getModel()->getRole()->getIsMovingR() && !model->getMonster()->at(i)->getMoveX())
            model->getMonster()->at(i)->setMoveX(!model->getMonster()->at(i)->getMoveX());
        else if(getModel()->getRole()->getIsMovingL() && model->getMonster()->at(i)->getMoveX())
            model->getMonster()->at(i)->setMoveX(!model->getMonster()->at(i)->getMoveX());
        showBloodCount = 0;
        this->model->getRole()->setIsHurted(true);
    }
}

void LandBoard::intersectYMonsterRole(int i)
{
    if(!getModel()->getRole()->getIsMovingL()
            && !getModel()->getRole()->getIsMovingR()
            && !model->getMonster()->at(i)->isDestroyed() && !model->getRole()->getUntouchable()){
        getModel()->getRole()->move(getModel()->getMonster()->at(i)->getRect().x(), getModel()->getRole()->getRect().y());
    }
}


void LandBoard::intersectBullet(int i)
{
    for(int j = 0; j < model->getFloors()->size(); j++){
        if(model->getBullet()->at(i)->getRect().intersects(model->getFloors()->at(j)->getRect()))
           model->getBullet()->at(i)->setDestroyed(true);
    }
    for(int j = 0; j < model->getSafes()->size(); j++){
        if(model->getBullet()->at(i)->getRect().intersects(model->getSafes()->at(j)->getRect()))
           model->getBullet()->at(i)->setDestroyed(true);
    }
    for(int j = 0; j < model->getMonster()->size(); j++){
        if(model->getBullet()->at(i)->getRect().intersects(model->getMonster()->at(j)->getRect())){
            if(!model->getMonster()->at(j)->isDestroyed()) {
                model->getBullet()->at(i)->setDestroyed(true);
                model->getMonster()->at(j)->setDestroyed(true);
            }
        }
    }
}

void LandBoard::intersectShield_Visual(int i)
{
    for(int j = 0; j < model->getMonster()->size(); j++){
        if(model->getShield_Visual()->at(i)->getRect().intersects(model->getMonster()->at(j)->getRect())){
            if(!model->getMonster()->at(j)->isDestroyed()) {
                model->getShield_Visual()->at(i)->setDestroyed(true);
            }
        }
    }
}


bool LandBoard::intersectBottomBrick(Brick * m)
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(m->intersectBottom(model->getFloors()->at(i)->getRect()))
            return true;
    }
    for(int i = 0; i<model->getSafes()->size(); i++){
        if(m->intersectBottom(model->getSafes()->at(i)->getRect()))
            return true;
    }
    return false;
}

bool LandBoard::intersectLeftBrick(Brick * m)
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(m->intersectLeft(model->getFloors()->at(i)->getRect()))
            return true;
    }
    for(int i = 0; i<model->getSafes()->size(); i++){
        if(m->intersectLeft(model->getSafes()->at(i)->getRect()))
            return true;
    }
    return false;
}

bool LandBoard::intersectRightBrick(Brick * m)
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(m->intersectRight(model->getFloors()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getSafes()->size(); i++){
        if(m->intersectRight(model->getSafes()->at(i)->getRect()))
            return true;
    }
    return false;
}

//-----------------------------------------------------------------------------------------------------------------------//

void LandBoard::splashScreen()
{
    if(getModel()->getSplashScreen()->getType() == SplashScreenType::GO){
        int x=model->getSplashScreen()->getRect().x();
        int y=model->getSplashScreen()->getRect().y();
        y--;
        if(model->getSplashScreen()->getRect().bottom() > 0 && model->getSplashScreen()->getIsSplashScreen())
            model->getSplashScreen()->move(x, y);
        else
            model->getSplashScreen()->setIsSplashScreen(false);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void LandBoard::goldAnim()
{
    if(tempGold == 20){
        Gold::currentFrame += 40;
        if (Gold::currentFrame >= 120)
            Gold::currentFrame = 0;
        tempGold = 0;
    }
    else
        tempGold++;
}

void LandBoard::MonsterAnim(int i)
{
    if(tempMonster == 15){
        Monster::currentFrame += 52;
        if (Monster::currentFrame >= 156)
            Monster::currentFrame = 1;
        tempMonster = 0;
    }
    else
        tempMonster++;
        int x=model->getMonster()->at(i)->getRect().x();
        if(!model->getMonster()->at(i)->isDestroyed()){
            moveBrick(x ,model->getMonster()->at(i));
            intersectXMonsterRole(i);
            if(model->getMonster()->at(i)->getMoveX())
                getModel()->getMonster()->at(i)->setSprite(QString(":land/dark_eater_right.png"));
            else
                getModel()->getMonster()->at(i)->setSprite(QString(":land/dark_eater.png"));
            model->getMonster()->at(i)->setSrcRect(QRect(Monster::currentFrame, 0, model->getMonster()->at(i)->getRect().width(), model->getMonster()->at(i)->getRect().height()));
        }
}

void LandBoard::flameAnim()
{

    if(tempFlame == 10){
        Flame::currentFrame += 58;
        if (Flame::currentFrame >= 520)
            Flame::currentFrame = 3;
        tempFlame = 0;
    }
    else
        tempFlame++;
    for(int i = 0; i<model->getFlame()->size(); i++){
        int x=model->getFlame()->at(i)->getRect().x();
        moveBrick(x ,model->getFlame()->at(i));
        model->getFlame()->at(i)->setSrcRect(QRect(Flame::currentFrame, 0, model->getFlame()->at(i)->getRect().width(), model->getFlame()->at(i)->getRect().height()));
        view->update(model->getFlame()->at(i)->getSrcRect());}
}

void LandBoard::BackgroundAnim(int i)
{
    if(iterBackground == 1){
        model->getBackground()->at(i)->moveBrick();
        iterBackground=0;
    }
    else{
        iterBackground++;
    }
}

void LandBoard::autoBackgroundAnim(int i)
{
    if(iterBackground == 1){
        model->getBackground()->at(i)->automoveBrick();
        iterBackground=0;
    }
    else{
        iterBackground++;
    }
}

void LandBoard::hurted()
{
    if(model->getRole()->getIsHurted() && !model->getRole()->getIsShielded() && model->getRole()->getIsJeted() == 0){
        model->getRole()->setUntouchable(true);
        if(showBloodCount >= 15){
            this->getModel()->getBlood()->setStopBlood(true);
            showBloodCount = 0;
        }
        else{
            showBloodCount++;
        }

        this->getModel()->getBlood()->move(model->getRole()->getRect().x() - 20, model->getRole()->getRect().y() - 5);

        if(getModel()->getRole()->getInvicible() == 0){
            model->getRole()->setLife(model->getRole()->getLife() - 1);
        }
        if(getModel()->getRole()->getInvicible() > 100){
            getModel()->getRole()->setUntouchable(false);
            getModel()->getRole()->setIsHurted(false);
            getModel()->getBlood()->setStopBlood(false);
            getModel()->getRole()->setInvicible(0);
        }
        else{
            getModel()->getRole()->setInvicible(getModel()->getRole()->getInvicible() + 1);
        }
    }

    if(model->getRole()->getIsHurted() && model->getRole()->getIsJeted() != 0){
        model->getRole()->setUntouchable(true);
        this->getModel()->getBlood()->setStopBlood(true);

        this->getModel()->getBlood()->move(model->getRole()->getRect().x() - 20, model->getRole()->getRect().y() - 5);

        if(getModel()->getRole()->getInvicible() > 500){
            getModel()->getRole()->setUntouchable(false);
            getModel()->getRole()->setIsHurted(false);
            getModel()->getBlood()->setStopBlood(false);
            getModel()->getRole()->setInvicible(0);
        }
        else{
            getModel()->getRole()->setInvicible(getModel()->getRole()->getInvicible() + 1);
        }
    }

    if(model->getRole()->getIsHurted() && model->getRole()->getIsShielded() && model->getRole()->getIsJeted() == 0){
        model->getRole()->setIsShielded(false);
        model->getRole()->setUntouchable(true);
        this->getModel()->getBlood()->setStopBlood(true);

        this->getModel()->getBlood()->move(model->getRole()->getRect().x() - 20, model->getRole()->getRect().y() - 5);

        if(getModel()->getRole()->getInvicible() > 100){
            getModel()->getRole()->setUntouchable(false);
            getModel()->getRole()->setIsHurted(false);
            getModel()->getBlood()->setStopBlood(false);
            getModel()->getRole()->setInvicible(0);
            getModel()->getRole()->setIsShielded(false);
        }
        else{
            getModel()->getRole()->setInvicible(getModel()->getRole()->getInvicible() + 1);
        }
    }
}


bool LandBoard::GameOver(){
    if(getModel()->getRole()->getLife() < 0 || getModel()->getRole()->getRect().y() > 500){
        if(getModel()->getSplashScreen()->getType() != SplashScreenType::GAME_OVER){
            getModel()->createGameOver(220, 80);
            getModel()->getSplashScreen()->setType(SplashScreenType::GAME_OVER);
        }
        model->getSplashScreen()->setIsSplashScreen(true);
        Brick::speed = 3;
        return true;
    }
    else
        return false;
}


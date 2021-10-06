#include "3magmaboard.h"
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <QTimer>

#include "3model.h"
#include "3view.h"
#include <iostream>
using namespace std;

MagmaBoard::MagmaBoard(Model2 *m, View2 *v) : QObject()
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

int Gold2::currentFrame = 0;
int Flame2::currentFrame = 0;
int MoveFloor::currentFrame = 0;
int MoveVertical::currentFrame = 0;
int Brick2::speed = 4;
//----------------------------------------------------------------------------------------------------------------//

MagmaBoard::~MagmaBoard()
{
    killTimer(timerId);
}

//----------------------------------------------------------------------------------------------------------------//


void MagmaBoard::timerEvent(QTimerEvent *)
{
    flameAnim();
    splashScreen();
    movementRole();
    getModel()->brickOrganisation();
    goldAnim();
    hurted();
    flying();
    GameOver();
    view->repaint();
}


void MagmaBoard::stopGame()
{
    gameStarted = false;
}

//----------------------------------------------------------------------------------------------------------------//

void MagmaBoard::movementRole()
{
    int y=model->getRole()->getRect().y();
    if(model->getRole()->getIsFlying() && (model->getRole()->getGoldNumber() > model->getRole()->getGoldNumberWhenFly() + 30))
        model->getRole()->setIsFlying(false);

    if(getIsJumping()){
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

    if((!intersectBottomRole(0) && !getIsJumping())){
        yRelatif=(-0.02*(xRelatif*xRelatif));
        for(int i=0;i<4;++i){xRelatif += 1;}
        y = startJumpY-yRelatif;
        moveXRole(y);
        model->getRole()->setCurrentFrame(0);
    }

}


void MagmaBoard::movementFly(int i)
{
        int x=model->getFly()->at(i)->getRect().x();
        if(model->getFly()->at(i)->getMoveCount()>0){

            model->getFly()->at(i)->setmoveCount(model->getFly()->at(i)->getMoveCount() - 1);
            if(moveMap  ){
                if(getModel()->getFly()->at(i)->getUp())
                    model->getFly()->at(i)->move(x-Brick2::speed, model->getFly()->at(i)->getRect().y() - 1);
                else
                    model->getFly()->at(i)->move(x-Brick2::speed, model->getFly()->at(i)->getRect().y() + 1);
            }
            else {
                if(getModel()->getFly()->at(i)->getUp())
                    model->getFly()->at(i)->move(x, model->getFly()->at(i)->getRect().y() - 1);
                else
                    model->getFly()->at(i)->move(x, model->getFly()->at(i)->getRect().y() + 1);
            }
        }
        else
            moveBrick(x ,model->getFly()->at(i));
}


void MagmaBoard::moveBrick(int x ,Brick2 * b)
{
    int speed;
    if(moveMap )
        speed=Brick2::speed ;
    else
        speed = 0;


    if(intersectBottomBrick(b)){
        if(b->getMoveX()){
            b->move(x-speed+2, b->getRect().y());
            if(intersectRightBrick(b))
                b->setMoveX(false);
        }
        else if(!b->getMoveX()){
            b->move(x-speed-2, b->getRect().y());
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
void MagmaBoard::movefloor(int x ,Brick2 * b)
{
    int speed;
    if(moveMap )
        speed=Brick2::speed ;
    else
        speed = 0;

    if(intersectBottomBrick(b)){
        if(b->getMoveX()){
            b->move(x-speed+2, b->getRect().y());
            if(intersectRightBrick(b))
                b->setMoveX(false);
        }
        else if(!b->getMoveX()){
            b->move(x-speed-2, b->getRect().y());
            if( intersectLeftBrick(b) || b->getRect().x()<3)
                b->setMoveX(true);
        }
        b->setYR(b->getYR());
        b->setXR(b->getXR());
        b->setStartY(b->getRect().y());
    }
    else{
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
void MagmaBoard::movevertical(int x , Brick2 *b)
{
    int speed;
    if(moveMap )
        speed=Brick2::speed ;
    else
        speed = 0;
    if(b->getRect().y()>=340){
        b->setMoveUp(false);
    }
    if(b->getRect().y()<=20){
        b->setMoveUp(true);
    }
    if(b->getMoveUp()){
        b->move(x-speed,b->getRect().y()+3);
    }else {
    b->move(x-speed,b->getRect().y()-3);
}}

void MagmaBoard::moveXRole(int y)
{
    int x=model->getRole()->getRect().x();

    if(!intersectLeftRole(0) && model->getRole()->getRect().x()>=2 && getIsMovingL() )
        x -= Brick2::speed;
    else if( !intersectRightRole(0) && model->getRole()->getRect().x()<=350  && getIsMovingR())
        x += Brick2::speed;
    if( !intersectRightRole(0)&& model->getRole()->getRect().x()>=350  && getIsMovingR() ){
        moveMap=true;
    }else if (model->getRole()->getRect().x()>360){
        moveMap = true;
    }
    else
        moveMap=false;
    model->getRole()->move(x,y);
}

//----------------------------------------------------------------------------------------------------------------//

bool MagmaBoard::intersectTopRole(int i)
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
                        model->createFly(model->getSafes()->at(i)->getRect().x(), model->getSafes()->at(i)->getRect().y(), true);
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

bool MagmaBoard::intersectBottomRole(int i)
{
    if(i<model->getFloors()->size()
            || i<model->getSafes()->size()
           ){
        if(!model->getFloors()->empty() && i<model->getFloors()->size()){
            if(model->getRole()->intersectBottom(model->getFloors()->at(i)->getRect()))
                return true;
        }
        if(!model->getSafes()->empty() && i<model->getSafes()->size()){
            if(model->getRole()->intersectBottom(model->getSafes()->at(i)->getRect())){
                return true;
            }
        }
        if(!model->getMoveFLoor()->empty() && i<model->getMoveFLoor()->size()){
            if(model->getRole()->intersectBottom(model->getMoveFLoor()->at(i)->getRect()) ){
                intersectYMoveFloorRole(i);
                return true;
            }
        }
        if(!model->getMoveVertical()->empty() && i<model->getMoveVertical()->size()){
            if(model->getRole()->intersectBottom(model->getMoveVertical()->at(i)->getRect()) ){
                intersectYMoveVerticalRole(i);
                return true;
            }
        }
        intersectBottomRole(i+1);
    }
    else
        return false;
}

bool MagmaBoard::intersectLeftRole(int i)
{
    if(i<model->getFloors()->size()
            || i<model->getSafes()->size()
            || i<model->getMoveFLoor()->size()
            || i<model->getMoveVertical()->size()){
    if(!model->getFloors()->empty() && i<model->getFloors()->size()){
        if(model->getRole()->intersectLeft(model->getFloors()->at(i)->getRect()))
            return true;
    }
    if(!model->getSafes()->empty() && i<model->getSafes()->size()){
        if(model->getRole()->intersectLeft(model->getSafes()->at(i)->getRect()))
            return true;
    }
    if(!model->getMoveFLoor()->empty() && i<model->getMoveFLoor()->size()){
        if(model->getRole()->intersectLeft(model->getMoveFLoor()->at(i)->getRect()))
            return true;
        }
    if(!model->getMoveVertical()->empty() && i<model->getMoveVertical()->size()){
        if(model->getRole()->intersectLeft(model->getMoveVertical()->at(i)->getRect()))
            return true;
        }
    intersectLeftRole(i+1);
    }
    else
        return false;
}

bool MagmaBoard::intersectRightRole(int i)
{
    if(i<model->getFloors()->size()
            || i<model->getSafes()->size()
            || i<model->getMoveFLoor()->size()
            || i<model->getMoveVertical()->size()){
        if(!model->getFloors()->empty() && i<model->getFloors()->size() ){
            if(model->getRole()->intersectRight(model->getFloors()->at(i)->getRect()))
                return true;

        }
        if(!model->getSafes()->empty() && i<model->getSafes()->size()){
            if(model->getRole()->intersectRight(model->getSafes()->at(i)->getRect()))
                return true;
        }
        if(!model->getMoveFLoor()->empty() && i<model->getMoveFLoor()->size()){
            if(model->getRole()->intersectRight(model->getMoveFLoor()->at(i)->getRect()))
                return true;
        }
        if(!model->getMoveVertical()->empty() && i<model->getMoveVertical()->size()){
            if(model->getRole()->intersectRight(model->getMoveVertical()->at(i)->getRect()))
                return true;
        }
        intersectRightRole(i+1);
    }
    else
        return false;
}

void MagmaBoard::intersectGoldRole(int i)
{
    if(model->getRole()->intersect(model->getGold()->at(i)->getRect())){
        model->getGold()->at(i)->setDestroyed(true);
        model->getRole()->setGoldNumber(model->getRole()->getGoldNumber()+1);
    }
}

void MagmaBoard::intersectFlameRole(int i)
{
        if(model->getRole()->intersect(model->getFlame()->at(i)->getRect()) && !model->getRole()->getUntouchable()){
            showBloodCount = 0;
            this->model->getRole()->setIsHurted(true);
        }
}

void MagmaBoard::intersectYMoveFloorRole(int i)
{
    if(!getModel()->getRole()->getIsMovingL()
            && !getModel()->getRole()->getIsMovingR()
            && !model->getMoveFLoor()->at(i)->isDestroyed()){
        getModel()->getRole()->move(getModel()->getMoveFLoor()->at(i)->getRect().x(), getModel()->getRole()->getRect().y());
    }
}

void MagmaBoard::intersectYMoveVerticalRole(int i)
{
    if(!getModel()->getRole()->getIsMovingL()
            && !getModel()->getRole()->getIsMovingR()
            && !model->getMoveVertical()->at(i)->isDestroyed()){
        getModel()->getRole()->move(getModel()->getMoveVertical()->at(i)->getRect().x(), getModel()->getRole()->getRect().y());
    }
}

void MagmaBoard::intersectFlyRole(int i)
{
        if(model->getRole()->intersect(model->getFly()->at(i)->getRect())){
            model->getFly()->at(i)->setDestroyed(true);
            model->getRole()->setIsFlying(500);
            model->getRole()->setGoldNumberWhenFly(model->getRole()->getGoldNumber());
            model->getRole()->setLife(model->getRole()->getLife() + 1);
            Brick2::speed = 8;
            yRelatif=(-0.02*(xRelatif*xRelatif)+350);
        }

}

void MagmaBoard::flying()
{
    if (getModel()->getRole()->getIsFlying() != 0) {
        getModel()->getRole()->setIsFlying(getModel()->getRole()->getIsFlying() - 1);
        cout << getModel()->getRole()->getIsFlying() << endl;
    }
}

bool MagmaBoard::intersectBottomBrick(Brick2 * m)
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
bool MagmaBoard::intersectLeftBrick(Brick2 * m)
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

bool MagmaBoard::intersectRightBrick(Brick2 * m)
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

void MagmaBoard::splashScreen()
{
    if(getModel()->getSplashScreen()->getType() == SplashScreenType2::GO){
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

void MagmaBoard::goldAnim()
{
    if(tempGold == 20){
        Gold2::currentFrame += 40;
        if (Gold2::currentFrame >= 120)
            Gold2::currentFrame = 0;
        tempGold = 0;
    }
    else
        tempGold++;
}

void MagmaBoard::MoveFloorAnim(int i)
{
    if(tempMoveFloor == 15){
        MoveFloor::currentFrame += 50;
        if (MoveFloor::currentFrame >= 150)
            MoveFloor::currentFrame = 1;
        tempMoveFloor = 0;
    }
    else
        tempMoveFloor++;
        int x=model->getMoveFLoor()->at(i)->getRect().x();
        if(!model->getMoveFLoor()->at(i)->isDestroyed()){
            movefloor(x ,model->getMoveFLoor()->at(i));
            if(model->getMoveFLoor()->at(i)->getMoveX())
                getModel()->getMoveFLoor()->at(i)->setSprite(QString(":magma/movebrick.png"));
            else
                getModel()->getMoveFLoor()->at(i)->setSprite(QString(":magma/movebrick.png"));
            model->getMoveFLoor()->at(i)->setSrcRect(QRect(MoveFloor::currentFrame, 0, model->getMoveFLoor()->at(i)->getRect().width(), model->getMoveFLoor()->at(i)->getRect().height()));
        }
        else{
            model->getMoveFLoor()->at(i)->setSrcRect(QRect(0, 0, model->getMoveFLoor()->at(i)->getRect().width(), model->getMoveFLoor()->at(i)->getRect().height()));

        }
}
void MagmaBoard::MoveVerticalAnim(int i){
{
    if(tempMoveVertical == 15){
        MoveVertical::currentFrame += 149;
        if (MoveVertical::currentFrame >= 150)
            MoveVertical::currentFrame = 1;
        tempMoveVertical = 0;
    }
    else
        tempMoveVertical++;
        int x=model->getMoveVertical()->at(i)->getRect().x();
        if(!model->getMoveVertical()->at(i)->isDestroyed()){
            movevertical(x ,model->getMoveVertical()->at(i));

            if(model->getMoveVertical()->at(i)->getMoveX())
                getModel()->getMoveVertical()->at(i)->setSprite(QString(":magma/movebrick.png"));
            else
                getModel()->getMoveVertical()->at(i)->setSprite(QString(":magma/movebrick.png"));
            model->getMoveVertical()->at(i)->setSrcRect(QRect(0, 0, model->getMoveVertical()->at(i)->getRect().width(), model->getMoveVertical()->at(i)->getRect().height()));
        }
        else{
            model->getMoveVertical()->at(i)->setSrcRect(QRect(0, 0, model->getMoveVertical()->at(i)->getRect().width(), model->getMoveVertical()->at(i)->getRect().height()));

        }
        return;
}}
void MagmaBoard::flameAnim()
{

    if(tempFlame == 10){
        Flame2::currentFrame += 58;
        if (Flame2::currentFrame >= 520)
            Flame2::currentFrame = 3;
        tempFlame = 0;
    }
    else
        tempFlame++;
    for(int i = 0; i<model->getFlame()->size(); i++){
        int x=model->getFlame()->at(i)->getRect().x();
        moveBrick(x ,model->getFlame()->at(i));
        model->getFlame()->at(i)->setSrcRect(QRect(Flame2::currentFrame, 0, model->getFlame()->at(i)->getRect().width(), model->getFlame()->at(i)->getRect().height()));
    //view->update(model->getFlame()->at(i)->getRect());
    view->update(model->getFlame()->at(i)->getSrcRect());}
}

void MagmaBoard::BackgroundAnim(int i)
{
    if(iterBackground == 2){
        model->getBackground()->at(i)->moveBrick();
        iterBackground=0;
    }
    else{
        iterBackground++;
    }
}

void MagmaBoard::hurted()
{
    if(model->getRole()->getIsHurted()){
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
}

bool MagmaBoard::GameOver(){
    if(getModel()->getRole()->getLife() < 0 || getModel()->getRole()->getRect().y() > 500){
        if(getModel()->getSplashScreen()->getType() != SplashScreenType2::GAME_OVER){
            getModel()->createGameOver(220, 80);
            getModel()->getSplashScreen()->setType(SplashScreenType2::GAME_OVER);
        }
        model->getSplashScreen()->setIsSplashScreen(true);
        return true;
    }
    else
        return false;
}

bool MagmaBoard::Completed(){
    if(getModel()->getRole()->getGoldNumber() >= 200){
        if(getModel()->getSplashScreen()->getType() != SplashScreenType2::COMPLETED){
            getModel()->createCompleted(360, 120);
            getModel()->getSplashScreen()->setType(SplashScreenType2::COMPLETED);
        }
        model->getSplashScreen()->setIsSplashScreen(true);
        return true;
    }
    else
        return false;
}

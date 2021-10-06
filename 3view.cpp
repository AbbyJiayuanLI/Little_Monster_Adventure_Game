#include "3view.h"
#include <QPainter>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <tuple>
#include "3model.h"
#include "3paintvisitor.h"

#include <iostream>
using namespace std;

View2::View2(QWidget *parent): QWidget(parent)
{}

View2::~View2()
{
    std::cout << ("View deleted\n");
}


void View2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    PaintVisitor2 *pVisitor = new PaintVisitor2(&painter);

    for(int i = control->getModel()->getCompteur()->indexOf(control->getModel()->getCompteur()->first()); i<control->getModel()->getCompteur()->size(); i++){
        if(control->getMoveMap()){
            control->getModel()->getCompteur()->at(i)->moveBrick();
        }
    }

    for(int i = control->getModel()->getBackground()->indexOf(control->getModel()->getBackground()->first()); i<control->getModel()->getBackground()->size(); i++){
        if(control->getMoveMap())
            control->BackgroundAnim(i);
          // painter.drawPixmap(event->rect(), control->getModel()->getBackground()->at(i)->getSprite(), control->getModel()->getBackground()->at(i)->getSrcRect());
        control->getModel()->getBackground()->at(i)->accept(pVisitor);
      }

    for(int i = 0; i<control->getModel()->getFly()->size(); i++){
        control->intersectFlyRole(i);
        control->movementFly(i);
        control->getModel()->getFly()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getFloors()->size(); i++){
    if(control->getMoveMap())
            control->getModel()->getFloors()->at(i)->moveBrick();
        control->getModel()->getFloors()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getSafes()->size(); i++){
        if(control->getMoveMap())
            control->getModel()->getSafes()->at(i)->moveBrick();
        control->getModel()->getSafes()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getGold()->size(); i++){
        control->intersectGoldRole(i);
        if(control->getMoveMap())
           control->getModel()->getGold()->at(i)->moveBrick();
        control->getModel()->getGold()->at(i)->setSrcRect(QRect(Gold2::currentFrame, 0, control->getModel()->getGold()->at(i)->getRect().width(), control->getModel()->getGold()->at(i)->getRect().height()));
        control->getModel()->getGold()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getFlame()->size(); i++){
      control->intersectFlameRole(i);
      control->getModel()->getFlame()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i < control->getModel()->getMoveFLoor()->size();i++){
        if (!control->getModel()->getMoveFLoor()->at(i)->isDestroyed()){
            control->MoveFloorAnim(i);
            control->getModel()->getMoveFLoor()->at(i)->accept(pVisitor);
        }
    }

    for(int i = 0; i < control->getModel()->getMoveVertical()->size();i++){
        if (!control->getModel()->getMoveVertical()->at(i)->isDestroyed()){
            control->MoveVerticalAnim(i);
            control->getModel()->getMoveVertical()->at(i)->accept(pVisitor);
        }
    }

    control->getModel()->getRole()->accept(pVisitor);

    painter.drawImage(control->getModel()->getHeader()->getRect().width() - 0, control->getModel()->getHeader()->getRect().height() / 8, control->getModel()->getHeader()->getGold());
    painter.setFont(QFont("Tahoma", 17, 0, true));
    QString goldText = QString::number(control->getModel()->getRole()->getGoldNumber());
    painter.drawText(control->getModel()->getHeader()->getGoldPosition(), goldText);

    painter.save();
    if(control->getModel()->getRole()->getUntouchable())
        painter.setOpacity(0.4);
    else
        painter.setOpacity(1);

    for(int i = 0 ; i < control->getModel()->getRole()->getLife() ; i++){
        painter.drawImage(control->getModel()->getHeader()->getHeart().size().height() * i, 0, control->getModel()->getHeader()->getHeart());
    }
    painter.restore();

    if(!control->getModel()->getBlood()->getStopBlood() && control->getModel()->getRole()->getIsHurted()){ // Paint Blood when hurted
        control->getModel()->getBlood()->accept(pVisitor);
    }

    if(control->GameOver()){
        painter.fillRect(QRect(0, 0, Model2::Longueur, Model2::Hauteur), QBrush(QColor(128, 128, 255, 230)));
        closeButton = new QPushButton(this);
        closeButton->setGeometry(QRect(360,330,250,80));
        closeButton->setStyleSheet("QPushButton{border-image:url(:begin/closeButton.png);}"
                                     "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
        connect(closeButton,SIGNAL(clicked()),this,SLOT(closeGame()));
        closeButton->setVisible(true);
    }
    else if(control->Completed())
        painter.fillRect(QRect(0, 0, Model2::Longueur, Model2::Hauteur), QBrush(QColor(29, 153, 215, 230)));

    if(control->getModel()->getSplashScreen()->getIsSplashScreen()){
        control->getModel()->getSplashScreen()->accept(pVisitor);
    }
}

//-------------------------------------------------------------------------------------------------------------------//

void View2::keyPressEvent(QKeyEvent *event)
{
    if(!control->GameOver()){
        if(event->key() == Qt::Key_Right) {
            control->setIsMovingR(true);
            control->getModel()->setBulletR(true);
        }
        else if(event->key() == Qt::Key_Left) {
            control->setIsMovingL(true);
            control->getModel()->setBulletR(false);
        }
        else if(event->key() == Qt::Key_Up && control->intersectBottomRole(0)){
            control->setIsJumping(true);
            control->setXRelatif(-100);
        }
        else
            event->ignore();
    }

    if (event->key() == Qt::Key_Escape)
    {
        control->stopGame();
        qApp->exit();
    }

}

//----------------------------------------------------------------------------------------------------------------//

void View2::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right ) {
        control->setIsMovingR(false);
        control->getModel()->getRole()->stopSprite = QPixmap(":magma/role.png");
    }
    else if(event->key() == Qt::Key_Left ) {
        control->setIsMovingL(false);
        control->getModel()->getRole()->stopSprite = QPixmap(":magma/role_left.png");
    }
    else if(event->key() == Qt::Key_Space ) {
        control->setIsFiring(false);
        cout << "release_space" << endl;
    }
    else
        event->ignore();
}

void View2::closeGame()
{
    this->close();
}


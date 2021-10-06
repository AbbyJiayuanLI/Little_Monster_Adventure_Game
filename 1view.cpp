#include "1view.h"
#include <QPainter>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <QPushButton>
#include <tuple>
#include "1model.h"
#include "1paintvisitor.h"

View::View(QWidget *parent): QWidget(parent)
{}

View::~View()
{
    std::cout << ("View deleted\n");
}


void View::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
   PaintVisitor *pVisitor = new PaintVisitor(&painter);

    for(int i = control->getModel()->getCompteur()->indexOf(control->getModel()->getCompteur()->first()); i<control->getModel()->getCompteur()->size(); i++){
        if(control->getMoveMap()) {
            if (control->getModel()->getRole()->getIsJeted() == 0) {
                control->getModel()->getCompteur()->at(i)->moveBrick();
            } else {
                control->getModel()->getCompteur()->at(i)->jetmoveBrick();
            }
        } else {
            control->getModel()->getCompteur()->at(i)->automoveBrick();
        }
    }

    for(int i = control->getModel()->getBackground()->indexOf(control->getModel()->getBackground()->first()); i<control->getModel()->getBackground()->size(); i++){
        control->getModel()->getBackground()->at(i)->accept(pVisitor);
      }

    for (int i = 0; i < control->getModel()->getBullet()->size(); i++) {
        if (!control->getModel()->getBullet()->at(i)->isDestroyed()){
            control->intersectBullet(i);
            control->movementBullet(i);
            control->getModel()->getBullet()->at(i)->accept(pVisitor);
        }
    }

    for(int i = 0; i<control->getModel()->getFloors()->size(); i++){
        if(control->getMoveMap()) {
            if (control->getModel()->getRole()->getIsJeted() == 0) {
                control->getModel()->getFloors()->at(i)->moveBrick();
            } else {
                control->getModel()->getFloors()->at(i)->jetmoveBrick();
            }

        } else {
            control->getModel()->getFloors()->at(i)->automoveBrick();
        }
        control->getModel()->getFloors()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getSafes()->size(); i++){
        if(control->getMoveMap()) {
            if (control->getModel()->getRole()->getIsJeted() == 0) {
                control->getModel()->getSafes()->at(i)->moveBrick();
            } else {
                control->getModel()->getSafes()->at(i)->jetmoveBrick();
            }

        } else {
            control->getModel()->getSafes()->at(i)->automoveBrick();
        }
        control->getModel()->getSafes()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getGold()->size(); i++){
        control->intersectGoldRole(i);
        if(control->getMoveMap()) {
            if (control->getModel()->getRole()->getIsJeted() == 0) {
                control->getModel()->getGold()->at(i)->moveBrick();
            } else {
                control->getModel()->getGold()->at(i)->jetmoveBrick();
            }
        } else {
            control->getModel()->getGold()->at(i)->automoveBrick();
        }
        control->getModel()->getGold()->at(i)->setSrcRect(QRect(Gold::currentFrame, 0, control->getModel()->getGold()->at(i)->getRect().width(), control->getModel()->getGold()->at(i)->getRect().height()));
        control->getModel()->getGold()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getShield()->size(); i++){
        control->intersectShieldRole(i);
        if(control->getMoveMap()) {
            if (control->getModel()->getRole()->getIsJeted() == 0) {
                control->getModel()->getShield()->at(i)->moveBrick();
            } else {
                control->getModel()->getShield()->at(i)->jetmoveBrick();
            }

        } else {
            control->getModel()->getShield()->at(i)->automoveBrick();
        }
        control->getModel()->getShield()->at(i)->setSrcRect(QRect(Shield::currentFrame, 0, control->getModel()->getShield()->at(i)->getRect().width(), control->getModel()->getShield()->at(i)->getRect().height()));
        control->getModel()->getShield()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getJet()->size(); i++){
        control->intersectJetRole(i);
        if(control->getMoveMap()) {
            if (control->getModel()->getRole()->getIsJeted() == 0) {
                control->getModel()->getJet()->at(i)->moveBrick();
            } else {
                control->getModel()->getJet()->at(i)->jetmoveBrick();
            }

        } else {
            control->getModel()->getJet()->at(i)->automoveBrick();
        }
        control->getModel()->getJet()->at(i)->setSrcRect(QRect(Jet::currentFrame, 0, control->getModel()->getJet()->at(i)->getRect().width(), control->getModel()->getJet()->at(i)->getRect().height()));
        control->getModel()->getJet()->at(i)->accept(pVisitor);
    }

    if (control->getModel()->getRole()->getIsShielded()) {
        shield_visual s(control->getModel()->getRole()->getRect().x()-12,control->getModel()->getRole()->getRect().y(),":land/shield_visual.png");
        s.accept(pVisitor);
    }



    for(int i = 0; i<control->getModel()->getBulletItem()->size(); i++){
        control->intersectBulletitemRole(i);
        if(control->getMoveMap()) {
            if (control->getModel()->getRole()->getIsJeted() == 0) {
                control->getModel()->getBulletItem()->at(i)->moveBrick();
            } else {
                control->getModel()->getBulletItem()->at(i)->jetmoveBrick();
            }

        } else {
            control->getModel()->getBulletItem()->at(i)->automoveBrick();
        }
        control->getModel()->getBulletItem()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getFlame()->size(); i++){
        control->intersectFlameRole(i);
      control->getModel()->getFlame()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getMonster()->size(); i++){
        if(!control->getModel()->getMonster()->at(i)->isDestroyed()){
            control->MonsterAnim(i);
            control->getModel()->getMonster()->at(i)->accept(pVisitor);
        }
    }

    if(control->getModel()->getRole()->getIsLittle()){
        control->getModel()->getRole()->setRect(QRect(control->getModel()->getRole()->getRect().x(), control->getModel()->getRole()->getRect().y(), 25, control->getModel()->getRole()->getMoveRSprite().height() - 30));
        control->getModel()->getRole()->setSrcRect(QRect(control->getModel()->getRole()->getCurrentFrame()+6, 0, control->getModel()->getRole()->getRect().width()+25, control->getModel()->getRole()->getRect().height()+27));
    }
    else{
        control->getModel()->getRole()->setRect(QRect(control->getModel()->getRole()->getRect().x(), control->getModel()->getRole()->getRect().y(), 45, control->getModel()->getRole()->getMoveRSprite().height() - 7));
        control->getModel()->getRole()->setSrcRect(QRect(control->getModel()->getRole()->getCurrentFrame()+6, 1, control->getModel()->getRole()->getRect().width(), control->getModel()->getRole()->getRect().height()));
    }

    control->getModel()->getRole()->accept(pVisitor);

    painter.drawImage(control->getModel()->getHeader()->getRect().width() - 0, control->getModel()->getHeader()->getRect().height() / 8, control->getModel()->getHeader()->getGold());
    painter.drawImage(control->getModel()->getHeader()->getRect().width() - 100, control->getModel()->getHeader()->getRect().height() / 8, control->getModel()->getHeader()->getBullet());
    painter.drawImage(control->getModel()->getHeader()->getRect().width() - 640, control->getModel()->getHeader()->getRect().height() / 8, control->getModel()->getHeader()->getWalked());
    painter.setFont(QFont("Tahoma", 17, 0, true));
    QString goldText = QString::number(control->getModel()->getRole()->getGoldNumber());
    QString bulletText = QString::number(control->getModel()->getRole()->getBulletNumber());
    QString walkedText = QString::number(control->getModel()->getRole()->getWalkedDistance());
    painter.drawText(control->getModel()->getHeader()->getGoldPosition(), goldText);
    painter.drawText(control->getModel()->getHeader()->getBulletPosition(), bulletText);
    painter.drawText(control->getModel()->getHeader()->getWalkedPosition(), walkedText);

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
        painter.fillRect(QRect(0, 0, Model::Longueur, Model::Hauteur), QBrush(QColor(128, 128, 255, 230)));
        painter.drawImage(100, 120, control->getModel()->getHeader()->getGold());
        painter.drawImage(100, 180, control->getModel()->getHeader()->getWalked());
        QString finalGold = QString::number(control->getModel()->getRole()->getGoldNumber());
        QString finalDistance = QString::number(control->getModel()->getRole()->getWalkedDistance());
        painter.drawText(QPoint(150,145), finalGold);
        painter.drawText(QPoint(150,205), finalDistance);

        closeButton = new QPushButton(this);
        closeButton->setGeometry(QRect(360,330,250,80));
        closeButton->setStyleSheet("QPushButton{border-image:url(:begin/closeButton.png);}"
                                     "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
        connect(closeButton,SIGNAL(clicked()),this,SLOT(closeGame()));
        closeButton->setVisible(true);

    }
    if(control->getModel()->getSplashScreen()->getIsSplashScreen()){
        control->getModel()->getSplashScreen()->accept(pVisitor);
    }
}

//-------------------------------------------------------------------------------------------------------------------//

void View::keyPressEvent(QKeyEvent *event)
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
        else if(event->key() == Qt::Key_Space) {
            if (control->getModel()->getRole()->getBulletNumber() > 0) {
                if (control->getModel()->getBulletR()) {
                    control->getModel()->createBullet(control->getModel()->getRole()->getRect().x()+40, control->getModel()->getRole()->getRect().y()+10, ":land/bullet.png");
                    control->getModel()->getBullet()->at(control->getModel()->getBullet()->size()-1)->setBulletR(true);
                }
                else {
                    control->getModel()->createBullet(control->getModel()->getRole()->getRect().x()-40, control->getModel()->getRole()->getRect().y()+10, ":land/bullet_left.png");
                    control->getModel()->getBullet()->at(control->getModel()->getBullet()->size()-1)->setBulletR(false);
                }
            control->getModel()->getRole()->setBulletNumber(control->getModel()->getRole()->getBulletNumber() - 1);
            }
        }
        else
            event->ignore();
    }
}

//----------------------------------------------------------------------------------------------------------------//

void View::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right ) {
        control->setIsMovingR(false);
        control->getModel()->getRole()->stopSprite = QPixmap(":land/role.png");
    }
    else if(event->key() == Qt::Key_Left ) {
        control->setIsMovingL(false);
        control->getModel()->getRole()->stopSprite = QPixmap(":land/role_left.png");
    }
    else if(event->key() == Qt::Key_Space ) {
        control->setIsFiring(false);
    }
    else
        event->ignore();
}

void View::closeGame()
{
    this->close();
}

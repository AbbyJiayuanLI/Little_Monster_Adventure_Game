#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QKeyEvent>
#include <QMutableMapIterator>
#include <QDebug>
#include <QPushButton>
#include "1safe.h"
#include "1floor.h"
#include "1role.h"
#include "1gold.h"
#include "1shield.h"
#include "1jet.h"
#include "1bullet_item.h"
#include "1view.h"
#include "1landboard.h"
#include "1monster.h"
#include "1blood.h"

class LandBoard;

class View : public QWidget
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
     ~View();
    void setControl(LandBoard *control){ this->control = control; }

public slots:
    void closeGame();

private:
    QPushButton *closeButton;
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    LandBoard *control;
    int marioSize;
    //int timerId;
    QTimer *autoMoveTimer;
};

#endif // VIEW_H

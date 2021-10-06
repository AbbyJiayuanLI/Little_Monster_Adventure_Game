#ifndef VIEW2_H
#define VIEW2_H

#include <QWidget>
#include <QKeyEvent>
#include <QMutableMapIterator>
#include <QDebug>
#include <QPushButton>

#include "3safe.h"
#include "3floor.h"
#include "3role.h"
#include "3gold.h"
#include "3view.h"
#include "3magmaboard.h"
#include "3movefloor.h"
#include "3fly.h"
#include "3blood.h"

class MagmaBoard;

class View2 : public QWidget
{
    Q_OBJECT

public:
    View2(QWidget *parent = 0);
     ~View2();
    void setControl(MagmaBoard *control){ this->control = control; }

public slots:
    void closeGame();

private:
    QPushButton *closeButton;
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    MagmaBoard *control;
    int marioSize;
    //int timerId;
    QTimer *autoMoveTimer;
};

#endif // VIEW2_H

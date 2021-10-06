#include "mainwindow.h"
#include "2seaboard.h"
#include "1landboard.h"
#include "1model.h"
#include "1view.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QRect>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <tuple>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qsrand(QTime::currentTime().second());

    // Set size.
    this->resize(1400,800);

    /* Init 5 buttons. */
    this->landButton = new QPushButton(this);
    this->landButton->setGeometry(QRect(1,1,1,1));
    this->landButton->setStyleSheet("QPushButton{border-image:url(:begin/landButton.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->landButton,SIGNAL(clicked()),this,SLOT(landMode()));

    this->seaButton = new QPushButton(this);
    this->seaButton->setGeometry(QRect(1,1,1,1));
    this->seaButton->setStyleSheet("QPushButton{border-image:url(:begin/seaButton.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->seaButton,SIGNAL(clicked()),this,SLOT(seaMode()));

    this->magmaButton = new QPushButton(this);
    this->magmaButton->setGeometry(QRect(1,1,1,1));
    this->magmaButton->setStyleSheet("QPushButton{border-image:url(:begin/magmaButton.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->magmaButton,SIGNAL(clicked()),this,SLOT(magmaMode()));

    this->infoButton = new QPushButton(this);
    this->infoButton->setGeometry(QRect(1,1,1,1));
    this->infoButton->setStyleSheet("QPushButton{border-image:url(:begin/infoButton.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->infoButton,SIGNAL(clicked()),this,SLOT(information()));

    this->closeButton = new QPushButton(this);
    this->closeButton->setGeometry(QRect(1,1,1,1));
    this->closeButton->setStyleSheet("QPushButton{border-image:url(:begin/closeButton.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->closeButton,SIGNAL(clicked()),this,SLOT(gameOver()));


    /* The refresh rate : 50Hz */
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    timer.start(20);

//    connect(this->overboard,SIGNAL(buttonVisible(bool,bool,bool)),this,SLOT(setButtonVisible(bool,bool,bool)));
//    把信号连回来

//   原paintEvent

//    QPainter painter(bufferPixmap);
//    QPainter mainWindowPainter(this);
//    mainWindowPainter.drawPixmap(QRect(100,100,400,400),bufferPixmap);
    }


MainWindow::~MainWindow(){
    delete this->landButton;
    delete this->seaButton;
    delete this->magmaButton;
    delete this->closeButton;
    delete this->infoButton;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    this->landButton->setGeometry(QRect(int((200.0/1400)*this->width()),
                                        int((400.0/800)*this->height()),
                                        int((300.0/1400)*this->width()),
                                        int((182.0/1400)*this->width())));
    this->seaButton->setGeometry(QRect(int((550.0/1400)*this->width()),
                                        int((400.0/800)*this->height()),
                                        int((300.0/1400)*this->width()),
                                        int((182.0/1400)*this->width())));
    this->magmaButton->setGeometry(QRect(int((900.0/1400)*this->width()),
                                        int((400.0/800)*this->height()),
                                        int((300.0/1400)*this->width()),
                                        int((182.0/1400)*this->width())));
    this->infoButton->setGeometry(QRect(int((375.0/1400)*this->width()),
                                        int((600.0/800)*this->height()),
                                        int((250.0/1400)*this->width()),
                                        int((100.0/1400)*this->width())));
    this->closeButton->setGeometry(QRect(int((740.0/1400)*this->width()),
                                        int((593.0/800)*this->height()),
                                        int((270.0/1400)*this->width()),
                                        int((120.0/1400)*this->width())));
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter Painter(this);
    Painter.drawPixmap(QRect(0,0,this->width(),this->height()),QPixmap(":begin/background.png"));
    Painter.drawPixmap(QRect(int((110.0/1400)*this->width()),
                             int((180.0/800)*this->height()),
                             int((1200.0/1400)*this->width()),
                             int((200.0/1400)*this->width())),QPixmap(":begin/title.png"));
    if (info) Painter.drawPixmap(QRect(0,0,this->width(),(343.0/800)*this->height()),QPixmap(":begin/information.png"));
}

/* landMode Initialization */

void MainWindow::landMode()
{
    land = true;
    this->close();
}


/* seaMode Initialization */

void MainWindow::seaMode()
{
    sea = true;
    this->close();
}


/* magmaMode Initialization */

void MainWindow::magmaMode()
{
    magma = true;
    this->close();
}


void MainWindow::gameOver(){
    this->close();
}

void MainWindow::information()
{
    info = true;
}




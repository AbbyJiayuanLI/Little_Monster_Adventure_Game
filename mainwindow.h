#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include "1landboard.h"


class MainWindow : public QMainWindow
{    
    Q_OBJECT
private:

    QTimer timer; // Main timer, refresh the interface.

    /* Buttons on the start panel. */
    QPushButton *landButton;
    QPushButton *seaButton;
    QPushButton *magmaButton;
    QPushButton *infoButton;
    QPushButton *closeButton;

    bool info = false;

public slots:
    void landMode();
    void seaMode();
    void magmaMode();
    void gameOver();
    void information();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); 
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    bool land = false;
    bool sea = false;
    bool magma = false;

};

#endif // MAINWINDOW_H

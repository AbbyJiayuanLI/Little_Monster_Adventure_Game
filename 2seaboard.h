#ifndef SeaBoard_H
#define SeaBoard_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QSound>
#include "2elebackground.h"
#include "2eleground.h"
#include "2elerole.h"
#include "2elepipe.h"
#include "2elescoreboard.h"
#include "2elereadyboard.h"
#include "2eleoverboard.h"
#include "2eletitleboard.h"

/* 4 status */
enum SeaModeStatus{GAMETITLE,
                GAMEREADY,
                GAMEPLAY,
                GAMEOVER};

class SeaBoard : public QMainWindow
{
    Q_OBJECT
private:
    QPixmap *bufferPixmap;

    /* Buttons on the start panel. */
    QPushButton *startButton;
    QPushButton *closeButton;
    QPushButton *infoButton;

    /* Elements need to draw */
    EleBackground *background;
    EleGround *ground;
    EleRole *role;
    ElePipe *pipe[3];
    EleScoreBoard *scoreboard;
    EleReadyBoard *readyboard;
    EleOverBoard *overboard;
    EleTitleBoard *titleboard;

    /* Sound */
    QSound *soundDie;
    QSound *soundHit;
    QSound *soundPoint;
    QSound *soundSwooshing;
    QSound *soundWing;

    int score; // Game score
    QRectF impactRoleRect; // the rectangle used to test the impact of role.
    SeaModeStatus status;
    QTimer timer; // Main timer, refresh the interface.

    /*Corresponding  to 4 game status. */
    void gameTitle();
    void gameReady();
    void gamePlay();
    void gameOver();
public:
    SeaBoard(QWidget *parent = 0);
    ~SeaBoard();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *);
    void center(QWidget &widget);
    void createButton();
    void deleteButton();
public slots:
    void getScore(); // socre increase.
    void startGame(); // The button clicked , game began.
    void closeGame();// The button clicked , game exit.
    void displayInfo();
    void setButtonVisible(bool,bool,bool); // set 3 button visible .
};

#endif // SeaBoard_H

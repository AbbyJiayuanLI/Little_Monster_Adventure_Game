#include "2seaboard.h"

SeaBoard::SeaBoard(QWidget *parent)
    : QMainWindow(parent)
{
    qsrand(QTime::currentTime().second());

    this->bufferPixmap = new QPixmap(288,512);
    // Set size.
    this->resize(1400,800);

    /* Init 3 buttons. */
    createButton();

    /* Init all the game elements. */
    this->background = new EleBackground();
    this->ground = new EleGround();
    this->role = new EleRole();
    this->scoreboard = new EleScoreBoard();
    this->readyboard = new EleReadyBoard();
    this->overboard = new EleOverBoard();
    this->titleboard = new EleTitleBoard();
    this->pipe[0] = new ElePipe(0);
    this->pipe[1] = new ElePipe(1);
    this->pipe[2] = new ElePipe(2);

    this->impactRoleRect.setRect(0,0,0.4*this->role->getBindRect().width(),
                                 0.4*this->role->getBindRect().height());

    /* Sound */
    this->soundDie = new QSound(":/sea/sounds/sfx_die.wav");
    this->soundHit = new QSound(":/sea/sounds/sfx_hit.wav");
    this->soundPoint = new QSound(":/sea/sounds/sfx_point.wav");
    this->soundSwooshing = new QSound(":/sea/sounds/sfx_swooshing.wav");
    this->soundWing = new QSound(":/sea/sounds/sfx_wing.wav");

    /* The refresh rate : 50Hz */
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    timer.start(20);

    /* Connect signals and slots */
    connect(this->pipe[0],SIGNAL(pipePass()),this,SLOT(getScore()));
    connect(this->pipe[1],SIGNAL(pipePass()),this,SLOT(getScore()));
    connect(this->pipe[2],SIGNAL(pipePass()),this,SLOT(getScore()));

    connect(this->overboard,SIGNAL(buttonVisible(bool,bool,bool)),this,SLOT(setButtonVisible(bool,bool,bool)));

    // Game Start.
    this->gameTitle();
}

SeaBoard::~SeaBoard()
{
    delete this->background;
    delete this->ground;
    delete this->role;
    delete this->scoreboard;
    delete this->readyboard;
    delete this->overboard;
    delete this->titleboard;
    delete this->pipe[0];
    delete this->pipe[1];
    delete this->pipe[2];
}

void SeaBoard::keyPressEvent(QKeyEvent *event)
{
    /*When the game is ready , start the game. */
    if( this->status == GAMEREADY && event->key() == Qt::Key_Up )
    {
        this->gamePlay();
    }

    /* When the game playing, role up */

    if( this->status == GAMEPLAY && event->key() == Qt::Key_Up )
    {
        this->soundWing->stop();
        this->role->roleUp();
        this->soundWing->play();
    }

}


void SeaBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this->bufferPixmap);

    /* Draw all the elements. */
    this->background->logic();
    this->background->draw(&painter);

    this->pipe[0]->logic();
    this->pipe[0]->draw(&painter);

    this->pipe[1]->logic();
    this->pipe[1]->draw(&painter);

    this->pipe[2]->logic();
    this->pipe[2]->draw(&painter);

    this->role->logic();
    this->role->draw(&painter);

    this->scoreboard->logic();
    this->scoreboard->draw(&painter);

    this->readyboard->logic();
    this->readyboard->draw(&painter);

    this->titleboard->logic();
    this->titleboard->draw(&painter);

    this->ground->logic();
    this->ground->draw(&painter);

    this->overboard->logic();
    this->overboard->draw(&painter);

    environmentElement::speedX += 0.0003;

    QPainter mainWindowPainter(this);
    mainWindowPainter.drawPixmap(QRect(0,0,this->width(),this->height()),*this->bufferPixmap);

    if(this->status == GAMEPLAY)
    {
        /* update the impact rectangle of role. */
        this->impactRoleRect.moveCenter(this->role->getBindRect().center());

        /* To test if the impact happened. */
        if(this->impactRoleRect.intersects(this->ground->getBindRect()))
        {
            this->soundHit->play();
            this->gameOver(); //Game over
        }
        if(this->impactRoleRect.intersects(this->pipe[0]->getRect(above))
           ||this->impactRoleRect.intersects(this->pipe[0]->getRect(following))
           ||this->impactRoleRect.intersects(this->pipe[1]->getRect(above))
           ||this->impactRoleRect.intersects(this->pipe[1]->getRect(following))
           ||this->impactRoleRect.intersects(this->pipe[2]->getRect(above))
           ||this->impactRoleRect.intersects(this->pipe[2]->getRect(following)))
        {
                this->soundHit->play();
                this->soundDie->play();
                this->gameOver(); //Game over
        }
    }
}

void SeaBoard::resizeEvent(QResizeEvent *)
{
    this->startButton->setGeometry(QRect(int((350.0/1400)*this->width()),
                                   int((540.0/800)*this->height()),
                                   int((300.0/1400)*this->width()),
                                   int((100.0/800)*this->height())));
    this->closeButton->setGeometry(QRect(int((750.0/1400)*this->width()),
                                         int((540.0/800)*this->height()),
                                         int((300.0/1400)*this->width()),
                                         int((100.0/800)*this->height())));
    this->infoButton->setGeometry(QRect(int((570.0/1400)*this->width()),
                                         int((290.0/512)*this->height()),
                                         int((260.0/1400)*this->width()),
                                         int((55.0/512)*this->height())));
}

void SeaBoard::gameTitle()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titleboard->enabledLogic = true;
    this->titleboard->enabledDraw = true;

    this->role->enabledLogic = false;
    this->role->enabledDraw = false;

    this->ground->enabledLogic = true;
    this->ground->enabledDraw = true;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->pipe[0]->enabledLogic = false;
    this->pipe[0]->enabledDraw = false;
    this->pipe[1]->enabledLogic = false;
    this->pipe[1]->enabledDraw = false;
    this->pipe[2]->enabledLogic = false;
    this->pipe[2]->enabledDraw = false;
    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->setButtonVisible(true,true,true);
    this->status = GAMETITLE;
}

void SeaBoard::gameReady()
{
    this->score = 0;

    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titleboard->enabledLogic = false;
    this->titleboard->enabledDraw = false;

    this->role->enabledLogic = false;
    this->role->enabledDraw = true;

    this->ground->enabledLogic = true;
    this->ground->enabledDraw = true;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->pipe[0]->enabledLogic = false;
    this->pipe[0]->enabledDraw = false;
    this->pipe[1]->enabledLogic = false;
    this->pipe[1]->enabledDraw = false;
    this->pipe[2]->enabledLogic = false;
    this->pipe[2]->enabledDraw = false;

    this->readyboard->enabledLogic = true;
    this->readyboard->enabledDraw = true;

    this->scoreboard->enabledLogic = true;
    this->scoreboard->enabledDraw = true;

    this->setButtonVisible(false,false,false);
    this->status = GAMEREADY;
}

void SeaBoard::gamePlay()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titleboard->enabledLogic = false;
    this->titleboard->enabledDraw = false;

    this->role->enabledLogic = true;
    this->role->enabledDraw = true;

    this->ground->enabledLogic = true;
    this->ground->enabledDraw = true;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->pipe[0]->enabledLogic = true;
    this->pipe[0]->enabledDraw = true;
    this->pipe[1]->enabledLogic = true;
    this->pipe[1]->enabledDraw = true;
    this->pipe[2]->enabledLogic = true;
    this->pipe[2]->enabledDraw = true;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = true;
    this->scoreboard->enabledDraw = true;

    this->status = GAMEPLAY;
}

void SeaBoard::gameOver()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titleboard->enabledLogic = false;
    this->titleboard->enabledDraw = false;

    this->role->enabledLogic = true;
    this->role->enabledDraw = true;

    this->ground->enabledLogic = false;
    this->ground->enabledDraw = true;

    this->overboard->setScore(this->score);
    this->overboard->enabledLogic = true;
    this->overboard->enabledDraw = true;

    this->pipe[0]->enabledLogic = false;
    this->pipe[0]->enabledDraw = true;
    this->pipe[1]->enabledLogic = false;
    this->pipe[1]->enabledDraw = true;
    this->pipe[2]->enabledLogic = false;
    this->pipe[2]->enabledDraw = true;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->status = GAMEOVER;
    createButton();
}

void SeaBoard::startGame()
{
    /* Init all the game elements. */
    this->background->init();
    this->ground->init();
    this->role->init();
    this->scoreboard->init();
    this->readyboard->init();
    this->overboard->init();
    this->pipe[0]->init();
    this->pipe[1]->init();
    this->pipe[2]->init();

    // Game Start.
    this->gameReady();
    this->soundSwooshing->play();
    deleteButton();
}

void SeaBoard::closeGame()
{
    this->soundSwooshing->play();
    this->close();
}

void SeaBoard::getScore()
{
    this->score += 1;
    this->scoreboard->setScore(this->score);
    this->soundPoint->play();
}

void SeaBoard::displayInfo()
{
    this->soundSwooshing->play();
    QMessageBox::information(this,"From","LiJiaYuan LiLingFeng");
}

void SeaBoard::setButtonVisible(bool _startBtn, bool _scoreBtn, bool _rateBtn)
{
    this->startButton->setVisible(_startBtn);
    this->closeButton->setVisible(_scoreBtn);
    this->infoButton->setVisible(_rateBtn);
}

void SeaBoard::createButton()
{
    this->startButton = new QPushButton(this);
    this->startButton->setGeometry(QRect(int((350.0/1400)*this->width()),
                                   int((540.0/800)*this->height()),
                                   int((300.0/1400)*this->width()),
                                   int((100.0/800)*this->height())));
    this->startButton->setStyleSheet("QPushButton{border-image:url(:sea/button_play.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->startButton,SIGNAL(clicked()),this,SLOT(startGame()));

    this->closeButton = new QPushButton(this);
    this->closeButton->setGeometry(QRect(int((750.0/1400)*this->width()),
                                         int((540.0/800)*this->height()),
                                         int((300.0/1400)*this->width()),
                                         int((100.0/800)*this->height())));
    this->closeButton->setStyleSheet("QPushButton{border-image:url(:sea/button_close.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->closeButton,SIGNAL(clicked()),this,SLOT(closeGame()));

    this->infoButton = new QPushButton(this);
    this->infoButton->setGeometry(QRect(int((570.0/1400)*this->width()),
                                         int((290.0/512)*this->height()),
                                         int((260.0/1400)*this->width()),
                                         int((55.0/512)*this->height())));
    this->infoButton->setStyleSheet("QPushButton{border-image:url(:sea/button_rate.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->infoButton,SIGNAL(clicked()),this,SLOT(displayInfo()));
}

void SeaBoard::deleteButton()
{
    delete startButton;
    delete closeButton;
    delete infoButton;
}

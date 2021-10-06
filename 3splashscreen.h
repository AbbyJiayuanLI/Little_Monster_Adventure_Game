#ifndef SPLASHSCREEN2_H
#define SPLASHSCREEN2_H

#include "3brick.h"

enum struct SplashScreenType2 { GO, GAME_OVER, COMPLETED};

class SplashScreen2 : public Brick2
{
public:
    SplashScreen2(int, int, QString);
    ~SplashScreen2();
    inline bool getIsSplashScreen(){ return isSplashScreen; }
    inline void setIsSplashScreen(bool splash){ this->isSplashScreen = splash; }
    inline void setType(SplashScreenType2 type){ this->type = type; }
    inline SplashScreenType2 getType(){ return this->type; }

private:
    bool isSplashScreen = true;
    SplashScreenType2 type = SplashScreenType2::GO;
};

#endif // SPLASHSCREEN2_H

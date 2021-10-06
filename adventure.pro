QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Project
TEMPLATE = app
QMAKE_CXXFLAGS+= -std=c++11 -O3
QMAKE_LFLAGS +=  -std=c++11

RESOURCES += adventure.qrc


SOURCES += \
    1background.cpp \
    1blood.cpp \
    1brick.cpp \
    1bullet.cpp \
    1bullet_item.cpp \
    1flame.cpp \
    1floor.cpp \
    1gold.cpp \
    1header.cpp \
    1jet.cpp \
    1model.cpp \
    1monster.cpp \
    1paintvisitor.cpp \
    1player.cpp \
    1role.cpp \
    1safe.cpp \
    1shield.cpp \
    1shield_visual.cpp \
    1splashscreen.cpp \
    1view.cpp \
    2elebackground.cpp \
    2eleground.cpp \
    2eleoverboard.cpp \
    2elepipe.cpp \
    2elereadyboard.cpp \
    2elerole.cpp \
    2elescoreboard.cpp \
    2eletitleboard.cpp \
    2environmentelement.cpp \
    2gameelement.cpp \
    main.cpp \
    mainwindow.cpp \
    2seaboard.cpp \
    1landboard.cpp \
    3background.cpp \
    3blood.cpp \
    3brick.cpp \
    3flame.cpp \
    3floor.cpp \
    3fly.cpp \
    3gold.cpp \
    3header.cpp \
    3model.cpp \
    3movefloor.cpp \
    3movevertical.cpp \
    3paintvisitor.cpp \
    3player.cpp \
    3role.cpp \
    3safe.cpp \
    3splashscreen.cpp \
    3view.cpp \
    3magmaboard.cpp

HEADERS  += \
    1background.h \
    1blood.h \
    1brick.h \
    1bullet.h \
    1bullet_item.h \
    1flame.h \
    1floor.h \
    1gold.h \
    1header.h \
    1jet.h \
    1model.h \
    1monster.h \
    1paintvisitor.h \
    1player.h \
    1role.h \
    1safe.h \
    1shield.h \
    1shield_visual.h \
    1splashscreen.h \
    1view.h \
    2elebackground.h \
    2eleground.h \
    2eleoverboard.h \
    2elepipe.h \
    2elereadyboard.h \
    2elerole.h \
    2elescoreboard.h \
    2eletitleboard.h \
    2environmentelement.h \
    2gameelement.h \
    mainwindow.h \
    2seaboard.h \
    1landboard.h \
    3background.h \
    3blood.h \
    3brick.h \
    3flame.h \
    3floor.h \
    3fly.h \
    3gold.h \
    3header.h \
    3model.h \
    3movefloor.h \
    3movevertical.h \
    3paintvisitor.h \
    3player.h \
    3role.h \
    3safe.h \
    3splashscreen.h \
    3view.h \
    3magmaboard.h

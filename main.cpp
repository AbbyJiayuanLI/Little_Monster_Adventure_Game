#include "mainwindow.h"
#include "1landboard.h"
#include "1model.h"
#include "1view.h"
#include "2seaboard.h"
#include "3magmaboard.h"
#include "3model.h"
#include "3view.h"
#include <QDesktopWidget>
#include <QApplication>


void center(QWidget &widget);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool game = true;
    while (game) {
        MainWindow w;
        w.setWindowTitle("Little Monster Adventure");
        w.show();
        a.exec();
        game = false;
        if (w.land) {
            Model m;
            View v;
            LandBoard window(&m, &v);
            v.setWindowTitle("Land Mode");
            v.show();
            center(v);
            a.exec();
            w.land = false;
            game = true;
        }
        if (w.sea) {
            SeaBoard s;
            s.setWindowTitle("Sea Mode");
            s.show();
            a.exec();
            w.sea = false;
            game = true;
        }
        if (w.magma) {
            Model2 m;
            View2 v;
            MagmaBoard window(&m, &v);
            v.setWindowTitle("Magma Mode");
            v.show();
            center(v);
            a.exec();
            w.magma = false;
            game = true;
        }
    }
    return 0;
}

void center(QWidget &widget)
{
    int x, y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - Model::Longueur) / 2;
    y = (screenHeight - Model::Hauteur) / 2;

    widget.setGeometry(x, y, Model::Longueur, Model::Hauteur);
    widget.setFixedSize(Model::Longueur, Model::Hauteur);
}

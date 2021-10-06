#include "3header.h"

Header2::Header2()
{
    this->rect = QRect(0, 0, 900, 40);
    this->color = QColor(Qt::white);
    this->text = QString("vie");
    this->heart = QImage();
    heart.load(":magma/heart.png");
    this->heartSize = heart.rect();
    gold.load(":magma/gold_small.png");
    this->goldSize = gold.rect();
    this->goldPosition = QPoint(this->getRect().width() + 40, this->getRect().height() - 10);
}

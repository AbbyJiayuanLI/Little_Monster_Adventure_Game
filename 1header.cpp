#include "1header.h"

Header::Header()
{
    this->rect = QRect(0, 0, 900, 40);
    this->color = QColor(Qt::white);
    this->text = QString("vie");
    this->heart = QImage();
    heart.load(":land/heart.png");
    this->heartSize = heart.rect();
    gold.load(":land/gold_small.png");
    this->goldSize = gold.rect();
    this->goldPosition = QPoint(this->getRect().width() + 40, this->getRect().height() - 10);
    bullet.load(":land/bullet_item_small.png");
    this->bulletSize = bullet.rect();
    this->bulletPosition = QPoint(this->getRect().width() - 60, this->getRect().height() - 10);
    walked.load(":land/walked.png");
    this->walkedSize = walked.rect();
    this->walkedPosition = QPoint(this->getRect().width() - 600, this->getRect().height() - 10);
}

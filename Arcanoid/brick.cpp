#include "brick.h"

Brick::Brick(std::string name, int x, int y)
{
    QString url = QString::fromStdString("../Arcanoid/resources/" + name + ".png");
    this->image = QImage(url);
    this->x = x;
    this->y = y;
    this->w = image.width();
    this->h = image.height();
    this->setData(QVariant::String, "Brick");
}

QRectF Brick::boundingRect() const
{
    return QRect(this->x, this->y, this->w, this->h);
}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

        painter->drawImage(x, y, image);
}


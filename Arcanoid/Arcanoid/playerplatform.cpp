#include "playerplatform.h"
#include <QDebug>

PlayerPlatform::PlayerPlatform(QGraphicsScene *parent)
{
    maxWidth = parent->sceneRect().width();
    maxHeight = parent->sceneRect().height();
    width = 135;
    height = 30;
    resetPosition();
    step = 25;
    image = QImage("../Arcanoid/resources/platform.png");
    setData(QVariant::String, "Platform");
}

QRectF PlayerPlatform::boundingRect() const
{
    return QRect(this->x, this->y, this->width, this->height);
}

void PlayerPlatform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(this->x, this->y, image);
}

void PlayerPlatform::moveRight()
{
    if(x + width < maxWidth)
        x += step;
}

void PlayerPlatform::moveLeft()
{
    if (x > 0)
        x -= step;
}

void PlayerPlatform::resetPosition()
{
    x = (maxWidth - width) / 2;
    y = (int) (maxHeight * 0.925);
}


#include "ball.h"
#include <QDebug>
#include "game.h"
#include "brick.h"

Ball::Ball(PlayerPlatform *playerPlatform)
{
    speed = 1;
    image = QImage("../Arcanoid/resources/ball.png");
    w = image.width();
    h = image.height();
    setData(QVariant::String, "Ball");
    this->playerPlatform = playerPlatform;
    resetPosition();
}

QRectF Ball::boundingRect() const
{
    return QRect(x, y, image.width(), image.height());
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(this->x, this->y, image);
}

void Ball::resetPosition()
{
    x = (Game::WIDTH - w) / 2;
    y = this->playerPlatform->y - h;
}

void Ball::startLeft()
{
    direction = topLeft;
    speed = 1;
}

void Ball::startRight()
{
    direction = topRight;
    speed = 1;
}

void Ball::advance(int phase)
{
    //if(!phase) return;

    switch(direction){
    case topRight:
        if (x + speed >= scene()->width())
        {
            direction = topLeft;
        }
        else if (y - speed <= 0)
        {
            direction = bottomRight;
        }
        x += speed;
        y -= speed;
        break;
    case topLeft:
        if (x - speed <= 0)
        {
            direction = topRight;
        }
        else if (y - speed < 0)
        {
            direction = bottomLeft;
        }
        x -= speed;
        y -= speed;
        break;
    case bottomRight:  if (x + speed >= scene()->width())
        {
            direction = bottomLeft;
        }
        else if (y + speed >= scene()->height())
        {
            direction = topRight;
        }
        x += speed;
        y += speed;
        break;
    case bottomLeft:
        if (x - speed <= 0)
        {
            direction = bottomRight;
        }
        else if (y + speed >= scene()->height())
        {
            direction = topLeft;
        }
        x -= speed;
        y += speed;
        break;
    }

    if (y + image.width() > this->playerPlatform->y)
    { // Если дошли до черты платформы
        if (this->boundingRect().intersects(this->playerPlatform->boundingRect()))
        {
            if (direction == bottomRight)
            {
                direction = topRight;
            }
            else
            {
                direction = topLeft;
            }
        }
        else
        {
            speed = 0; // TODO RESET
        }
    }

    foreach(QGraphicsItem *item, scene()->items())
    {
        if (item->data(QVariant::String).toString() == "Brick")
        {
            Brick *b = (Brick*) item;
            if(this->boundingRect().intersects(b->boundingRect()))
            {
                // Выясняем откуда произошел удар
                switch(direction)
                {
                case topRight:
                    if ((y <= (b->y+b->h)) && (x + w >= b->x) && (x <= b->x + b->w))
                    { // Ударили в дно
                        direction = bottomRight;
                        break;
                    }
                    if ((x + w >= b->x) && (y <= b->y + b->h) && (y + h >= b->y))
                    { // Ударили в левый край
                        direction = topLeft;
                        break;
                    }
                    break;
                case topLeft:
                    if ((y <= (b->y+b->h)) && (x + w >= b->x) && (x <= b->x + b->w))
                    { // Ударили в дно
                        direction = bottomLeft;
                        break;
                    }
                    if (x <= b->x + b->h && y <= b->y + b->h && y + h >= b->y)
                    { // Ударили в правую стенку
                        direction = topRight;
                        break;
                    }
                    break;
                case bottomRight:
                    if ((x + w >= b->x) && (y <= b->y + b->h) && (y + h >= b->y))
                    { // Ударили в левый край
                        direction = bottomLeft;
                        break;
                    }
                    if (y + h >= b->y && x + w >= b->x && x <= b->x + b->h)
                    { // Ударили в верхнюю крышку
                        direction = topRight;
                        break;
                    }
                    break;
                case bottomLeft:
                    if (y + h >= b->y && x + w >= b->x && x <= b->x + b->h)
                    { // Ударили в верхнюю крышку
                        direction = topLeft;
                        break;
                    }
                    if (x <= b->x + b->h && y <= b->y + b->h && y + h >= b->y)
                    { // Ударили в правую стенку
                        direction = bottomRight;
                        break;
                    }
                    break;
                }
                scene()->removeItem(b);
            }
        }
    }

    scene()->update();
}


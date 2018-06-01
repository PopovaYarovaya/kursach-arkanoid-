#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "playerplatform.h"

class Ball : public QGraphicsItem
{
public:
    Ball(PlayerPlatform *playerPlatform);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void resetPosition();
    void startLeft();
    void startRight();

    int speed;

protected:
    void advance(int phase);

private:
    int x, y, w, h;
    QImage image;
    enum directions{topRight, topLeft, bottomRight, bottomLeft};
    int direction;
    PlayerPlatform *playerPlatform;
};

#endif // BALL_H

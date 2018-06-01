#ifndef PLAYERPLATFORM_H
#define PLAYERPLATFORM_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class PlayerPlatform : public QGraphicsItem
{
public:
    PlayerPlatform(QGraphicsScene *parent);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void moveRight();
    void moveLeft();
    int x, y, width, height, maxWidth, maxHeight, step;
    QImage image;
    void resetPosition();
};

#endif // PLAYERPLATFORM_H

#ifndef BRICK_H
#define BRICK_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <string>

class Brick : public QGraphicsItem
{
public:
    Brick(std::string name, int x, int y);
    QImage image;
    int x, y, h, w;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // BRICK_H

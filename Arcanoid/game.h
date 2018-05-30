#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include "playerplatform.h"
#include "ball.h"


namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    static const int WIDTH = 800;
    static const int HEIGHT = 600;
    explicit Game(QWidget *parent = 0);
    ~Game();

    Ball *ball;
    PlayerPlatform *playerPlatform;

private:
    Ui::Game *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    int lives;
    void updateTitle();
    QPixmap bg;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // GAME_H

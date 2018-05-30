#include "game.h"
#include "brick.h"
#include "ui_game.h"
#include <iostream>
#include <QMap>

using namespace std;

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    lives = 5;
    this->setWindowTitle("Arcanoind - Lives left: " + QString::number(lives));
    ui->setupUi(this);
    setFocus();
    this->setFixedSize(WIDTH, HEIGHT);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    scene->setSceneRect(0, 0, WIDTH, HEIGHT);

    //qDebug() << QDir::currentPath();

    bg = QPixmap("../Arcanoid/resources/bg.jpg");
    scene->addPixmap(bg);

    int spacing = 2;

    QMap<string, int> widths;
    widths["short"] =  Brick("short", 0, 0).w + spacing;
    widths["medium"] =  Brick("medium", 0, 0).w + spacing;
    widths["long"] = Brick("long", 0, 0).w + spacing;

    int anyHeight = Brick("short", 0, 0).h + spacing;

    QMap<string, int> counts;
    counts["short"] =  (WIDTH * 0.9) / widths["short"];
    counts["medium"] = (WIDTH * 0.95) / widths["medium"];
    counts["long"] = WIDTH / widths["long"];

    QMap<string, int> startPositions;
    startPositions["short"] = (WIDTH - widths["short"] * counts["short"]) / 2;
    startPositions["medium"] = (WIDTH - widths["medium"] * counts["medium"]) / 2;
    startPositions["long"] = (WIDTH - widths["long"] * counts["long"]) / 2;

    int heightStartPos = 20; // Просто выбрал как угодно

    string levels[] = {"short", "medium", "long", "medium", "short"};
    int levelsLength = 5;
    // level 1 -- short
    for(int level = 0; level < levelsLength; level++)
    {
        for(int i = 0; i < counts[levels[level]]; i++)
        {
            scene->addItem(new Brick(levels[level], startPositions[levels[level]] + i * widths[levels[level]], heightStartPos + level * anyHeight));
        }
    }

    playerPlatform = new PlayerPlatform(scene);
    ball = new Ball(playerPlatform);
    scene->addItem(playerPlatform);
    scene->addItem(ball);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(5);
    this->setWindowTitle("Arcanoind - Lives left: " + QString::number(lives));
}

Game::~Game()
{
    delete ui;
}

void Game::updateTitle()
{
    this->setWindowTitle("Arcanoind - Lives left: " + QString::number(lives));
}


void Game::keyPressEvent(QKeyEvent *event)
{
    if (lives == 0)
    {
        QList<QGraphicsItem*> all = scene->items();
        for (int i = 0; i < all.size(); i++)
        {
            QGraphicsItem *gi = all[i];
            if(gi->parentItem()==NULL) {
                delete gi;
            }
        }
        scene->addPixmap(bg);
        QGraphicsTextItem *text = scene->addText("You lose");
        text->setPos(10, 10);
        text->setDefaultTextColor(Qt::white);
        text->setFont(QFont("Arial", 25));
    }
    int key = event->key();
    switch(key)
    {
    case Qt::Key_Right:
        playerPlatform->moveRight();
        break;
    case Qt::Key_Left:
        playerPlatform->moveLeft();
        break;
    case Qt::Key_Escape:
        if (ball->speed == 0)
        {
            lives--;
            updateTitle();
            ball->resetPosition();
            playerPlatform->resetPosition();
        }
        break;
    case Qt::Key_Space:
        if ((playerPlatform->x + playerPlatform->width / 2) > WIDTH / 2)
        {
            ball->startLeft();
        }
        else
        {
            ball->startRight();
        }

    }
    scene->update();
}

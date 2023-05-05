#ifndef SCENE_H
#define SCENE_H

#include <QDebug>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <bird.h>
#include <pipe.h>
#include <background.h>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void birddef();
    void mainstart();
    void Scoreadd();

signals:

private:
    void setpipetimer();
    QTimer* pipetimer;
    birditem* bird;
    QGraphicsPixmapItem* startImage;
    QGraphicsPixmapItem* gameoverImage;
    bool startsign;
    void gameover();
    groundItem* ground;
    bool gameoverbool;
    int score;
    QGraphicsTextItem* scoretext;
    void showscore();

public slots:

    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H

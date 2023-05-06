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
#include <QMediaPlaylist>
#include <QMediaPlayer>

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
    QMediaPlaylist * flymusicList;
    QMediaPlayer* flysoundPlayer;
    QMediaPlaylist * hitmusicList;
    QMediaPlayer* hitsoundPlayer;
    QMediaPlaylist * pointmusicList;
    QMediaPlayer* pointsoundPlayer;
public slots:

    // QGraphicsScene interface
protected:
    void pointsoundEvent(QMediaPlayer* pointsoundPlayer);
    void hitsoundEvent(QMediaPlayer* hitsoundPlayer);
    void flysoundEvent(QMediaPlayer* flysoundPlayer);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H

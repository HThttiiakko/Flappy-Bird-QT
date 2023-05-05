#include "background.h"
#include "bird.h"
#include <QPixmap>
#include <QTimer>
#include <QPropertyAnimation>

    groundItem::groundItem(QObject *parent) : QObject(parent),
        QGraphicsPixmapItem(QPixmap(":/new/prefix1/ground.png"))
    {
        setPos(0, 500);

        //生成地面向左移动的动画
        groundanimotion = new QPropertyAnimation(this, "groundx", this);
        groundanimotion->setStartValue(0);
        groundanimotion->setEndValue(-100);
        groundanimotion->setDuration(1000);
        groundanimotion->setLoopCount(-1);
        groundanimotion->start();

    }

    qreal groundItem::groundx() const
    {
        return x_groundx;
    }


    void groundItem::setgroundx(qreal groundx)
    {
        x_groundx = groundx;
        setPos(groundx, y());
    }

    void groundItem::groundstop()
    {
        groundanimotion->stop();
    }

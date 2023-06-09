#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <bird.h>

class groundItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal groundx READ groundx WRITE setgroundx)
    qreal x_groundx;

public:
explicit groundItem(QObject *parent = nullptr);
qreal groundx() const;
//地面当前位置
QPropertyAnimation* groundanimotion;
//让地面从右往左进行移动

public slots:
void setgroundx(qreal groundx);
void groundstop();

signals:
};

#endif // GROUND_H

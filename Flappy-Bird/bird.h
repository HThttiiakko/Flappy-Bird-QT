#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class birditem : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE sety)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
public:
    explicit birditem(QPixmap pixmap,QObject *parent = nullptr);
    void wings();
    //处理鸟的翅膀扇动动画
    qreal y() const;
    //鸟的当前位置
    qreal rotation() const;
    //鸟的当前旋转角度
    void jump();

    void birdstart();

    void birdstop();

    bool collision();
    //判断鸟是否与其他物体相撞

public slots:

    void sety(qreal y);

    void setRotation(qreal rotation);

    void falling();

private:
    bool wingdirect;//0 下 1 上
    int wingpos;//0 向上 1 中間 2 向下
    QPropertyAnimation* fallanimotion;
    QPropertyAnimation* spinanimotion;
    qreal m_y;
    qreal m_rotation;
    qreal groundline;

signals:
    void collidesignal2();
};

#endif // BIRDITEM_H

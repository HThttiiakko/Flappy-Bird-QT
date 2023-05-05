#include <bird.h>
#include <background.h>
#include <QTimer>
#include <QGraphicsScene>
#include <scene.h>

//扇动翅膀函数
void birditem::wings()
{
    if(wingpos==0)
    {
        setPixmap(QPixmap(":/new/prefix1/bird01.png"));
        wingpos=1;
        wingdirect=0;
    }
    if(wingpos==1)
    {
        if(wingdirect==0)
        {
            setPixmap(QPixmap(":/new/prefix1/bird02.png"));
            wingpos=2;
        }
        else
        {
            setPixmap(QPixmap(":/new/prefix1/bird03.png"));
            wingpos=0;
        }
    }
    if(wingpos==2)
    {
        setPixmap(QPixmap(":/new/prefix1/bird02.png"));
        wingpos=1;
        wingdirect=1;
    }
}

birditem::birditem(QPixmap pixmap, QObject *parent) : QObject(parent),
  wingdirect(0),wingpos(0),m_y(0)
{
    setPixmap(pixmap);

    //设置定时器 让鸟翅膀扇动
    QTimer* wingtimer = new QTimer(this);
    connect(wingtimer,&QTimer::timeout,[=](){wings();});
    wingtimer->start(100);

    //计算地面位置
    groundline=scenePos().y()+485;

    //设置鸟的坠落
    yanimotion = new QPropertyAnimation(this,"y",this);
    yanimotion->setStartValue(scenePos().y());
    yanimotion->setEndValue(groundline);
    yanimotion->setEasingCurve(QEasingCurve::InQuad);
    yanimotion->setDuration(1000);

    //设置坠落时的体态——嘴朝地
    spinanimotion = new QPropertyAnimation(this,"rotation",this);
    spinanimotion->setStartValue(rotation());
    spinanimotion->setEndValue(90);
    spinanimotion->setEasingCurve(QEasingCurve::InQuad);
    spinanimotion->setDuration(1200);


}


qreal birditem::y() const
{
    return m_y;
}

qreal birditem::rotation() const
{
    return m_rotation;
}

void birditem::leap()
{
    yanimotion->stop();
    spinanimotion->stop();

    //让鸟跳跃完成后自然下坠
    connect(yanimotion,&QPropertyAnimation::finished,[=]{falling();});

    //设置鸟的跳跃动画
    yanimotion->setStartValue(y());
    yanimotion->setEndValue(y() - 70);
    yanimotion->setEasingCurve(QEasingCurve::OutQuad);
    yanimotion->setDuration(320);
    yanimotion->start();

    //设置鸟的跳跃旋转动画
    spinanimotion->setStartValue(rotation());
    spinanimotion->setEndValue(-45);
    spinanimotion->setEasingCurve(QEasingCurve::InOutQuad);
    spinanimotion->setDuration(200);
    spinanimotion->start();
}

void birditem::birdstart()
{
    yanimotion->setStartValue(250);
    yanimotion->start();
    spinanimotion->start();
}

void birditem::birdstop()
{
    yanimotion->stop();
    spinanimotion->stop();
}

//碰撞检测函数
bool birditem::collision()
{
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
      foreach (QGraphicsItem * item , collidingItems){
          groundItem * groundtemp = dynamic_cast<groundItem*>(item);
          if(groundtemp){
              return true;
          }
      }
      return false;

}



void birditem::sety(qreal y)
{
    setPos(this->pos().x(),y);

    //若碰撞地板 则发出碰撞信号
    if(collision()){
        emit collidesignal2();
    }

    m_y = y;
}

//将旋转中心放置鸟图元中心
void birditem::setRotation(qreal rotation)
{
    m_rotation = rotation;
    QPointF temp = boundingRect().center();
    setTransformOriginPoint(temp);
    QGraphicsItem::setRotation(rotation);
}

//鸟的自然下坠
void birditem::falling()
{
    if(y()<(this->scenePos().y()+460))
    {
    spinanimotion->stop();

    yanimotion->setStartValue(y());
    yanimotion->setEndValue(groundline);
    yanimotion->setEasingCurve(QEasingCurve::InQuad);
    yanimotion->setDuration(1100);
    yanimotion->start();

    spinanimotion->setStartValue(rotation());
    spinanimotion->setEndValue(90);
    spinanimotion->setEasingCurve(QEasingCurve::InQuad);
    spinanimotion->setDuration(1000);
    spinanimotion->start();
    }
}

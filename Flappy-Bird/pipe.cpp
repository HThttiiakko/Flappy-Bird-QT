#include <pipe.h>
#include <bird.h>
#include <scene.h>
#include <QPointF>
#include <time.h>

PipeItem::PipeItem() :
    newpipe(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/pipe.png"))),pass(0)
{
    //随机生成右侧新管道的上下位置
    ramy=-(200+rand()%(480-200+1));
    newpipe->setPos(580,ramy);

    //创造管道水平向左移动动画
    pipexanimotion = new QPropertyAnimation(this,"x",this);
    pipexanimotion->setStartValue(580);
    pipexanimotion->setEndValue(-100);
    pipexanimotion->setDuration(3500);
    pipexanimotion->start();

    //当动画结束 移除管道 有利于节省空间
    connect(pipexanimotion, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });

    addToGroup(newpipe);
}



PipeItem::~PipeItem()
{
}

qreal PipeItem::x() const
{
    return m_x;
}

void PipeItem::pipestop()
{
    pipexanimotion->stop();
}

void PipeItem::setX(qreal x)
{
    m_x = x;

    //如果小鸟通过了管道，增加1分
    if(x<-98&&!pass){
        pass=1;
        QGraphicsScene* nowscene=scene();
                Scene* myscene = dynamic_cast<Scene *>(nowscene);
                if(nowscene){
                    score++;
                    myscene->Scoreadd();
                }
    }

    if(score<=20)//当你的分数增加时管道的移动速度变快，难度增加
        pipexanimotion->setDuration(3500);
    else if(score>20)
        pipexanimotion->setDuration(3000);
    else if(score>50)
        pipexanimotion->setDuration(2000);
    else if(score>100)
        pipexanimotion->setDuration(1000);
    else if(score>200)
        pipexanimotion->setDuration(500);

    //如果小鸟撞上了管道，发出碰撞信号
    if(collision()){
        emit collidesignal();
    }
    setPos(x,ramy);
}

//碰撞检测函数
bool PipeItem::collision()
{
    QList<QGraphicsItem*> collidingItems = newpipe->collidingItems();
      foreach (QGraphicsItem * item , collidingItems){
          birditem * birdie = dynamic_cast<birditem*>(item);
          if(birdie){
              return true;
          }
      }
      return false;
}

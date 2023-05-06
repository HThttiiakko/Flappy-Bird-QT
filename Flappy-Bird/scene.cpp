#include <scene.h>
#include <QMouseEvent>
#include <bird.h>
#include <background.h>
#include <QMediaPlaylist>
#include <QMediaPlayer>


Scene::Scene(QObject *parent) : QGraphicsScene(parent),startsign(0),gameoverbool(0),score(0)
{
    setpipetimer();
    //水管定时器 用于定时间间隔生成新水管

    startImage = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/start.png"));
    addItem(startImage);
    startImage->setPos(0,0);
    startImage->setZValue(100);//放在最顶层

    gameoverImage = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/gameover.png"));



    ground = new groundItem;
       addItem(ground);
          ground->setZValue(10); // 设置Z值为大于0，放在背景之上
}

void Scene::birddef()
{
    bird = new birditem(QPixmap(":/new/prefix1/bird01.png"));
    addItem(bird);
    bird->setPos(0,250);
    bird->setZValue(300);
}

void Scene::mainstart()
{
    startsign=1;
    removeItem(startImage);
        delete startImage;
    bird->birdstart();
    bird->setPos(0,250);
if(!pipetimer->isActive()){
    pipetimer->start(2000);
}
}


void Scene::pointsoundEvent(QMediaPlayer *pointsoundPlayer)
{
    pointmusicList = new QMediaPlaylist(this);  //添加音乐列表
    pointmusicList->addMedia(QUrl("qrc:/music01/pointsound .mp3")) ; //添加音乐列表

    pointsoundPlayer = new QMediaPlayer(this);  //创建音乐播放器
    pointsoundPlayer->setPlaylist(pointmusicList);  //设置音乐列表
    pointsoundPlayer->setVolume(50);
    pointsoundPlayer->play();
}



void Scene::Scoreadd()
{
    pointsoundEvent(pointsoundPlayer);//加大分音效
    score++;
}

void Scene::setpipetimer()
{
 pipetimer = new QTimer(this);
 connect(pipetimer,&QTimer::timeout,[=](){
     PipeItem* pipe = new PipeItem;

     //如果小鸟与水管碰撞，游戏结束
     connect(pipe,&PipeItem::collidesignal,[=](){
         pipetimer->stop();
         gameover();
     });
     //如果小鸟与地板碰撞，游戏结束
     connect(bird,&birditem::collidesignal2,[=](){
         gameover();
     });
     addItem(pipe);
 });
}


void Scene::hitsoundEvent(QMediaPlayer *hitsoundPlayer)
{
    hitmusicList = new QMediaPlaylist(this);  //添加音乐列表
    hitmusicList->addMedia(QUrl("qrc:/music01/hitsound .mp3")) ; //添加音乐列表

    hitsoundPlayer = new QMediaPlayer(this);  //创建音乐播放器
    hitsoundPlayer->setPlaylist(hitmusicList);  //设置音乐列表
    hitsoundPlayer->setVolume(50);
    hitsoundPlayer->play();

}


void Scene::gameover()
{
    gameoverbool=1; //已结束游戏
    bird->birdstop();   //鸟停止运动
    ground->groundstop();   //地板停止运动
    hitsoundEvent(hitsoundPlayer);//发出撞击声
    showscore();

    addItem(gameoverImage);
    gameoverImage->setPos(0,0);
    gameoverImage->setZValue(100);
    //显示游戏结束

    //将画面内所有水管都停止运动
    QList<QGraphicsItem*> sceneItems = items();
        for(int i=0; i<sceneItems.size(); i++){
            PipeItem * pipe = qgraphicsitem_cast<PipeItem*>(sceneItems[i]);
            if(pipe){
                pipe->pipestop();
            }
        }
        pipetimer->stop();
        //停止水管计时器 不再生成新水管
}

void Scene::showscore()
{
    scoretext = new QGraphicsTextItem();
    QString lastscore="你的分数为: " + QString::number(score);
    scoretext->setHtml(lastscore);

    //设置分数显示界面字体和颜色
    QFont font("楷体",30,QFont::Normal);
    scoretext->setFont(font);
    QColor color(255,215,0);
    scoretext->setDefaultTextColor(color);

    //设置位置
    addItem(scoretext);
    scoretext->setPos(35 ,280);
}


void Scene::flysoundEvent(QMediaPlayer *flysoundPlayer)
{
    flymusicList = new QMediaPlaylist(this);  //添加音乐列表
    flymusicList->addMedia(QUrl("qrc:/music01/flysound .mp3")) ; //添加音乐列表

    flysoundPlayer = new QMediaPlayer(this);  //创建音乐播放器
    flysoundPlayer->setPlaylist(flymusicList);  //设置音乐列表
    flysoundPlayer->setVolume(50);
    flysoundPlayer->play();
}


void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(startsign==0)
        mainstart();
    //第一次鼠标左键将移除开始界面图片，并让小鸟，水管开始运动
    if(!gameoverbool)
    {
if(event->button()==Qt::LeftButton){
    flysoundEvent(flysoundPlayer);
    bird->leap();
}
if(event->button()==Qt::RightButton){
    flysoundEvent(flysoundPlayer);
    bird->leap();
    }
QGraphicsScene::mousePressEvent(event);//若游戏已结束 则鼠标左右键不再有任何作用
    }
}

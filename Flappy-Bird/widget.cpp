#include <widget.h>
#include <ui_widget.h>
#include <pipe.h>
#include <bird.h>
#include <background.h>
#include <QGraphicsPixmapItem>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("FlappyBird");

    scene = new Scene(this);

    scene->setSceneRect(0,0,432,644);
    //设置场景矩形大小

    QTime current_time =QTime::currentTime();

    QGraphicsPixmapItem* pixItem;

    //根据时间更换早晚背景
    if(current_time.hour()>=18||current_time.hour()<=6)
        pixItem = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/background01.png"));

    else
        pixItem = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/background02.png"));

    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0));
    //游戏背景载入

    scene->birddef();
    //新建小鸟对象

    ui->Box->setScene(scene);
}
Widget::~Widget()
{
    delete ui;
}


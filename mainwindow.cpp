#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qDebug() << "start";



    QPushButton *GroupOne = new QPushButton(tr("Group One"), this);
    QPushButton *GroupTwo = new QPushButton(tr("Group Two"), this);
    QPushButton *GroupThree = new QPushButton(tr("Group Three"), this);
    ui->setupUi(this);
    ui->bottom_Hlayout->addWidget(GroupOne);
    ui->bottom_Hlayout->addWidget(GroupTwo);
    ui->bottom_Hlayout->addWidget(GroupThree);
    canvas = new MyGraphicsView();


    scene = new MyGraphicsScene();
    canvas->setScene(scene);
  //  item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg").scaled(this->width(),this->height()));
    scene->addPixmap(QPixmap("/home/tao/Desktop/test.jpg").scaled(this->width(),this->height()));

    connect(GroupOne,SIGNAL(clicked()),canvas, SLOT(DrawRect()));
    connect(GroupTwo,SIGNAL(clicked()),canvas, SLOT(DrawEllipse()));
  //  connect(GroupThree,SIGNAL(clicked()),canvas, SLOT(DrawAll()));
    connect(canvas, SIGNAL(mouseClickEvent(vector<pair<QRect,QString>>)), canvas, SLOT(clickHandler(vector<pair<QRect,QString>>)));
    ui->top_Hlayout->addWidget(canvas);
//    ui->horizontalLayout->addWidget(canvas);




}


/*
void MainWindow::drawRect()
{
    canvas->setRect(true);
    canvas->setEllipse(false);
    vector<QRect> channelRect = canvas->getRects();
    scene->clear();
    item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg"));
    scene->addItem(item);
    scene->addRect(channelRect[0],QPen(QColor(255,0,0),6));
    scene->addRect(channelRect[1],QPen(QColor(255,0,0),6));

}

void MainWindow::drawEllipse()
{
    canvas->setEllipse(true);
    canvas->setRect(false);
    vector<QRect> channelRect = canvas->getEllipses();
    scene->clear();
    item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg"));
    scene->addItem(item);
    scene->addEllipse(channelRect[0],QPen(QColor(255,200,0),6));
    scene->addEllipse(channelRect[1],QPen(QColor(255,200,0),6));
}*/
MainWindow::~MainWindow()
{
    delete ui;
}

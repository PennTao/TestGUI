#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qDebug() << "start";

    ui->setupUi(this);

    QPushButton *GroupOne = new QPushButton(tr("Group One"), this);
    QPushButton *GroupTwo = new QPushButton(tr("Group Two"), this);
    QPushButton *GroupThree = new QPushButton(tr("Group Three"), this);

    ui->bottom_Hlayout->addWidget(GroupOne);
    ui->bottom_Hlayout->addWidget(GroupTwo);
    ui->bottom_Hlayout->addWidget(GroupThree);

    player = new QMediaPlayer();
    videoItem = new QGraphicsVideoItem();
    canvas = new QGraphicsView();
    scene = new MyGraphicsScene();
    cover = new MyGraphicsView();
    cover_scene = new MyGraphicsScene();

    xmlparser = new XMLDataParser();
    xmlparser->loadXML(":/xml/test.xml");
    xmlparser->parseXML();
    cover->setParser(xmlparser);
    timer = new QTimer(this);
    timer->setInterval(5000);
    timer->start();
    connect(timer, SIGNAL(timeout()), cover, SLOT(ShowNextFrame()));

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(QString("/home/tao/TestGUI/tbbt-s04-e08.ts")));
    //videoItem->showMaximized();
    player->setPlaylist(playlist);
//    qDebug() <<"b4 play";
//    qDebug()<<"resolution"<<playlist->currentMedia().canonicalResource().resolution().height()<<" "<<playlist->currentMedia().canonicalResource().resolution().width();
    player->setVideoOutput(videoItem);
    videoItem->setSize(QSize(this->width(),this->height()));
    scene->addItem(videoItem);
    connect(playlist,SIGNAL(currentMediaChanged(QMediaContent)),cover,SLOT(UpdateResolution(QMediaContent)));
 //   cover_scene->addRect(this->x(),this->y(),this->width(),this->height(),QPen(QColor(255,0,0),6));
 //  canvas->setGeometry(videoWidget->geometry());
    canvas->setScene(scene);
    canvas->setFrameStyle( QFrame::NoFrame );
    canvas->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    canvas->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    cover->setScene(cover_scene);
    cover->setFrameStyle( QFrame::NoFrame );
    cover->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    cover->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );


    cover->setSceneRect(scene->sceneRect());

    player->play();

//    qDebug() <<"after play";
//    qDebug()<<"resolution"<<playlist->currentMedia().canonicalResource().resolution().height()<<" "<<playlist->currentMedia().canonicalResource().resolution().width();

    cover->setBackgroundRole( QPalette::Window );
    cover->setStyleSheet("background:transparent");
    cover->setAttribute(Qt::WA_TranslucentBackground);
  //  item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg").scaled(this->width(),this->height()));
  //  cover_scene->addPixmap(QPixmap("/home/tao/TestGUI/background.png").scaled(this->width(),this->height()));
  //  canvas->showFullScreen();
    connect(GroupOne,SIGNAL(clicked()),cover, SLOT(ToggleDrawRect()));
  //  connect(GroupTwo,SIGNAL(clicked()),cover, SLOT(DrawEllipse()));
  //  connect(GroupThree,SIGNAL(clicked()),canvas, SLOT(DrawAll()));
    connect(cover, SIGNAL(mouseClickEvent()), cover, SLOT(clickHandler()));
    ui->top_Hlayout->addWidget(canvas,0,0);
    ui->top_Hlayout->addWidget(cover,0,0);

//    ui->horizontalLayout->addWidget(canvas);




}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    canvas->setSceneRect(this->rect());
    videoItem->setSize(QSize(this->width(),this->height()));
    cover->setSceneRect(this->rect());
 //   cover->resize(canvas->size().width(),canvas->size().height());
 //   qDebug() <<"resized";
//    cover_scene->setSceneRect(scene->sceneRect());
//    cover->setBaseSize(canvas->size());
//    cover_scene->addRect(cover_scene->sceneRect(),QPen(QColor(0,255,0),8));
//    scene->addRect(scene->sceneRect(),QPen(QColor(255,255,0),8));
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

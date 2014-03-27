#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <vector>
#include  <QWidget>
#include  <QPushButton>
#include "mygraphicsview.h"
#include "mygraphicsscene.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsVideoItem>
#include "xmldataparser.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:

    QGraphicsView *canvas;
    MyGraphicsView *cover;
    MyGraphicsScene *scene;
    MyGraphicsScene *cover_scene;
    QMediaPlayer *player;
    QGraphicsVideoItem *videoItem;
    QMediaPlaylist *playlist;
    QPixmap *bgd;

    QGraphicsPixmapItem *item;
    vector <QRect> channelRect;
    XMLDataParser* xmlparser;
    QTimer *timer;
protected:
//    void mouseReleaseEvent(QMouseEvent *e);
//    void mousePressEvent(QMouseEvent *e);


public:
    explicit MainWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent* event);
    ~MainWindow();


public slots:
//    void drawRect();
//    void drawEllipse();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

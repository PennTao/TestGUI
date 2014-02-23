#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <utility>
#include "socketcomm.h"
#include "mygraphicsscene.h"
using namespace std;
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

signals:
    void mouseClickEvent(vector< pair<QRect, QString> >);

public slots:
    void clickHandler(vector< pair<QRect, QString> > rects);
    void DrawRect();
    void DrawEllipse();
    void DrawAll();

public:
    explicit MyGraphicsView(QWidget *parent = 0);
    vector< pair<QRect, QString> > getRects();
    vector< pair<QRect, QString> > getEllipses();
    void setRect(bool);
    void setEllipse(bool);

protected:
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    bool bMousePress;
    bool bGroupRect;
    bool bGroupEllipse;
    QPixmap *background;
    QPoint m_lastPos;
    vector< pair<QRect, QString> > rects;
    vector< pair<QRect, QString> > ellipses;
    QTcpSocket * socket;
    SocketComm* client;


};

#endif // MYGRAPHICSVIEW_H

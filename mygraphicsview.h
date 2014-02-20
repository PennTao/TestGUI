#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include "mygraphicsscene.h"
using namespace std;
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

signals:
    void mouseClickEvent(vector<QRect>);

public slots:
    void clickHandler(vector<QRect> rects);
    void DrawRect();
    void DrawEllipse();

public:
    explicit MyGraphicsView(QWidget *parent = 0);
    vector<QRect> getRects();
    vector<QRect> getEllipses();
    void setRect(bool);
    void setEllipse(bool);

protected:
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    bool bMouseClick;
    bool bGroupRect;
    bool bGroupEllipse;

    QPoint m_lastPos;
    vector<QRect> rects;
    vector<QRect> ellipses;
};

#endif // MYGRAPHICSVIEW_H

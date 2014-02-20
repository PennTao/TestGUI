#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{

    bGroupEllipse = false;
    bGroupRect = false;
    rects.push_back(QRect(584,405,100,70));
    rects.push_back(QRect(150,168,60,150));
    ellipses.push_back(QRect(384,305,90,80));
    ellipses.push_back(QRect(684,205,80,170));
    QWidget::setMouseTracking(true);

}
void MyGraphicsView::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "pressed at  X: "<<e->pos().x() <<"    Y:" << e->pos().y();
    m_lastPos = e->pos();
    bMouseClick = true;

}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "release at  X: "<<e->pos().x() <<"    Y:" << e->pos().y();
    if(bMouseClick && (m_lastPos == e->pos()) && bGroupRect)
    {
       // qDebug() << "click in MyGraphicsView";
        emit mouseClickEvent(rects);
        bMouseClick = false;
    }
    if(bMouseClick && (m_lastPos == e->pos()) && bGroupEllipse)
    {
       // qDebug() << "click in MyGraphicsView";
        emit mouseClickEvent(ellipses);
        bMouseClick = false;
    }
}
void MyGraphicsView::clickHandler(vector<QRect> rects)
{

    QRect curRect;
    for(uint i = 0; i < rects.size(); i++)
    {
        curRect = rects[i];
        if(curRect.contains(m_lastPos))
        {
            qDebug() <<"click in ROI";
        }
    }

}
void MyGraphicsView::mouseMoveEvent(QMouseEvent *e)
{
  //  qDebug() << "mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
    QRect curRect;
    QGraphicsScene *scene;
    if(bGroupRect)
    {
        DrawRect();
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i];
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addRect(rects[i],QPen(QColor(255,255,0),6));
                qDebug() <<"in rect "<<i<<" mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
            }
        }
    }
    if(bGroupEllipse)
    {
        DrawEllipse();
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i];
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addEllipse(ellipses[i],QPen(QColor(255,255,0),6));
                qDebug() <<"in ellipse "<<i<<" mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
            }
        }
    }
}
void MyGraphicsView::setRect(bool val)
{
    bGroupRect = val;
}
void MyGraphicsView::setEllipse(bool val)
{
    bGroupEllipse = val;
}
void MyGraphicsView::DrawRect()
{
    QGraphicsScene *scene;

    this->setRect(true);
    this->setEllipse(false);
    scene = this->scene();

    scene->clear();
    scene->addPixmap(QPixmap("/home/tao/Desktop/panda_AP.jpg"));
    scene->addRect(rects[0],QPen(QColor(255,0,0),6));
    scene->addRect(rects[1],QPen(QColor(255,0,0),6));

}

void MyGraphicsView::DrawEllipse()
{
    QGraphicsScene *scene;

    this->setRect(false);
    this->setEllipse(true);
    scene = this->scene();

    scene->clear();
    scene->addPixmap(QPixmap("/home/tao/Desktop/panda_AP.jpg"));
    scene->addEllipse(ellipses[0],QPen(QColor(255,0,0),6));
    scene->addEllipse(ellipses[1],QPen(QColor(255,0,0),6));
}
vector<QRect> MyGraphicsView::getRects()
{
    return rects;
}
vector<QRect> MyGraphicsView::getEllipses()
{
    return ellipses;
}

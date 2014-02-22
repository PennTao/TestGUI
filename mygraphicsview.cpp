#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    background = new QPixmap("/home/tao/Desktop/panda_AP.jpg");
    bGroupEllipse = false;
    bGroupRect = false;
    rects.push_back(QRect(584,405,100,70));
    rects.push_back(QRect(150,168,60,150));
    ellipses.push_back(QRect(384,305,90,80));
    ellipses.push_back(QRect(684,205,80,170));
    QWidget::setMouseTracking(true);
    client = new SocketComm();
    client->connectToServer("127.0.0.1", 1234);

}
void MyGraphicsView::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "pressed at  X: "<<e->pos().x() <<"    Y:" << e->pos().y();
    QRect curRect;
    QGraphicsScene *scene;
    m_lastPos = e->pos();
    bMousePress = true;
    scene = this->scene();
    if(bGroupRect)
    {
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i];
            if(curRect.contains(m_lastPos))
            {
                scene->addRect(rects[i],QPen(QColor(0,255,0),6));
            }
        }
    }
    if(bGroupEllipse)
    {
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i];
            if(curRect.contains(m_lastPos))
            {
                scene->addEllipse(ellipses[i],QPen(QColor(0,255,0),6));
            }
        }
    }

}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *e)
{

    qDebug() << "release at  X: "<<e->pos().x() <<"    Y:" << e->pos().y();
    qDebug() << "View Rect: "<<this->rect().x()<<"  "<<this->rect().y()<<"  "<<this->rect().height()<<" "<<this->rect().width();
    qDebug() << "SceneRect: "<<this->scene()->sceneRect().x()<<"    "<<this->scene()->sceneRect().y()<<"    "<<this->scene()->sceneRect().height()<<"   "<<this->scene()->sceneRect().width();


    QRect curRect;
    QGraphicsScene *scene;
    if(bMousePress &&  bGroupRect)
    {
       // qDebug() << "click in MyGraphicsView";
        bMousePress = false;
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i];
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addRect(rects[i],QPen(QColor(255,255,0),6));
            }
        }
        if(m_lastPos == e->pos())
            emit mouseClickEvent(rects);

    }
    if(bMousePress && bGroupEllipse)
    {
       // qDebug() << "click in MyGraphicsView";
        bMousePress = false;
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i];
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addEllipse(ellipses[i],QPen(QColor(255,255,0),6));
            }
        }
        if(m_lastPos == e->pos() )
            emit mouseClickEvent(ellipses);

    }
}
void MyGraphicsView::clickHandler(vector<QRect> rects)
{

    QRect curRect;
    QString test;
    test = "TV";
    for(uint i = 0; i < rects.size(); i++)
    {
        curRect = rects[i];
        if(curRect.contains(m_lastPos))
        {
            client->sendToServer(test);
            qDebug() <<"click in ROI";
        }
    }

}
void MyGraphicsView::mouseMoveEvent(QMouseEvent *e)
{
  //  qDebug() << "mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
    QRect curRect;
    QGraphicsScene *scene;
    if(bGroupRect && !bMousePress)
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
    if(bGroupEllipse && !bMousePress)
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
    scene->addPixmap(background->scaled(this->width(),this->height()));
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
    scene->addPixmap(background->scaled(this->width(),this->height()));
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

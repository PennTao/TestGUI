#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    background = new QPixmap("/home/tao/Desktop/test.jpg");
    bGroupEllipse = false;
    bGroupRect = false;
    rects.push_back(make_pair(QRect(50,362,120,100),QString("High-heel shoes")));
    rects.push_back(make_pair(QRect(313,331,180,100),QString("Handbag")));
    ellipses.push_back(make_pair(QRect(553,200,150,280),QString("iPhone")));
   // ellipses.push_back(QRect(684,205,80,170));
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
            curRect = rects[i].first;
            if(curRect.contains(m_lastPos))
            {
                scene->addRect(rects[i].first,QPen(QColor(0,255,0),6));
            }
        }
    }
    if(bGroupEllipse)
    {
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i].first;
            if(curRect.contains(m_lastPos))
            {
                scene->addEllipse(ellipses[i].first,QPen(QColor(0,255,0),6));
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
            curRect = rects[i].first;
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addRect(rects[i].first,QPen(QColor(255,255,0),6));
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
            curRect = ellipses[i].first;
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addEllipse(ellipses[i].first,QPen(QColor(255,255,0),6));
            }
        }
        if(m_lastPos == e->pos() )
            emit mouseClickEvent(ellipses);

    }
}
void MyGraphicsView::clickHandler(vector< pair<QRect, QString> > rects)
{

    QRect curRect;
    QString curStr;

    for(uint i = 0; i < rects.size(); i++)
    {
        curRect = rects[i].first;
        curStr = rects[i].second;
        if(curRect.contains(m_lastPos))
        {
            client->sendToServer(curStr);
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

        if(!bGroupEllipse)
            DrawRect();
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i].first;
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addRect(rects[i].first,QPen(QColor(255,255,0),6));
                qDebug() <<"in rect "<<i<<" mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
            }
        }
    }
    if(bGroupEllipse && !bMousePress)
    {
        if(!bGroupRect)
            DrawEllipse();
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i].first;
            scene = this->scene();
            if(curRect.contains(e->pos()))
            {
                scene->addEllipse(ellipses[i].first,QPen(QColor(255,255,0),6));
                qDebug() <<"in ellipse "<<i<<" mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
            }
        }
    }
    if(bGroupRect && bGroupEllipse && !bMousePress)
    {
        DrawAll();
        scene = this->scene();
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i].first;

            if(curRect.contains(e->pos()))
            {
                scene->addRect(rects[i].first,QPen(QColor(255,255,0),6));
                qDebug() <<"in rect "<<i<<" mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
            }
        }
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i].first;

            if(curRect.contains(e->pos()))
            {
                scene->addEllipse(ellipses[i].first,QPen(QColor(255,255,0),6));
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
    for(uint i = 0; i < rects.size(); i++)
    {
        scene->addRect(rects[i].first,QPen(QColor(255,0,0),6));
    }


}

void MyGraphicsView::DrawEllipse()
{
    QGraphicsScene *scene;

    this->setRect(false);
    this->setEllipse(true);
    scene = this->scene();

    scene->clear();
    scene->addPixmap(background->scaled(this->width(),this->height()));
    for(uint i = 0; i < ellipses.size(); i++)
    {
        scene->addEllipse(ellipses[i].first,QPen(QColor(255,0,0),6));
    }
}

void MyGraphicsView::DrawAll()
{
    QGraphicsScene *scene;
    this->setRect(true);
    this->setEllipse(true);
    scene = this->scene();

    scene->clear();
    scene->addPixmap(background->scaled(this->width(),this->height()));
    for(uint i = 0 ; i < rects.size();i++)
    {
        scene->addRect(rects[i].first,QPen(QColor(255,0,0),6));
    }
    for(uint i = 0 ; i < ellipses.size();i++)
    {
        scene->addEllipse(ellipses[i].first,QPen(QColor(255,0,0),6));
    }
}

vector< pair<QRect, QString> > MyGraphicsView::getRects()
{
    return rects;
}
vector< pair<QRect, QString> > MyGraphicsView::getEllipses()
{
    return ellipses;
}

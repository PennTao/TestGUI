#include "frame.h"

Frame::Frame(QObject *parent) :
    QObject(parent)
{
    items = new QQueue<QMap<QString,QString> >();

}

void Frame::InsertItem(QMap <QString, QString> item)
{
    items->append(item);
}

QQueue<QMap<QString,QString> >* Frame::GetAll()
{
    return items;
}


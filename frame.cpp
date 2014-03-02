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

void Frame::DisplayContent()
{
    for(int i = 0; i < items->count(); i++)
    {
        for(QMap<QString,QString>::const_iterator itr = items->at(i).begin(); itr != items->at(i).end(); itr++)
        {
            qDebug() << itr.key()<<"    "<<itr.value();
        }
    }
}

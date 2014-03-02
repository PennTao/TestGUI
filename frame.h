#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QQueue>
#include <QMap>
#include <QDebug>
class Frame : public QObject
{
    Q_OBJECT

private:
    QMap<QString,QString> item;
    QQueue<QMap<QString,QString> > *items;
public:
    explicit Frame(QObject *parent = 0);
    void InsertItem(QMap<QString,QString> );
    void DisplayContent();
    QQueue<QMap<QString,QString> >* GetAll();
signals:

public slots:

};

#endif // FRAME_H

#ifndef XMLDATAPARSER_H
#define XMLDATAPARSER_H

#include <QObject>
#include <QMap>
#include <QQueue>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include "frame.h"
class XMLDataParser : public QObject
{
    Q_OBJECT
private:
    QFile *xmlFile;
    QXmlStreamReader xmlReader;
    QString dataType;
    QMap < int, Frame* >  dataMap;

public:
    explicit XMLDataParser(QObject *parent = 0);
    void loadXML(QString filename);
    Frame* parseFrame(QXmlStreamReader& xml);
    void parseXML();
signals:

public slots:

};

#endif // XMLDATAPARSER_H

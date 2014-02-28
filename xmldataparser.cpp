#include "xmldataparser.h"

XMLDataParser::XMLDataParser(QObject *parent) :
    QObject(parent)
{
}

void XMLDataParser::loadXML(QString filename)
{
    xmlFile = new QFile(filename);
    qDebug()<<filename;
    // If we can't open it, let's show an error message.
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot Open XML file";
    }
    xmlReader.setDevice(xmlFile);
}

void XMLDataParser::parseXML()
{
    while(!xmlReader.atEnd() &&
            !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument)
            continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xmlReader.name() == "frame")
            {
                Frame* curFrame;
                curFrame = this->parseFrame(xmlReader);
                dataMap[xmlReader.attributes().value("num").toInt()] = curFrame;
            }

        }
    }

}
Frame* XMLDataParser::parseFrame(QXmlStreamReader &xmlReader)
{
    Frame * outputFrame = new Frame();




    return outputFrame;


}

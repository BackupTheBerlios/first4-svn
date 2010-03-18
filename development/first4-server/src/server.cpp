#include <QObject>
#include <QTcpServer>
#include <QByteArray>
#include <QHostInfo>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
//
#include "server.h"
//
QString version = "1.9.80";
QString client_required = "1.9.80";
//
bool first4server::startServer ( )
{
        //Start Server
        f4srv = new QTcpServer();
        bool succ = f4srv->listen(QHostAddress::Any, 15000);
	connect(f4srv, SIGNAL(newConnection()), this, SLOT(listen()));
	return succ;
}
//
uint first4server::getPort ( )
{
	return f4srv->serverPort();
}
//
void first4server::listen ( )
{
	client = f4srv->nextPendingConnection();
    QByteArray answ;
    QXmlStreamWriter stream(&answ);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("first4server");
    stream.writeAttribute("href", "http://first4.procopio.ch/");
    stream.writeTextElement("Version", version);
    stream.writeTextElement("Host", QHostInfo::localHostName()+"."+QHostInfo::localDomainName());
    stream.writeTextElement("ClientRequired", client_required);
    stream.writeEndElement(); 
    stream.writeEndDocument();
    client->write(answ);
	connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
}
//
void first4server::startRead()
{
	QByteArray request;
	request = client->read(client->bytesAvailable());
	QXmlStreamReader xmlrequest(request);
	while (!xmlrequest.atEnd()) {
        	xmlrequest.readNext();
		if(xmlrequest.isStartElement())
		        qDebug() << xmlrequest.name();
		else if(xmlrequest.isCharacters())
		        qDebug() << xmlrequest.text();
	}
}
//
void first4server::writeBack(QString answer)
{
    QByteArray answ;
    QXmlStreamWriter stream(&answ);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("bookmark");
    stream.writeAttribute("href", "http://www.qtsoftware.com/");
    stream.writeTextElement("title", "Qt Home");
    stream.writeEndElement(); // bookmark
    stream.writeEndDocument();
    client->write(answ);
}
//
QString first4server::performAction(QString input)
{
    return "hallo";
}

#include <QtNetwork>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
//
#include "first4thread.h"
//
extern QString f4srv_version;
extern QString f4srv_client_required;
//
first4thread::first4thread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}
//
void first4thread::run()
{
	QTcpSocket tcpSocket;
        if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        	emit error(tcpSocket.error());
		return;
	}
	QByteArray initansw;
	QXmlStreamWriter stream(&initansw);
	stream.setAutoFormatting(true);
	stream.writeStartDocument();
	stream.writeStartElement("first4server");
	stream.writeAttribute("href", "http://first4.procopio.ch/");
	stream.writeTextElement("Version", f4srv_version);
	stream.writeTextElement("Host", QHostInfo::localHostName()+"."+QHostInfo::localDomainName());
	stream.writeTextElement("ClientRequired", f4srv_client_required);
	stream.writeEndElement();
	stream.writeEndDocument();
        tcpSocket.write(initansw);

	connect(&tcpSocket, SIGNAL(readyRead()), SLOT(startRead()), Qt::AutoConnection);
        tcpSocket.flush();
        //tcpSocket.disconnectFromHost();
        //tcpSocket.waitForDisconnected();
}
//
void first4thread::startRead()
{
	QTcpSocket tcpSocket;
        QByteArray request;
        request = tcpSocket.read(tcpSocket.bytesAvailable());
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
void first4thread::writeBack(QString answer)
{
	QTcpSocket tcpSocket;
    QByteArray answ;
    QXmlStreamWriter stream(&answ);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("bookmark");
    stream.writeAttribute("href", "http://www.qtsoftware.com/");
    stream.writeTextElement("title", "Qt Home");
    stream.writeEndElement(); // bookmark
    stream.writeEndDocument();
    tcpSocket.write(answ);
}
//
QString first4thread::performAction(QString input)
{
    return "hallo";
}


#include <QtNetwork>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QDomDocument>
//
#include "first4thread.h"
//
extern QString f4srv_version;
extern QString f4srv_client_required;
QTcpSocket tcpSocket;
//
first4thread::first4thread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}
//
void first4thread::run()
{
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
        connect(&tcpSocket, SIGNAL(readyRead()), SLOT(incomingRequest()), Qt::AutoConnection);
        tcpSocket.flush();
        //tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
}
//
void first4thread::incomingRequest()
{
    if(tcpSocket.canReadLine())
    {
        QDomDocument incReq("req");
        QByteArray request;
        request = tcpSocket.read(tcpSocket.bytesAvailable());
        incReq.setContent(request);

        QDomElement docElem = incReq.documentElement();
        QDomNode n = docElem.firstChild();
        while(!n.isNull()) {
            QDomElement e = n.toElement();
            if(!e.isNull() && e.tagName() == "Action") {
                qDebug() << performAction(e.text());
            }
            n = n.nextSibling();
        }
    }
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
QString first4thread::performAction(QString action)
{
    return action;
}

#include <QObject>
#include <QTcpServer>
#include <QByteArray>
#include <QHostInfo>
#include <QDebug>
//
#include "server.h"
//
QString version = "1.9.80";
QString xmlheader = "<?xml-version=\"1.0\"?>";
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
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint16)0;
	out << tr("first4server Version %1 on %2.%3\n").arg(version).arg(QHostInfo::localHostName()).arg(QHostInfo::localDomainName());
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));

	qDebug() << "Starting connection";
	client = f4srv->nextPendingConnection();
	client->write(block);
	connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
}
//
void first4server::startRead()
{
	char buffer[1024] = {0};
	client->read(buffer, client->bytesAvailable());
	qDebug() << QString("%1").arg(buffer).simplified();
	if(QString("%1").arg(buffer).simplified() != "quit")
		writeBack(buffer);
	else
		client->disconnectFromHost();
}
//
void first4server::writeBack(char *buffer)
{
    QByteArray answ;
    answ.append(xmlheader);
    client->write(answ);
}

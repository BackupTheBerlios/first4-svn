#ifndef __FIRST4SERVER_H__
#define __FIRST4SERVER_H__

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket> 

class first4server : public QObject
{
Q_OBJECT
public:
	bool startServer();
	uint getPort();
private slots:
	void listen();
	void startRead();
	void writeBack(char*);
private:
	QTcpServer *f4srv;
	QTcpSocket *client;
};
#endif // __FIRST4SERVER_H__

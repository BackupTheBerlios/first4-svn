#ifndef FIRST4SERVER_H
#define FIRST4SERVER_H

#include <QStringList>
#include <QTcpServer>

class first4server : public QTcpServer
{
    Q_OBJECT
public:
	first4server(QObject *parent = 0);
	QString f4srvversion;
	QString f4srv_client_required;
protected:
    void incomingConnection(int socketDescriptor);
private:
};

#endif


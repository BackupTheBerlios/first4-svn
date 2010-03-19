#ifndef FIRST4THREAD_H
#define FIRST4THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDomDocument>

class first4thread : public QThread
{
    Q_OBJECT

public:
    first4thread(int socketDescriptor, QObject *parent);
    void run();
signals:
    void error(QTcpSocket::SocketError socketError);
private:
    int socketDescriptor;
    bool performAction(QString, QDomElement);
    void closeConnection();
    void performAuthAction(QString, QDomElement);
private slots:
    void writeBack(QDomDocument);
    void incomingRequest();
};

#endif


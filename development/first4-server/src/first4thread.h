#ifndef FIRST4THREAD_H
#define FIRST4THREAD_H

#include <QThread>
#include <QTcpSocket>

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
    QString performAction(QString);
    QString text;
private slots:
    void writeBack(QString);
    void startRead();
    void incomingRequest();
};

#endif


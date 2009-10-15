#include <QtCore/QCoreApplication>
#include <QDebug>
//
#include "server.h"
//
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    first4server srv;
    srv.startServer();
    qDebug() << srv.getPort();
    return a.exec();
}

#include <stdlib.h>
//
#include "first4server.h"
#include "first4thread.h"
//
first4server::first4server(QObject *parent)
    : QTcpServer(parent)
{

}
//
void first4server::incomingConnection(int socketDescriptor)
{
        first4thread *f4thread = new first4thread(socketDescriptor, this);
        connect(f4thread, SIGNAL(finished()), f4thread, SLOT(deleteLater()));
        f4thread->start();
}

#include <QtCore/QCoreApplication>
#include <QDebug>
//
#include <stdlib.h>
//
#include "first4server.h"
//
quint16 f4srvport = 15000;
//
extern QString f4srv_version = "1.9.80";
extern QString f4srv_client_required = "1.9.80";
//
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	first4server f4srv;
	if(f4srv.listen(QHostAddress::Any, f4srvport))
		qDebug() << "first4server started on port" << f4srvport;
	else
		qDebug() << "first4server NOT started";

	return a.exec();
}

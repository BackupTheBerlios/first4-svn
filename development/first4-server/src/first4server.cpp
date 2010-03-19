#include <stdlib.h>
#include <QFile>
#include <QDomDocument>
#include <QSqlDatabase>
#include <QDebug>
//
#include "first4server.h"
#include "first4thread.h"
//
first4server::first4server(QObject *parent)
    : QTcpServer(parent)
{
    readConfiguration();
}
//
void first4server::incomingConnection(int socketDescriptor)
{
        first4thread *f4thread = new first4thread(socketDescriptor, this);
        connect(f4thread, SIGNAL(finished()), f4thread, SLOT(deleteLater()));
        f4thread->start();
}
//
void first4server::readConfiguration()
{
    QDomDocument dbs("databases");
    QFile file ( "/etc/first4server/databases.conf" );
    if (file.open(QIODevice::ReadOnly))
    {
	dbs.setContent(file.readAll());
	file.close();
    }
    else
	qDebug() << "Can't read database file";

    QDomElement db = dbs.documentElement();
    QDomNodeList nlist = db.elementsByTagName("Database");
    if(nlist.size() > 0)
    {
	QDomElement e = nlist.at(0).toElement();
	if(!e.isNull())
	    connectToDatabase(e.attribute("Host"), e.attribute("Port").toInt(), e.attribute("DBName"), e.attribute("User"), e.attribute("Password"));
    }
}
//
void first4server::connectToDatabase(QString Host, int Port, QString DBName, QString User, QString Password)
{
    QSqlDatabase first4DB;
    first4DB = QSqlDatabase::addDatabase("QMYSQL");
    first4DB.setDatabaseName(DBName);
    first4DB.setUserName(User);
    first4DB.setPassword(Password);
    first4DB.setPort(Port);
    first4DB.setHostName(Host);
    if(first4DB.open())
    {
	qDebug() << "Connected to database " << DBName << " on Host " << Host << " Port " << Port <<  " with the User " << User;
    }
    else
    {
	qDebug() << "Can't open database " << DBName << " on Host " << Host << " Port " << Port <<  " with the User " << User;
	exit(0);
    }
}

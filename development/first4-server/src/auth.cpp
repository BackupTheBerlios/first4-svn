#include <QDebug>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QVariant>
#include <QDateTime>
//
#include "auth.h"
//
extern QString fullname, token;
//
int Auth::loginUser(QString username, QString passwd)
{
    token.clear();
    QString cpass = "";
    QCryptographicHash *pass = new QCryptographicHash(QCryptographicHash::Sha1);
    pass->addData(passwd.toAscii());

    int r;
    // Database successfully opened;
    QString qstr = QString( "SELECT fullname, id FROM users WHERE username='%1' AND userpass = '%2';").arg(username).arg(cpass.append(pass->result().toBase64()));
    QSqlQuery query(qstr);
    if(query.isActive())
    {
	query.next();
	fullname = query.value(0).toString();
	QDateTime now = QDateTime::currentDateTime();
	QCryptographicHash *t = new QCryptographicHash(QCryptographicHash::Sha1);
	t->addData(username.toAscii());
	t->addData(QString("%1").arg(now.toTime_t()).toAscii());
	token = token.append(t->result().toBase64());
	if(query.size()>0)
	    r = 0;
	else
	    r = -1;
    }
    else
    {
	qDebug() << "Query Error";
    }

    return r;
}
//
bool Auth::logoutUser(QString username)
{
    qDebug() << "Processing Logout User: " << username;
    return true;
}

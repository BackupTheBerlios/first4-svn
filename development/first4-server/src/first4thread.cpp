#include <QtNetwork>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QDomDocument>
//
#include "first4thread.h"
#include "auth.h"
//
extern QString f4srv_version;
extern QString f4srv_client_required;
QTcpSocket *tcpSocket;
//
first4thread::first4thread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}
//
void first4thread::run()
{
    tcpSocket = new QTcpSocket;
    if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
	emit error(tcpSocket->error());
	return;
    }
    qDebug() << "New connection from: " << tcpSocket->peerAddress().toString();

    QDomDocument doc("first4server");
    QDomElement root = doc.createElement("first4server");
    doc.appendChild(root);
	QDomElement srv_ver = doc.createElement("Version");
	root.appendChild(srv_ver);
	    QDomText srv_ver_value = doc.createTextNode(f4srv_version);
	    srv_ver.appendChild(srv_ver_value);
	QDomElement srv_host = doc.createElement("Host");
	root.appendChild(srv_host);
	    QDomText srv_host_value = doc.createTextNode(QHostInfo::localHostName()+"."+QHostInfo::localDomainName());
	    srv_host.appendChild(srv_host_value);
	QDomElement srv_client_ver = doc.createElement("ClientRequired");
	root.appendChild(srv_client_ver);
	    QDomText srv_client_ver_value = doc.createTextNode(f4srv_client_required);
	    srv_client_ver.appendChild(srv_client_ver_value);

    tcpSocket->write(doc.toByteArray());
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(incomingRequest()), Qt::AutoConnection);
    tcpSocket->flush();
    //tcpSocket->disconnectFromHost();
    tcpSocket->waitForDisconnected();
}
//
void first4thread::incomingRequest()
{
    if(tcpSocket->canReadLine())
    {
        QDomDocument incReq("req");
        QByteArray request;
	request = tcpSocket->read(tcpSocket->bytesAvailable());
        incReq.setContent(request);

        QDomElement docElem = incReq.documentElement();
	QDomNodeList nlist = docElem.elementsByTagName("Action");

	if(nlist.size() > 0)
	{
	    QDomElement e = nlist.at(0).toElement();
	    if(!e.isNull())
		performAction(e.text(), docElem);
	}
    }
}
//
void first4thread::writeBack(QDomDocument doc)
{
    qDebug() << doc.toByteArray();
    tcpSocket->write(doc.toByteArray());
    tcpSocket->flush();
}
//
bool first4thread::performAction(QString action, QDomElement docElem)
{
    if (action.section(".", 0, 0) == "Auth")
	writeBack(performAuthAction(action, docElem));
    else if (action.section(".", 0, 0) == "Idle")
	qDebug() << "Processing Idle action: " << action;
    else
	qDebug() << "Unknown action: " << action;
    return true;
}
//
QDomDocument first4thread::performAuthAction(QString action, QDomElement docElem)
{
    Auth auth;
    QDomDocument doc("first4server");
    if(action.section(".", 1, 1) == "Login")
    {
	QDomNodeList user = docElem.elementsByTagName("User");
	QDomNodeList pass = docElem.elementsByTagName("Password");
	QDomNodeList clientid = docElem.elementsByTagName("ClientId");
	if(auth.loginUser(user.at(0).toElement().text(), pass.at(0).toElement().text(), clientid.at(0).toElement().text()))
	{
	    QDomElement root = doc.createElement("first4server");
	    doc.appendChild(root);
		QDomElement success = doc.createElement("Login");
		root.appendChild(success);
		    QDomText success_value = doc.createTextNode("0");
		    success.appendChild(success_value);
	}
    }
    else if(action.section(".", 1, 1) == "Logout")
    {
	QDomNodeList user = docElem.elementsByTagName("User");
	QDomNodeList clientid = docElem.elementsByTagName("ClientId");
	if(auth.logoutUser(user.at(0).toElement().text(), clientid.at(0).toElement().text()))
	{
	    tcpSocket->flush();
	    tcpSocket->disconnectFromHost();
	    this->terminate();
	}
    }
    else
	qDebug() << "Processing Auth action: " << action;
    return doc;
}

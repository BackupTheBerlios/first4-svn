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
QString user, fullname, token;
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

    QDomDocument doc("first4");
    QDomElement root = doc.createElement("first4server");
    doc.appendChild(root);
	QDomElement server = doc.createElement("Server");
	server.setAttribute("Version", f4srv_version);
	server.setAttribute("Host", QHostInfo::localHostName()+"."+QHostInfo::localDomainName());
	server.setAttribute("ClientRequired", f4srv_client_required);
	root.appendChild(server);

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
	QDomNodeList nlist = docElem.elementsByTagName("Request");
	if(nlist.size() > 0)
	{
	    QDomElement e = nlist.at(0).toElement();
	    if(!e.isNull())
		performAction(e.attribute("Action"), e);
	}
    }
}
//
void first4thread::closeConnection()
{
    tcpSocket->flush();
    tcpSocket->disconnectFromHost();
    this->terminate();
}
//
void first4thread::writeBack(QDomDocument doc)
{
    qDebug() << doc.toByteArray();
    tcpSocket->write(doc.toByteArray());
    tcpSocket->flush();
}
//
bool first4thread::performAction(QString action, QDomElement e)
{
    if (action.section(".", 0, 0) == "Auth")
	performAuthAction(action, e);
    else if (action.section(".", 0, 0) == "Idle")
	qDebug() << "Processing Idle action: " << action;
    else
	qDebug() << "Unknown action: " << action;
    return true;
}
//
void first4thread::performAuthAction(QString action, QDomElement e)
{
    Auth auth;
    QDomDocument doc("first4");
    if(action.section(".", 1, 1) == "Login")
    {
	int answ = auth.loginUser(e.attribute("Username"), e.attribute("Password"));
	QDomElement root = doc.createElement("first4server");
	doc.appendChild(root);
	QDomElement request = doc.createElement("Request");
	request.setAttribute("Action", action);
	request.setAttribute("Answer", answ);
	if(answ == 0)
	{
	    request.setAttribute("Token", token);
	    request.setAttribute("Fullname", fullname);
	    root.appendChild(request);
	    writeBack(doc);
	}
	else
	{
	    root.appendChild(request);
	    writeBack(doc);
	    closeConnection();
	}
    }
    else if(action.section(".", 1, 1) == "Logout")
    {
	if(auth.logoutUser(e.attribute("Username")))
	{
	    tcpSocket->flush();
	    tcpSocket->disconnectFromHost();
	    this->terminate();
	}
    }
    else
	qDebug() << "Processing Auth action: " << action;
}

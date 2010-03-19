#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTcpSocket>
#include <QDomDocument>
#include <QCryptographicHash>
//
#include "loginfrm.h"
#include "cfgfrm.h"
#include "vars.h"
#include "loginconfserversfrm.h"
//
extern int uid;
extern QString username, fullname, docfolder, templatefolder, firstver;
extern QString dbhost, dbname, dbuid, dbpwd, dbport;
extern QTcpSocket *tcpSocket;
//
QStringList dbserver, dbname_local, uids, pwd, port;
QStringList f4host, f4port;
//
loginfrm::loginfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
//
void loginfrm::init() //Server
{
    this->setFixedSize(this->width(), this->height());
    this->setWindowTitle(this->windowTitle()+firstver);	
    
    vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
	    if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
    }	
    
    connect( btnok, SIGNAL( released() ), this, SLOT( checkpwd() ) );
    connect( btnservers, SIGNAL( released() ), this, SLOT( configure_servers() ) );
}
//
bool loginfrm::loadservers() //Server
{
    f4host.clear();
    f4port.clear();

    QDomDocument srvs("servers");
    QFile sfile ( QDir::homePath() +"/.first4/servers.conf" );
    if (sfile.open(QIODevice::ReadOnly))
    {
	srvs.setContent(sfile.readAll());
	sfile.close();
    }
    else
	qDebug() << "Can't read servers file";

    QDomElement srv = srvs.documentElement();
    QDomNodeList nlist = srv.elementsByTagName("Server");
    if(nlist.size() > 0)
    {
	for(int i = 0; i < nlist.size(); i++)
	{
	    QDomElement e = nlist.at(i).toElement();
	    if(!e.isNull())
	    {
		cmbdb->addItem(e.attribute("Description"));
		f4host.append(e.attribute("Host"));
		f4port.append(e.attribute("Port"));
	    }
	}
    }
    return TRUE;
}
//
void loginfrm::checkpwd()
{
    /*
    bool ok = FALSE;
    if(boxuser->text() != "")
    {	
    	QSqlDatabase first4DB;
    	if(dbserver[cmbdb->currentIndex()] != "")
    	{
			first4DB = QSqlDatabase::addDatabase("QMYSQL");
			first4DB.setDatabaseName(dbname_local[cmbdb->currentIndex()]);
			first4DB.setUserName(uids[cmbdb->currentIndex()]);
			first4DB.setPassword(pwd[cmbdb->currentIndex()]);
			first4DB.setPort(port[cmbdb->currentIndex()].toInt());
			first4DB.setHostName(dbserver[cmbdb->currentIndex()]);	
   		}
   		else
   		{
   			first4DB = QSqlDatabase::addDatabase("QSQLITE");
   			first4DB.setDatabaseName(dbname_local[cmbdb->currentIndex()]);
  		}
		if(first4DB.open())
		{
		    // Database successfully opened;
		    cfgfrm cfrm;
		    QSqlQuery querycheck("SHOW TABLES LIKE 'userstab';");
		    if(querycheck.size() == 0)	
		    	querycheck.exec("SHOW TABLES LIKE 'users';");
		    querycheck.next();
		    QString qstr = QString( "SELECT fullname, id FROM %1 WHERE username='%2' AND userpass = '%3';").arg(querycheck.value(0).toString()).arg(boxuser->text()).arg(cfrm.cryptpwd(boxpwd->text()));
		    QSqlQuery query(qstr);
		    if(query.isActive())
		    {
				query.next();
				if(query.size()>0)
				{
					ok = TRUE;
				    vars v;
					v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
				    username = boxuser->text();
				    fullname = query.value(0).toString();
				    uid = query.value(1).toInt();
				    loadsysvars();
				    this->accept();
				}
				else if(query.size() == -1 && query.value(0).toString() != "")
				{
					ok = TRUE;
				   	vars v;
					v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
				   	username = boxuser->text();
				    fullname = query.value(0).toString();
				    uid = query.value(1).toInt();
				   	loadsysvars();
				    this->accept();
				}
				else
				{
				    boxpwd->setText("");
				    boxuser->setFocus();
				    boxuser->selectAll();
				    QMessageBox::warning(this,"Login...",tr("Invalid Username or Password"));
				}
		    }
			else
    		{
    			QSqlError sqlerror = first4DB.lastError();
				QMessageBox::critical(0,"Error...", tr("Query Error.")+"\n\n"+sqlerror.text());
			}
		} else {
			QSqlError sqlerror = first4DB.lastError();
		    QMessageBox::critical(0,"Error...",tr("Unable to connect to database server!\n\n")+sqlerror.text());
		}
		if(!ok)
			first4DB.close();
    }*/

    QString cpass = "";
    QCryptographicHash *pass = new QCryptographicHash(QCryptographicHash::Sha1);
    pass->addData(boxpwd->text().toAscii());

    QDomDocument doc("first4");
    QDomElement root = doc.createElement("first4client");
    doc.appendChild(root);
	QDomElement server = doc.createElement("Request");
	server.setAttribute("Action", "Auth.Login");
	server.setAttribute("Username", boxuser->text());
	server.setAttribute("Password", cpass.append(pass->result().toBase64()));
	root.appendChild(server);

    qDebug() << doc.toString();

    tcpSocket = new QTcpSocket;
    tcpSocket->connectToHost(f4host[cmbdb->currentIndex()], f4port[cmbdb->currentIndex()].toInt());
    tcpSocket->waitForConnected();
    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
	tcpSocket->write(doc.toByteArray());
	tcpSocket->flush();
    }
    else
    {
	QMessageBox::critical(this,"Login...",tr("Can't connect to server!"));
    }
}
//
void loginfrm::saveservers()
{
    int ii = cmbdb->currentIndex();
    
    dbhost= dbserver[ii];
    dbname = dbname_local[ii];
    dbuid = uids[ii];
    dbpwd = pwd[ii];
    dbport = port[ii];
   
    QDir d(QDir::homePath()+"/.first4");
    if(!d.exists() )
    {
		if(!d.mkdir(QDir::homePath()+"/.first4"))
	    	QMessageBox::critical(0,"Error...", tr("Error when storing the server list!"));
    }
    QDir tmpdir(QDir::homePath()+"/.first4/tmp");
    if(!tmpdir.exists() )
    {
		if(!tmpdir.mkdir(QDir::homePath()+"/.first4/tmp"))
	    	QMessageBox::critical(0,"Error...", tr("Error when storing the server list!"));
    }
   
	QStringList lines;
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QTextStream stream ( &file );
		while(!stream.atEnd())
			lines << stream.readLine();
	}
	file.close();
    
	if ( file.open ( QIODevice::WriteOnly ) )
	{
		int i;
		QTextStream stream(&file);
		bool foundsec = FALSE;
		for(i=0;i<lines.count();i++)
		{
			if(lines[i] == "[SERVERS]")
			{
				foundsec = TRUE;
				stream << "[SERVERS]" << "\n";
				if(dbserver[ii] != "")
					stream << "MYSQL:" << uids[ii] << ":" << pwd[ii] << "@" << dbserver[ii] << "/" << dbname_local[ii] << ":" << port[ii] << "\n";
				else
					stream << "SQLITE:" << dbname_local[ii] << "\n";
				for(ii=0;ii<cmbdb->currentIndex();ii++)
				{
					if(dbserver[ii] != "")
		    			stream << "MYSQL:" << uids[ii] << ":" << pwd[ii] << "@" << dbserver[ii] << "/" << dbname_local[ii] << ":" << port[ii] << "\n";	
		    		else
		    			stream << "SQLITE:" << dbname_local[ii] << "\n";
				}
				for(ii=cmbdb->currentIndex()+1;ii<cmbdb->count();ii++)
				{
					if(dbserver[ii] != "")
		    			stream << "MYSQL:" << uids[ii] << ":" << pwd[ii] << "@" << dbserver[ii] << "/" << dbname_local[ii] << ":" << port[ii] << "\n";	
		    		else
		    			stream << "SQLITE:" << dbname_local[ii] << "\n";
				}

				while(lines[i].simplified() != "")
					i++;
				while(i<lines.count())
				{
					stream << lines[i] << "\n";	
					i++;
				}
			}
			else
			{
				stream << lines[i] << "\n";	
			}
		}
		if(!foundsec)
		{
			stream << "\n" << "[SERVERS]" << "\n";
			
			if(dbserver[ii] != "")
				stream << "MYSQL:" << uids[ii] << ":" << pwd[ii] << "@" << dbserver[ii] << "/" << dbname_local[ii] << ":" << port[ii] << "\n";
			else
				stream << "SQLITE:" << dbname_local[ii] << "\n";
				
			for(ii=0;ii<cmbdb->currentIndex();ii++)
			{
				if(dbserver[ii] != "")
	    			stream << "MYSQL:" << uids[ii] << ":" << pwd[ii] << "@" << dbserver[ii] << "/" << dbname_local[ii] << ":" << port[ii] << "\n";	
	    		else
	    			stream << "SQLITE:" << dbname_local[ii] << "\n";
			}
			for(ii=cmbdb->currentIndex()+1;ii<cmbdb->count();ii++)
			{
				if(dbserver[ii] != "")
	    			stream << "MYSQL:" << uids[ii] << ":" << pwd[ii] << "@" << dbserver[ii] << "/" << dbname_local[ii] << ":" << port[ii] << "\n";
	    		else
	    			stream << "SQLITE:" << dbname_local[ii] << "\n";
			}
			stream << "\n";
		}
		file.close();
	}
	else
		QMessageBox::warning(0, "Window positions...", "Can't write to configuration file.");
}
//
void loginfrm::loadsysvars()
{
	QString qstr = "SELECT var, value FROM maincfg WHERE `var` = 'docfolder' OR `var` = 'templatefolder' ORDER BY var ASC;";
	QSqlQuery vars(qstr);
	vars.next();
	docfolder = vars.value(1).toString();
	vars.next();
	templatefolder = vars.value(1).toString();
}
//
void loginfrm::configure_servers()
{
	loginconfserversfrm *conffrm = new loginconfserversfrm;
	conffrm->init();
	if(conffrm->exec())
		loadservers();
}

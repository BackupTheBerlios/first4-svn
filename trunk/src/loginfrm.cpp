#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "loginfrm.h"
#include "cfgfrm.h"
#include "vars.h"
#include "newdbfrm.h"

extern QString username, fullname, docfolder, templatefolder;
extern QString dbhost, dbname, dbuid, dbpwd,dbport;

QStringList dbserver,dbname_local,uid,pwd,port;
//
loginfrm::loginfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
//
void loginfrm::loadservers()
{
    this->setFixedSize(this->width(), this->height());
    vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
	    if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
    }	
	
	connect( btnok, SIGNAL( released() ), this, SLOT( checkpwd() ) );
    QFile file(QDir::homePath()+"/.first4/servers.conf" );
    if(file.open(QIODevice::ReadOnly))
    {
	QTextStream stream(&file);
	QString streamline;
	while(!stream.atEnd())
	{
	    streamline = stream.readLine();
	    uid.append(streamline.section("@",0,0).section(":",0,0));
	    pwd.append(streamline.section("@",0,0).section(":",1,1));
	    dbserver.append(streamline.section("@",1,1).section("/",0,0));
	    dbname_local.append(streamline.section("@",1,1).section("/",1,1).section(":",0,0));
	    port.append(streamline.section("@",1,1).section("/",1,1).section(":",1,1));
	    cmbdb->addItem(streamline.section("@",0,0).section(":",0,0) + "@"+ streamline.section("@",1,1).section("/",0,0) +"/"+streamline.section("@",1,1).section("/",1,1).section(":",0,0));
	}
	file.close();    
    }
    
    if(cmbdb->count()==0)
    {
		newdbfrm ndb;
		ndb.init();
		if(ndb.exec())
		    this->loadservers();
		else
		    this->reject();
    }
}
//
void loginfrm::checkpwd()
{
    if(boxuser->text() != "")
    {	
		QSqlDatabase pwdcheckDB = QSqlDatabase::addDatabase("QMYSQL");
		pwdcheckDB.setDatabaseName(dbname_local[cmbdb->currentIndex()]);
		pwdcheckDB.setUserName(uid[cmbdb->currentIndex()]);
		pwdcheckDB.setPassword(pwd[cmbdb->currentIndex()]);
		pwdcheckDB.setPort(port[cmbdb->currentIndex()].toInt());
		pwdcheckDB.setHostName(dbserver[cmbdb->currentIndex()]);
		if(pwdcheckDB.open())
		{
		    // Database successfully opened;
		    cfgfrm cfrm;
		    QString qstr = QString( "SELECT fullname FROM userstab WHERE username='%1' AND userpass = '%2'").arg(boxuser->text()).arg(cfrm.cryptpwd(boxpwd->text()));
		    QSqlQuery query(qstr);
		    if(query.isActive())
		    {
				if(query.size()>0)
				{
				    query.next();
				    username = boxuser->text();
				    fullname = query.value(0).toString();
				    loadsysvars();
				    vars v;
					v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
				    this->accept();
				}
				else
				{
				    QMessageBox::warning(this,"Login...",tr("Invalid Username or Password"));
				    boxpwd->setText("");
				    boxuser->setFocus();
				    boxuser->selectAll();
				}
		    }
		    pwdcheckDB.close();
		    QSqlDatabase::removeDatabase("pwdcheckDB");
		} else {
		    QMessageBox::critical(0,"Error...",tr("Unable to connect to database server!"));
		}
    }
}
//
void loginfrm::saveservers()
{
    int i = cmbdb->currentIndex();
    
    dbhost= dbserver[i];
    dbname = dbname_local[i];
    dbuid = uid[i];
    dbpwd = pwd[i];
    dbport = port[i];
   
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
   
    QFile file(QDir::homePath()+"/.first4/servers.conf");
    if(file.open(QIODevice::WriteOnly))
    {
		QTextStream stream(&file);	
		stream << uid[i] << ":" << pwd[i] << "@" << dbserver[i] << "/" << dbname_local[i] << ":" << port[i] << "\n";
		for(i=0;i<cmbdb->currentIndex();i++)
		    stream << uid[i] << ":" << pwd[i] << "@" << dbserver[i] << "/" << dbname_local[i] << ":" << port[i] << "\n";
		for(i=cmbdb->currentIndex()+1;i<cmbdb->count();i++)
		    stream << uid[i] << ":" << pwd[i] << "@" << dbserver[i] << "/" << dbname_local[i] << ":" << port[i] << "\n";
		file.close();
    }
}
//
void loginfrm::loadsysvars()
{
	QString qstr = "SELECT var, value FROM maincfgtab WHERE `var` = 'docfolder' OR `var` = 'templatefolder' ORDER BY var ASC;";
	QSqlQuery vars(qstr);
	vars.next();
	docfolder = vars.value(1).toString();
	vars.next();
	templatefolder = vars.value(1).toString();
}

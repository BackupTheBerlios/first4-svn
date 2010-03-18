#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
//
#include "loginfrm.h"
#include "cfgfrm.h"
#include "vars.h"
#include "loginconfserversfrm.h"
//
extern int uid;
extern QString username, fullname, docfolder, templatefolder, firstver;
extern QString dbhost, dbname, dbuid, dbpwd, dbport;
//
QStringList dbserver, dbname_local, uids, pwd, port;
//
loginfrm::loginfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
//
void loginfrm::init()
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
bool loginfrm::loadservers()
{
	cmbdb->clear();
	dbserver.clear();
	dbname_local.clear();
	uids.clear();
	pwd.clear();
	port.clear();
	QStringList tmp;
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QString streamline;
		QTextStream stream ( &file );
		while(stream.readLine() != "[SERVERS]" && !stream.atEnd()) ;
		do {
			streamline = stream.readLine();
			if(streamline != "")
			{
				if(streamline.section(":", 0, 0) == "SQLITE")
				{
					streamline = streamline.section(":", 1, 10);
			    	uids.append("");
		    		pwd.append("");
			    	dbserver.append("");
		    		dbname_local.append(streamline);
			    	port.append("");
					cmbdb->addItem(streamline + " (SQLite3)");
				}
				else
				{
					streamline = streamline.section(":", 1, 10);
			    	uids.append(streamline.section("@",0,0).section(":",0,0));
		    		pwd.append(streamline.section("@",0,0).section(":",1,1));
			    	dbserver.append(streamline.section("@",1,1).section("/",0,0));
		    		dbname_local.append(streamline.section("@",1,1).section("/",1,1).section(":",0,0));
			    	port.append(streamline.section("@",1,1).section("/",1,1).section(":",1,1));
		    		cmbdb->addItem(streamline.section("@",0,0).section(":",0,0) + "@"+ streamline.section("@",1,1).section("/",0,0) +"/"+streamline.section("@",1,1).section("/",1,1).section(":",0,0) + " (MySQL)");
				}
			}
		} while (streamline != "" && !stream.atEnd());
		file.close();
	}
    
    if(cmbdb->count()==0)
    	return FALSE;
    else
    	return TRUE;
}
//
void loginfrm::checkpwd()
{
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

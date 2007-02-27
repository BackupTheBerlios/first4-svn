#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDir>

#include "newdbfrm.h"
//
newdbfrm::newdbfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void newdbfrm::init()
{
    this->setFixedSize(this->width(), this->height());
    mainwidget->setCurrentIndex(0);
    connect(btnnext, SIGNAL(released()), this, SLOT(checkdatabases()));
    connect(btnfinish, SIGNAL(released()), this, SLOT(writeconffile()));
}
//
void newdbfrm::checkdatabases()
{
    QSqlDatabase checkDB = QSqlDatabase::addDatabase("QMYSQL");
    checkDB.setUserName(txtuser->text());
    checkDB.setPassword(txtpwd->text());
    checkDB.setHostName(txthost->text());
    checkDB.setPort(txtport->text().toInt());
    if(checkDB.open())
    {
		// Database successfully opened;
		QSqlQuery query;
		query.prepare( "SHOW DATABASES;");
		query.exec();
		if(query.isActive())
		{
		    while(query.next())
				cmbdb->insertItem(-1, query.value(0).toString());
		}
		checkDB.close();
	}
    else
    {
		QMessageBox::critical(0,"Error...",tr("Unable to connect to server!"));
    }
    mainwidget->setCurrentIndex(1);
}
//
void newdbfrm::writeconffile()
{
    QDir d(QDir::homePath()+"/.first4");
    if(!d.exists() )
    {
	if(!d.mkdir(QDir::homePath()+"/.first4"))
	    QMessageBox::critical(0,"Error...", tr("Error when storing the server list!"));
    }    
   
    QFile file(QDir::homePath()+"/.first4/servers.conf");
    if(!file.exists ())
    {
	if(file.open(QIODevice::WriteOnly))
	{
	    QTextStream stream(&file);	
	    stream << txtuser->text() << ":" << txtpwd->text() << "@" << txthost->text() << "/" << cmbdb->currentText() << ":" << txtport->text() << "\n";
	}
	file.close();
    }
    else
    {
	if(file.open(QIODevice::WriteOnly | QIODevice::Append ))
	{
	    QTextStream stream(&file);	
	    stream << txtuser->text() << ":" << txtpwd->text() << "@" << txthost->text() << "/" << cmbdb->currentText() << ":" << txtport->text() << "\n";
	}
	file.close();
    }
}

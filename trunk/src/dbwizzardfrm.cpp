#include <QPushButton>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include <QTextStream>
//
#include "dbwizzardfrm.h"
//
dbwizzardfrm::dbwizzardfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void dbwizzardfrm::init()
{
	connect(rbtnmysqlex, SIGNAL(clicked()), this, SLOT(enable_next()));
	connect(rbtnmysqlnew, SIGNAL(clicked()), this, SLOT(enable_next()));
	connect(btnnext, SIGNAL(clicked()), this, SLOT(next()));
	connect(btnback, SIGNAL(clicked()), this, SLOT(back()));
	connect(btncheckdb, SIGNAL(released()), this, SLOT(checkdbs()));
	
	mainstackwidget->setCurrentIndex(0);
}
//
void dbwizzardfrm::next()
{
	int minindex = 0;
	int maxindex = 0;
	if(rbtnmysqlex->isChecked())
	{
		minindex = 1;
		maxindex = 2;
	}
	else if(rbtnmysqlnew->isChecked())
	{
		minindex = 3;
		maxindex = 7;
	}

	if(mainstackwidget->currentIndex() == maxindex)
	{
		if(rbtnmysqlex->isChecked())
		{
			writeconffile();
		}
		else if(rbtnmysqlnew->isChecked())
		{
			createnewmysql();
			//writeconffile();
		}
	}

	if(mainstackwidget->currentIndex() < maxindex)
	{
		if(mainstackwidget->currentIndex() < minindex)
			mainstackwidget->setCurrentIndex(minindex-1);
		mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()+1);
		if(mainstackwidget->currentIndex() == maxindex)
		{
			btnnext->setText(QApplication::translate("dbwizzardfrm", "&Finish", 0, QApplication::UnicodeUTF8));	
			if(rbtnmysqlex->isChecked())
			{
				lblexhost->setText(txtexhost->text());
				lblexport->setText(txtexport->text());
				lblexuser->setText(txtexuser->text());
				lblexdbname->setText(cmbexdb->currentText().section(" (", 0, 0));
				lblexdbversion->setText(cmbexdb->currentText().section(" (", 1, 1).section(")", 0, 0));
			}
			if(rbtnmysqlnew->isChecked())
			{
				lblnewhost->setText(txtnewhost->text());
				lblnewport->setText(txtnewport->text());
				lblnewdbname->setText(txtnewdbname->text());
				lblnewuser->setText(txtnewfirstuser->text());
				lblnewadministrators->setText(txtnewadminuser->text());
			}
		}
		else
		{
			btnnext->setText(QApplication::translate("dbwizzardfrm", "&Next >>", 0, QApplication::UnicodeUTF8));	
		}
	}
}
//
void dbwizzardfrm::back()
{
	int minindex = 0;
	int maxindex = 0;
	btnnext->setText(QApplication::translate("dbwizzardfrm", "&Next >>", 0, QApplication::UnicodeUTF8));
	if(rbtnmysqlex->isChecked())
	{
		minindex = 1;
		maxindex = 2;
	}
	else if(rbtnmysqlnew->isChecked())
	{
		minindex = 3;
		maxindex = 7;
	}

	if(mainstackwidget->currentIndex() > minindex)
	{
		mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()-1);
	}
	else
		mainstackwidget->setCurrentIndex(0);
}
void dbwizzardfrm::enable_next()
{
	btnnext->setEnabled(TRUE);
}
//
void dbwizzardfrm::checkdbs()
{
    QSqlDatabase checkDB = QSqlDatabase::addDatabase("QMYSQL");
    checkDB.setUserName(txtexuser->text());
    checkDB.setPassword(txtexpwd->text());
    checkDB.setHostName(txtexhost->text());
    checkDB.setPort(txtexport->text().toInt());
    if(checkDB.open())
    {
		// Database successfully opened;
		QSqlQuery query;
		query.prepare( "SHOW DATABASES;");
		query.exec();
		if(query.isActive())
		{
		    while(query.next())
		    {
				QString qstr = "SELECT value FROM maincfgtab WHERE var = 'dbversion';";
				QSqlQuery query2(qstr);
				query2.next();
				QString firstversion = query2.value(0).toString();
				if(firstversion == "")
					firstversion = "ERR";
				cmbexdb->insertItem(-1, query.value(0).toString()+" ("+firstversion+")");	
	    	}	
		}
		checkDB.close();
	}
    else
    {
    	QSqlError sqlerror = checkDB.lastError();
		QMessageBox::critical(0,"Error...",tr("Unable to connect to server!")+"\n\n"+sqlerror.text());
    }
}
//
void dbwizzardfrm::writeconffile()
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
	    	if(rbtnmysqlex->isChecked())
		    	stream << lblexuser->text() << ":" << txtexpwd->text() << "@" << lblexhost->text() << "/" << lblexdbname->text() << ":" << lblexport->text() << "\n";
		}
		file.close();
    }
    else
    {
		if(file.open(QIODevice::WriteOnly | QIODevice::Append ))
		{
	    	QTextStream stream(&file);	
	    	if(rbtnmysqlex->isChecked())
		    	stream << lblexuser->text() << ":" << txtexpwd->text() << "@" << lblexhost->text() << "/" << lblexdbname->text() << ":" << lblexport->text() << "\n";
		}
		file.close();
    }
    this->accept();
}
//
void dbwizzardfrm::createnewmysql()
{
	QSqlError sqlerror;
    QSqlDatabase checkDB = QSqlDatabase::addDatabase("QMYSQL");
    checkDB.setHostName(txtnewhost->text());
    checkDB.setUserName(txtnewuser->text());
    checkDB.setPassword(txtnewpwd->text());
    checkDB.setPort(txtnewport->text().toInt());
    if(checkDB.open())
    {
    	QString qstr_newdb = QString("CREATE DATABASE %1").arg(txtnewdbname->text()); //creating database
		QSqlQuery query_newdb(qstr_newdb);
		sqlerror = query_newdb.lastError();
		if(sqlerror.isValid())
			QMessageBox::critical(0,"Error...",tr("Unable to connect to server!")+"\n\n"+sqlerror.text());
		else
		{
			//Creating tables;
			QString qsqr_tables;
			QSqlQuery query_newtables(qsqr_tables);
			sqlerror = query_newtables.lastError();
			if(sqlerror.isValid())
				QMessageBox::critical(0,"Error...",tr("Unable to connect to server!")+"\n\n"+sqlerror.text());
		}
		checkDB.close();
	}
    else
    {
    	QSqlError sqlerror = checkDB.lastError();
		QMessageBox::critical(0,"Error...",tr("Unable to connect to server!")+"\n\n"+sqlerror.text());
    }
}

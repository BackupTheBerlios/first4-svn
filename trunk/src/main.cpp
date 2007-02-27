#include <QApplication>
#include <QSplashScreen>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "mainfrm.h"
#include "loginfrm.h"

extern QString dbhost, dbname, dbuid, dbpwd, dbport;

bool createConnections()
{
    // create the default database connection
    QSqlDatabase firstDB = QSqlDatabase::addDatabase("QMYSQL");
    firstDB.setDatabaseName(dbname);
    firstDB.setUserName(dbuid);
    firstDB.setPassword(dbpwd);
    firstDB.setHostName(dbhost);
    firstDB.setPort(dbport.toInt());
    if (!firstDB.open() ) {
        QMessageBox::critical(0,"Error...", "Unable to connect to database server!");
    }
    return TRUE;
}

int main(int argc, char ** argv)
{
	QApplication app( argc, argv );
	QString langfile;
	QFile file(QDir::homePath()+"/.first4/lang.conf");
    if(file.open(QIODevice::ReadOnly))
    {
		QTextStream stream(&file);
		langfile = stream.readLine();
		file.close();
	}
    else
		QMessageBox::critical(0,"Error...", "Error during Language-File reading!");
    
    QTranslator translator;
    translator.load(langfile); 
    app.installTranslator( &translator );
	
    loginfrm logfrm;
    logfrm.loadservers();
    if(logfrm.exec()) {
   		logfrm.saveservers();
   		createConnections();
		QSplashScreen splash(QPixmap(":/images/images/startsplash.png"));
	    splash.show();
	    app.processEvents();

		splash.showMessage(
			QObject::tr("Initializing..."),
			Qt::AlignHCenter|Qt::AlignTop,
			Qt::black
	    ); 
	   	mainfrm mfrm;
		splash.finish(&mfrm);
		mfrm.show();
		mfrm.loaduserdata();
		mfrm.checkmsg();

		app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
		return app.exec();
		QSqlDatabase::removeDatabase("firstDB");	
   	}	
}

#include <QApplication>
#include <QSplashScreen>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>

#include "mainfrm.h"
#include "loginfrm.h"
#include "dbwizzardfrm.h"

extern QString dbhost, dbname, dbuid, dbpwd, dbport;

bool createConnections()
{
	// create the default database connection
	QSqlDatabase firstDB = QSqlDatabase::addDatabase ( "QMYSQL" );
	firstDB.setDatabaseName ( dbname );
	firstDB.setUserName ( dbuid );
	firstDB.setPassword ( dbpwd );
	firstDB.setHostName ( dbhost );
	firstDB.setPort ( dbport.toInt() );
	if ( !firstDB.open() )
	{
		QMessageBox::critical ( 0,"Error...", "Unable to connect to database server!" );
	}
	return TRUE;
}

int main ( int argc, char ** argv )
{
	QApplication app ( argc, argv );
	QString langfile;
	QFile file ( QDir::homePath() +"/.first4/lang.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QTextStream stream ( &file );
		langfile = stream.readLine();
		file.close();
	}
	else
		QMessageBox::critical ( 0,"Error...", "Error during Language-File reading!" );

	QTranslator translator;
	translator.load ( langfile );
	app.installTranslator ( &translator );

	loginfrm logfrm;
	if(!logfrm.loadservers())
	{
		dbwizzardfrm dbwiz;
		dbwiz.init();
		if(dbwiz.exec())
		    logfrm.loadservers();
		else
		{
			QMessageBox::information ( 0,"No Server defined...", "You must define at least one Server." );
			app.quit();
		}	
	}
	
	if ( logfrm.exec() )
	{
		logfrm.saveservers();
		createConnections();
		QSplashScreen splash ( QPixmap ( ":/images/images/newsplash.png" ) );
		splash.show();
		app.processEvents();
		mainfrm *mfrm = new mainfrm();
		splash.showMessage ( QObject::tr ( "Initializing ..." ), Qt::AlignHCenter|Qt::AlignBottom, Qt::black );

		splash.showMessage ( QObject::tr ( "Initializing userdata ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
		mfrm->loaduserdata();
		
		splash.showMessage ( QObject::tr ( "Initializing plugins ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
		mfrm->initplugins();
		
		splash.showMessage ( QObject::tr ( "Initializing messages ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
		mfrm->checkmsg();

		mfrm->show();

		app.connect ( &app, SIGNAL ( lastWindowClosed() ), &app, SLOT ( quit() ) );
		splash.finish( mfrm );
		return app.exec();
		QSqlDatabase::removeDatabase ( "firstDB" );
	}
	return 0;
}

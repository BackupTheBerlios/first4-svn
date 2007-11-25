#include <QApplication>
#include <QSplashScreen>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>

#include "mainfrm.h"
#include "loginfrm.h"
#include "dbwizzardfrm.h"

extern QString dbhost, dbname, dbuid, dbpwd, dbport;

int main ( int argc, char ** argv )
{
	QApplication app ( argc, argv );
	QString langfile;
	QFile file ( QDir::homePath() +"/.first4/translation.conf" );
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
		QSplashScreen splash ( QPixmap ( ":/newsplash.png" ) );
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

		app.connect ( &app, SIGNAL ( lastWindowClosed() ), &app, SLOT ( quit() ) );
		
		int sec = QTime::currentTime().second();
		while(sec != QTime::currentTime().second()-1) ; //wait 2 secs
		
	    mfrm->show();
		
		splash.finish( mfrm );
		return app.exec();
		QSqlDatabase::removeDatabase ( "firstDB" );
	}
	return 0;
}

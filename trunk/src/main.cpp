#include <QApplication>
#include <QSplashScreen>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QTranslator>
#include <QTime>

#include "mainfrm.h"
#include "loginfrm.h"
#include "dbwizzardfrm.h"

extern QString dbhost, dbname, dbuid, dbpwd, dbport;

int main ( int argc, char ** argv )
{
	QApplication app ( argc, argv );
	
	QString langfile;
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	QTextStream stream ( &file );
	
	if(!file.exists())
	{
		if ( file.open ( QIODevice::WriteOnly ) )
		{
			stream << "[GENERAL]" << "\n" << "TRANSLATION=" << "\n";
			file.close();
		}
	}
	
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QString line;
		while(!stream.atEnd())
		{
			line = stream.readLine();
			if(line.section("=",0,0) == "TRANSLATION")
				langfile = line.section("=", 1, 1);	
		}
		file.close();
	}
	
	QTranslator translator;
	translator.load ( langfile );
	app.installTranslator ( &translator );

	loginfrm logfrm;
	logfrm.init();
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
		
		splash.showMessage ( QObject::tr ( "Checking database ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
		if(mfrm->checkdb() != 0)
		{
			qApp->closeAllWindows();
		}
		else
		{
			splash.showMessage ( QObject::tr ( "Initializing userdata ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
			mfrm->loaduserdata();
		
			splash.showMessage ( QObject::tr ( "Initializing plugins ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
			mfrm->initplugins();
		
			splash.showMessage ( QObject::tr ( "Initializing messages ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
			mfrm->checkmsg();

			splash.showMessage ( QObject::tr ( "Startup completed ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );

			app.connect ( &app, SIGNAL ( lastWindowClosed() ), &app, SLOT ( quit() ) );
			QTime now = QTime::currentTime();
			while(now.addSecs(1) >= QTime::currentTime()) ; //wait 1 secs
			mfrm->show();
			splash.finish( mfrm );
			return app.exec();
		}
	}
	return 0;
}

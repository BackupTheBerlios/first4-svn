#include <QApplication>
#include <QSplashScreen>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QTranslator>
#include <QTime>
//
#include "mainfrm.h"
#include "loginfrm.h"
#include "dbwizzardfrm.h"
#include "vars.h"
//
extern QString firstver, dbhost, dbname, dbuid, dbpwd, dbport;
//
int main ( int argc, char ** argv )
{
	QApplication app ( argc, argv );
	
	QStringList arguments = app.arguments();
	if(arguments.count() > 1)
	{
		QTextStream cout(stdout,QIODevice::WriteOnly);
		for(int i=0; i<arguments.count(); i++)
		{
			cout << "\n";
			if(arguments[i] == "-v")
				cout << QString("first4 Version: %1\n").arg(firstver);
			app.quit();
		}
	}
	
	QString langfile;
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	QTextStream stream ( &file );
	
	//Create basic config file if not exist
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
		//Load Language settings
		QString line;
		while(!stream.atEnd())
		{
			line = stream.readLine();
			if(line.section("=",0,0) == "TRANSLATION")
				langfile = line.section("=", 1, 1);	
		}
		file.close();
	}
	
	//Load translation
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
			app.quit(); //Quit if no DB's are defined
		}	
	}
	if(logfrm.exec()) //Login will be accepted if username and passwort are correct
	{
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		logfrm.saveservers();
		QSplashScreen splash ( QPixmap ( ":/newsplash.png" ) );
		splash.show();
		app.processEvents();
		mainfrm *mfrm = new mainfrm();
		splash.showMessage ( QObject::tr ( "Initializing ..." ), Qt::AlignHCenter|Qt::AlignBottom, Qt::black );
		splash.showMessage ( QObject::tr ( "Checking database ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
		if(mfrm->checkdb() != 0) //check if the db is locked or old version
		{
			QApplication::restoreOverrideCursor();
			qApp->closeAllWindows();
		}
		else
		{
			splash.showMessage ( QObject::tr ( "Initializing userdata ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
			mfrm->loaduserdata(); //Load and set usersettings
			splash.showMessage ( QObject::tr ( "Initializing plugins ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
			mfrm->initplugins(); //Load plugins
			splash.showMessage ( QObject::tr ( "Initializing messages ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
			mfrm->checkmsg(); //Check if there are new messages
			splash.showMessage ( QObject::tr ( "Startup completed ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
			app.connect ( &app, SIGNAL ( lastWindowClosed() ), &app, SLOT ( quit() ) );
			QTime now = QTime::currentTime();
			while(now.addSecs(1) >= QTime::currentTime()) ; //wait 1 secs
			QApplication::restoreOverrideCursor();
			mfrm->show();
			splash.finish( mfrm );
			return app.exec();
		}
	}
	return 0;
}

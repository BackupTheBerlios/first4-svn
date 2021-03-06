#include <QTimer>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDir>
#include <QPluginLoader>
#include <QStatusBar>
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QDesktopServices>
#include <QUrl>
#include <QSplashScreen>
//
#include "mainfrm.h"
#include "vars.h"
#include "cfgfrm.h"
#include "aboutfrm.h"
#include "addrfrm.h"
#include "datafrm.h"
#include "ordersfrm.h"
#include "invfrm.h"
#include "docopenfrm.h"
#include "doceditfrm.h"
#include "plugininterface.h"
#include "procedurefrm.h"
#include "accountsfrm.h"
#include "accountseditfrm.h"
#include "msgfrm.h"
#include "msgeditfrm.h"
#include "dbupdatefrm.h"
#include "addrimpexpfrm.h"
#include "dataimpexpfrm.h"
#include "loginfrm.h"
//
extern int uid;
extern QString username, fullname, firstver;
extern QString dbhost, dbname, dbuid, dbpwd, dbrequire;

//
mainfrm::mainfrm ( QWidget * parent, Qt::WFlags f )
: QMainWindow ( parent, f )
{
  setupUi ( this );
}
//
void mainfrm::loaduserdata()
{
	lbluser->setText ( username );
	lbldb->setText ( dbname );
	lblserver->setText ( dbhost );
	this->setWindowTitle ( QString ( "first4 %1" ).arg ( firstver ) );

	maintoolbox->setCurrentIndex ( maintoolbox->count()-1 );

	QTimer *timer = new QTimer();
	connect ( timer, SIGNAL ( timeout() ), this, SLOT ( checkmsg() ) );
	timer->start ( 15000 );

	vars v;
	QStringList sgeo = v.loadgeo ( this->objectName() );
	if ( sgeo.size() > 0	)
	{
		if ( sgeo[0] == "1" )
			this->setWindowState ( this->windowState() ^ Qt::WindowMaximized );
		this->setGeometry ( sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt() );
	}

	//Slot Connections
	connect ( btnbrowsedir, SIGNAL ( released() ), this, SLOT ( browseaddr() ) );
	connect ( btnbrowsedata, SIGNAL ( released() ), this, SLOT ( browsedata() ) );
	connect ( btnvieworders, SIGNAL ( released() ), this, SLOT ( vieworders() ) );
	connect ( btninventory, SIGNAL ( released() ), this, SLOT ( inventory() ) );
	connect ( btnbrowsedoc, SIGNAL ( released() ), this, SLOT ( opendoc() ) );
	connect ( btnnewdoc, SIGNAL ( released() ), this, SLOT ( newdoc() ) );
	connect ( btnbrowseorders, SIGNAL ( released() ), this, SLOT ( browseorders() ) );
	connect ( btnneworder, SIGNAL ( released() ), this, SLOT ( neworder() ) );
	connect ( btnbrowseaccounts, SIGNAL ( released() ), this, SLOT ( browseaccounts() ) );
	connect ( btnbrowsemsgs, SIGNAL ( released() ), this, SLOT ( browsemsgs() ) );
	connect ( btnnewmsg, SIGNAL ( released() ), this, SLOT ( newmsg() ) );
	connect ( btnimpexpdir, SIGNAL ( released() ), this, SLOT ( addrimpexp() ) );
	connect ( btnimpexpdata, SIGNAL ( released() ), this, SLOT ( dataimpexp() ) );

	this->menuBar()->clear();
	this->createMenu();
}
//
int mainfrm::checkdb()
{
	int retr = 0;

	QSqlQuery querydblock("SELECT ID FROM maincfg WHERE var='dblocked' AND value='1';");
	if(querydblock.size() > 0)
	{
		querydblock.exec("SELECT value FROM maincfg WHERE var='dblockedmsg';");
		querydblock.next();
		QMessageBox::critical( 0, tr("DB update..."), tr("The selected database is locked by the Administrator:\n\n")+querydblock.value(0).toString());
		retr = 1;
	}
	QSqlError qerror = querydblock.lastError();
	if(qerror.isValid())
		QMessageBox::warning ( 0, tr ( "Check DB-Lock..." ), qerror.text());

	if(retr == 0 || uid == 0)
	{
		retr = 0;
		dbupdatefrm *updfrm = new dbupdatefrm;
		if(updfrm->init() != 0)
		{
			QApplication::restoreOverrideCursor();
			if(uid == 0)
				updfrm->exec();
			else
			{
				QMessageBox::information( 0, tr("DB update..."), tr("Database update is needed.\nPlease login as Administrator to perform the update.") );
				retr = 1;
			}
		}

		QString dbver; 
		QString qstr = "SELECT value FROM maincfg WHERE var = 'dbversion';";
		QSqlQuery query ( qstr );
		if ( query.isActive() )
		{
			query.next();
			dbver = query.value ( 0 ).toString();
		}
		if(dbrequire != dbver)
		{
			QApplication::restoreOverrideCursor();
			QMessageBox::critical( 0, tr("Wrong DB version..."), tr("This version of first4 needs a database with the version: %1 .\nThe selected database has version: %2").arg(dbrequire).arg(dbver) );
			retr = 1;
		}
	}
	return retr;
}
//
// TODO:	Add by ChMaster (aka: Alexander Saal)
void mainfrm::initplugins() {
	QDir pluginsDir = QDir ( qApp->applicationDirPath() );
	// FIXME: change plugindirectory to $HOME/.first4/plugins

	if(pluginsDir.exists())
	{
		pluginsDir.cd ( "plugins" );
		foreach ( QString fileName, pluginsDir.entryList ( QDir::Files ) )
		{
			if ( fileName.split ( "." ).value ( 1 ).toLower()  == "dll" || fileName.split ( "." ).value ( 1 ).toLower() == "so" )
			{
				QPluginLoader loader( pluginsDir.absoluteFilePath ( fileName ) );
				QObject *plug = loader.instance();
	
				if ( plug != NULL )
				{
					First4PluginInterface *fpi = qobject_cast<First4PluginInterface *> ( plug );
					if ( fpi )
					{
						if( maintoolbox->count() > fpi->toolBoxIndex() || fpi->toolBoxIndex() == -1 )
						{
							if( !fpi->pluginName().isEmpty() || !fpi->pluginName().isNull() )
							{
								maintoolbox->insertItem( maintoolbox->count() - 1, fpi->newToolBoxWidget(), fpi->img(), fpi->pluginName() );
								QStringList parameters = (QStringList() << username << fullname << firstver << dbhost << dbname);
								fpi->setenv(parameters);
							}
							else
							{
								maintoolbox->insertItem( maintoolbox->count() - 1, fpi->newToolBoxWidget(), fpi->img(), fileName.split ( "." ).value ( 0 ) );
							}
						}
					}
				}
			}
		}
	}
	else
		QMessageBox::information( 0, tr("Plugins-Directory doesn't exist..."), tr("Can't load plugins.\nPlugins-Directory doesn't exist.") );
}

//
void mainfrm::checkmsg()
{
	QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
	QSqlQuery query;
	query.prepare ( "SELECT ID FROM messages WHERE `user` LIKE :user;" );
	query.bindValue ( ":user", "%"+username+"%" );
	query.exec();
	query.next();

	statusBar()->setStyleSheet("font : bold 11px;"); 
	statusBar()->showMessage(tr ( "Messages: %1" ).arg ( query.size(), 0, 10 ));

	if(uid == 0 )
		admtasks();
	else
	{
		QSqlQuery querydblock("SELECT ID FROM maincfg WHERE var='dblocked' AND value='1';");
		if(querydblock.size() > 0)
		{
			querydblock.exec("SELECT value FROM maincfg WHERE var='dblockedmsg';");
			querydblock.next();
			QMessageBox::critical( 0, tr("DB update..."), tr("The current database was locked by the Administrator:\n\n")+querydblock.value(0).toString()+tr("\n\nYou will be logged out now!"));
			QApplication::quit();
		}
	}
	QApplication::restoreOverrideCursor();
}
//
void mainfrm::admtasks()
{
	QStringList queryreturn1, queryreturn2;
	//Auftraege ueberpruefen
	QString qstr1 = QString("SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM procedures WHERE `complete_until` < '%1';").arg(QDate::currentDate().toString("yyyy-MM-dd"));
	QSqlQuery query1(qstr1);
	if(query1.isActive())
	{
		while(query1.next())
		{
			QString qstr2 = QString("SELECT * FROM messages WHERE `data2`='%1' AND `data3`='%2' AND `data4`='%3';").arg(query1.value(6).toString()).arg(query1.value(5).toString()).arg(query1.value(10).toString());
			QSqlQuery query2(qstr2);
			if(query2.size()==0)
				queryreturn1.append(query1.value(3).toString()+"//"+query1.value(6).toString()+"//"+query1.value(5).toString()+"//"+query1.value(10).toString());
		}
	}
	else
	{
		QSqlError qerror = query1.lastError();
		if(qerror.isValid())
			QMessageBox::warning ( 0, tr ( "Check procedures..." ), qerror.text());
	}
	
	//Ein/Aus ueberpruefen
	QString qstr3 = QString("SELECT state, ID, date, refnr, address, code, description, amount FROM incexp WHERE `type`='inc' AND `date` < '%1';").arg(QDate::currentDate().toString("yyyy-MM-dd"));
	QSqlQuery query3(qstr3);
	if(query3.isActive())
	{
		while(query3.next())
		{
			QString qstr2 = QString("SELECT * FROM messages WHERE `data2`='%1' AND `data3`='%2' AND `data4`='%3';").arg(query3.value(3).toString()).arg(query3.value(2).toString()).arg(query3.value(7).toString());
			QSqlQuery query4(qstr2);
			if(query4.size()==0)
				queryreturn2.append(query3.value(4).toString()+"//"+query3.value(3).toString()+"//"+query3.value(2).toString()+"//"+query3.value(7).toString());
		}
	}
	else
	{
		QSqlError qerror = query3.lastError();
		if(qerror.isValid())
			QMessageBox::warning ( 0, tr ( "Check finances..." ), qerror.text());
	}	
	
	int i;
	msgeditfrm *emsg = new msgeditfrm;
	emsg->init("ord");
	for(i=0;i<queryreturn1.count();i++)
	{
		emsg->ord_customer->setText(queryreturn1[i].section("//", 0, 0).section(" (", 0, 0));
		emsg->ord_lbladdrid->setText(queryreturn1[i].section("//", 0, 0).section(" (", 1, 1).section(")", 0, 0));
		emsg->ord_ordernr->setText(queryreturn1[i].section("//", 1, 1));
		QString s = queryreturn1[i].section("//", 2, 2);
		emsg->ord_date1->setDate(QDate(s.section("-", 0, 0).toInt(),s.section("-", 1, 1).toInt(),s.section("-", 2, 2).toInt()));
		s = queryreturn1[i].section("//", 3, 3);
		emsg->ord_date2->setDate(QDate(s.section("-", 0, 0).toInt(),s.section("-", 1, 1).toInt(),s.section("-", 2, 2).toInt()));
		emsg->newentry();
	}
	emsg->init("iem");
	for(i=0;i<queryreturn2.count();i++)
	{
		emsg->iem_customer->setText(queryreturn2[i].section("//", 0, 0).section(" (", 0, 0));
		emsg->iem_lbladdrid->setText(queryreturn2[i].section("//", 0, 0).section(" (", 1, 1).section(")", 0, 0));
		emsg->iem_ordernr->setText(queryreturn2[i].section("//", 1, 1));
		QString s = queryreturn2[i].section("//", 2, 2);
		emsg->iem_date1->setDate(QDate(s.section("-", 0, 0).toInt(),s.section("-", 1, 1).toInt(),s.section("-", 2, 2).toInt()));
		emsg->iem_amount->setText(queryreturn2[i].section("//", 3, 3));
		emsg->newentry();
	}
}
//
void mainfrm::config()
{
	cfgfrm *cfg = new cfgfrm;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	cfg->init();
	QApplication::restoreOverrideCursor();
	cfg->show();
}
//
void mainfrm::about()
{
	aboutfrm *about = new aboutfrm;
	about->show();
}
//
void mainfrm::quitapplication()
{
	int r = QMessageBox::question ( this, tr ( "Exit..." ),tr ( "Exit First4?" ), QMessageBox::Yes, QMessageBox::No );
	if ( r == QMessageBox::Yes )
		this->close();
}
//
void mainfrm::closeEvent ( QCloseEvent* ce )
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	cleanup();
	vars v;
	v.savegeo ( this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height() );
	ce->accept();
	QApplication::restoreOverrideCursor();
	qApp->quit();
}
//
void mainfrm::browseaddr()
{
	addrfrm *afrm =  new addrfrm;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	afrm->init();
	QApplication::restoreOverrideCursor();
	afrm->show();
}
//
void mainfrm::browsedata()
{
	datafrm *dfrm = new datafrm;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	dfrm->init();
	QApplication::restoreOverrideCursor();
	dfrm->show();
}
//
void mainfrm::vieworders()
{
	ordersfrm *ofrm = new ordersfrm;
	if ( ofrm->init() != 0 )
		ofrm->show();
}
//
void mainfrm::inventory()
{
	invfrm *ifrm = new invfrm;
	if ( ifrm->init() != 0 )
		ifrm->show();
}
//
void mainfrm::opendoc()
{
	docopenfrm *dofrm = new docopenfrm;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	dofrm->init();
	QApplication::restoreOverrideCursor();
	dofrm->show();
}
//
void mainfrm::newdoc()
{
	doceditfrm *docfrm = new doceditfrm;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	docfrm->init();
	docfrm->cmbdoc->setCurrentIndex(0);
	docfrm->selecteddocument();
	QApplication::restoreOverrideCursor();
	docfrm->show();
}
//
void mainfrm::browseorders()
{
	procedurefrm *pfrm = new procedurefrm;
	if(pfrm->init() != 0)
		pfrm->show();
}
//
void mainfrm::neworder()
{
	procedurefrm *pfrm = new procedurefrm;
	if(pfrm->init() == 2)
		pfrm->neworder();
}
//
void mainfrm::browseaccounts()
{
	accountsfrm *afrm = new accountsfrm;
	if(afrm->init() != 0)
		afrm->show();
}
//
void mainfrm::cleanup()
{
	QDir tmpfolder = QDir::homePath() + "/.first4/tmp/";
	QStringList filelist = tmpfolder.entryList(QDir::Files);
	QString file;
	foreach(file,filelist)
	{
		QFile f(QDir::homePath() + "/.first4/tmp/"+file);
		f.remove();
	}
}
//
void mainfrm::browsemsgs()
{
	msgfrm *mfrm = new msgfrm;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	mfrm->init();
	QApplication::restoreOverrideCursor();
	mfrm->show();
}
//
void mainfrm::newmsg()
{
	msgeditfrm *emsg = new msgeditfrm;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	emsg->init("per");
	emsg->date->setDate(QDate::currentDate());
	QApplication::restoreOverrideCursor();
	emsg->exec();
}
//
void mainfrm::addrimpexp()
{
	addrimpexpfrm *addrimpexp = new addrimpexpfrm;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	addrimpexp->init();
	QApplication::restoreOverrideCursor();
	addrimpexp->exec();
}
//
void mainfrm::dataimpexp()
{
	dataimpexpfrm *dataimpexp = new dataimpexpfrm;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	dataimpexp->init();
	QApplication::restoreOverrideCursor();
	dataimpexp->exec();
}
//
void mainfrm::createMenu()
{
	QAction* changeDBAct = new QAction(tr("&Change DB-Connection"), this);
	changeDBAct->setStatusTip(tr("Change Database"));
	connect(changeDBAct, SIGNAL(triggered()), this, SLOT(changeDB()));

	QAction* settingsAct = new QAction(tr("&Settings"), this);
	settingsAct->setStatusTip(tr("first4 Settings"));
	connect(settingsAct, SIGNAL(triggered()), this, SLOT(config()));

	QAction* exitAct = new QAction(tr("&Exit first4"), this);
	exitAct->setStatusTip(tr("Exit first4"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(quitapplication()));

	QAction* aboutAct = new QAction(tr("&About first4"), this);
	aboutAct->setStatusTip(tr("About first4"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	QAction* websiteAct = new QAction(tr("&first4 Website"), this);
	websiteAct->setStatusTip(tr("Visit first4 Website"));
	connect(websiteAct, SIGNAL(triggered()), this, SLOT(visitwebsite()));

	QMenu* fileMenu; 
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(changeDBAct);
	fileMenu->addSeparator();
	fileMenu->addAction(settingsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	QMenu* infoMenu; 
	infoMenu = menuBar()->addMenu(tr("&?"));
	infoMenu->addAction(aboutAct);
	infoMenu->addSeparator();
	infoMenu->addAction(websiteAct);
}
//
void mainfrm::visitwebsite()
{
	QUrl first4website;
	first4website.setUrl ( "http://www.procopio.ch" );
	QDesktopServices::openUrl ( first4website );
}
//
void mainfrm::changeDB()
{
	loginfrm logfrm;
	logfrm.init();
	if(logfrm.loadservers())
	{
		this->hide();
		if(logfrm.exec())
		{
			QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
			logfrm.saveservers();
			QSplashScreen splash ( QPixmap ( ":/newsplash.png" ) );
			splash.show();
			splash.showMessage ( QObject::tr ( "Initializing ..." ), Qt::AlignHCenter|Qt::AlignBottom, Qt::black );
			
			splash.showMessage ( QObject::tr ( "Checking database ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
			if(this->checkdb() != 0)
			{
				QApplication::restoreOverrideCursor();
				qApp->closeAllWindows();
			}	
			else
			{
				splash.showMessage ( QObject::tr ( "Initializing userdata ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
				lbluser->setText ( username );
				lbldb->setText ( dbname );
				lblserver->setText ( dbhost );

				splash.showMessage ( QObject::tr ( "Initializing messages ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );
				this->checkmsg();
	
				splash.showMessage ( QObject::tr ( "Startup completed ..." ), Qt::AlignLeft|Qt::AlignBottom, Qt::black );

				QApplication::restoreOverrideCursor();
				this->show();
				splash.finish( this );
			}
		}
	}
	else
		QMessageBox::information ( 0,"No Server defined...", "You must define at least one Server." );
}

#include <QTimer>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QDir>
#include <QPluginLoader>
#include <QStatusBar>
#include <QCloseEvent>
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
	this->setFixedSize ( this->width(), this->height() );
	lbluser->setText ( username );
	lbldb->setText ( dbname );
	lblserver->setText ( dbhost );
	this->setWindowTitle ( QString ( "first %1" ).arg ( firstver ) );

	maintoolbox->setCurrentIndex ( maintoolbox->count()-1 );

	QTimer *timer = new QTimer();
	connect ( timer, SIGNAL ( timeout() ), this, SLOT ( checkmsg() ) );
	timer->start ( 30000 );

	vars v;
	QStringList sgeo = v.loadgeo ( this->objectName() );
	if ( sgeo.size() > 0	)
	{
		if ( sgeo[0] == "1" )
			this->setWindowState ( this->windowState() ^ Qt::WindowMaximized );
		this->setGeometry ( sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt() );
	}

	//Slot Connections
	connect ( btnsettings, SIGNAL ( released() ), this, SLOT ( config() ) );
	connect ( btnabout, SIGNAL ( released() ), this, SLOT ( about() ) );
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
	connect ( btnmsgicon, SIGNAL ( released() ), this, SLOT ( browsemsgs() ) );
	connect ( btnimpexpdir, SIGNAL ( released() ), this, SLOT ( addrimpexp() ) );
	connect ( btnimpexpdata, SIGNAL ( released() ), this, SLOT ( dataimpexp() ) );
}
//
int mainfrm::checkdb()
{
	int retr = 0;
	dbupdatefrm *updfrm = new dbupdatefrm;
	if(updfrm->init() != 0)
	{
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
		QMessageBox::critical( 0, tr("Wrong DB version..."), tr("This version of first4 needs at least a database with the version: %1 .\nThe selected database has version: %2").arg(dbrequire).arg(dbver) );
		retr = 1;
	}
	return retr;
}
//
// TODO:	Add by ChMaster (aka: Alexander Saal)
void mainfrm::initplugins() {
	QDir pluginsDir = QDir ( qApp->applicationDirPath() );
	// FIXME: change plugindirectory to $HOME/.first4/plugins
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
							maintoolbox->insertItem( maintoolbox->count() - 1, fpi->newToolBoxWidget(), fpi->img(), fpi->pluginName() );
						else
							maintoolbox->insertItem( maintoolbox->count() - 1, fpi->newToolBoxWidget(), fpi->img(), fileName.split ( "." ).value ( 0 ) );
					}
				}
			}
		}
	}

}

//
void mainfrm::checkmsg()
{
	QSqlQuery query;
	query.prepare ( "SELECT * FROM messages WHERE `user` LIKE :user;" );
	query.bindValue ( ":user", "%"+username+"%" );
	query.exec();
	query.next();
	lblmsgcount->setText ( tr ( "%1" ).arg ( query.size(), 0, 10 ) );
	if(lbluser->text() == "Administrator" )
		admtasks();
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
		//Ein/Aus ueberpruefen
	QString qstr3 = QString("SELECT status, ID, date, refnr, address, code, description, amount FROM incexp WHERE `typ`='inc' AND `date` < '%1';").arg(QDate::currentDate().toString("yyyy-MM-dd"));
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
	int i;
	msgeditfrm *emsg = new msgeditfrm;
	emsg->init("ord");
	for(i=0;i<queryreturn1.count();i++)
	{
	    emsg->ord_customer->setText(queryreturn1[i].section("//", 0, 0).section(" (", 0, 0));
	    emsg->ord_lbladdrid->setText(queryreturn1[i].section("//", 0, 0).section(" (", 1, 1).section(")", 0, 0));
	    emsg->ord_ordernr->setText(queryreturn1[i].section("//", 1, 1));
	    QString s = queryreturn1[i].section("//", 2, 2);
	    emsg->ord_date1->setDate(QDate::QDate(s.section("-", 0, 0).toInt(),s.section("-", 1, 1).toInt(),s.section("-", 2, 2).toInt()));
	    s = queryreturn1[i].section("//", 3, 3);
	    emsg->ord_date2->setDate(QDate::QDate(s.section("-", 0, 0).toInt(),s.section("-", 1, 1).toInt(),s.section("-", 2, 2).toInt()));
	    emsg->newentry();
	}
	emsg->init("iem");
	for(i=0;i<queryreturn2.count();i++)
	{
	    emsg->iem_customer->setText(queryreturn2[i].section("//", 0, 0).section(" (", 0, 0));
	    emsg->iem_lbladdrid->setText(queryreturn2[i].section("//", 0, 0).section(" (", 1, 1).section(")", 0, 0));
	    emsg->iem_ordernr->setText(queryreturn2[i].section("//", 1, 1));
	    QString s = queryreturn2[i].section("//", 2, 2);
	    emsg->iem_date1->setDate(QDate::QDate(s.section("-", 0, 0).toInt(),s.section("-", 1, 1).toInt(),s.section("-", 2, 2).toInt()));
	    emsg->iem_amount->setText(queryreturn2[i].section("//", 3, 3));
	    emsg->newentry();
	}
}
//
void mainfrm::config()
{
	cfgfrm *cfg = new cfgfrm;
	cfg->init();
	cfg->show();
}
//
void mainfrm::about()
{
	aboutfrm *about = new aboutfrm;
	about->show();
}
//
void mainfrm::closeEvent ( QCloseEvent* ce )
{
	int r = QMessageBox::question ( this, tr ( "Exit..." ),tr ( "Exit First?" ), QMessageBox::Yes, QMessageBox::No );
	if ( r == QMessageBox::Yes )
	{
		cleanup();
		vars v;
		v.savegeo ( this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height() );
		ce->accept();
		qApp->quit();
	} else {
		ce->ignore();
	}
}
//
void mainfrm::browseaddr()
{
	addrfrm *afrm =  new addrfrm;
	afrm->init();
	afrm->show();
}
//
void mainfrm::browsedata()
{
	datafrm *dfrm = new datafrm;
	dfrm->init();
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
	dofrm->init();
	dofrm->show();
}
//
void mainfrm::newdoc()
{
	doceditfrm *docfrm = new doceditfrm;
	docfrm->init();
    docfrm->cmbdoc->setCurrentIndex(0);
	docfrm->selecteddocument();
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
	mfrm->init();
	mfrm->show();
}
//
void mainfrm::newmsg()
{
	msgeditfrm *emsg = new msgeditfrm;
	emsg->init("per");
	emsg->date->setDate(QDate::currentDate());
	emsg->exec();
}
//
void mainfrm::addrimpexp()
{
	addrimpexpfrm *addrimpexp = new addrimpexpfrm;
	addrimpexp->init();
	addrimpexp->exec();
}
//
void mainfrm::dataimpexp()
{
	dataimpexpfrm *dataimpexp = new dataimpexpfrm;
	dataimpexp->init();
	dataimpexp->exec();
}

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
//
extern QString username, fullname, firstver;
extern QString dbhost, dbname, dbuid, dbpwd, dbport;

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

	maintoolbox->setCurrentIndex ( maintoolbox->count() );

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
	connect ( btnnewpayment, SIGNAL ( released() ), this, SLOT ( newpayment() ) );

}
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
	QStringList queryreturn1, queryreturn2;
	QSqlQuery query;
	query.prepare ( "SELECT * FROM msgtab WHERE `user` LIKE :user;" );
	query.bindValue ( ":user", "%"+username+"%" );
	query.exec();
	query.next();
	lblmsg->setText ( tr ( "Messages: %1" ).arg ( query.size(), 0, 10 ) );
	//QString("Messages: %1").arg(query.size(), 0, 10)
	if ( lbluser->text() == "Administrator" )
	{ /*
				//AuftrÃ¤ge Ã¼berprfen
				QSqlQuery query1;
				query1.prepare( "SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM proceduretab WHERE `complete_until` < :complete_until;");
				query1.bindValue( ":complete_until", QDate::currentDate().toString("yyyy-MM-dd") );
				query1.exec();

				if(query1.isActive())
				{
				    while(query1.next())
				    {
						QString connstr2 = QString("SELECT * FROM msgtab WHERE `data2`='%1' AND `data3`='%2' AND `data4`='%3';").arg(query1.value(6).toString()).arg(query1.value(5).toString()).arg(query1.value(10).toString());
						QSqlQuery query2(connstr2);
						if(query2.size()==0)
						    queryreturn1.append(query1.value(3).toString()+"//"+query1.value(6).toString()+"//"+query1.value(5).toString()+"//"+query1.value(10).toString());
				    }
				}

				//Ein/Aus Ã¼berprfen
				QString connstr = QString("SELECT status, ID, date, refnr, address, code, description, amount FROM ietab WHERE `typ`='inc' AND `date` < '%1';").arg(QDate::currentDate().toString("yyyy-MM-dd"));
				QSqlQuery query3(connstr);
				if(query3.isActive())
				{
				    while(query3.next())
				    {
						QString connstr2 = QString("SELECT * FROM msgtab WHERE `data2`='%1' AND `data3`='%2' AND `data4`='%3';").arg(query3.value(3).toString()).arg(query3.value(2).toString()).arg(query3.value(7).toString());
						QSqlQuery query4(connstr2);
						if(query4.size()==0)
						    queryreturn2.append(query3.value(4).toString()+"//"+query3.value(3).toString()+"//"+query3.value(2).toString()+"//"+query3.value(7).toString());
				    }
				}

				unsigned int i;
				editmsgfrm *emsg = new editmsgfrm;
				emsg->initfrm("auftr");
				for(i=0;i<queryreturn1.count();i++)
				{
				    emsg->txtkunde->setText(queryreturn1[i].section("//", 0, 0).section(" (", 0, 0));
				    emsg->lbladrID->setText(queryreturn1[i].section("//", 0, 0).section(" (", 1, 1).section(")", 0, 0));
				    emsg->txtauftragnr->setText(queryreturn1[i].section("//", 1, 1));
				    QString s = queryreturn1[i].section("//", 2, 2);
				    emsg->dateein->setDate(QDate::QDate(s.section("-", 0, 0).toInt(),s.section("-", 1, 1).toInt(),s.section("-", 2, 2).toInt()));
				    s = queryreturn1[i].section("//", 3, 3);
				    emsg->datebis->setDate(QDate::QDate(s.section("-", 0, 0).toInt(),s.section("-", 1, 1).toInt(),s.section("-", 2, 2).toInt()));
				    emsg->newentry();
				}
				emsg->initfrm("einau");
				for(i=0;i<queryreturn2.count();i++)
				{
				    emsg->txtkunde_2->setText(queryreturn2[i].section("//", 0, 0).section(" (", 0, 0));
				    emsg->lbladrID_2->setText(queryreturn2[i].section("//", 0, 0).section(" (", 1, 1).section(")", 0, 0));
				    emsg->txtauftragnr_2->setText(queryreturn2[i].section("//", 1, 1));
				    QString s = queryreturn2[i].section("//", 2, 2);
				    emsg->datefrist->setDate(QDate::QDate(s.section("-", 0, 0).toInt(),s.section("-", 1, 1).toInt(),s.section("-", 2, 2).toInt()));
				    emsg->txtbetrag->setText(queryreturn2[i].section("//", 3, 3));
				    emsg->newentry();
				}*/
	}
}
//
void mainfrm::config()
{
	cfgfrm *cfg = new cfgfrm;
	cfg->initfrm();
	cfg->lbluser->setText ( username );
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
void mainfrm::newpayment()
{
	
}

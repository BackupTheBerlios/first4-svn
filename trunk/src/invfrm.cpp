#include <QMessageBox>
#include <QMenu>
#include <QSqlQuery>
#include <QHeaderView>
#include <QTableWidget>
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QCloseEvent>
#include <QSqlError>
//
#include "invfrm.h"
#include "vars.h"
#include "progfrm.h"
#include "invnewfrm.h"
#include "cmntfrm.h"
//
extern QString username, fullname, docfolder, templatefolder;
QStringList comments, inv, rights, finished;
bool changes;
//
invfrm::invfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
int invfrm::init()
{
    switch (this->checkrights())
    {
    	case 0:
			QMessageBox::information(0, tr("Authorization Required..."), tr("You are not authorized to open this modul\n\nPlease contact your Administrator")); 
			return 0;
		break;
	    case 1:
			btnnew->setEnabled(FALSE);
			btnsave->setEnabled(FALSE);
			btncomplete->setEnabled(FALSE);
		break;
    }
    
	maintab->hideColumn(0);
    maintab->hideColumn(1);
    maintab->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents );
    maintab->horizontalHeader()->setResizeMode(3, QHeaderView::ResizeToContents );
    maintab->horizontalHeader()->setResizeMode(4, QHeaderView::ResizeToContents );
    maintab->horizontalHeader()->setResizeMode(5, QHeaderView::ResizeToContents );
    maintab->horizontalHeader()->setResizeMode(6, QHeaderView::ResizeToContents );
    maintab->horizontalHeader()->setResizeMode(7, QHeaderView::ResizeToContents );
    maintab->horizontalHeader()->setResizeMode(8, QHeaderView::ResizeToContents );
    maintab->horizontalHeader()->setResizeMode(9, QHeaderView::ResizeToContents );

    lbluser->setText(username);
    
    this->loadinv();
    this->loaddata();
    
    changes = FALSE;
     
    QMenu* btnprintmenu = new QMenu( this );
    Q_CHECK_PTR( btnprintmenu );

    QAction* print_preview = new QAction( tr("&Print pre&view"), this );
	connect(print_preview , SIGNAL(triggered()), this, SLOT(printpreview()));
	btnprintmenu->addAction(print_preview);
    QAction* print = new QAction( tr("&Print"), this );
	connect(print , SIGNAL(triggered()), this, SLOT(print())); 
	btnprintmenu->addAction(print);
		
	btnprint->setMenu(btnprintmenu);
	
	vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
	    if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
    }
    
	connect(btnnew , SIGNAL(released()), this, SLOT(newinv()));
	connect(btnsave , SIGNAL(released()), this, SLOT(savedata()));
	connect(btncomments , SIGNAL(released()), this, SLOT(viewcomments()));
	connect(cmbinv , SIGNAL(activated(int)), this, SLOT(loaddata()));
	connect(btncomplete , SIGNAL(released()), this, SLOT(complete()));
	connect(maintab , SIGNAL(cellChanged(int, int)), this, SLOT(setchange()));
	connect(btnclose , SIGNAL(released()), this, SLOT(close()));
    
    return 1;
}
//
int invfrm::checkrights()
{
    int permission = 0;
    if(username != "Administrator")
    {
    	QString qstr = "SELECT users FROM inventorycfg WHERE `users` LIKE '%"+username+" [1%';";
	    QSqlQuery query(qstr);
    	if(query.isActive())
	    {
			if(query.next())
			{
		    	permission = 1;
			    if(query.value(0).toString().section(username, 1, 1).section(" ", 1, 1) == "[11]")
					permission = 2;
			}
    	}
   	}
   	else
   		permission = 2;
    return permission;
}
//
void invfrm::loadinv()
{
    cmbinv->clear();
    comments.clear();
    inv.clear();
    rights.clear();
    finished.clear();
    QString qstr = "SELECT ID, NAME, DATATABLE, TABLENAME, DATE, USERS, FINISHED, COMMENTS FROM inventories WHERE `users` LIKE '%"+username+" [1%';";
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		while(query.next())
		{
		    cmbinv->addItem(query.value(3).toString()+" - "+query.value(4).toString());
		    inv << query.value(1).toString();
		    comments << query.value(7).toString();
		    rights << query.value(5).toString().section(username, 1, 1).section(" ", 1, 1);
		    finished << query.value(6).toString();
		}
    }
}

void invfrm::setchange()
{
    changes = TRUE;
}

void invfrm::loaddata()
{
	if(cmbinv->count() > 0)
	{
	    if(finished[cmbinv->currentIndex()] == "1")
	    {
			btnnew->setEnabled(FALSE);
			btnsave->setEnabled(FALSE);
			btncomplete->setEnabled(FALSE);
	    }
    
	    QString qstr = "SELECT ID, STOCK_ID, NAME, DESCRIPTION, QUANTITY, EP, VP, AP, NEW_QUANTITY, COMMENTS FROM "+inv[cmbinv->currentIndex()]+" ORDER BY ID ASC;";
	    QSqlQuery query(qstr);
	    if(query.isActive())
	    {
			progbar->setMaximum(query.size());
			int i;
			int ii = 0;
			maintab->setRowCount(query.size());
			while(query.next())
			{
			    for(i=0;i<10;i++)
			    {
			    	QTableWidgetItem *item = new QTableWidgetItem;
	   				item->setText(query.value(i).toString());
					maintab->setItem(ii, i, item);
		    	}
			    ii++;
			    progbar->setValue(query.at());
			}
	    }
	    progbar->setValue(progbar->maximum());	
	}
}
//
void invfrm::savedata()
{
    QString conn;
    QSqlQuery query;
    int i;
    progbar->setMaximum(maintab->rowCount());
    for(i=0;i<maintab->rowCount();i++)
    {
		query.prepare("UPDATE `"+inv[cmbinv->currentIndex()]+"` SET `AP`=:AP, `NEW_QUANTITY`=:NQ, `COMMENTS`=:CMNTS WHERE ID = :ID;");
		QTableWidgetItem *item = maintab->item(i, 7);
		query.bindValue( ":AP", item->text());
		item = maintab->item(i, 8);
		query.bindValue( ":NQ", item->text() );
		item = maintab->item(i, 9);
		query.bindValue( ":CMNTS", item->text() );
		item = maintab->item(i, 0);
		query.bindValue( ":ID", item->text() );
		query.exec();
		query.prepare("UPDATE `inventories` SET `COMMENTS`=:CMNTS WHERE NAME = :NAME;");
		query.bindValue( ":CMNTS", comments[cmbinv->currentIndex()] );
		query.bindValue( ":NAME", inv[cmbinv->currentIndex()] );
		query.exec();
		
		progbar->setValue(i);
    }
    progbar->setValue(progbar->maximum());
}
//
void invfrm::print()
{
    QString documentfile = writetexfile();
    
    QTime now = QTime::currentTime();
	while(now.addSecs(2) >= QTime::currentTime()) ; //wait 2 secs
		    		    
    QString psfile = documentfile;
    
    QProcess *procps = new QProcess( this );
    QStringList args;
    args << "-o" << psfile.replace(".dvi", ".ps") << documentfile;
    procps->start("dvips", args);
	if(procps->exitStatus() == QProcess::CrashExit ) 
		QMessageBox::critical(0,"Error...", tr("Can't convert to Postscript file."));
	else
	{
	    QProcess *procprint = new QProcess( this );
    	args.clear();
	    args << psfile;
	    procprint->start("kprinter", args);
	    if(procprint->exitStatus() != QProcess::NormalExit ) 
			QMessageBox::critical(0,"Error...", tr("Error during printing process."));
	}
}
//
void invfrm::printpreview()
{
	vars v;
	QString tool = v.get_tool("DVIVIEWER");
	if(tool != "")
	{
    	QString documentfile = writetexfile();
	    QProcess *procshow = new QProcess( this );
    	QStringList args;
	    args << documentfile;
		procshow->start(tool, args);
		if(procshow->exitStatus() != QProcess::NormalExit ) 
			QMessageBox::critical(0,"Error...", tr("Can't show DVI file."));
	}
	else
		QMessageBox::critical(0,"Error...", tr("You must first define a DVI-Viewer like KDVI or Okular in the settings module"));
}
//
QString invfrm::writetexfile()
{
    int i, ii;
    QString tabhead;
    for(i=2;i<maintab->columnCount();i++)
    {
    	QTableWidgetItem *item = maintab->horizontalHeaderItem(i);
	    tabhead += item->text() + " & ";
   	}
    tabhead = tabhead.mid(0, tabhead.length()-3);

    QString tabcontent = "";
    for(i=0;i<maintab->rowCount();i++)
    {	    
		for(ii=2;ii<maintab->columnCount();ii++)
		    tabcontent += maintab->item(i, ii)->text().replace("&", "") + " & ";
		tabcontent = tabcontent.mid(0, tabcontent.length()-3) + "\\\\ \\hline \n";
    }
    
    QString templatestr = loadtemplatedata();

    QTime now = QTime::currentTime();
	QDate today = QDate::currentDate();
    QFile output(QDir::homePath()+"/.first4/tmp/"+username+"-"+today.toString("yyyyMMdd")+now.toString("hhmmsszzz")+".tex");
	if(output.open(QIODevice::WriteOnly) )
	{
	    QTextStream outstream( &output );
	    templatestr = templatestr.replace("+++DATE+++", today.toString("dd. MMMM yyyy"));
	    templatestr = templatestr.replace("+++PAGE+++", tr("Page:"));
		templatestr = templatestr.replace("+++TITLE+++", cmbinv->currentText().replace("_", "\\_"));
		templatestr = templatestr.replace("+++TABHEAD+++", tabhead);
		templatestr = templatestr.replace("+++TABCONTENT+++", tabcontent);
		outstream << templatestr << "\n";
	    output.close();
	} else {
	    QMessageBox::critical(0,"Error...",tr("Can't write ouputfile!"));
	}
    
    //converting text to dvi
    QProcess *procdvi = new QProcess( this );
    QStringList args;
    args << "-output-directory="+QDir::homePath()+"/.first4/tmp/" << output.fileName();
    procdvi->start("latex", args);
	if(procdvi->exitStatus() != QProcess::NormalExit ) 
			QMessageBox::critical(0,"Error...", tr("Error during conversion to DVI file."));
			
	return output.fileName().replace(".tex", ".dvi");
}
//
void invfrm::complete()
{
    if(QMessageBox::information(this, tr("Complete Inventory..."), tr("Completed Inventories can't be edited!\n\nComplete nevertheless?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
		this->savedata();
		changes = FALSE;
		QSqlQuery query;
		query.prepare( "UPDATE `inventories` SET `FINISHED` = '1' WHERE `NAME` = :NAME LIMIT 1;");
		query.bindValue( ":NAME",  inv[cmbinv->currentIndex()]);
		query.exec();
		this->loadinv();
		this->loaddata();
    }
}
//
void invfrm::newinv()
{
    QStringList tabname;
    invnewfrm* ninv = new invnewfrm;
    QString connstr = QString("SELECT * FROM datatables WHERE users LIKE '%%1 [1%' AND `tabtyp` = 'stock';").arg(username);
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		while(query.next())
		{
		    ninv->cmbinv->addItem(query.value(2).toString());
		    tabname.append(query.value(1).toString());
		}
    }
    if(ninv->exec())
    {
		int invcount = 1;
		QString invname = "";
		QString qstr = "SELECT * FROM inventories ORDER BY name ASC;";	
		QSqlQuery query1(qstr);
		if(query1.isActive())
		{
		    while(query1.next())
		    {
				if(QString("inv%1").arg(invcount,0,10) == query1.value(1).toString())
				    invcount++;
				else
				{
				    if(invname == "")
						invname = QString("inv%1").arg(invcount,0,10);
				}
		    }
		    if(invname == "")
				invname = QString("inv%1").arg(invcount++,0,10);
		}

		QString conn2 = "INSERT INTO `inventories` (ID, NAME, DATATABLE, TABLENAME, DATE, USERS, FINISHED, COMMENTS) VALUES ('', '"+invname+"', '"+tabname[ninv->cmbinv->currentIndex()]+"', '"+ninv->cmbinv->currentText()+"', '"+QDate::currentDate().toString("yyyy-MM-dd")+"','Administrator [11] , "+username+" [11]', '0', '"+ninv->txtcomments->toPlainText()+"');";
		QSqlQuery query2(conn2);
	
		QString conn3 = "CREATE TABLE `"+invname+"` (`ID` INT(11)  NOT NULL AUTO_INCREMENT, `STOCK_ID` TEXT  NOT NULL, `NAME` TEXT  NOT NULL,`DESCRIPTION` TEXT  NOT NULL,`QUANTITY` TEXT  NOT NULL, `EP` TEXT NOT NULL, `VP` TEXT NOT NULL, `AP` TEXT NOT NULL, `NEW_QUANTITY` TEXT NOT NULL, `COMMENTS` TEXT  NOT NULL, PRIMARY KEY(`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
		QSqlQuery query3(conn3);
	
		progfrm* pfrm = new progfrm;
		QString conn4 = "SELECT ID, col1, col2, col3, col7, col8 FROM "+tabname[ninv->cmbinv->currentIndex()]+";";
		QSqlQuery query4(conn4);
		if(query4.isActive())
		{
		    pfrm->setFixedSize(pfrm->width(), pfrm->height());
		    pfrm->progbar->setMaximum(query4.size());
		    pfrm->txtcomments->setText("Creating Inventory...");
		    pfrm->show();
		    while(query4.next())
		    {
				QString conn5 = "INSERT INTO "+invname+" (STOCK_ID, NAME, DESCRIPTION, QUANTITY, EP, VP, AP, NEW_QUANTITY, COMMENTS) VALUES ('"+tabname[ninv->cmbinv->currentIndex()]+"_"+query4.value(0).toString()+"', '"+query4.value(1).toString()+"', '"+query4.value(2).toString()+"', '"+query4.value(3).toString()+"', '"+query4.value(4).toString()+"', '"+query4.value(5).toString()+"', '', '', '');";
				QSqlQuery query5(conn5);
				pfrm->progbar->setValue(query4.at());
		    }
		    pfrm->progbar->setValue(pfrm->progbar->maximum());
		    pfrm->close();
		}
		this->loadinv();
		this->loaddata();
    }
}
//
void invfrm::viewcomments()
{
    cmntfrm* cfrm = new cmntfrm;
    if(rights[cmbinv->currentIndex()] != "[11]")
		cfrm->txtcomments->setReadOnly(TRUE);
    cfrm->txtcomments->setText(comments[cmbinv->currentIndex()]);
    if(cfrm->exec())
		comments[cmbinv->currentIndex()] = cfrm->txtcomments->toPlainText();
    this->setchange();
}
//
void invfrm::closeEvent(QCloseEvent* ce )
{
    if(changes && finished[cmbinv->currentIndex()] != "1")
    {
		int r = QMessageBox::information(this, tr("Save Data..."), tr("Save Inventory?"), QMessageBox::Yes, QMessageBox::No,QMessageBox::Cancel);
		if(r == QMessageBox::Yes)
		{
		    this->savedata();
		    changes = FALSE;	
		}
		if(r == QMessageBox::Cancel)
		    ce->ignore();
		else
		{
			vars v;
			v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
			ce->accept();
		}
    }
    else
    {
		vars v;
		v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
		ce->accept();
   	}
}
//
QString invfrm::loadtemplatedata()
{
	QString answ;
	QSqlQuery query("SELECT data FROM templates WHERE `name`='sys_inventory';");
	if ( query.isActive())
	{
		query.next();
		answ = query.value(0).toString();
	}
	else
	{
		QSqlError qerror = query.lastError();
		QMessageBox::warning ( 0, tr ( "Can't load template..." ), qerror.text() );
	}
	return answ;
}

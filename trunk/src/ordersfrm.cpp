#include <QMessageBox>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QHeaderView>
#include <QDate>
#include <QMenu>
//
#include "ordersfrm.h"
#include "orderseditfrm.h"
#include "vars.h"
//
extern QString username;
//
ordersfrm::ordersfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
int ordersfrm::init()
{
    int r = this->checkrights();
    if(r == 1)
		btnadd->setEnabled(FALSE);
    if(r==0)
		QMessageBox::information(0, tr("Authorization Required..."), tr("You are not authorized to open this modul\n\nPlease contact your Administrator")); 

	treeindex->header()->setResizeMode(0, QHeaderView::Stretch);
	treeindex->setColumnWidth(1, 50);
	treeindex->setColumnHidden(2, TRUE);
	
	treemain->setColumnWidth(0, 40);
	
    vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
        if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
   	}
    
   	lbluser->setText(username);
   	progbar->setMaximum(1);
   	progbar->setValue(1);
    this->countentries();

	connect(treeindex, SIGNAL(itemClicked ( QTreeWidgetItem*, int)), this, SLOT(loadentries()));
	connect(btnadd, SIGNAL(released()), this, SLOT(newentry()));
	connect(btnedit, SIGNAL(released()), this, SLOT(editentry()));
	connect(btndelete, SIGNAL(released()), this, SLOT(deleteentry()));
	connect(btncompleted, SIGNAL(released()), this, SLOT(complete()));
	connect(treemain, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));

    return r;
}
//
void ordersfrm::closeEvent( QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void ordersfrm::countentries()
{
	int i;
	QString qstr;
	QSqlQuery query;
	QTreeWidgetItem *item = new QTreeWidgetItem;
	for(i=0;i<4;i++)
	{
		QTreeWidgetItem *item = treeindex->topLevelItem(i);
		qstr = QString("SELECT ID FROM orderstab WHERE `STATUS`= '%1';").arg(i);
		QSqlQuery query(qstr);
		query.next();
		if(item != 0)
		{
			if(i<3)
				item->setText(1, QString("%1").arg(query.size(), 0, 10));
			else
				item->setText(1, "-");
		}
	}
}
//
int ordersfrm::checkrights()
{
    int permission = 0;
    QString conn = "SELECT users FROM orderscfgtab WHERE `users` LIKE '%"+username+" [1%';";
    QSqlQuery query(conn);
    if ( query.isActive())
    {
		query.next();
		if(query.value(0).toString().section(username, 1, 1).section(" ", 1, 1)=="[10]")
		    permission = 1;
		if(query.value(0).toString().section(username, 1, 1).section(" ", 1, 1)=="[11]")
		    permission = 2;
    }
    return permission;
}
//
void ordersfrm::loadentries()
{
    treemain->clear();
    QTreeWidgetItem *item = treeindex->currentItem();
    if(item != 0)
    {
    	QString qstr = QString("SELECT ID, STATUS, ORDERED_BY, FOR_ORDER, STOCK, DATE1, DATE2, DATE3, DEF, DESCRIPTION, QUANTITY, SUPPLIER, PRICE, COMMENTS FROM orderstab WHERE `STATUS`= '%1' ORDER BY DATE1;").arg(item->text(2));
		QSqlQuery query(qstr);
		if ( query.isActive())
		{
			progbar->setMaximum(query.size());
		    while(query.next())
		    {
				QTreeWidgetItem *checkitem = new QTreeWidgetItem(treemain);
				checkitem->setCheckState(0, Qt::Unchecked);
				QString st = query.value(1).toString();
				checkitem->setText(0, query.value(0).toString());
				checkitem->setText(1, query.value(5+st.toInt()).toDate().toString("dd.MM.yyyy"));
				checkitem->setText(2, query.value(8).toString());
				checkitem->setText(3, query.value(9).toString());
				checkitem->setText(4, query.value(10).toString());
				checkitem->setText(5, query.value(12).toString());
				checkitem->setText(6, query.value(3).toString());
				checkitem->setText(7, query.value(2).toString());
				checkitem->setText(8, query.value(4).toString());
				checkitem->setText(9, query.value(11).toString());
				checkitem->setText(10, query.value(13).toString());
				progbar->setValue(query.at()+1);
		    }
		}
		if(item->text(2).toInt() < 3)
		    btncompleted->setEnabled(TRUE);
		else
		    btncompleted->setEnabled(FALSE);
	    }	
}
//
void ordersfrm::newentry()
{
    orderseditfrm *oefrm = new orderseditfrm;
    oefrm->init();
    if(oefrm->exec())
    {
		this->loadentries();
		this->countentries();
    }
}
//
void ordersfrm::editentry()
{
    QTreeWidgetItem *item = treemain->currentItem();
    orderseditfrm *oefrm = new orderseditfrm;
    oefrm->init();
    oefrm->editentry(item->text(0));
    if(oefrm->exec())
    {
		this->loadentries();
		this->countentries();
    }
}
//
void ordersfrm::deleteentry()
{
    QTreeWidgetItem *item = treemain->currentItem();
    if(item != 0)
    {
		int r = QMessageBox::question(this, tr("Delete purchase order..."),tr("Delete purchase order for %1?").arg(item->text(3).mid(0,50)),QMessageBox::Yes, QMessageBox::No);
		if(r == QMessageBox::Yes)
		{
			QString qstr = QString("DELETE FROM orderstab WHERE `ID`= '%1' LIMIT 1;").arg(item->text(0));
		    QSqlQuery query(qstr);
		    this->loadentries();
		    this->countentries();
		}
    }
}
//
void ordersfrm::complete()
{
	int r = QMessageBox::question(this, tr("Complete items..."),tr("Change status for completed items?"),QMessageBox::Yes, QMessageBox::No);
    if(r == QMessageBox::Yes)
    {
		int i;
		QTreeWidgetItem *item = new QTreeWidgetItem;
		for(i=0;i<treemain->topLevelItemCount();i++)
		{
				item = treemain->topLevelItem(i);
		    if(item->checkState(0))
		    {
		    	QString qstr = QString("SELECT STATUS, STOCK, DEF FROM `orderstab` WHERE `ID`=%1;").arg(item->text(0));
				QSqlQuery query1(qstr);
				query1.next();
		
				if(query1.value(0).toInt() < 2)
				{
				    QSqlQuery query2;
				    query2.prepare("UPDATE `orderstab` SET `STATUS`= :status, `DATE"+QString("%1").arg(query1.value(0).toInt()+2, 0, 10)+"`= :date WHERE `ID`=:ID LIMIT 1;");
				    query2.bindValue(":status", query1.value(0).toInt()+1);
				    query2.bindValue(":date", QDate::currentDate().toString("yyyy-MM-dd"));
				    query2.bindValue(":ID", item->text(0));
				    query2.exec();
				}
		
				if(query1.value(0).toInt() == 2)
				{
					qstr = QString("UPDATE `orderstab` SET `STATUS`= '%1' WHERE `ID`='%2' LIMIT 1;").arg(query1.value(0).toInt()+1).arg(item->text(0));
				    QSqlQuery query2(qstr);
		    
		    		qstr = QString("SELECT NAME, USERS FROM datatabs WHERE `DESCRIPTION`='%1';").arg(query1.value(1).toString());
				    QSqlQuery query3(qstr);
				    query3.next();
				    QString stock = query3.value(0).toString();
		    
		    		qstr = QString("SELECT ID, col3 FROM %1 WHERE `col1`= '%2';").arg(stock).arg(item->text(2));
		    		QSqlQuery query4(qstr);
				    query4.next();
				    QString id = query4.value(0).toString();
				    QString old_q = query4.value(1).toString();
		    	    
		    	    qstr = QString("UPDATE `%1` SET `col3`= '%2' WHERE `ID`= '%3' LIMIT 1;").arg(stock).arg(old_q.toInt() + item->text(4).toInt()).arg(id);
				    QSqlQuery query5(qstr);
				    QMessageBox::question(this, tr("Complete items..."), query5.executedQuery());
				}
		    }
		}
		loadentries();
		countentries();
    }
}
//
void ordersfrm::contmenu()
{
    QMenu* contextMenu = new QMenu( this );
    Q_CHECK_PTR( contextMenu );

    QAction* edititem = new QAction( tr("&Edit entry"), this );
	connect(edititem , SIGNAL(triggered()), this, SLOT(editentry()));
	contextMenu->addAction(edititem);

    QAction* delitem = new QAction( tr("&Delete entry"), this );
	connect(delitem , SIGNAL(triggered()), this, SLOT(deleteentry()));
	contextMenu->addAction(delitem);
		
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}

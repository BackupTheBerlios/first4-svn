#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>
#include <QCloseEvent>
//
#include "proceduresearch.h"
#include "vars.h"
//
proceduresearch::proceduresearch( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void proceduresearch::init()
{
	treemain->setColumnWidth(0, 150);
    treemain->setColumnWidth(1, 80);
    treemain->setColumnWidth(2, 0);
    treemain->setColumnWidth(3, 190);
    treemain->setColumnWidth(4, 300);
    treemain->setColumnWidth(5, 80);
    
	vars v;
	QStringList sgeo = v.loadgeo ( this->objectName() );
	if ( sgeo.size() > 0	)
	{
		if ( sgeo[0] == "1" )
			this->setWindowState ( this->windowState() ^ Qt::WindowMaximized );
		this->setGeometry ( sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt() );
	}
    
    connect(txtsearch, SIGNAL(returnPressed()), this, SLOT(searchentry()));
    connect(btnsearch, SIGNAL(released()), this, SLOT(searchentry()));
    connect(btnclear, SIGNAL(released()), this, SLOT(clearsearch()));
    connect(btncancel, SIGNAL(released()), this, SLOT(cancelbtn()));
    connect(btnaccept, SIGNAL(released()), this, SLOT(acceptbtn()));
    connect(treemain, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(acceptbtn()));
}
//
void proceduresearch::searchentry()
{
	treemain->clear();
    QStringList searchrow, status;
    searchrow << "orderid" << "client" << "description" << "tasks" << "orders";
	status << tr("Incomming orders") << tr("Offers") << tr("Open orders") << tr("Completed orders") << tr("Deliverynotes") << tr("Invoices") << tr("Archive");

	QString qstr1 = QString("SELECT ID, status, completed, client, description, date FROM proceduretab WHERE `%1` LIKE '%%2%' ORDER BY status;").arg(searchrow[cmbsearchrow->currentIndex()]).arg(txtsearch->text());
	QSqlQuery query(qstr1);
	if(query.isActive())
	{
		while(query.next())
		{
		   	QTreeWidgetItem *item = new QTreeWidgetItem;
		    item->setText(0, status[query.value(1).toInt()]);
			if(query.value(2).toString() == "1")
				item->setIcon(1, QIcon(QString::fromUtf8(":/images/images/button_ok_small.png")));
			else
			    item->setIcon(1, QIcon(QString::fromUtf8(":/images/images/kill.png")));
		    item->setText(2, query.value(0).toString());
		    item->setText(3, query.value(3).toString());
		    item->setText(4, query.value(4).toString());
		    item->setText(5, QDate::fromString(query.value(5).toString(), "yyyy-MM-dd").toString("dd.MM.yyyy"));
	    	treemain->addTopLevelItem(item);
		}	
	}
}
//
void proceduresearch::clearsearch()
{
	txtsearch->setText("");
	treemain->clear();
}
//
void proceduresearch::closeEvent( QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void proceduresearch::acceptbtn()
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	QTreeWidgetItem *item = treemain->currentItem();
	done(item->text(2).toInt());
}
//
void proceduresearch::cancelbtn()
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	reject();
}
//

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QCloseEvent>
//
#include "cashpoint_main.h"
#include "stockselfrm.h"
//
extern QString username, fullname, firstver;
//
QStringList vatlist;
//
CashPoint *cashpoint_instance = NULL;
CashPoint::CashPoint( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
	cashpoint_instance = this;
}
//
void CashPoint::init(QStringList parameters)
{
	username=parameters[0];
	fullname=parameters[1];
	firstver=parameters[2];
	QString dbhost = parameters[3];
	QString dbname = parameters[4];
	this->setWindowTitle(QString("first4 Cashpoint-Plugin / User: %1 (%2) connected to %3@%4").arg(fullname).arg(username).arg(dbname).arg(dbhost));
	//lblTotAmount->setText(QString("%1").arg(tot, 0, 'f',2));
	txtsearch->setText("");
	
	//Create connections
	connect(btnsearch, SIGNAL(released()), this, SLOT(checkdb()));
	connect(txtsearch, SIGNAL(returnPressed()), this, SLOT(checkdb()));
	connect(btnclose, SIGNAL(released()), this, SLOT(close()));
	
	//VAT
	initvat();
}
//
void CashPoint::checkdb()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	if(txtsearch->text()!="")
    {
	    QSqlQuery query("SELECT name, description FROM datatables WHERE `tabtyp` = 'stock' AND `users` LIKE '%"+username+"%';");
	    if(query.isActive())
	    {
	    	stockselfrm *sfrm = new stockselfrm;
			while(query.next())
			{
				QString qstr = QString("SELECT ID, col1, col2, col3, col5, col8, col12, col6 FROM %1 WHERE col1 LIKE '%%2%' AND `col13`='1' ORDER BY col1 ASC;").arg(query.value(0).toString()).arg(txtsearch->text());
			    QSqlQuery query2(qstr);
			    if(query2.isActive())
			    {
					while(query2.next())
					{
						QTreeWidgetItem *item = new QTreeWidgetItem(sfrm->treemain);
					    item->setText(0, query2.value(0).toString());
				    	item->setText(1, query2.value(1).toString());
					    item->setText(2, query2.value(2).toString().section("\n", 0, 0));
				    	item->setText(3, query2.value(3).toString());
					    item->setText(4, query2.value(4).toString());
				    	item->setText(5, query2.value(5).toString());
					    item->setText(6, vatlist[query2.value(6).toInt()]);
				    	item->setText(7, query2.value(7).toString());
					    item->setText(8, query.value(0).toString()+":#:"+query2.value(0).toString());
					}
			    }
			}
			if(sfrm->treemain->topLevelItemCount()>1)
			{
				sfrm->init();
				QApplication::restoreOverrideCursor();
				sfrm->exec();
			}
		}
    }
	QApplication::restoreOverrideCursor();
}
//
void CashPoint::initvat()
{
	vatlist.clear();
	QSqlQuery query("SELECT col1 FROM vattable ORDER BY ID;");
	if(query.isActive())
	{
		while(query.next())
			vatlist << query.value(0).toString();
	}
	else
	{
		QSqlError qerror = query.lastError();
		QMessageBox::warning ( 0, tr ( "Can't load template description..." ), qerror.text() );
	}
}
//
void CashPoint::closeEvent( QCloseEvent* ce )
{
	disconnect(btnsearch, SIGNAL(released()), this, SLOT(checkdb()));
	disconnect(txtsearch, SIGNAL(returnPressed()), this, SLOT(checkdb()));
	disconnect(btnclose, SIGNAL(released()), this, SLOT(close()));
	ce->accept();
}

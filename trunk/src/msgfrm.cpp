#include <QtCore>
#include <QCloseEvent>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
//
#include "msgfrm.h"
#include "vars.h"
#include "printfrm.h"
#include "progfrm.h"
//
extern QString username, fullname, templatefolder;
//
msgfrm::msgfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
void msgfrm::init()
{
	lbluser->setText(username);
	
	treeindex->hideColumn(1);
	treeindex->hideColumn(2);
	treeindex->hideColumn(3);
    treeindex->header()->setClickable(FALSE);
    treeindex->header()->setResizeMode(QHeaderView::Fixed);	
	
	connect(btnclose, SIGNAL(released()), this, SLOT(close()));
	connect(treeindex, SIGNAL(itemClicked(QTreeWidgetItem* , int)), this, SLOT(loadmsg()));
	
    vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
        if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
   	}
   	
   	loadmsgcfg();
   	initmainlistview("per");
}
//
void msgfrm::closeEvent(QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void msgfrm::loadmsgcfg()
{
    int i;
    progbar->setMaximum(4);
    QString qstr = "SELECT ID, name, users FROM msgcfgtab ORDER BY ID ASC;";
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		QTreeWidgetItem *item = treeindex->topLevelItem(0);
		item->setText(2, "per");
		item->setText(3, "11");
		for(i=1;i<5;i++)
		{
			item = new QTreeWidgetItem;
			item = treeindex->topLevelItem(i);
		    query.next();
		    item->setText(2, query.value(1).toString());
		    item->setText(3, query.value(2).toString().section(username+" [", 1, 1).section("]", 0, 0));
		    progbar->setValue(i+1);
		}
    }	
}
//
void msgfrm::loadmsg()
{
    QTreeWidgetItem *indexitem = treeindex->currentItem();
    initmainlistview(indexitem->text(2));
    
    if(indexitem->text(2) == "10" || indexitem->text(2) == "11" || username == "Administrator")
    {
		if(indexitem->text(2) == "11" || username == "Administrator")
		{
		    btnnew->setEnabled(TRUE);
		    btnedit->setEnabled(TRUE);
		    btndelete->setEnabled(TRUE);
		    btncomplete->setEnabled(TRUE);
		}
		else
		{
		    btnnew->setEnabled(FALSE);
		    btnedit->setEnabled(FALSE);
		    btndelete->setEnabled(FALSE);
		    btncomplete->setEnabled(FALSE);
		}

		QString connstr = QString("SELECT ID, typ, user, date, msgtext, data1, data2, data3, data4, data5 FROM msgtab WHERE `typ` = '%1' ORDER BY ID DESC;").arg(indexitem->text(1));
		QSqlQuery query(connstr);
		if(query.isActive())
		{
		    progbar->setMaximum(query.size());
		    while(query.next())
		    {
				progbar->setValue(query.at()+1);
				QTreeWidgetItem *item = new QTreeWidgetItem(treemain);
				item->setText(0, query.value(0).toString());
				item->setText(1, query.value(1).toString());
				item->setText(2, query.value(2).toString());
				QString s = query.value(3).toString();
				item->setText(3, s.section("-", 2, 2) + "." + s.section("-", 1, 1) + "." + s.section("-", 0, 0));
				item->setText(4, query.value(4).toString());
				item->setText(5, query.value(5).toString());
				if(indexitem->text(1)=="ord" || indexitem->text(1)=="iem")
				    item->setText(5, item->text(5).section(" (", 0, 0));
				item->setText(6, query.value(6).toString());
				item->setText(7, query.value(7).toString());
				item->setText(8, query.value(8).toString());
				if(indexitem->text(1)=="ord")
				{
				    s = item->text(7);
				    item->setText(7, s.section("-", 2, 2) + "." + s.section("-", 1, 1) + "." + s.section("-", 0, 0));
				    s = item->text(8);
				    item->setText(8, s.section("-", 2, 2) + "." + s.section("-", 1, 1) + "." + s.section("-", 0, 0));
				}
				if(indexitem->text(1)=="iem")
				{
				    s = item->text(7);
				    item->setText(7, s.section("-", 2, 2) + "." + s.section("-", 1, 1) + "." + s.section("-", 0, 0));
				}
				item->setText(9, query.value(9).toString());
		    }
		}
    }
}
//
void msgfrm::initmainlistview(QString type)
{
    treemain->clear();
    treemain->setColumnCount(11);

    int i;
    for(i=0;i<treemain->columnCount();i++)
    	treemain->showColumn(i);

    treemain->header()->setClickable(FALSE);
    
    treemain->headerItem()->setText(0, tr("ID"));
    treemain->headerItem()->setText(1, "");
    treemain->headerItem()->setIcon(1, QIcon(QString::fromUtf8(":/button_ok_small.png")));
    treemain->headerItem()->setText(2, tr("type"));
    treemain->headerItem()->setText(3, tr("user"));
    treemain->headerItem()->setText(4, tr("Date"));

    treemain->hideColumn(0);
	treemain->setColumnWidth(1, 35);
    treemain->hideColumn(2);
    treemain->hideColumn(3);
    treemain->setColumnWidth(4, 75);
    
    if(type=="per")
    {
    	treemain->headerItem()->setText(5, tr("Info"));
    	treemain->setColumnWidth(5, 580);
		treemain->hideColumn(6);
		treemain->hideColumn(7);
		treemain->hideColumn(8);
		treemain->hideColumn(9);
		treemain->hideColumn(10);
    }
    else if(type=="gen")
    {
    	treemain->headerItem()->setText(5, tr("Info"));
    	treemain->setColumnWidth(5, 580);
		treemain->hideColumn(6);
		treemain->hideColumn(7);
		treemain->hideColumn(8);
		treemain->hideColumn(9);
		treemain->hideColumn(10);
    }
    else if(type=="sto")
    {
    	treemain->headerItem()->setText(5, tr("info"));
    	treemain->headerItem()->setText(6, tr("Label"));
    	treemain->headerItem()->setText(7, tr("Description"));
    	treemain->headerItem()->setText(8, tr("Stock"));
    	treemain->headerItem()->setText(9, tr("Min. quantity"));
    	treemain->headerItem()->setText(10, tr("Supplier"));
    	
    	treemain->hideColumn(5);
    	treemain->setColumnWidth(6, 100);
    	treemain->setColumnWidth(7, 300);
    	treemain->setColumnWidth(8, 75);
    	treemain->setColumnWidth(9, 75);
    	treemain->setColumnWidth(10, 100);
    }
    else if(type=="ord")
    {
		treemain->headerItem()->setText(5, tr("info"));
    	treemain->headerItem()->setText(6, tr("Client"));
    	treemain->headerItem()->setText(7, tr("Order.-Nr."));
    	treemain->headerItem()->setText(8, tr("Date of entry"));
    	treemain->headerItem()->setText(9, tr("Complete until"));
    	treemain->headerItem()->setText(10, tr("data"));
		
		treemain->hideColumn(5);
	   	treemain->setColumnWidth(6, 200);
    	treemain->setColumnWidth(7, 100);
    	treemain->setColumnWidth(8, 100);
    	treemain->setColumnWidth(9, 100);
		treemain->hideColumn(10);
    }
    else
    {
		treemain->headerItem()->setText(5, tr("info"));
    	treemain->headerItem()->setText(6, tr("Client"));
    	treemain->headerItem()->setText(7, tr("Ref-Nr."));
    	treemain->headerItem()->setText(8, tr("Last payment"));
    	treemain->headerItem()->setText(9, tr("Amount"));
    	treemain->headerItem()->setText(10, tr("data"));
		
		treemain->hideColumn(5);
	   	treemain->setColumnWidth(6, 200);
    	treemain->setColumnWidth(7, 100);
    	treemain->setColumnWidth(8, 100);
    	treemain->setColumnWidth(9, 100);
		treemain->hideColumn(10);
    }
}

#include <QSqlQuery>
//
#include "addrselectfrm.h"
//
QStringList dirtabname;
extern QString username;
//
addrselectfrm::addrselectfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void addrselectfrm::init()
{
	this->setFixedSize(this->width(), this->height());
	treemain->setColumnWidth(0, 170);
	treemain->setColumnWidth(1, 170);
	treemain->setColumnHidden(3, TRUE);
	treemain->setColumnHidden(4, TRUE);
	dirtabname.clear();
	
	QString connstr = "SELECT * FROM adrtabs WHERE users LIKE '%"+username+" %';";
	  
	QSqlQuery query(connstr);
	if(query.isActive())
	{
		while(query.next())
		{
			cmbdir->addItem(query.value(2).toString());
			dirtabname << query.value(1).toString();
		}
	}
	
	connect(btnsearch, SIGNAL(released()), this, SLOT(searchaddress()));
	connect(btncancelsearch, SIGNAL(released()), this, SLOT(clearsearch()));
	
	if(txtsearch->text() != "")
		searchaddress();
}
//
QString addrselectfrm::getaddress()
{
	QTreeWidgetItem *item = treemain->currentItem();
	if(item)
		return item->text(3);
	else
		return " ";
}
//
QString addrselectfrm::getrabatt()
{
	QTreeWidgetItem *item = treemain->currentItem();
		if(item)
		return item->text(4);
	else
		return "0";
}
//
void addrselectfrm::searchaddress()
{
    QString connstr = "SELECT company, lastname, firstname, nameadd, pobox, street_nr, zip_location, ID, discount FROM ";
    connstr += dirtabname[cmbdir->currentIndex()];
    connstr += " WHERE company LIKE '%"+txtsearch->text()+"%' OR lastname LIKE '%"+txtsearch->text()+"%' OR firstname LIKE '%"+txtsearch->text()+"%';";
    QSqlQuery query(connstr);
    if ( query.isActive())
    {
		progbar->setValue(0);
		progbar->setMaximum(query.size());
		treemain->clear();
		QString col4 ="";
		int count = 0;
		while ( query.next())
		{
			QTreeWidgetItem *item = new QTreeWidgetItem;
		    item->setText(0, query.value(0).toString());
		    item->setText(1, query.value(1).toString());
		    item->setText(2, query.value(2).toString());
		    col4 ="";
		    if(query.value(0).toString()!="")
				col4 += query.value(0).toString() + "<BR>";
		    if(query.value(0).toString()!="" && query.value(3).toString()!="")
				col4 += query.value(3).toString() + " ";
		    if(query.value(1).toString()!="" || query.value(2).toString()!="")
				col4 += query.value(2).toString() + " " +query.value(1).toString()+ "<BR>";
		    if(query.value(4).toString()!="")
				col4 += query.value(4).toString() + "<BR>";
		    if(query.value(5).toString()!="")
				col4 += query.value(5).toString() + "<BR>";
		    if(query.value(6).toString()!="")
				col4 += query.value(6).toString();
		    col4 += ":#:" + QString(dirtabname[cmbdir->currentIndex()]).mid(3) + "_" + query.value(7).toString();
		    item->setText(3, col4);
		    item->setText(4, query.value(8).toString());
		    treemain->addTopLevelItem(item);
		    progbar->setValue(count++);
		}
    }
}
//
void addrselectfrm::clearsearch()
{
    QString connstr = "SELECT company, lastname, firstname, nameadd, pobox, street_nr, zip_location, discount, ID FROM ";
    connstr += dirtabname[cmbdir->currentIndex()];
    connstr += ";";
    QSqlQuery query(connstr);
    if ( query.isActive())
    {
		progbar->setValue(0);
		progbar->setMaximum(query.size());
		treemain->clear();
		QString col4 ="";
		int count = 0;
		while ( query.next())
		{
			QTreeWidgetItem *item = new QTreeWidgetItem;
		    item->setText(0, query.value(0).toString());
		    item->setText(1, query.value(1).toString());
		    item->setText(2, query.value(2).toString());
		    col4 ="";
		    if(query.value(0).toString()!="")
				col4 += query.value(0).toString() + ";";
		    if(query.value(0).toString()!="" && query.value(3).toString()!="")
				col4 += query.value(3).toString() + " ";
		    if(query.value(1).toString()!="" || query.value(2).toString()!="")
				col4 += query.value(2).toString() + " " +query.value(1).toString()+ ";";
		    if(query.value(4).toString()!="")
				col4 += query.value(4).toString() + ";";
		    if(query.value(5).toString()!="")
				col4 += query.value(5).toString() + ";";
		    if(query.value(6).toString()!="")
				col4 += query.value(6).toString();
		    col4 += ":#:" + QString(dirtabname[cmbdir->currentIndex()]).mid(3) + "_" + query.value(8).toString();
		    item->setText(3, col4);
		    item->setText(4, query.value(7).toString());
		    treemain->addTopLevelItem(item);
		    progbar->setValue(count++);
		}
    }
}

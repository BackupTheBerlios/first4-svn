#include "QSqlQuery"
#include "QMessageBox"
#include "QCloseEvent"
//
#include "docopendraftsfrm.h"
#include "addrselectfrm.h"
#include "vars.h"
//
QStringList srow, dart, dlabel;
//
docopendraftsfrm::docopendraftsfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void docopendraftsfrm::init()
{
	this->setFixedSize(this->width(), this->height());
	treeindex->hideColumn(1);
	
	treemain->setColumnWidth(0, 20);
    treemain->setColumnWidth(1, 100);
    treemain->setColumnWidth(2, 75);
    treemain->setColumnWidth(3, 150);
    treemain->setColumnWidth(4, 65);
    treemain->setColumnWidth(5, 60);
    treemain->setColumnWidth(6, 210);
	treemain->hideColumn(7);
	treemain->hideColumn(8);

	srow.clear();
    srow << "client" <<  "docID" << "date" << "data" << "comments";

	readdoctab();
       
	progbar->setMaximum(1);
	progbar->setValue(1);

	connect(btnopen, SIGNAL(released()), this, SLOT(close_accept()));
	connect(btnsearch, SIGNAL(released()), this, SLOT(searchdoc()));
	connect(txtsearch, SIGNAL(returnPressed()), this, SLOT(searchdoc()));
	connect(btnclear, SIGNAL(released()), this, SLOT(clearsearch()));
	connect(treeindex, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(loaddocs()));
	connect(treemain, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(loaddocsdetails()));
	connect(treemain, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(close_accept()));
	connect(cmbsearchrow, SIGNAL(activated(int)), this, SLOT(adressbtnonoff()));
	connect(btnaddr, SIGNAL(released()), this, SLOT(openseladdressfrm()));
}
//
void docopendraftsfrm::readdoctab()
{   
	dlabel.clear();
	dlabel << tr("Offer") << tr("Order confirmation") << tr("Delivery note") << tr("Bill");
    QString qstr = "SELECT name FROM doctab ORDER BY ID;";
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		while(query.next())
		{
			QTreeWidgetItem *item = new QTreeWidgetItem(treeindex);
			item->setText(0, dlabel[query.at()]);
			item->setText(1, query.value(0).toString());
		}
    }
}
//
void docopendraftsfrm::loaddocs()
{
    QTreeWidgetItem *indexitem = treeindex->currentItem();
    if(indexitem!=0)
    {
		treemain->clear();
		QString connstr = QString("SELECT ID, docID, date, client, amount, discount, comments FROM docdrafts WHERE `doctyp` LIKE '%1' ORDER BY ID;").arg(indexitem->text(1));
		QString connstr2;
		QSqlQuery query(connstr);
		if(query.isActive())
		{	
		    progbar->setMaximum(query.size());
		    while(query.next())
		    {
				QTreeWidgetItem *item = new QTreeWidgetItem(treemain);
				item->setText(0, query.value(0).toString());
				item->setText(1, query.value(1).toString());
				item->setText(2, query.value(2).toString());
				item->setText(7, query.value(3).toString());
				item->setText(4, query.value(4).toString());
				item->setText(5, query.value(5).toString());
				item->setText(6, query.value(6).toString());
		    
				connstr2 = QString("SELECT company, lastname, firstname, nameadd, pobox, street_nr, zip_location FROM adr%1 WHERE `ID`='%2';").arg(item->text(7).section( "_", 0, 0 )).arg(item->text(7).section("_", 1, 1 ));
				QSqlQuery query2(connstr2);
				query2.next();
				QString adresse ="";
				if(query2.size() != 0)
				{
				    item->setText(3, query2.value(0).toString() + " " + query2.value(1).toString() + " " + query2.value(2).toString());
				    if(query2.value(0).toString()!="")
						adresse += query2.value(0).toString() + "<BR>";
				    if(query2.value(0).toString() != "" && query2.value(3).toString()!="")
						adresse += query2.value(3).toString() + " ";
				    if(query2.value(1).toString()!="" || query2.value(2).toString()!="")
						adresse += query2.value(1).toString() + " " +query2.value(2).toString()+ "<BR>";
				    if(query2.value(4).toString()!="")
						adresse += query2.value(4).toString() + "<BR>";
				    if(query2.value(5).toString()!="")
						adresse += query2.value(5).toString() + "<BR>";
				    if(query2.value(6).toString()!="")
						adresse += query2.value(6).toString();
				}
				else
				    adresse = tr("No Address found in database!");
				item->setText(8, adresse);
				progbar->setValue(query.at()+1);
		    }
		}
		progbar->setValue(progbar->maximum());
    }
}
//
void docopendraftsfrm::loaddocsdetails()
{
    QTreeWidgetItem *item = treemain->currentItem();
    if(item!=0 && item->childCount() == 0)
    {
		QString connstr = "SELECT DESCRIPTION, QUANTITY FROM docpositions WHERE DOCID = '"+item->text(0)+"' ORDER BY DOC_POSITION;";
		QSqlQuery querypos(connstr);
		if(querypos.isActive())
		{
		    while(querypos.next())
		    {
				QTreeWidgetItem *childitem = new QTreeWidgetItem(item);
				childitem->setText(2, querypos.value(1).toString());
				childitem->setText(3, querypos.value(0).toString());
		    }
		}
    }
}
//
void docopendraftsfrm::close_accept()
{
    QTreeWidgetItem *item = treemain->currentItem();
    if(item!=0)
		this->done(item->text(0).toInt());
    else
		this->reject();
}
//
void docopendraftsfrm::searchdoc()
{
    QTreeWidgetItem *indexitem = treeindex->currentItem();
    if(indexitem!=0)
    {
		QString connstr;
		if(cmbsearchrow->currentIndex() > 0)
		    connstr = QString("SELECT ID, docID, date, client, amount, discount, comments FROM docdrafts WHERE `doctyp` LIKE '%1' AND `%2` = '%3' ORDER BY ID;").arg(indexitem->text(1)).arg(srow[cmbsearchrow->currentIndex()]).arg(txtsearch->text());
		else
		    connstr = QString("SELECT ID, docID, date, client, amount, discount, comments FROM docdrafts WHERE `doctyp` LIKE '%1' AND `%2` = '%3' ORDER BY ID;").arg(indexitem->text(1)).arg(srow[cmbsearchrow->currentIndex()]).arg(txtsearch->text().section(" (", 1, 1).section(")", 0, 0));
	
		QString connstr2;
		QSqlQuery query(connstr);
		if(query.isActive())
		{
		    treemain->clear();
		    progbar->setMaximum(query.size());
		    while(query.next())
		    {
				QTreeWidgetItem *item = new QTreeWidgetItem(treemain);
				item->setText(0, query.value(0).toString());
				item->setText(1, query.value(1).toString());
				item->setText(2, query.value(2).toString());
				item->setText(7, query.value(3).toString());
				item->setText(4, query.value(4).toString());
				item->setText(5, query.value(5).toString());
				item->setText(6, query.value(6).toString());
		    
				connstr2 = QString("SELECT company, lastname, firstname, nameadd, pobox, street_nr, zip_location FROM adr%1 WHERE `ID`='%2';").arg(item->text(7).section( "_", 0, 0 )).arg(item->text(7).section("_", 1, 1 ));
				QSqlQuery query2(connstr2);
				query2.next();
				item->setText(3, query2.value(0).toString() + " " + query2.value(1).toString() + " " + query2.value(2).toString());
				QString adresse ="";
				if(query2.value(0).toString()!="")
				    adresse += query2.value(0).toString() + "<BR>";
				if(query2.value(0).toString() != "" && query2.value(3).toString()!="")
				    adresse += query2.value(3).toString() + " ";
				if(query2.value(1).toString()!="" || query2.value(2).toString()!="")
				    adresse += query2.value(1).toString() + " " +query2.value(2).toString()+ "<BR>";
				if(query2.value(4).toString()!="")
				    adresse += query2.value(4).toString() + "<BR>";
				if(query2.value(5).toString()!="")
				    adresse += query2.value(5).toString() + "<BR>";
				if(query2.value(6).toString()!="")
				    adresse += query2.value(6).toString();
				item->setText(8, adresse);
				progbar->setValue(query.at()+1);
		    }
		}
    }
}
//
void docopendraftsfrm::clearsearch()
{
    txtsearch->setText("");
}
//
void docopendraftsfrm::openseladdressfrm()
{
    addrselectfrm *addrfrm = new addrselectfrm;   
    addrfrm->init();
    if(addrfrm->exec())
		txtsearch->setText(addrfrm->getadress().replace("<BR>", ";").replace(":#:", " (")+")");
}
//
void docopendraftsfrm::adressbtnonoff()
{
    txtsearch->setText("");
    if(cmbsearchrow->currentIndex()==0)
		btnaddr->setEnabled(TRUE);
    else
		btnaddr->setEnabled(FALSE);
}

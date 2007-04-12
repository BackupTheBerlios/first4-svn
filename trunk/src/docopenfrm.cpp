#include <QCloseEvent>
#include <QHeaderView>
#include <QMessageBox>
#include <QSqlQuery>
//
#include "docopenfrm.h"
#include "vars.h"
#include "addrselectfrm.h"
#include "doceditfrm.h"
//
QStringList searchrowlist, docart, doclabel, docsource;
extern QString username, fullname;
//
docopenfrm::docopenfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
void docopenfrm::init()
{
    searchrowlist.clear();
    doclabel.clear();
    docart.clear();
    docsource.clear();
    searchrowlist << "client" <<  "docID" << "date" << "data" << "comments";
    doclabel << tr("Offer") << tr("Order confirmation") << tr("Delivery note") << tr("Bill");
    docart << "1 offer" << "2 orderconf" << "3 deliverynote" << "4 bill";
    docsource << "docs" << "docdrafts";
    
    int i;
    for(i=0;i<4;i++)
    {
		QTreeWidgetItem *item = new QTreeWidgetItem(treeindex);
		item->setText(0, doclabel[i]);
		item->setText(1, docart[i]);
		item->setText(2, QString("%1").arg(i, 0, 10));
    }
    treeindex->hideColumn(1);
    treeindex->hideColumn(2);
    
    treemain->setColumnWidth(0, 20);
    treemain->setColumnWidth(1, 150);
    treemain->setColumnWidth(2, 75);
    treemain->setColumnWidth(3, 150);
    treemain->setColumnWidth(4, 75);
    treemain->setColumnWidth(5, 75);
    treemain->setColumnWidth(6, 210);
    treemain->hideColumn(7);
    treemain->hideColumn(8);
    
    lbluser->setText(username);
    adressbtnonoff();
    
    connect(treeindex, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(loaddocs()));
    connect(treemain, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(loaddocsdetails()));
    connect(btnnew, SIGNAL(released()), this, SLOT(newdoc()));
    connect(btnedit, SIGNAL(released()), this, SLOT(editdoc()));
    connect(btndelete, SIGNAL(released()), this, SLOT(deletedoc()));
    connect(btnprint, SIGNAL(released()), this, SLOT(print()));
    connect(btnclearsearch, SIGNAL(released()), this, SLOT(clearsearch()));
    connect(btnsearch, SIGNAL(released()), this, SLOT(searchdoc()));
    connect(btnaddr, SIGNAL(released()), this, SLOT(openseladressfrm()));
    connect(txtsearch, SIGNAL(returnPressed ()), this, SLOT(searchdoc()));
    connect(cmbsearchrow, SIGNAL(activated(int)), this, SLOT(adressbtnonoff()));
    
	vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
	    if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
    }
}
//
void docopenfrm::adressbtnonoff()
{
    txtsearch->setText("");
    if(cmbsearchrow->currentIndex()==0)
		btnaddr->setEnabled(TRUE);
    else
		btnaddr->setEnabled(FALSE);
}
//
void docopenfrm::closeEvent( QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void docopenfrm::loaddocs()
{
    QTreeWidgetItem *indexitem = treeindex->currentItem();
    if(indexitem!=0)
    {
		treemain->clear();
		btnnew->setEnabled(TRUE);
		QString qstr2;
		QString qstr = QString("SELECT ID, docID, date, client, amount, discount, comments FROM docs WHERE `doctyp` LIKE '%1' ORDER BY ID;").arg(indexitem->text(1));
		QSqlQuery query(qstr);
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
		    
				qstr2 = QString("SELECT company, lastname, firstname, nameadd, pobox, street_nr, zip_location FROM adr%1 WHERE `ID`='%2';").arg(item->text(7).section( "_", 0, 0 )).arg(item->text(7).section("_", 1, 1 ));
				QSqlQuery query2(qstr2);
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
    }
}
//
void docopenfrm::loaddocsdetails()
{
    QTreeWidgetItem *item = treemain->currentItem();
    if(item!=0 && item->childCount() == 0)
    {
		QString qstr = "SELECT DESCRIPTION, QUANTITY FROM docpositions WHERE DOCID = '"+item->text(0)+"' ORDER BY DOC_POSITION;";
		QSqlQuery querypos(qstr);
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
void docopenfrm::deletedoc()
{
    QTreeWidgetItem *item = treemain->currentItem();
    if(item->parent() != 0)
    	item = item->parent();
    if(item!=0)
    {
		QTreeWidgetItem *indexitem = treeindex->currentItem();
		int exit=QMessageBox::information(this, tr("Delete Document..."), tr("Delete %1 %2?").arg(indexitem->text(0)).arg(item->text(1)), QMessageBox::Yes, QMessageBox::No);
		if(exit == QMessageBox::Yes)
		{
		    QString connstr;
		    connstr = QString("DELETE FROM `docs` WHERE `ID` = '%2';").arg(item->text(0));
		    QSqlQuery query(connstr);
		    treemain->takeTopLevelItem(treemain->indexOfTopLevelItem(item));
		}
    }
}
//
void docopenfrm::newdoc()
{
    QTreeWidgetItem *item = treeindex->currentItem();
    if(item && item->parent() != 0)
    	item = item->parent();
    if(item!=0)
    {
		doceditfrm *doc = new doceditfrm;
		doc->init();
		if(item->text(2)=="0")
		    doc->cmbdoc->setCurrentIndex(1);
		doc->cmbdoc->setCurrentIndex(item->text(2).toInt());
		doc->selecteddocument();
		doc->show();
		loaddocs();
    }
}
//
void docopenfrm::editdoc()
{
	QTreeWidgetItem *item = treemain->currentItem();
    if(item->parent() != 0)
    	item = item->parent();
    if(item!=0)
    {
		doceditfrm *doc = new doceditfrm;
		doc->init();    
		doc->opendocfromid("docs", item->text(0));
		doc->calc_tot();
		doc->show();
	}
}
//
void docopenfrm::print()
{
    QTreeWidgetItem *item = treemain->currentItem();
    if(item->parent() != 0)
    	item = item->parent();
    if(item!=0)
    {
		doceditfrm *doc = new doceditfrm;
		doc->init();    
		doc->opendocfromid("docs", item->text(0));
		doc->calc_tot();
		doc->print();
	}
}
//
void docopenfrm::searchdoc()
{
    QTreeWidgetItem *indexitem = treeindex->currentItem();
    if(indexitem!=0)
    {
		btnnew->setEnabled(TRUE);
		treemain->clear();

		QString qstr;
		switch (cmbsearchrow->currentIndex()) {
			case 0:
				qstr = QString("SELECT ID, docID, date, client, amount, discount, comments FROM docs WHERE `doctyp` LIKE '%1' AND `%2` = '%3' ORDER BY ID;").arg(indexitem->text(1)).arg(searchrowlist[cmbsearchrow->currentIndex()]).arg(txtsearch->text().section(" (", 1, 1).section(")", 0, 0));
				break;
			case 3:
				{
					qstr = "SELECT ID, docID, date, client, amount, discount, comments FROM docs WHERE";
					QString qstrpos = QString("SELECT DOCID FROM `docpositions` WHERE `label` LIKE '%%1%' OR `description` LIKE '%%1%';").arg(txtsearch->text());
					QSqlQuery querypos(qstrpos);
					while(querypos.next())
					{
						qstr += QString(" `ID`='%1' OR").arg(querypos.value(0).toString());
					}
					qstr = qstr.leftJustified(qstr.length()-3, '.', TRUE) + ";";
				}
				break;
			default:
				qstr = QString("SELECT ID, docID, date, client, amount, discount, comments FROM docs WHERE `doctyp` LIKE '%1' AND `%2` = '%3' ORDER BY ID;").arg(indexitem->text(1)).arg(searchrowlist[cmbsearchrow->currentIndex()]).arg(txtsearch->text());
				break;
		}
		QString qstr2;
		QSqlQuery query(qstr);
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
			    
				qstr2 = QString("SELECT company, lastname, firstname, nameadd, pobox, street_nr, zip_location FROM adr%1 WHERE `ID`='%2';").arg(item->text(7).section( "_", 0, 0 )).arg(item->text(7).section("_", 1, 1 ));
				QSqlQuery query2(qstr2);
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
void docopenfrm::clearsearch()
{
    txtsearch->setText("");
}
//
void docopenfrm::openseladressfrm()
{
    addrselectfrm *adrfrm = new addrselectfrm;   
    adrfrm->init();
    if(adrfrm->exec())
		txtsearch->setText(adrfrm->getadress().replace(":#:", " (")+")");
}

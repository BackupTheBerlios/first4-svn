#include <QCloseEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include <QHeaderView>
#include <QMenu>
//
#include "procedurefrm.h"
#include "procedureeditfrm.h"
#include "proceduresearch.h"
#include "vars.h"
#include "doceditfrm.h"
//
QString prefix;
extern QString username;
QStringList queryreturn;
//
procedurefrm::procedurefrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
int procedurefrm::init()
{
    lbluser->setText(username);
	
	int r = checkrights();
    switch (r) 
    {
    case 0:
		QMessageBox::information(0, tr("Authorization Required..."), tr("You are not authorized to open this modul\n\nPlease contact your Administrator")); 
		this->close();
		break;
    case 1:
		btnadd->setEnabled(FALSE);
		break;
    }
    
    treemain->setColumnWidth(0, 80);
    treemain->setColumnWidth(1, 0);
    treemain->setColumnWidth(2, 190);
    treemain->setColumnWidth(3, 300);
    treemain->setColumnWidth(4, 80);
	
	vars v;
	QStringList sgeo = v.loadgeo ( this->objectName() );
	if ( sgeo.size() > 0	)
	{
		if ( sgeo[0] == "1" )
			this->setWindowState ( this->windowState() ^ Qt::WindowMaximized );
		this->setGeometry ( sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt() );
	}
	
    treeindex->header()->setClickable(FALSE);
    treeindex->header()->setResizeMode(QHeaderView::Fixed);
    treeindex->setColumnWidth(0, 150);
	treeindex->hideColumn(2);
	treeindex->setCurrentItem(treemain->topLevelItem(0));
    
    QString connstr = QString("SELECT value FROM `maincfg` WHERE `var` = 'docpref';");
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		query.next();
		prefix = query.value(0).toString();
    }
    countabl(); 
    treeindex->setCurrentItem(treemain->topLevelItem(0));
    
	connect(treeindex, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(settable()));
	connect(btnadd, SIGNAL(released()), this, SLOT(neworder()));
    connect(btnedit, SIGNAL(released()), this, SLOT(checkeditID()));
    connect(treemain, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int) ), this, SLOT(checkeditID()));
    connect(btndelete, SIGNAL(released()), this, SLOT(checkdeleteID()));
    connect(btndocument, SIGNAL(released()), this, SLOT(completeorder()));
    connect(btncomplete, SIGNAL(released()), this, SLOT(updatedatabase()));
    connect(treemain, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));
    connect(btnsearch, SIGNAL(released()), this, SLOT(search()));
    return r;
}
//
void procedurefrm::closeEvent( QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
int procedurefrm::checkrights()
{
    int permission = 0;
    QString conn = "SELECT users FROM procedurecfg WHERE `users` LIKE '%"+username+" [1%';";
    QSqlQuery query(conn);
    if ( query.isActive())
    {
		query.next();
		if(query.value(0).toString().section(lbluser->text(), 1, 1).section(" ", 1, 1)=="[10]")
		    permission = 1;
		if(query.value(0).toString().section(lbluser->text(), 1, 1).section(" ", 1, 1)=="[11]")
		    permission = 2;
    }
    return permission;
}
//
void procedurefrm::countabl()
{
    int i;
    
    for(i=0;i<6;i++)
    {
    	QTreeWidgetItem* item = treeindex->topLevelItem(i);
		QString connstr = "SELECT ID FROM procedures WHERE `status` = '"+QString("%1").arg(i, 0, 10)+"';" ;
		QSqlQuery query(connstr);
		if(query.isActive())
		    item->setText(1, QString("%1").arg(query.size(), 0, 10));
    }
	QTreeWidgetItem* item = treeindex->topLevelItem(6);
    item->setText(1, "-");
}
//
void procedurefrm::settable()
{
    QTreeWidgetItem* item = treeindex->currentItem();
   
    btnedit->setEnabled(TRUE);
    btndelete->setEnabled(TRUE);
    btncomplete->setEnabled(TRUE);
    
    filltable(item->text(2).toInt());
}
//
void procedurefrm::filltable(int state)
{
    treemain->clear();    
    
    treemain->header()->setClickable(FALSE);
    treemain->header()->setResizeMode(QHeaderView::Fixed);
    
    QString qstr;
    if(state < 6)
		qstr = "SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM procedures WHERE `status` = '"+QString("%1").arg(state, 0, 10)+"';";
    else
		qstr = "SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM procedurearchive;";
   
    QSqlQuery query(qstr);
    if( query.isActive())
    { 
		while(query.next())
		{
		    QTreeWidgetItem *row = new QTreeWidgetItem(treemain);
		    row->setText(1, query.value(0).toString());
		    if(query.value(2).toString()=="1")
				row->setCheckState(0, Qt::Checked);
			else
				row->setCheckState(0, Qt::Unchecked);
		    row->setText(2, query.value(3).toString().section(" (", 0, 0));
			
		    row->setText(3, query.value(4).toString());
		    QString s =  query.value(5).toString();
		    row->setText(4, s.section("-", 2, 2)+"."+s.section("-", 1, 1)+"."+s.section("-", 0, 0));
			
		    QTreeWidgetItem* childrow0 = new QTreeWidgetItem(row);
		    childrow0->setText(2, tr("Tasks"));
		    //childrow0->setText(1, query.value(11).toString());
			
			QString qstrtasks = QString("SELECT state, task, date FROM proceduretasks WHERE `PROC_ID`='%1';").arg(query.value(0).toString());
		    QSqlQuery tasks(qstrtasks);
		    while(tasks.next())
		    {
				QTreeWidgetItem* childchild = new QTreeWidgetItem(childrow0);
				if(tasks.value(0).toString() == "1")
					childchild->setIcon(2, QIcon(QString::fromUtf8(":/images/images/button_ok_small.png")));
				else
				    childchild->setIcon(2, QIcon(QString::fromUtf8(":/images/images/kill.png")));
				childchild->setText(2, " "+tasks.value(1).toString());
				childchild->setText(3, tasks.value(2).toString());	
		    }
		
		    QTreeWidgetItem* childrow1 = new QTreeWidgetItem(row);
		    childrow1->setText(2, tr("Orders"));
		    //childrow1->setText(1, query.value(12).toString());
		
			QString qstrorders = QString("SELECT state, label, quantity FROM procedureorders WHERE `PROC_ID`='%1';").arg(query.value(0).toString());
		    QSqlQuery orders(qstrorders);
		    while(orders.next())
		    {
				QTreeWidgetItem* childchild = new QTreeWidgetItem(childrow1);
				if(orders.value(0).toString() == "1")
				    childchild->setIcon(2, QIcon(QString::fromUtf8(":/images/images/button_ok_small.png")));
				else
				    childchild->setIcon(2, QIcon(QString::fromUtf8(":/images/images/kill.png")));
				childchild->setText(2, " "+orders.value(1).toString());
				childchild->setText(3, tr("Quantity: %1").arg(orders.value(2).toString()));
		    }
	    
		    QTreeWidgetItem* childrow2 = new QTreeWidgetItem(row);
		    childrow2->setText(2, tr("Order ID:"));
		    childrow2->setText(3, query.value(6).toString());
		
		    QTreeWidgetItem* childrow3 = new QTreeWidgetItem(row);
		    childrow3->setText(2, tr("Priority:"));
		    childrow3->setText(3, query.value(7).toString());
		
		    QTreeWidgetItem* childrow4 = new QTreeWidgetItem(row);
		    childrow4->setText(2, tr("Contact:"));
		    childrow4->setText(3, query.value(8).toString());
		
		    QTreeWidgetItem* childrow5 = new QTreeWidgetItem(row);
		    childrow5->setText(2, tr("Client ID:"));
		    childrow5->setText(3, query.value(3).toString().section(" (", 1, 1).section(")", 0, 0));
		
		    QTreeWidgetItem* childrow6 = new QTreeWidgetItem(row);
		    childrow6->setText(2, tr("Resp. Person:"));
		    childrow6->setText(3, query.value(9).toString());
		
		    QTreeWidgetItem* childrow7 = new QTreeWidgetItem(row);
		    childrow7->setText(2, tr("Complete until:"));
		    s = query.value(10).toString();
		    childrow7->setText(3, s.section("-", 2, 2)+"."+s.section("-", 1, 1)+"."+s.section("-", 0, 0));

		    progbar->setValue(100/query.size()*(query.at()+1));
		}
    }
    countabl();
}
//
void procedurefrm::neworder()
{
    procedureeditfrm *eorder = new procedureeditfrm;
    eorder->setWindowTitle( tr("New order..."));
    eorder->init();
    eorder->neworder();
    eorder->chkcompleted->setChecked(FALSE);
    
    QTreeWidgetItem *item = treemain->currentItem();
    if(item != 0)
	    eorder->cmbstate->setCurrentIndex(item->text(2).toInt());
	else
		eorder->cmbstate->setCurrentIndex(0);
    if(eorder->exec())
    {
		//ansicht aktualisieren
		treemain->clearSelection();
		treeindex->clearSelection();
		if(treeindex->currentItem() != 0)
			filltable(treeindex->currentItem()->text(2).toInt());
    }
}
//
void procedurefrm::checkeditID()
{
    QTreeWidgetItem* item = treemain->currentItem();
    if(item != 0)
    {
    	while(item->parent() != 0)
    		item = item->parent();
    	QTreeWidgetItem* indexitem = treeindex->currentItem();
    	if(indexitem != 0)
    	{
    		if(indexitem->text(2).toInt() != 6) //Open order or Archive?
    			editorder(item->text(1));
    		else
    			editarchiveorder(item->text(1));
   		}
   	}
}
//
void procedurefrm::checkdeleteID()
{
    QTreeWidgetItem* item = treemain->currentItem();
    if(item != 0)
    {
    	while(item->parent() != 0)
    		item = item->parent();
	    deleteorder(item->text(1));
    }
}
//
void procedurefrm::editorder(QString dbID)
{
	procedureeditfrm *eorders = new procedureeditfrm;
    eorders->init();
	eorders->loadentry(dbID);
    if(eorders->exec())
    {
    	//ansicht aktualisieren
		treeindex->clearSelection();
		treemain->clearSelection();	
		this->filltable(eorders->cmbstate->currentIndex());
    }
}
//
void procedurefrm::editarchiveorder(QString dbID)
{
	procedureeditfrm *eorders = new procedureeditfrm;
	eorders->init();
	eorders->loadarchiveentry(dbID);
	eorders->exec();
}
//
void procedurefrm::deleteorder(QString dbID)
{
    QString conn = "SELECT orderid FROM procedures WHERE `ID` = '"+dbID+"';";
    QSqlQuery query(conn);
    if( query.isActive())
		query.next();
    if(QMessageBox::information(this, tr("Delete order..."), tr("Delete order %1?").arg(query.value(0).toString()), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
		conn = "DELETE FROM `procedures` WHERE `ID`='"+dbID+"';";
		QSqlQuery query2(conn);
    }
}
//
void procedurefrm::deletearchivorder(QString dbID)
{
    QString conn = "SELECT orderid FROM procedurearchive WHERE `ID` = '"+dbID+"';";
	
    QSqlQuery query(conn);
    if( query.isActive())
		query.next();
    if(QMessageBox::information(this, tr("Delete order..."), tr("Delete order %1?").arg(query.value(0).toString()), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
    {
		conn = "DELETE FROM `procedurearchive` WHERE `ID`='"+dbID+"';";
		QSqlQuery query2(conn);
	    this->filltable(treemain->currentItem()->text(2).toInt());
	    treemain->setFocus();
    }
}
//
void procedurefrm::completeorder()
{
    int i;
	QTreeWidgetItem* indexitem = treeindex->currentItem();
    for(i=0; i<treemain->topLevelItemCount(); i++)
    {	
   	    QTreeWidgetItem* item = treemain->topLevelItem(i);
		if(item->checkState(0) == Qt::Checked)
		{
			QTreeWidgetItem* childitem = item->child(2); //Order-ID
		    switch(indexitem->text(2).toInt())
		    {
			    case 0: //Offerte erstellen
					this->createdoc_1(item->text(1));
					if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create offer for order %1 ?").arg(childitem->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
					    this->createdoc_2(0, item->text(1));
					break;
			    case 1: //Auftragsbestäigung erstellen
					this->createdoc_1(item->text(1));
					if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create order confirmation for order %1 ?").arg(childitem->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
					    this->createdoc_2(1, item->text(1));
					break;
			    case 3: //Lieferschein erstellen
					this->createdoc_1(item->text(1));
					if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create deliverynote for order %1 ?").arg(childitem->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
					    this->createdoc_2(3, item->text(1));
					break;
			    case 4: //Rechnung erstellen
					this->createdoc_1(item->text(1));
					if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create bill for order %1 ?").arg(childitem->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
					    this->createdoc_2(4, item->text(1));
					break;	
		    }	    
		}
    }
}
//
void procedurefrm::createdoc_1(QString dbID)
{
    int i;    
    QString connstr = "SELECT status, completed, priority, date, client, contactperson, orderid, description, resp_person, complete_until FROM procedures WHERE `ID` = '"+dbID+"'";
    QSqlQuery query(connstr);
    query.next();
    queryreturn.clear();
    for(i=0;i<=9;i++)
		queryreturn.append(query.value(i).toString());
}
//
void procedurefrm::createdoc_2(int doctype, QString docid)
{
    doceditfrm *doc = new doceditfrm();
    doc->init();
    doc->setWindowFlags(Qt::Dialog);
    doc->setWindowModality(Qt::WindowModal);
    doc->navtabonoff(false);

    doc->btnprint->setEnabled(TRUE);
    doc->btncomplete->setEnabled(TRUE);
    doc->boxaddress->setText(queryreturn[4].section(" (", 0, 0));
    doc->lblID->setText(queryreturn[4].section(" (", 1, 1).section(")", 0, 0));
    doc->boxcomments->setText(queryreturn[7]);
    doc->lbluser->setText(queryreturn[8]);
    doc->lblOrderID->setText(docid);
    
    QString qstr1 = QString("SELECT stock, stock_id, state, label, description, quantity, unit, price, vat FROM procedureorders WHERE `PROC_ID`='%1' AND `state`= '1' ORDER BY ID;").arg(docid);
    QSqlQuery orders(qstr1);

    doc->tabmain->setRowCount(orders.size());

    while(orders.next())
    {
    	QTableWidgetItem *tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(orders.at()+1, 0, 10));
		doc->tabmain->setItem(orders.at(), 0, tabitem);
    	
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(orders.value(3).toString());
		doc->tabmain->setItem(orders.at(), 1, tabitem);
    	
		tabitem = new QTableWidgetItem;
    	tabitem->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
    	doc->tabmain->setItem(orders.at(), 2, tabitem);
    	
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(orders.value(4).toString()));
    	doc->tabmain->setItem(orders.at(), 3, tabitem);
    	
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(orders.value(5).toString()));
    	doc->tabmain->setItem(orders.at(), 4, tabitem);
    	
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(orders.value(6).toString()));
    	doc->tabmain->setItem(orders.at(), 5, tabitem);
	    	
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(QString("%1").arg(orders.value(7).toString().toFloat(), 0, 'f',2)));
    	doc->tabmain->setItem(orders.at(), 6, tabitem);
    
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(QString("%1").arg(orders.value(5).toInt()*orders.value(7).toString().toFloat(), 0, 'f',2)));
    	doc->tabmain->setItem(orders.at(), 7, tabitem);
    		   
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(orders.value(8).toString()));
    	doc->tabmain->setItem(orders.at(), 8, tabitem);

		//check act. quantity and min. quantity///////////////////////////
		QString connstr = "SELECT col3, col4 FROM "+orders.value(0).toString()+" WHERE `ID` = "+orders.value(1).toString()+";";
		QSqlQuery querycheckdb(connstr);
		querycheckdb.next();
		
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(querycheckdb.value(0).toString()));
    	doc->tabmain->setItem(orders.at(), 9, tabitem);
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(querycheckdb.value(1).toString()));
    	doc->tabmain->setItem(orders.at(), 10, tabitem);

		//check act. quantity and min. quantity///////////////////////////
	
    	tabitem = new QTableWidgetItem;
    	tabitem->setText(QString("%1").arg(orders.value(0).toString()+":#:"+orders.value(1).toString()));
    	doc->tabmain->setItem(orders.at(), 11, tabitem);
    }
   	//load discount for customer
   	QString discountstring = QString("SELECT discount FROM adr%1 WHERE `ID`='%2';").arg(queryreturn[4].section(" (", 1, 1).section("_", 0, 0)).arg(queryreturn[4].section(" (", 1, 1).section("_", 1, 1).section(")", 0, 0));
   	QSqlQuery discountquery(discountstring);
   	discountquery.next();
   	doc->boxdiscount->setText(discountquery.value(0).toString());
    
    doc->addrow();
    doc->calc_tot();	
    doc->navtabonoff(true);

    switch(doctype)
    {
	    case 0:
			doc->cmbdoc->setCurrentIndex(1);  //leerzeile entfernen
			doc->cmbdoc->setCurrentIndex(0);
			doc->txtdoccount->setText(prefix+"2"+queryreturn[6].rightJustified(7, '0'));
			doc->selecteddocument(); 
			doc->show();
			break;
	    case 1:
			doc->cmbdoc->setCurrentIndex(1);
			doc->txtdoccount->setText(prefix+"2"+queryreturn[6].rightJustified(7, '0'));
			doc->selecteddocument();
			doc->show();
			break;
	    case 3:
			doc->cmbdoc->setCurrentIndex(2);
			doc->txtdoccount->setText(prefix+"2"+queryreturn[6].rightJustified(7, '0'));
			doc->selecteddocument();
			doc->show();
			break;
	    case 4:
			doc->cmbdoc->setCurrentIndex(3);
			doc->txtdoccount->setText(prefix+"2"+queryreturn[6].rightJustified(7, '0'));
			doc->selecteddocument();
			doc->show();
			break;
    }
}
//
void procedurefrm::updatedatabase()
{
	QTreeWidgetItem *indexitem = new QTreeWidgetItem;
	indexitem = treeindex->currentItem();
	if(indexitem!=0)
	{
		if(indexitem->text(2).toInt() < 5)
		{
		    if(QMessageBox::information(this, tr("Order completed..."), tr("Change status for selected entries?"), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
		    {
			    int i;
			    for(i=0; i<treemain->topLevelItemCount(); i++)
			    {	
			   	    QTreeWidgetItem* item = treemain->topLevelItem(i);
					if(item->checkState(0) == Qt::Checked)
					{
					    QString qstr = "UPDATE `procedures` SET `status`='"+QString("%1").arg(indexitem->text(2).toInt()+1, 0, 10)+"' WHERE `ID`='"+item->text(1)+"';";
					    QSqlQuery query(qstr);
						
						//Reset state for orders
						qstr = QString("UPDATE procedureorders SET state = '0' WHERE `PROC_ID`='%1';").arg(item->text(1));
						QSqlQuery updorders(qstr);
					}
				}
				filltable(indexitem->text(2).toInt());
	    	}
		}
		else
		{
			if(QMessageBox::information(this, tr("Procedure completed..."), tr("Archive completed entries?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
			{
			    int i;
			    for(i=0; i<treemain->topLevelItemCount(); i++)
			    {	
			   	    QTreeWidgetItem* item = treemain->topLevelItem(i);
					if(item->checkState(0) == Qt::Checked)
					{
						this->createdoc_1(item->text(1));
					    QString connstr1 = "INSERT INTO `procedurearchive` (`ID`, `status`, `completed`, `priority`, `date`, `client`, `contactperson`, `orderid`, `description`, `resp_person`, `complete_until`) VALUES (NULL, '6', '1', '"+queryreturn[2]+"', '"+queryreturn[3]+"', '"+queryreturn[4]+"', '"+queryreturn[5]+"', '"+queryreturn[6]+"', '"+queryreturn[7]+"', '"+queryreturn[8]+"', '"+queryreturn[9]+"');" ;
					    QSqlQuery query1(connstr1);
						    
					    QSqlQuery checkid;
					    checkid.prepare("SELECT id FROM procedurearchive WHERE `priority`=:prio AND `date`=:date AND `client`=:client AND `contactperson`=:contact AND `orderid`=:orderid AND `description`=:desc AND `resp_person`=:resp AND `complete_until`=:complete;");
					    checkid.bindValue(":prio", queryreturn[2]);
					    checkid.bindValue(":date", queryreturn[3]);
					    checkid.bindValue(":client", queryreturn[4]);
					    checkid.bindValue(":contact", queryreturn[5]);
					    checkid.bindValue(":orderid", queryreturn[6]);
					    checkid.bindValue(":desc", queryreturn[7]);
					    checkid.bindValue(":resp", queryreturn[8]);
					    checkid.bindValue(":complete", queryreturn[9]);
					    checkid.exec();
					    checkid.next();
		
					    QSqlQuery tasks;
					    tasks.prepare("UPDATE `proceduretasks` SET `PROC_ID`=:newid WHERE `proc_id`=:id;");
					    tasks.bindValue(":newid", "A_"+checkid.value(0).toString());
					    tasks.bindValue(":id", item->text(1));
					    tasks.exec();
				    
					    QSqlQuery orders;
					    orders.prepare("UPDATE `procedureorders` SET `PROC_ID`=:newid WHERE `proc_id`=:id;");
					    orders.bindValue(":newid", "A_"+checkid.value(0).toString());
					    orders.bindValue(":id", item->text(1));
					    orders.exec();
							    
					    QString connstr2 = "DELETE FROM `procedures` WHERE `ID`="+item->text(1)+" LIMIT 1;";
					    QSqlQuery query2(connstr2);	
				    }
				}
				filltable(indexitem->text(2).toInt());
			}	
		}
   	}
}
//
void procedurefrm::contmenu()
{
	QTreeWidgetItem* item = treemain->currentItem();
    if(item != 0)
    {
	    QMenu* contextMenu = new QMenu( this );
	    Q_CHECK_PTR( contextMenu );

	    QAction* offer = new QAction( tr("Create Offer"), this );
		connect(offer , SIGNAL(triggered()), this, SLOT(createoffer()));
		contextMenu->addAction(offer);
	
	    QAction* confirmation = new QAction( tr("Create Orderconfirmation"), this );
		connect(confirmation , SIGNAL(triggered()), this, SLOT(createorderconf()));
		contextMenu->addAction(confirmation);
	
	    QAction* deliverynote = new QAction( tr("Create Delivery note"), this );
		connect(deliverynote , SIGNAL(triggered()), this, SLOT(createdeliverynote()));
		contextMenu->addAction(deliverynote);
	
	    QAction* invoice = new QAction( tr("Create Bill"), this );
		connect(invoice , SIGNAL(triggered()), this, SLOT(createinvoice()));
		contextMenu->addAction(invoice);
			
	    contextMenu->exec( QCursor::pos() );
	    delete contextMenu;
   	}
}
void procedurefrm::search()
{
	proceduresearch *psearch = new proceduresearch;
	psearch->init();
	int r = psearch->exec();
	if(r)
		editorder(QString("%1").arg(r, 0, 10));
}
//
void procedurefrm::createoffer()
{
    QTreeWidgetItem* item = treemain->currentItem();
    while(item->parent() != 0)
    		item = item->parent();
    if(item != 0)
    {
	    this->createdoc_1(item->text(1));
	    this->createdoc_2(0, item->text(1));	
   	}
}
//
void procedurefrm::createorderconf()
{
    QTreeWidgetItem* item = treemain->currentItem();
    while(item->parent() != 0)
    		item = item->parent();
    if(item != 0)
    {
	    this->createdoc_1(item->text(1));
	    this->createdoc_2(1, item->text(1));
    }
}
//
void procedurefrm::createdeliverynote()
{
    QTreeWidgetItem* item = treemain->currentItem();
    while(item->parent() != 0)
    		item = item->parent();
    if(item != 0)
    {
	    this->createdoc_1(item->text(1));
	    this->createdoc_2(3, item->text(1));
    }
}
//
void procedurefrm::createinvoice()
{
	QTreeWidgetItem* item = treemain->currentItem();
    while(item->parent() != 0)
    		item = item->parent();
    if(item != 0)
    {
	    this->createdoc_1(item->text(1));
	    this->createdoc_2(4, item->text(1));
    }
}


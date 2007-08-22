#include <QCloseEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include <QHeaderView>
//
#include "procedurefrm.h"
#include "procedureeditfrm.h"
#include "vars.h"
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
	treeindex->hideColumn(2);
	treeindex->setCurrentItem(treemain->topLevelItem(0));
    
    QString connstr = QString("SELECT value FROM `maincfgtab` WHERE `var` = 'docpref';");
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		query.next();
		prefix = query.value(0).toString();
    }
    this->countabl(); 
    treeindex->setCurrentItem(treemain->topLevelItem(0));
    
	connect(treeindex, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(settable()));
	connect(btnadd, SIGNAL(released()), this, SLOT(neworder()));
    connect(btnedit, SIGNAL(released()), this, SLOT(checkeditID()));
    connect(btndelete, SIGNAL(released()), this, SLOT(checkdeleteID()));
    connect(btncomplete, SIGNAL(released()), this, SLOT(completeorder()));
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
    QString conn = "SELECT users FROM procedurecfgtab WHERE `users` LIKE '%"+username+" [1%';";
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
		QString connstr = "SELECT ID FROM proceduretab WHERE `status` = '"+QString("%1").arg(i, 0, 10)+"';" ;
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
		qstr = "SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM proceduretab WHERE `status` = '"+QString("%1").arg(state, 0, 10)+"';";
    else
		qstr = "SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM procedurearchiv;";
   
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
		QTreeWidgetItem* row = new QTreeWidgetItem(treemain);

		//datenbank aktualisieren
		int i;
		QString completed = "0";
		QString tasks = "";
		QString orders = "";

		if(eorder->chkcompleted->isChecked())
		    completed = "1";
		QString qstr = "INSERT INTO `proceduretab` (`ID`, `status`, `completed`, `priority`, `date`, `client`, `contactperson`, `orderid`, `description`, `resp_person`, `complete_until`) VALUES (NULL, '"+QString("%1").arg(eorder->cmbstate->currentIndex(), 0, 10)+"', '"+completed+"', '"+eorder->cmbpriority->currentText()+"', '"+eorder->dateedit1->date().toString("yyyy-MM-dd")+"', '"+eorder->txtcustomer->toPlainText()+" ("+eorder->lblcustomerid->text()+")', '"+eorder->txtcontact->text()+"', '"+eorder->txtorderid->text()+"', '"+eorder->txtcomments->toPlainText()+"', '"+eorder->txtresponsible->text()+"', '"+eorder->dateedit2->date().toString("yyyy-MM-dd")+"');" ;
		QSqlQuery query(qstr);
		qstr = "SELECT ID FROM proceduretab WHERE `status` = '"+QString("%1").arg(eorder->cmbstate->currentIndex(), 0, 10)+"' AND `completed` = '"+completed+"' AND `priority` = '"+eorder->cmbpriority->currentText()+"' AND `date` = '"+eorder->dateedit1->date().toString("yyyy-MM-dd")+"' AND `client` = '"+eorder->txtcustomer->toPlainText()+" ("+eorder->lblcustomerid->text()+")' AND `contactperson` = '"+eorder->txtcontact->text()+"' AND `orderid` = '"+eorder->txtorderid->text()+"' AND `description` = '"+eorder->txtcomments->toPlainText()+"' AND `resp_person` = '"+eorder->txtresponsible->text()+"' AND `complete_until` = '"+eorder->dateedit2->date().toString("yyyy-MM-dd")+"';";
		QSqlQuery query2(qstr);
		query2.next();
		row->setText(1, query2.value(0).toString());	
		if(eorder->tabtasks->rowCount()>1)
		{
		    for(i=0;i<eorder->tabtasks->rowCount()-1;i++)
		    {
				QTableWidgetItem *tmpitem = eorder->tabtasks->item(i, 0);
				QString state;
				if(tmpitem->checkState() == Qt::Checked)
				    state ="1";
				else
				    state ="0";
				QSqlQuery querytask;
				querytask.prepare("INSERT INTO `proceduretasks` (`PROC_ID`, `STATE`, `TASK`, `DATE`) VALUE (:proc_id, :state, :task, :date);");
				querytask.bindValue(":proc_id", query2.value(0).toString());
				querytask.bindValue(":state", state);
				tmpitem = eorder->tabtasks->item(i, 1);
				querytask.bindValue(":task", tmpitem->text());
				tmpitem = eorder->tabtasks->item(i, 2);
				querytask.bindValue(":date", tmpitem->text());
				querytask.exec();
		    }
		}
		if(eorder->taborders->rowCount() > 1)
		{
		    for(i=0;i<eorder->taborders->rowCount()-1;i++)
		    {
				QTableWidgetItem *tmpitem = eorder->taborders->item(i, 0);
				QString state;
				if(tmpitem->checkState() == Qt::Checked)
				    state = "1";
				else
				    state = "0";
				QSqlQuery queryorder;
				queryorder.prepare("INSERT INTO `procedureorders` (`ID`, `PROC_ID`, `STOCK`, `STOCK_ID`, `STATE`, `LABEL`, `DESCRIPTION`, `QUANTITY`, `UNIT`, `PRICE`, `VAT`) VALUES ('', :proc_id, :stock, :stock_id, :state, :label, :description, :quantity, :unit, :price, :vat);");
				queryorder.bindValue( ":proc_id", query2.value(0).toString());
				tmpitem = eorder->taborders->item(i, 11);
				queryorder.bindValue( ":stock", tmpitem->text().section(":#:", 0, 0));
				queryorder.bindValue( ":stock_id", tmpitem->text().section(":#:", 1, 1));
				queryorder.bindValue( ":state", QString("%1").arg(state, 0, 10));
				tmpitem = eorder->taborders->item(i, 1);
				queryorder.bindValue( ":label", tmpitem->text());
				tmpitem = eorder->taborders->item(i, 3);
				queryorder.bindValue( ":description", tmpitem->text());
				tmpitem = eorder->taborders->item(i, 4);
				queryorder.bindValue( ":quantity", tmpitem->text());
				tmpitem = eorder->taborders->item(i, 5);
				queryorder.bindValue( ":unit", tmpitem->text());
				tmpitem = eorder->taborders->item(i, 6);
				queryorder.bindValue( ":price", tmpitem->text());
				tmpitem = eorder->taborders->item(i, 8);
				queryorder.bindValue( ":vat", tmpitem->text());
				queryorder.exec();
		    }
		}
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
    		if(indexitem->text(2).toInt() == 6) //Open order or Archive?
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
    int i;
    procedureeditfrm *eorders = new procedureeditfrm;
    eorders->init();
    eorders->setWindowTitle( tr("Edit order..."));
    
    QString qstr = "SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM proceduretab WHERE `ID` = '"+dbID+"';";
	
    QSqlQuery query(qstr);
    if( query.isActive())
    { 
		query.next();
		eorders->lbldbID->setText(dbID);
		eorders->cmbstate->setCurrentIndex(query.value(1).toInt());
		if(query.value(2).toString() == "1")
		    eorders->chkcompleted->setCheckState(Qt::Checked);
		eorders->txtcustomer->setText(query.value(3).toString().section(" (", 0, 0));
		eorders->txtcomments->setText(query.value(4).toString());
		QString s = query.value(5).toString();
		eorders->dateedit1->setDate(QDate::QDate(s.section("-", 0, 0).toInt(), s.section("-", 1, 1).toInt(), s.section("-", 2, 2).toInt()));		
		eorders->txtorderid->setText(query.value(6).toString());
		s = query.value(10).toString();
		eorders->dateedit2->setDate(QDate::QDate(s.section("-", 0, 0).toInt(), s.section("-", 1, 1).toInt(), s.section("-", 2, 2).toInt()));
		eorders->txtcontact->setText(query.value(8).toString());
		eorders->lblcustomerid->setText(query.value(3).toString().section("(",1,1).section(")", 0, 0));        
		eorders->cmbpriority->setEditText(query.value(7).toString());    
		eorders->txtresponsible->setText(query.value(9).toString());  	

		QString qstr = QString("SELECT state, task, date FROM proceduretasks WHERE `PROC_ID`='%1' ORDER BY ID;").arg(query.value(0).toString());
		QSqlQuery tasks(qstr);

		while(tasks.next())
		{
		    QTableWidgetItem *tmpitem = new QTableWidgetItem;
   		    if(tasks.value(0).toString() == "1")
			    tmpitem->setCheckState(Qt::Checked);
			else
				tmpitem->setCheckState(Qt::Unchecked);
		    eorders->tabtasks->setItem(tasks.at(), 0, tmpitem);
			
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(tasks.value(1).toString());
		    eorders->tabtasks->setItem(tasks.at(), 1, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(tasks.value(2).toString());
		    eorders->tabtasks->setItem(tasks.at(), 2, tmpitem);
		    eorders->navtasktab(tasks.at());
		}
		
		qstr = QString("SELECT stock, stock_id, state, label, description, quantity, unit, price, vat FROM procedureorders WHERE `PROC_ID`='%1' ORDER BY ID;").arg(query.value(0).toString());
		QSqlQuery orders(qstr);

		while(orders.next())
		{
		    QTableWidgetItem *tmpitem = new QTableWidgetItem;
   		    if(orders.value(2).toString() == "1")
			    tmpitem->setCheckState(Qt::Checked);
			else
				tmpitem->setCheckState(Qt::Unchecked);
		    eorders->taborders->setItem(orders.at(), 0, tmpitem);

		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(3).toString());
		    eorders->taborders->setItem(orders.at(), 1, tmpitem);

		    tmpitem = new QTableWidgetItem;
		    tmpitem->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
		    eorders->taborders->setItem(orders.at(), 2, tmpitem);

		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(4).toString());
		    eorders->taborders->setItem(orders.at(), 3, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(5).toString());
		    eorders->taborders->setItem(orders.at(), 4, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(6).toString());
		    eorders->taborders->setItem(orders.at(), 5, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(QString("%1").arg(orders.value(7).toString().toFloat(), 0, 'f',2));
		    eorders->taborders->setItem(orders.at(), 6, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(8).toString());
		    eorders->taborders->setItem(orders.at(), 7, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(0).toString()+":#:"+orders.value(1).toString());
		    eorders->taborders->setItem(orders.at(), 10, tmpitem);
		    
		    QString qstr2 = QString("SELECT col3, col4 FROM %1 WHERE `ID`='%2';").arg(orders.value(0).toString()).arg(orders.value(1).toString());
		    QSqlQuery checkdbquery(qstr2);
		    checkdbquery.next();
		    
		    //Actual quantity
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(checkdbquery.value(0).toString());
		    eorders->taborders->setItem(orders.at(), 8, tmpitem);
		    
		    //Minimal quantity
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(checkdbquery.value(1).toString());
		    eorders->taborders->setItem(orders.at(), 9, tmpitem);
		    
		    eorders->navordertabs(orders.at());
		}
    }
    
    if(eorders->exec())
    {	    
		if(eorders->tabtasks->rowCount()>1)
		{
		    //Alte Daten löschen
		    QSqlQuery querytask_clean;
		    querytask_clean.prepare("DELETE FROM `proceduretasks` WHERE `PROC_ID`=:id;");
		    querytask_clean.bindValue(":id", dbID);
		    querytask_clean.exec();
		    
		    for(i=0;i<eorders->tabtasks->rowCount()-1;i++)
		    {
		    	QTableWidgetItem *tmpitem = eorders->tabtasks->item(i, 1);
				if(tmpitem->text() != "") 
				{
					tmpitem = eorders->tabtasks->item(i, 0);
					QString state;
					if(tmpitem->checkState() == Qt::Checked)
					    state ="1";
					else
					    state ="0";
					QSqlQuery querytask;
					querytask.prepare("INSERT INTO `proceduretasks` (`PROC_ID`, `STATE`, `TASK`, `DATE`) VALUE (:proc_id, :state, :task, :date);");
					querytask.bindValue(":proc_id", dbID);
					querytask.bindValue(":state", state);
					tmpitem = eorders->tabtasks->item(i, 1);
					querytask.bindValue(":task", tmpitem->text());
					tmpitem = eorders->tabtasks->item(i, 2);
					querytask.bindValue(":date", tmpitem->text());
					querytask.exec();
					

				}
		    }
		}
	
		if(eorders->taborders->rowCount() > 1)
		{
		    //Alte Daten löschen
		    QSqlQuery queryorder_clean;
		    queryorder_clean.prepare("DELETE FROM `procedureorders` WHERE `PROC_ID`=:id;");
		    queryorder_clean.bindValue(":id", dbID);
		    queryorder_clean.exec();
		    for(i=0; i < eorders->taborders->rowCount()-1; i++)
		    {
		    	QTableWidgetItem *tmpitem = eorders->taborders->item(i, 0);
				
				QString state;
				if(tmpitem->checkState() == Qt::Checked)
				    state = "1";
				else
				    state = "0";
				    
				QStringList strlorders;
	
				tmpitem = new QTableWidgetItem;
			    tmpitem = eorders->taborders->item(i, 10);
				strlorders << tmpitem->text().section(":#:", 0, 0) << tmpitem->text().section(":#:", 1, 1) << state;
	
			    tmpitem = new QTableWidgetItem;
			    tmpitem = eorders->taborders->item(i, 1);
				strlorders << tmpitem->text();
				
				tmpitem = new QTableWidgetItem;
			    tmpitem = eorders->taborders->item(i, 3);
				strlorders << tmpitem->text();
				
				tmpitem = new QTableWidgetItem;
			    tmpitem = eorders->taborders->item(i, 4);
				strlorders << tmpitem->text();
				
				tmpitem = new QTableWidgetItem;
			    tmpitem = eorders->taborders->item(i, 5);
				strlorders << tmpitem->text();
				
				tmpitem = new QTableWidgetItem;
			    tmpitem = eorders->taborders->item(i, 6);
				strlorders << tmpitem->text();
				
				tmpitem = new QTableWidgetItem;
			    tmpitem = eorders->taborders->item(i, 7);
				strlorders << tmpitem->text();
				
				QString qstr = QString("INSERT INTO `procedureorders` (`ID`, `PROC_ID`, `STOCK`, `STOCK_ID`, `STATE`, `LABEL`, `DESCRIPTION`, `QUANTITY`, `UNIT`, `PRICE`, `VAT`) VALUES ('', '"+dbID+"', '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9');").arg(strlorders[0]).arg(strlorders[1]).arg(strlorders[2]).arg(strlorders[3]).arg(strlorders[4]).arg(strlorders[5]).arg(strlorders[6]).arg(strlorders[7]).arg(strlorders[8]);
				QSqlQuery queryorders(qstr);
		    }
		}
		
		//datenbank aktualisieren
		QString completed = "0";
		if(eorders->chkcompleted->isChecked())
		    completed = "1";
		QString connstr = "UPDATE `proceduretab` SET `status` = '"+QString("%1").arg(eorders->cmbstate->currentIndex(), 0, 10)+"', `completed` = '"+completed+"', `client` = '"+eorders->txtcustomer->toPlainText()+" ("+eorders->lblcustomerid->text()+")', `description` = '"+eorders->txtcomments->toPlainText()+"', `date` = '"+eorders->dateedit1->date().toString("yyyy-MM-dd")+"', `orderid` = '"+eorders->txtorderid->text()+"', `priority` = '"+eorders->cmbpriority->currentText()+"', `contactperson` = '"+eorders->txtcontact->text()+"', `resp_person` = '"+eorders->txtresponsible->text()+"',  `complete_until` = '"+eorders->dateedit2->date().toString("yyyy-MM-dd")+"' WHERE `ID` = '"+dbID+"' LIMIT 1;";
		QSqlQuery query(connstr);		
		
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
    eorders->setWindowTitle( tr("Edit order..."));
    
    QString qstr = "SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM procedurearchiv WHERE `ID` = '"+dbID+"';";
	
    QSqlQuery query(qstr);
    if( query.isActive())
    { 
		query.next();
		eorders->lbldbID->setText(dbID);
		eorders->cmbstate->setCurrentIndex(query.value(1).toInt());
		if(query.value(2).toString() == "1")
		    eorders->chkcompleted->setCheckState(Qt::Checked);
		eorders->txtcustomer->setText(query.value(3).toString().section(" (", 0, 0));
		eorders->txtcomments->setText(query.value(4).toString());
		QString s = query.value(5).toString();
		eorders->dateedit1->setDate(QDate::QDate(s.section("-", 0, 0).toInt(), s.section("-", 1, 1).toInt(), s.section("-", 2, 2).toInt()));		
		eorders->txtorderid->setText(query.value(6).toString());
		s = query.value(10).toString();
		eorders->dateedit2->setDate(QDate::QDate(s.section("-", 0, 0).toInt(), s.section("-", 1, 1).toInt(), s.section("-", 2, 2).toInt()));
		eorders->txtcontact->setText(query.value(8).toString());
		eorders->lblcustomerid->setText(query.value(3).toString().section("(",1,1).section(")", 0, 0));        
		eorders->cmbpriority->setEditText(query.value(7).toString());    
		eorders->txtresponsible->setText(query.value(9).toString());  	

		QString qstr = QString("SELECT state, task, date FROM proceduretasks WHERE `PROC_ID`='A_%1' ORDER BY ID;").arg(query.value(0).toString());
		QSqlQuery tasks(qstr);

		while(tasks.next())
		{
		    QTableWidgetItem *tmpitem = new QTableWidgetItem;
   		    if(tasks.value(0).toString() == "1")
			    tmpitem->setCheckState(Qt::Checked);
			else
				tmpitem->setCheckState(Qt::Unchecked);
		    eorders->tabtasks->setItem(tasks.at(), 0, tmpitem);
			
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(tasks.value(1).toString());
		    eorders->tabtasks->setItem(tasks.at(), 1, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(tasks.value(2).toString());
		    eorders->tabtasks->setItem(tasks.at(), 2, tmpitem);
		    eorders->navtasktab(tasks.at());
		}
		
		qstr = QString("SELECT stock, stock_id, state, label, description, quantity, unit, price, vat FROM procedureorders WHERE `PROC_ID`='A_%1' ORDER BY ID;").arg(query.value(0).toString());
		QSqlQuery orders(qstr);

		while(orders.next())
		{
		    QTableWidgetItem *tmpitem = new QTableWidgetItem;
   		    if(orders.value(2).toString() == "1")
			    tmpitem->setCheckState(Qt::Checked);
			else
				tmpitem->setCheckState(Qt::Unchecked);
		    eorders->taborders->setItem(orders.at(), 0, tmpitem);

		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(3).toString());
		    eorders->taborders->setItem(orders.at(), 1, tmpitem);

		    tmpitem = new QTableWidgetItem;
		    tmpitem->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
		    eorders->taborders->setItem(orders.at(), 2, tmpitem);

		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(4).toString());
		    eorders->taborders->setItem(orders.at(), 3, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(5).toString());
		    eorders->taborders->setItem(orders.at(), 4, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(6).toString());
		    eorders->taborders->setItem(orders.at(), 5, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(QString("%1").arg(orders.value(7).toString().toFloat(), 0, 'f',2));
		    eorders->taborders->setItem(orders.at(), 6, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(8).toString());
		    eorders->taborders->setItem(orders.at(), 7, tmpitem);
		    
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(orders.value(0).toString()+":#:"+orders.value(1).toString());
		    eorders->taborders->setItem(orders.at(), 10, tmpitem);
		    
		    QString qstr2 = QString("SELECT col3, col4 FROM %1 WHERE `ID`='%2';").arg(orders.value(0).toString()).arg(orders.value(1).toString());
		    QSqlQuery checkdbquery(qstr2);
		    checkdbquery.next();
		    
		    //Actual quantity
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(checkdbquery.value(0).toString());
		    eorders->taborders->setItem(orders.at(), 8, tmpitem);
		    
		    //Minimal quantity
		    tmpitem = new QTableWidgetItem;
		    tmpitem->setText(checkdbquery.value(1).toString());
		    eorders->taborders->setItem(orders.at(), 9, tmpitem);
		    
		    eorders->navordertabs(orders.at());
		}
    }
    eorders->btnaccept->setText("Schliessen");
    eorders->show();
}
//
void procedurefrm::deleteorder(QString dbID)
{
    QString conn = "SELECT orderid FROM proceduretab WHERE `ID` = '"+dbID+"';";
    QSqlQuery query(conn);
    if( query.isActive())
		query.next();
    if(QMessageBox::information(this, tr("Delete order..."), tr("Delete order %1?").arg(query.value(0).toString()), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
		conn = "DELETE FROM `proceduretab` WHERE `ID`='"+dbID+"';";
		QSqlQuery query2(conn);
    }
}
//
void procedurefrm::deletearchivorder(QString dbID)
{
    QString conn = "SELECT orderid FROM procedurearchiv WHERE `ID` = '"+dbID+"';";
	
    QSqlQuery query(conn);
    if( query.isActive())
		query.next();
    if(QMessageBox::information(this, tr("Delete order..."), tr("Delete order %1?").arg(query.value(0).toString()), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
    {
		conn = "DELETE FROM `procedurearchiv` WHERE `ID`='"+dbID+"';";
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
    for(i=0;i<treemain->topLevelItemCount();i++)
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
					    this->createdoc_2(0);
					this->updatedatabase(0, item->text(1));
					this->filltable(0);
					break;
			    case 1: //Auftragsbestäigung erstellen
					this->createdoc_1(item->text(1));
					if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create order confirmation for order %1 ?").arg(childitem->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
					    this->createdoc_2(1);
					this->updatedatabase(1, item->text(1));
					this->filltable(1);
					break;
			    case 2: //Auftrag erledigt
					this->createdoc_1(item->text(1));
					if(QMessageBox::information(this, tr("Procedure completed..."), tr("All works on procedure %1 completed?").arg(childitem->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
					    this->updatedatabase(2, item->text(1));
					this->filltable(2);
					break;
			    case 3: //Lieferschein erstellen
					this->createdoc_1(item->text(1));
					if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create deliverynote for order %1 ?").arg(childitem->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
					    this->createdoc_2(3);
					this->updatedatabase(3, item->text(1));
					this->filltable(3);
					break;
			    case 4: //Rechnung erstellen
					this->createdoc_1(item->text(1));
					if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create bill for order %1 ?").arg(childitem->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
					    this->createdoc_2(4);
					this->updatedatabase(4, item->text(1));
					this->filltable(4);
					break;
			    case 5: //Auftrag abgeschlossen und archivieren
					this->createdoc_1(item->text(1));
					if(QMessageBox::information(this, tr("Procedure completed..."), tr("Complete and archive order %1 ?").arg(childitem->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
					    this->updatedatabase(5, item->text(1));
					this->filltable(5);
					break;		
		    }	    
		}
    }
}
//
void procedurefrm::createdoc_1(QString dbID)
{
    int i;    
    QString connstr = "SELECT status, completed, priority, date, client, contactperson, orderid, description, resp_person, complete_until FROM proceduretab WHERE `ID` = '"+dbID+"'";
    QSqlQuery query(connstr);
    query.next();
    queryreturn.clear();
    for(i=0;i<=9;i++)
		queryreturn.append(query.value(i).toString());
}
//
void procedurefrm::createdoc_2(int doctype)
{/*
    int i;
    docsfrm *doc = new docsfrm;
    doc->initdocsfrm();

    doc->btnprint->setEnabled(TRUE);
    doc->btncomplete->setEnabled(TRUE);
    doc->boxadress->setText(queryreturn[4].section(" (", 0, 0));
    doc->lblID->setText(queryreturn[4].section(" (", 1, 1).section(")", 0, 0));
    doc->box_btext->setText(queryreturn[7]);
    doc->lbluser->setText(queryreturn[8]);
    
    QListViewItem* item = mainlisttable->currentItem();
    QSqlQuery orders;
    orders.prepare("SELECT stock, stock_id, state, label, description, quantity, unit, price, vat FROM procedureorders WHERE `PROC_ID`=:id ORDER BY ID;");
    orders.bindValue(":id", item->text(1));
    orders.exec();
    doc->maintable->setNumRows(orders.size());
    while(orders.next())
    {
	doc->maintable->setText(i, 0, QString("%1").arg(orders.at()+1, 0, 10));
	doc->maintable->setText(orders.at(), 1, orders.value(3).toString());
	doc->maintable->setPixmap(i, 2, QPixmap::fromMimeSource( "viewmag2.png" ));	
	doc->maintable->setText(orders.at(), 3, orders.value(4).toString());	
	doc->maintable->setText(orders.at(), 4, orders.value(5).toString());
	doc->maintable->setText(orders.at(), 5, orders.value(6).toString());	    
	doc->maintable->setText(orders.at(), 6, QString("%1").arg(orders.value(7).toString().toFloat(), 0, 'f',2));	    
	doc->maintable->setText(orders.at(), 7, QString("%1").arg(orders.value(5).toInt()*orders.value(7).toString().toFloat(), 0, 'f',2));	    
	doc->maintable->setText(orders.at(), 8, orders.value(8).toString());
	
	//check act. quantity and min. quantity///////////////////////////
	QString connstr = "SELECT col3, col4 FROM "+orders.value(0).toString()+" WHERE `ID` = "+orders.value(1).toString()+";";
	QSqlQuery querycheckdb(connstr);
	querycheckdb.next();
	doc->maintable->setText(orders.at(), 9, querycheckdb.value(0).toString());
	doc->maintable->setText(orders.at(), 10, querycheckdb.value(1).toString());
	//check act. quantity and min. quantity///////////////////////////
	
	doc->maintable->setText(orders.at(), 11, orders.value(0).toString()+":#:"+orders.value(1).toString());
    }
    
    doc->navtable(doc->maintable->numRows(), doc->maintable->numCols());
    doc->calc_tot();	

    switch(docart)
    {
    case 0:
	doc->cmbdoc->setCurrentItem(1);  //leerzeile entfernen
	doc->cmbdoc->setCurrentItem(0);
	doc->doccount->setText(abdocpref+queryreturn[6]);
	doc->selecteddocument(); 
	doc->show();
	break;
    case 1:
	doc->cmbdoc->setCurrentItem(1);
	doc->doccount->setText(abdocpref+queryreturn[6]);
	doc->selecteddocument();
	doc->show();
	break;
    case 2:	    
	break;
    case 3:
	doc->cmbdoc->setCurrentItem(2);
	doc->doccount->setText(abdocpref+queryreturn[6]);
	doc->selecteddocument();
	doc->show();
	break;
    case 4:
	doc->cmbdoc->setCurrentItem(3);
	doc->doccount->setText(abdocpref+queryreturn[6]);
	doc->selecteddocument();
	doc->show();
	break;
    }*/
}
//
void procedurefrm::updatedatabase(int doctype, QString dbID)
{
    if(QMessageBox::information(this, tr("Order completed..."), tr("Save changes for order %1 in database?").arg(queryreturn[6]), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
    {
		if(doctype<5)
		{
		    QString connstr = "UPDATE `proceduretab` SET `status`='"+QString("%1").arg(doctype+1, 0, 10)+"' WHERE `ID`='"+dbID+"';";
		    QSqlQuery query(connstr);
		}
		else
		{
		    QString connstr1 = "INSERT INTO `procedurearchiv` (`ID`, `status`, `completed`, `priority`, `date`, `client`, `contactperson`, `orderid`, `description`, `resp_person`, `complete_until`) VALUES (NULL, '6', '1', '"+queryreturn[2]+"', '"+queryreturn[3]+"', '"+queryreturn[4]+"', '"+queryreturn[5]+"', '"+queryreturn[6]+"', '"+queryreturn[7]+"', '"+queryreturn[8]+"', '"+queryreturn[9]+"');" ;
		    QSqlQuery query1(connstr1);
		    
		    QSqlQuery checkid;
		    checkid.prepare("SELECT id FROM procedurearchiv WHERE `priority`=:prio AND `date`=:date AND `client`=:client AND `contactperson`=:contact AND `orderid`=:orderid AND `description`=:desc AND `resp_person`=:resp AND `complete_until`=:complete;");
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
		    tasks.bindValue(":id", dbID);
		    tasks.exec();
	    
		    QSqlQuery orders;
		    orders.prepare("UPDATE `procedureorders` SET `PROC_ID`=:newid WHERE `proc_id`=:id;");
		    orders.bindValue(":newid", "A_"+checkid.value(0).toString());
		    orders.bindValue(":id", dbID);
		    orders.exec();
			    
		    QString connstr2 = "DELETE FROM `proceduretab` WHERE `ID`="+dbID+" LIMIT 1;";
		    QSqlQuery query2(connstr2);
		}
	queryreturn.clear();
    }
}
/*
//
void procedurefrm::searchentry()
{
    srchablfrm *srchfrm = new srchablfrm;
    srchfrm->initfrm();
    //Werte setzen
    srchfrm->searchtxt->setText(searchtext->text());
    srchfrm->cmbrow->setCurrentItem(cmbrow->currentItem());
    srchfrm->lbluser->setText(lbluser->text());
    if(searchtext->text() != "")
	srchfrm->search();
    srchfrm->exec();
    this->setFocus();
}
//
void procedurefrm::contmenu()
{
    QPopupMenu* contextMenu = new QPopupMenu( this );
    Q_CHECK_PTR( contextMenu );
    contextMenu->insertItem( tr("Create Offer"),  this, SLOT(createoffer()));
    contextMenu->insertItem( tr("Create Orderconfirmation"),  this, SLOT(createorderconf()));
    contextMenu->insertItem( tr("Create Delivery note"),  this, SLOT(createdeliverynote()));
    contextMenu->insertItem( tr("Create Bill"),  this, SLOT(createbill()));
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}
//
void procedurefrm::createoffer()
{
    QListViewItem* item = mainlisttable->currentItem();
    this->createdoc_1(item->text(1));
    this->createdoc_2(0);
}
//
void procedurefrm::createorderconf()
{
    QListViewItem* item = mainlisttable->currentItem();
    this->createdoc_1(item->text(1));
    this->createdoc_2(1);
}
//
void procedurefrm::createdeliverynote()
{
    QListViewItem* item = mainlisttable->currentItem();
    this->createdoc_1(item->text(1));
    this->createdoc_2(3);
}
//
void procedurefrm::createinvoice()
{
    QListViewItem* item = mainlisttable->currentItem();
    if(item->depth() > 0)
	item = item->parent();
    this->createdoc_1(item->text(1));
    this->createdoc_2(4);
}
*/

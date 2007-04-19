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
    connect(btnedit, SIGNAL(released()), this, SLOT(checkeditID()));
    connect(btndelete, SIGNAL(released()), this, SLOT(checkdeleteID()));
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
		    row->setText(2, query.value(3).toString().section(" (", 0, 0));
			
		    row->setText(3, query.value(4).toString());
		    QString s =  query.value(5).toString();
		    row->setText(4, s.section("-", 2, 2)+"."+s.section("-", 1, 1)+"."+s.section("-", 0, 0));
			
		    QTreeWidgetItem* childrow0 = new QTreeWidgetItem(row);
		    childrow0->setText(2, tr("Tasks"));
		    childrow0->setText(1, query.value(11).toString());
			
		    QSqlQuery tasks;
		    tasks.prepare("SELECT state, task, date FROM proceduretasks WHERE `PROC_ID`=:id;");
		    tasks.bindValue(":id", query.value(0).toString());
		    tasks.exec();
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
		    childrow1->setText(1, query.value(12).toString());
		
		    QSqlQuery orders;
		    orders.prepare("SELECT state, label, quantity FROM procedureorders WHERE `PROC_ID`=:id;");
		    orders.bindValue(":id", query.value(0).toString());
		    orders.exec();
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
    eorder->chkcompleted->setChecked(TRUE);
    
    QTreeWidgetItem *item = treemain->currentItem();
    if(item != 0)
	    eorder->cmbstate->setCurrentIndex(item->text(2).toInt());
	else
		eorder->cmbstate->setCurrentIndex(0);
    if(eorder->exec())
    {
    	QMessageBox::information(0, "test", "test4");
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
	filltable(treeindex->currentItem()->text(2).toInt());
    }
}
//
void procedurefrm::checkeditID()
{
    QTreeWidgetItem* item = treemain->currentItem();
    item = treemain->topLevelItem(treemain->indexOfTopLevelItem(item));
    //editorder(item->text(1));
}
//

void procedurefrm::checkdeleteID()
{
    QTreeWidgetItem* item = treemain->currentItem();
    item = treemain->topLevelItem(treemain->indexOfTopLevelItem(item));
    //deleteorder(item->text(1));
}
//
/*
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
		    	
		eorders->navtasktab(0, 0);
		QSqlQuery tasks;
		tasks.prepare("SELECT state, task, date FROM proceduretasks WHERE `PROC_ID`=:id ORDER BY ID;");
		tasks.bindValue(":id", query.value(0).toString());
		tasks.exec();
		while(tasks.next())
		{
		    QCheckTableItem* tmpitem = (QCheckTableItem*)nafrm->tabletasks->item(tasks.at(), 0);
		    if(tasks.value(0).toString() == "1")
			tmpitem->setChecked(TRUE);
		    eorders->tabletasks->setText(tasks.at(), 1, tasks.value(1).toString());
		    eorders->tabletasks->setText(tasks.at(), 2, tasks.value(2).toString());
		    eorders->navtasktab(tasks.at(), 0);
		}
	
		nafrm->navtasktab(0, 0);
		QSqlQuery orders;
		orders.prepare("SELECT stock, stock_id, state, label, description, quantity, unit, price, vat FROM procedureorders WHERE `PROC_ID`=:id ORDER BY ID;");
		orders.bindValue(":id", query.value(0).toString());
		orders.exec();
		while(orders.next())
		{
		    QCheckTableItem* tmpitem = (QCheckTableItem*)nafrm->tableorders->item(tasks.at(), 0);
		    if(tasks.value(0).toString() == "1")
			tmpitem->setChecked(TRUE);
		    eorders->tableorders->setText(orders.at(), 1, orders.value(3).toString());
		    eorders->tableorders->setPixmap(i, 2, QPixmap::fromMimeSource( "viewmag2.png" ));	
		    eorders->tableorders->setText(orders.at(), 3, orders.value(4).toString());
		    eorders->tableorders->setText(orders.at(), 4, orders.value(5).toString());
		    eorders->tableorders->setText(orders.at(), 5, orders.value(6).toString());	
		    eorders->tableorders->setText(orders.at(), 6, QString("%1").arg(orders.value(7).toString().toFloat(), 0, 'f',2));
		    eorders->tableorders->setText(orders.at(), 7, QString("%1").arg(orders.value(5).toInt()*orders.value(7).toString().toFloat(), 0, 'f',2));
		    eorders->tableorders->setText(orders.at(), 8, orders.value(8).toString());
		    eorders->tableorders->setText(orders.at(), 11, orders.value(0).toString()+":#:"+orders.value(1).toString());
		    eorders->navordertabs(orders.at(), 0);
		}
    }
    
    if(eorders->exec()==QDialog::Accepted)
    {	    
		if(eorders->tabletasks->numRows()>1)
		{
		    //Alte Daten löschen
		    QSqlQuery querytask_clean;
		    querytask_clean.prepare("DELETE FROM `proceduretasks` WHERE `PROC_ID`=:id;");
		    querytask_clean.bindValue(":id", dbID);
		    querytask_clean.exec();
		    for(i=0;i<nafrm->tabletasks->numRows()-1;i++)
		    {
				QCheckTableItem* tmpitem = (QCheckTableItem*)nafrm->tabletasks->item(i, 0);
				if(nafrm->tabletasks->text(i, 1) != "") 
				{
				    QString state;
			    	if(tmpitem->isChecked())
						state ="1";
				    else
						state ="0";
				    QSqlQuery querytask;
				    querytask.prepare("INSERT INTO `proceduretasks` (`PROC_ID`, `STATE`, `TASK`, `DATE`) VALUE (:proc_id, :state, :task, :date);");
				    querytask.bindValue(":proc_id", dbID);
				    querytask.bindValue(":state", state);
				    querytask.bindValue(":task", nafrm->tabletasks->text(i, 1));
				    querytask.bindValue(":date", nafrm->tabletasks->text(i, 2));
				    querytask.exec();
				}
		    }
		}
	
		if(nafrm->tableorders->numRows()>1)
		{
		    //Alte Daten löschen
		    QSqlQuery queryorder_clean;
		    queryorder_clean.prepare("DELETE FROM `procedureorders` WHERE `PROC_ID`=:id;");
		    queryorder_clean.bindValue(":id", dbID);
		    queryorder_clean.exec();
		    for(i=0;i<nafrm->tableorders->numRows()-1;i++)
		    {
				QCheckTableItem* tmpitem = (QCheckTableItem*)nafrm->tableorders->item(i, 0);
				QString state;
				if(tmpitem->isChecked())
				    state = "1";
				else
				    state = "0";
	
				QSqlQuery queryorder;
				queryorder.prepare("INSERT INTO `procedureorders` (`ID`, `PROC_ID`, `STOCK`, `STOCK_ID`, `STATE`, `LABEL`, `DESCRIPTION`, `QUANTITY`, `UNIT`, `PRICE`, `VAT`) VALUES ('', :proc_id, :stock, :stock_id, :state, :label, :description, :quantity, :unit, :price, :vat);");
				queryorder.bindValue( ":proc_id", dbID);
				queryorder.bindValue( ":stock", nafrm->tableorders->text(i, 11).section(":#:", 0, 0));
				queryorder.bindValue( ":stock_id", nafrm->tableorders->text(i, 11).section(":#:", 1, 1));
				if(tmpitem->isChecked())
				    queryorder.bindValue( ":state", "1");
				else
				    queryorder.bindValue( ":state", "0");
				queryorder.bindValue( ":label", nafrm->tableorders->text(i, 1));
				queryorder.bindValue( ":description", nafrm->tableorders->text(i, 3));
				queryorder.bindValue( ":quantity", nafrm->tableorders->text(i, 4));
				queryorder.bindValue( ":unit", nafrm->tableorders->text(i, 5));
				queryorder.bindValue( ":price", nafrm->tableorders->text(i, 6));
				queryorder.bindValue( ":vat", nafrm->tableorders->text(i, 8));
				queryorder.exec();
		    }
		}
		
		//datenbank aktualisieren
		QString erledigt = "0";
		if(nafrm->chkerledigt->isChecked())
		    erledigt = "1";
		QString connstr = "UPDATE `proceduretab` SET `status` = '"+QString("%1").arg(nafrm->cmbstatus->currentItem(), 0, 10)+"', `completed` = '"+erledigt+"', `client` = '"+nafrm->txtkunde->text()+" ("+nafrm->lblkundenid->text()+")', `description` = '"+nafrm->txtbeschreibung->text()+"', `date` = '"+nafrm->dateedit1->date().toString("yyyy-MM-dd")+"', `orderid` = '"+nafrm->boxauftragid->text()+"', `priority` = '"+nafrm->cmbprioritaet->currentText()+"', `contactperson` = '"+nafrm->boxkontakt->text()+"', `resp_person` = '"+nafrm->boxverarbeitet->text()+"',  `complete_until` = '"+nafrm->dateedit2->date().toString("yyyy-MM-dd")+"' WHERE `ID` = '"+dbID+"' LIMIT 1;";
		QSqlQuery query(connstr);		
		
		//ansicht aktualisieren
		mainlistview->clearSelection();
		mainlisttable->clearSelection();	
		this->filltable(nafrm->cmbstatus->currentItem());
		mainlisttable->setFocus();
    }
}
//
void procedurefrm::editarchiveorder(QString dbID)
{
    int i;    
    neuauftragfrm *nafrm = new neuauftragfrm;
    nafrm->initfrm();
    nafrm->setCaption( tr("Edit order..."));
    QString conn = "SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM procedurearchiv WHERE `ID` = '"+dbID+"';";
	
    QSqlQuery query(conn);
    if( query.isActive())
    { 
	while(query.next())
	{
	    nafrm->lbldbID->setText(dbID);
	    nafrm->cmbstatus->setCurrentItem(mainlistview->currentItem()->text(2).toInt());
	    if(query.value(2).toString()=="1")
		nafrm->chkerledigt->setChecked(TRUE);
	    nafrm->txtkunde->setText(query.value(3).toString().section(" (", 0, 0),"");
	    nafrm->txtbeschreibung->setText(query.value(4).toString(),"");  
	    QString s = query.value(5).toString();
	    nafrm->dateedit1->setDate(QDate::QDate(s.section("-", 0, 0).toInt(), s.section("-", 1, 1).toInt(), s.section("-", 2, 2).toInt()));		
	    nafrm->boxauftragid->setText(query.value(6).toString());
	    s = query.value(10).toString();
	    nafrm->dateedit2->setDate(QDate::QDate(s.section("-", 0, 0).toInt(), s.section("-", 1, 1).toInt(), s.section("-", 2, 2).toInt()));
	    nafrm->boxkontakt->setText(query.value(8).toString());
	    nafrm->lblkundenid->setText(query.value(3).toString().section("(",1,1).section(")", 0, 0));        
	    nafrm->cmbprioritaet->setCurrentText(query.value(7).toString());    
	    nafrm->boxverarbeitet->setText(query.value(9).toString());  		
		
	    if(query.value(11).toString().contains(":##:")>0)
		nafrm->navtasktab(0, 0);
	    for(i=0; i<query.value(11).toString().contains(":##:"); i++)
	    {
		QString textzeilen = query.value(11).toString().section(":##:", i, i);
		QCheckTableItem* tmpitem = (QCheckTableItem*)nafrm->tabletasks->item(i, 0);
		if(textzeilen.section( ":#:", 0, 0 )=="1")
		    tmpitem->setChecked(TRUE);
		nafrm->tabletasks->setText(i, 1, textzeilen.section( ":#:", 1, 1 ));
		nafrm->tabletasks->setText(i, 2, textzeilen.section( ":#:", 2, 2 ));
		nafrm->navtasktab(i, 0);
	    }
		
	    if(query.value(12).toString().contains(":##:")>0)
		nafrm->navordertabs(0, 0);
	    for(i=0; i<query.value(12).toString().contains(":##:"); i++)
	    {
		QString textzeilen = query.value(12).toString().section(":##:", i, i);
		QCheckTableItem* tmpitem = (QCheckTableItem*)nafrm->tableorders->item(i, 0);
		if(textzeilen.section( ":#:", 0, 0 )=="1")
		    tmpitem->setChecked(TRUE);
		nafrm->tableorders->setText(i, 1, textzeilen.section( ":#:", 1, 1 ));	
		nafrm->tableorders->setPixmap(i, 2, QPixmap::fromMimeSource( "viewmag2.png" ));	
		nafrm->tableorders->setText(i, 3, textzeilen.section( ":#:", 2, 2 ));	
		nafrm->tableorders->setText(i, 3, textzeilen.section( ":#:", 3, 3 ));
		nafrm->tableorders->setText(i, 4, textzeilen.section( ":#:", 4, 4 ));	    
		nafrm->tableorders->setText(i, 5, textzeilen.section( ":#:", 5, 5 ));	    
		nafrm->tableorders->setText(i, 6, textzeilen.section( ":#:", 6, 6 ));	    
		nafrm->tableorders->setText(i, 7, textzeilen.section( ":#:", 7, 7 ));	    
		nafrm->tableorders->setText(i, 8, textzeilen.section( ":#:", 8, 8 ));
		nafrm->navordertabs(i, 0);
	    }		
	}
    }
    nafrm->btnaccept->setCaption("Schliessen");
    nafrm->show();
}
//
void procedurefrm::deleteorder(QString dbID)
{
    QString conn = "SELECT orderid FROM proceduretab WHERE `ID` = '"+dbID+"';";
    QSqlQuery query(conn);
    if( query.isActive())
    { 
	query.next();
    }   
    if(QMessageBox::information(this, tr("Delete order..."), tr("Delete order %1?").arg(query.value(0).toString()), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
	conn = "DELETE FROM `proceduretab` WHERE `ID`='"+dbID+"';";
	QSqlQuery query2(conn);
    }
    this->filltable(mainlistview->currentItem()->text(2).toInt());
    mainlisttable->setFocus();
}
//
void procedurefrm::deletearchivorder(QString dbID)
{
    QString conn = "SELECT orderid FROM procedurearchiv WHERE `ID` = '"+dbID+"';";
	
    QSqlQuery query(conn);
    if( query.isActive())
    { 
	query.next();
    }   
    if(QMessageBox::information(this, tr("Delete order..."), tr("Delete order %1?").arg(query.value(0).toString()), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
    {
	conn = "DELETE FROM `procedurearchiv` WHERE `ID`='"+dbID+"';";
	QSqlQuery query2(conn);
    }
}
//
void procedurefrm::completeitems()
{
    int i;
    QCheckListItem* item = (QCheckListItem*)mainlisttable->firstChild();
    for(i=0;i<mainlisttable->childCount();i++)
    {	
	if(i>0)
	{
	    item = (QCheckListItem*)item->itemBelow();	    
	    while(item->text(1).stripWhiteSpace()=="")
		item=(QCheckListItem*)item->itemBelow();
	}
	QListViewItem* itemchild = (QCheckListItem*)item->firstChild();
	itemchild = (QCheckListItem*)itemchild->itemBelow();
	itemchild->setOpen(FALSE);
	itemchild = (QCheckListItem*)itemchild->itemBelow();
	itemchild->setOpen(FALSE);	
	itemchild = (QCheckListItem*)itemchild->itemBelow();
	if(item->isOn())
	{
	    switch(mainlistview->currentItem()->text(2).toInt())
	    {
	    case 0: //Offerte erstellen
		this->createdoc_1(item->text(1));
		if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create offer for order %1 ?").arg(itemchild->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
		    this->createdoc_2(0);
		this->updatedatabase(0, item->text(1));
		break;
	    case 1: //Auftragsbestäigung erstellen
		this->createdoc_1(item->text(1));
		if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create order confirmation for order %1 ?").arg(itemchild->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
		    this->createdoc_2(1);
		this->updatedatabase(1, item->text(1));
		this->filltable(1);
		break;
	    case 2: //Auftrag erledigt
		this->createdoc_1(item->text(1));
		if(QMessageBox::information(this, tr("Procedure completed..."), tr("All works on procedure %1 completed?").arg(itemchild->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
		    this->updatedatabase(2, item->text(1));
		this->filltable(2);
		break;
	    case 3: //Lieferschein erstellen
		this->createdoc_1(item->text(1));
		if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create deliverynote for order %1 ?").arg(itemchild->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
		    this->createdoc_2(3);
		this->updatedatabase(3, item->text(1));
		this->filltable(3);
		break;
	    case 4: //Rechnung erstellen
		this->createdoc_1(item->text(1));
		if(QMessageBox::information(this, tr("Procedure completed..."), tr("Create bill for order %1 ?").arg(itemchild->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
		    this->createdoc_2(4);
		this->updatedatabase(4, item->text(1));
		this->filltable(4);
		break;
	    case 5: //Auftrag abgeschlossen und archivieren
		this->createdoc_1(item->text(1));
		if(QMessageBox::information(this, tr("Procedure completed..."), tr("Complete and archive order %1 ?").arg(itemchild->text(3)), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
		    this->updatedatabase(5, item->text(1));
		this->filltable(5);
		break;		
	    }	    
	}
    }
    ablauf::filltable(0);
}
//
void procedurefrm::createdoc_1(QString dbID)
{
    int i;    
    QString connstr = "SELECT status, completed, priority, date, client, contactperson, orderid, description, resp_person, complete_until FROM proceduretab WHERE `ID` = '"+dbID+"'";
    QSqlQuery query(connstr);
    query.next();
    queryreturn.clear();
    for(i=0;i<=11;i++)
    {
	queryreturn.append(query.value(i).toString());
    }
}
//
void procedurefrm::createdoc_2(int doctype)
{   
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
    }
}
//
void procedurefrm::updatedatabase(int doctype, QString dbID)
{
    if(QMessageBox::information(this, tr("Order completed..."), tr("Save changes for order %1 in database?").arg(queryreturn[6]), QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
    {
	if(docart<5)
	{
	    QString connstr = "UPDATE `proceduretab` SET `status`='"+QString("%1").arg(docart+1, 0, 10)+"' WHERE `ID`='"+dbID+"';";
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
void procedurefrm::closeEvent( QCloseEvent* ce )
{
    varfrm* v = new varfrm;
    v->savegeo(this->name(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
    ce->accept();
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

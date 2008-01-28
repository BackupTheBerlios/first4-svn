#include <QCloseEvent>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QMenu>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QFileDialog>
#include <QHeaderView>
//
#include "accountsfrm.h"
#include "vars.h"
#include "accountseditfrm.h"
#include "accountscomplfrm.h"
#include "printfrm.h"
#include "progfrm.h"
#include "accountsimpexpfrm.h"
//
extern QString username, fullname, templatefolder, docfolder;
//
QString accountid;
//
accountsfrm::accountsfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
int accountsfrm::init()
{
    lbluser->setText(username);
    initindexlist();
    loadaccounts();
    mainstack->setCurrentIndex (0);	
	
	treeindex->hideColumn(1);
	treeindex->hideColumn(2);
	treeindex->hideColumn(3);
	treeindex->hideColumn(4);
	treeindex->hideColumn(5);
	treeindex->hideColumn(6);
	treeindex->hideColumn(7);
    treeindex->header()->setClickable(FALSE);
    treeindex->header()->setResizeMode(QHeaderView::Fixed);	
	
	connect(btnnew, SIGNAL(released()), this, SLOT(newentry()));
	connect(btnedit, SIGNAL(released()), this, SLOT(editentry()));
	connect(btndelete, SIGNAL(released()), this, SLOT(deleteentry()));
	connect(btnprint, SIGNAL(released()), this, SLOT(print()));
	connect(btntransfer, SIGNAL(released()), this, SLOT(datatransfer()));
	connect(btncomplete, SIGNAL(released()), this, SLOT(completeitems()));
	connect(btnclose, SIGNAL(released()), this, SLOT(close()));
	connect(treeindex, SIGNAL(itemClicked(QTreeWidgetItem* , int)), this, SLOT(loaddetails()));
	connect(treemain, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));
	
	vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
	    if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
    }
    
    inittreemainoverview();
    
    return 2;
}
//
void accountsfrm::closeEvent( QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void accountsfrm::initindexlist()
{
    QTreeWidgetItem *item = new QTreeWidgetItem(treeindex, 0);
    item->setText( 0, tr("Accounts"));
    item->setText( 1, "account");
    
    item = new QTreeWidgetItem(treeindex, item );
    item->setText( 0, tr("Incomes"));
    item->setText( 1, "inc");
    item->setText( 2, "ietab");
    
    item = new QTreeWidgetItem( treeindex, item );
    item->setText( 0, tr("Expenditures"));
    item->setText( 1, "exp");
    item->setText( 2, "ietab");
    
    item = new QTreeWidgetItem( treeindex, item );
    item->setText( 0, tr("Archiv"));
    item->setText( 1, "archiv");
    item->setText( 2, "ietabarchiv");    
    
    QTreeWidgetItem *childitem = new QTreeWidgetItem(item, 0);
    childitem->setText( 0, tr("Incomes"));
    childitem->setText( 1, "inc");
    childitem->setText( 2, "ietabarchiv");
    childitem = new QTreeWidgetItem(item, childitem );
    childitem->setText( 0, tr("Expenditures"));
    childitem->setText( 1, "exp");
    childitem->setText( 2, "ietabarchiv");
}
//
void accountsfrm::inittreemainaccounts()
{
	treemain->clear();
    treemain->setColumnCount(8);
    
    //Spalten definieren
    treemain->headerItem()->setText(0, tr("ID"));
    treemain->headerItem()->setText(1, tr("Date"));
    treemain->headerItem()->setText(2, tr("RefNr."));
    treemain->headerItem()->setText(3, tr("Address"));
    treemain->headerItem()->setText(4, tr("Code"));
    treemain->headerItem()->setText(5, tr("Description"));
    treemain->headerItem()->setText(6, tr("Amount"));
    treemain->headerItem()->setText(7, tr("Account"));

    treemain->hideColumn(0);
    treemain->setColumnWidth(1, 80);
    treemain->setColumnWidth(2, 100);
    treemain->setColumnWidth(3, 150);
    treemain->setColumnWidth(4, 60);
    treemain->setColumnWidth(5, 300);
    treemain->setColumnWidth(6, 70);
    treemain->setColumnWidth(7, 80);
    
    mainstack->setCurrentIndex(2);
}

void accountsfrm::inittreemainoverview()
{
	treemain->clear();
    treemain->setColumnCount(7);
    
    //Spalten definieren
    treemain->headerItem()->setText(0, tr("ID"));
    treemain->headerItem()->setText(1, tr("Account"));
    treemain->headerItem()->setText(2, tr("Account-Nr."));
    treemain->headerItem()->setText(3, tr("Bank"));
    treemain->headerItem()->setText(4, tr("Clearing"));
    treemain->headerItem()->setText(5, tr("Amount"));
    treemain->headerItem()->setText(6, tr("Currency"));

    treemain->hideColumn(0);
    treemain->setColumnWidth(1, 130);
    treemain->setColumnWidth(2, 100);
    treemain->setColumnWidth(3, 130);
    treemain->setColumnWidth(4, 50);
    treemain->setColumnWidth(5, 90);
    treemain->setColumnWidth(6, 70);
    
    mainstack->setCurrentIndex(0);
}

void accountsfrm::initmaintreeincexp()
{
	treemain->clear();
    treemain->setColumnCount(9);
    
    //Spalten definieren
    treemain->headerItem()->setText(0, "ID");
    treemain->headerItem()->setText(1, "");
    treemain->headerItem()->setIcon(1, QIcon(QString::fromUtf8(":/button_ok_small.png")));
    treemain->headerItem()->setText(2, tr("Date"));
    treemain->headerItem()->setText(3, tr("RefNr."));
    treemain->headerItem()->setText(4, tr("Address"));
    treemain->headerItem()->setText(5, tr("Code"));
    treemain->headerItem()->setText(6, tr("Description"));
    treemain->headerItem()->setText(7, tr("Amount"));
    treemain->headerItem()->setText(8, tr("ClientID"));
    
    treemain->hideColumn(0);
    treemain->setColumnWidth(1, 25);
    treemain->setColumnWidth(2, 100);
    treemain->setColumnWidth(3, 150);
    treemain->setColumnWidth(4, 250);
    treemain->setColumnWidth(5, 80);
    treemain->setColumnWidth(6, 250);
    treemain->setColumnWidth(7, 80);
    treemain->hideColumn(8);
    
    mainstack->setCurrentIndex(1);
}
//
void accountsfrm::loadaccounts()
{
    QString connstr = "SELECT ID, name, description, accountnr, bank, blz, currency, users FROM accounttab WHERE users LIKE '%"+username+" [1%' AND name LIKE '%account%';"; 
    QSqlQuery query1(connstr);
    if ( query1.isActive())
    {
		progbar->setValue(0);
		progbar->setMaximum(query1.size());
		int count = 0;
		QTreeWidgetItem *item = treeindex->topLevelItem(0);
		while(query1.next())
		{
		    progbar->setValue(++count);
		    QTreeWidgetItem *childitem = new QTreeWidgetItem(item);
		    childitem->setText(0, query1.value(2).toString());
		    childitem->setText(1, query1.value(0).toString());
		    childitem->setText(2, query1.value(1).toString());
		    childitem->setText(3, query1.value(3).toString());
		    childitem->setText(4, query1.value(4).toString());
		    childitem->setText(5, query1.value(5).toString());
		    childitem->setText(6, query1.value(6).toString());
		    childitem->setText(7, query1.value(7).toString().section(username+" [", 1, 1).section("]", 0, 0));
		}
    }
    
    connstr = "SELECT users FROM accounttab WHERE name LIKE '%ietab%';"; 
    QSqlQuery query2(connstr);
    if(query2.isActive())
    {
		QTreeWidgetItem *item = treeindex->topLevelItem(1);
		query2.next();
		item->setText(7, query2.value(0).toString().section(username+" [", 1, 1).section("]", 0, 0));
		
		item = new QTreeWidgetItem;
		item = treeindex->topLevelItem(2);
		item->setText(7, query2.value(0).toString().section(username+" [", 1, 1).section("]", 0, 0));

		item = new QTreeWidgetItem;
		item = treeindex->topLevelItem(3);
		
		QTreeWidgetItem *childitem = item->child(0);
		childitem->setText(7, query2.value(0).toString().section(username+" [", 1, 1).section("]", 0, 0));

		childitem = new QTreeWidgetItem;
		childitem = item->child(1);
		childitem->setText(7, query2.value(0).toString().section(username+" [", 1, 1).section("]", 0, 0));
		
		item->setExpanded(FALSE);
	}
}
//
void accountsfrm::loaddetails()
{
    QTreeWidgetItem* item = treeindex->currentItem();
    if(item!=0)
    {
		btncomplete->setEnabled(FALSE);
		if(item->parent() != 0)
		{
		    if(item->text(2) != "ietabarchiv")
		    {
				lblname->setText(item->text(0));
				lblaccountnr->setText(item->text(3));
				lblbank->setText(item->text(4));
				lblclearing->setText(item->text(5));
				lblcurrency->setText(item->text(6));	
				lblcurr1->setText("-");
				lblcurr2->setText("-");
				lblcurr3->setText("-");
				accountid = item->text(2); //lblkontoid->setText(item->text(2));
				if(item->text(7)=="11" || username == "Administrator")
				{
				    btnnew->setEnabled(TRUE);
				    btnedit->setEnabled(TRUE);
				    btndelete->setEnabled(TRUE);
				    btntransfer->setEnabled(TRUE);		
				}
				else
				{
				    btnnew->setEnabled(FALSE);
				    btnedit->setEnabled(FALSE);
				    btndelete->setEnabled(FALSE);
				    btntransfer->setEnabled(FALSE);
				}
				tot->setText("-");
				totin->setText("-");
				totout->setText("-");
				inittreemainaccounts();
				loadaccountdata(item->text(2));
		    }
		    else
		    {
				btnnew->setEnabled(FALSE);
				btnedit->setEnabled(FALSE);
				btndelete->setEnabled(FALSE);
				btntransfer->setEnabled(FALSE);
				    
				lblname->setText("-");
				lblaccountnr->setText("-");
				lblbank->setText("-");
				lblclearing->setText("-");
				lblcurrency->setText("-");
				lblcurr1->setText("-");
				lblcurr2->setText("-");
				lblcurr3->setText("-");
				tot->setText("-");
				totin->setText("-");
				totout->setText("-");
				accountid = "-";
				initmaintreeincexp();	
		
				if(item->text(7)=="11" || username == "Administrator")
				{
				    btncomplete->setEnabled(TRUE);
				    btnnew->setEnabled(TRUE);
				    btnedit->setEnabled(TRUE);
				    btndelete->setEnabled(TRUE);
				    btntransfer->setEnabled(TRUE);
 				    accountid = item->text(2);
	 				loadarchivdata(item->text(1));
				}
				else if(item->text(7)=="10")
				{
				    btnnew->setEnabled(FALSE);
				    btnedit->setEnabled(FALSE);
				    btndelete->setEnabled(FALSE);
				    btntransfer->setEnabled(FALSE);
 				    accountid = item->text(2);
	 				loadarchivdata(item->text(1));
				}
		    }
		}
		else
		{
		    lblname->setText("-");
		    lblaccountnr->setText("-");
		    lblbank->setText("-");
		    lblclearing->setText("-");
		    lblcurrency->setText("-");
		    lblcurr1->setText("-");
		    lblcurr2->setText("-");
		    lblcurr3->setText("-");
		    totin->setText("-");
		    totout->setText("-");
		    tot->setText("-");
		    accountid = "-";
	    
		    if(item->text(1) == "account")
		    {
				inittreemainoverview();
				int i;
				for(i=0;i<item->childCount();i++)
				{
					QTreeWidgetItem* tmpitem = item->child(i);

				    QTreeWidgetItem* mainlistitem = new QTreeWidgetItem(treemain);
				    mainlistitem->setText(0, tmpitem->text(1));
				    mainlistitem->setText(1, tmpitem->text(0));
				    mainlistitem->setText(2, tmpitem->text(3));
				    mainlistitem->setText(3, tmpitem->text(4));
				    mainlistitem->setText(4, tmpitem->text(5));
				    mainlistitem->setText(6, tmpitem->text(6));
				    
				    //Saldo berechnen
				    bool ok;
				    float saldo = 0;
				    QString qstr = "SELECT amount FROM "+tmpitem->text(2)+" ORDER BY ID DESC;"; 
				    QSqlQuery query(qstr);
				    while(query.next())
				    {
						saldo += query.value(0).toString().toFloat(&ok);
				    }
				    mainlistitem->setText(5, QString("%1").arg(saldo, 0, 'f',2));
				}
		    }
		    else
		    {
				initmaintreeincexp();
				lblname->setText(item->text(0));
				if(item->text(7) == "11" || username == "Administrator")
				{
				    btncomplete->setEnabled(TRUE);
				    btnnew->setEnabled(TRUE);
				    btnedit->setEnabled(TRUE);
				    btndelete->setEnabled(TRUE);
				    btntransfer->setEnabled(TRUE);
				    accountid = item->text(2);
				    loadincexpdata(item->text(1));
				    
				    tot->setText(calctotal(0));
				    totin->setText(calctotal(1));
				    totout->setText(calctotal(2));
				    lblcurr1->setText("CHF");
				    lblcurr2->setText("CHF");
				    lblcurr3->setText("CHF");
				}
				else if(item->text(7)=="10")
				{
				    btnnew->setEnabled(FALSE);
				    btnedit->setEnabled(FALSE);
				    btndelete->setEnabled(FALSE);
				    btntransfer->setEnabled(TRUE);
					accountid = item->text(2);
					loadincexpdata(item->text(1));
				    
				    tot->setText(this->calctotal(0));
				    totin->setText(this->calctotal(1));
				    totout->setText(this->calctotal(2));
				    lblcurr1->setText("CHF");
				    lblcurr2->setText("CHF");
				    lblcurr3->setText("CHF");
				}
				else
				{
				    btnnew->setEnabled(FALSE);
				    btnedit->setEnabled(FALSE);
				    btndelete->setEnabled(FALSE);
				    btntransfer->setEnabled(TRUE);
				}
		    }
		}
    }
}
//
void accountsfrm::loadaccountdata(QString ID)
{
    treemain->clear();
    QString qstr = QString("SELECT ID, date, refnr, address, code, description, amount FROM %1 ORDER BY date DESC;").arg(ID);
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		bool ok;
		float saldo = 0;
		while(query.next())
		{
		    QTreeWidgetItem* item = new QTreeWidgetItem(treemain);
		    item->setText(0, query.value(0).toString());
		    item->setText(1, query.value(1).toString().section("-", 2, 2)+"."+query.value(1).toString().section("-", 1, 1)+"."+query.value(1).toString().section("-", 0, 0));
		    item->setText(2, query.value(2).toString());
		    item->setText(3, query.value(3).toString().section(" (", 0, 0));
		    item->setText(4, query.value(4).toString());
		    item->setText(5, query.value(5).toString());
		    item->setText(6, query.value(6).toString());
		    saldo += query.value(6).toString().toFloat(&ok);
		    item->setText(7, QString("%1").arg(saldo, 0, 'f',2));
		}
    }
}
//
void accountsfrm::loadincexpdata(QString type)
{
    treemain->clear();
    QString qstr = "SELECT state, ID, date, refnr, address, code, description, amount FROM ietab WHERE `type`= '"+type+"' ORDER BY date DESC;";
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		while(query.next())
		{
		    QTreeWidgetItem* item = new QTreeWidgetItem(treemain);

		    if(query.value(0).toString()=="1")
		    	item->setCheckState(1, Qt::Checked);
		    else
		    	item->setCheckState(1, Qt::Unchecked);
		    	
		    item->setText(0, query.value(1).toString());
		    item->setText(2, query.value(2).toString().section("-", 2, 2)+"."+query.value(2).toString().section("-", 1, 1)+"."+query.value(2).toString().section("-", 0, 0));
		    item->setText(3, query.value(3).toString());
		    item->setText(4, query.value(4).toString().section(" (", 0, 0));
		    item->setText(5, query.value(5).toString());
		    item->setText(6, query.value(6).toString());
		    item->setText(7, query.value(7).toString());
		    item->setText(8, "("+query.value(4).toString().section(" (", 1, 1));
		}
    }
}
//
void accountsfrm::loadarchivdata(QString type)
{
    treemain->clear();
    QString qstr = "SELECT state, ID, date, refnr, address, code, description, amount FROM ietabarchiv WHERE `type`='"+type+"' ORDER BY date ASC;"; 
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		bool ok;
		float saldo = 0;
		while(query.next())
		{
		    QTreeWidgetItem* item = new QTreeWidgetItem(treemain);
		    item->setText(0, "Ok");
		    item->setIcon(0, QIcon(QString::fromUtf8(":/button_ok_small.png")));
		    item->setText(1, query.value(1).toString());
		    item->setText(2, query.value(2).toString().section("-", 2, 2)+"."+query.value(2).toString().section("-", 1, 1)+"."+query.value(2).toString().section("-", 0, 0));
		    item->setText(3, query.value(3).toString());
		    item->setText(4, query.value(4).toString().section(" (", 0, 0));
		    item->setText(5, query.value(5).toString());
		    item->setText(6, query.value(6).toString());
		    item->setText(7, query.value(7).toString());
		    item->setText(8, "("+query.value(4).toString().section(" (", 1, 1));
		    saldo += query.value(7).toString().toFloat(&ok);
		}
	    tot->setText(QString("%1").arg(saldo, 0, 'f',2));
	    lblcurr1->setText("CHF");
	    lblcurr2->setText("CHF");
	    lblcurr3->setText("CHF");
    }
}
//
QString accountsfrm::calctotal(int type)
{
    float ein = 0;
    float aus = 0;
    bool ok;
    QString qstr = "SELECT type, amount FROM ietab;";
    QString return_value = "0.00";
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		while(query.next())
		{
		    if(query.value(0) == "inc")
				ein += query.value(1).toString().toFloat(&ok);
		    else
				aus += query.value(1).toString().toFloat(&ok);
		}
    }
	switch(type) 
    {
	    case 0:
			return_value = QString("%1").arg(ein - aus, 0, 'f',2);
			break;
	    case 1:
			return_value =  QString("%1").arg(ein, 0, 'f',2);
			break;	    
	    case 2:
			return_value = QString("%1").arg(aus, 0, 'f',2);
		    break;
   }
   return return_value;
}
//
void accountsfrm::contmenu()
{
    QMenu* contextMenu = new QMenu( this );
    Q_CHECK_PTR( contextMenu );

    QAction* newentry = new QAction( tr("&New Entry"), this );
	connect(newentry , SIGNAL(triggered()), this, SLOT(newentry()));
	contextMenu->addAction(newentry);

    QAction* editentry = new QAction( tr("&Edit Entry"), this );
	connect(editentry , SIGNAL(triggered()), this, SLOT(editentry()));
	contextMenu->addAction(editentry);
	
    QAction* deleteentry = new QAction( tr("&Delete Entry"), this );
	connect(deleteentry , SIGNAL(triggered()), this, SLOT(deleteentry()));
	contextMenu->addAction(deleteentry);
		
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}
//
void accountsfrm::newentry()
{
    accountseditfrm *efrm = new accountseditfrm;
    efrm->init();
    efrm->setdbID(accountid);
    efrm->date1->setDate(QDate::currentDate());
    efrm->setWindowTitle(tr("New Entry..."));
    if(accountid == "ietab")
    {
		QTreeWidgetItem* tmpitem = treeindex->currentItem();
		if(tmpitem->text(1) == "inc")
		    efrm->cmbincexp->setCurrentIndex(0);
		else
		    efrm->cmbincexp->setCurrentIndex(1);
	    }    
    else
    {
		efrm->lbl_8->setVisible(FALSE);
		efrm->cmbincexp->setVisible(FALSE);
    }
    if(efrm->exec())
	    loaddetails();
}
//
void accountsfrm::editentry()
{
    QTreeWidgetItem* item = treemain->currentItem();
    if(item!=0 && accountid != "-")
    {
		accountseditfrm *editfrm = new accountseditfrm;
		editfrm->init();	
		editfrm->setWindowTitle(tr("Edit Entry..."));
	    editfrm->loadentry(accountid+"_"+item->text(0));
	    editfrm->txtRefNr->setReadOnly(TRUE);
	    editfrm->lbl_8->setVisible(FALSE);
	    editfrm->cmbincexp->setVisible(FALSE);
		if(editfrm->exec())
		    loaddetails();
    }
}
//
void accountsfrm::deleteentry()
{
    QTreeWidgetItem* item =  treemain->currentItem();
    if(item != 0 && accountid != "-")
    {    
    	int resp;
		if(accountid=="ietab")
			resp = QMessageBox::information(this, tr("Delete Entry..."), tr("Delete entry %1 ?").arg(item->text(3)), QMessageBox::Yes, QMessageBox::No);
		else
			resp = QMessageBox::information(this, tr("Delete Entry..."), tr("Delete entry %1 ?").arg(item->text(2)), QMessageBox::Yes, QMessageBox::No);
		if(resp == QMessageBox::Yes)
		{
		    QString qstr = QString("DELETE FROM `%1` WHERE `ID` = '%2';").arg(accountid).arg(item->text(0));
		    QSqlQuery query(qstr);
		    loaddetails();
		}
    }
}
//
void accountsfrm::completeitems()
{
    accountscomplfrm *cfrm = new accountscomplfrm;
    cfrm->init();
    if(cfrm->exec())
    {
		progfrm *pfrm = new progfrm;
		pfrm->setFixedSize(pfrm->width(), pfrm->height());
		pfrm->show();
	
	if(cfrm->chkbox_3->isChecked()) //complete all
	{
	    cfrm->chkbox_1->setChecked(TRUE);
	    cfrm->chkbox_2->setChecked(TRUE);
	}
	
	if(cfrm->chkbox_2->isChecked())//check all
	{
	    //search existing accounts
	    int i;
	    
	    QString qstr1 = "SELECT ID, name, description, accountnr, bank, blz, currency, users FROM accounttab WHERE users LIKE '%"+username+" [%' AND name LIKE '%account%';"; 
	    QSqlQuery query1(qstr1);
	    if ( query1.isActive())
	    {
			while(query1.next())
			{
			    pfrm->txtcomments->setText(tr("Search entries, who can be completed in account '%1'...").arg(query1.value(2).toString()));
			    pfrm->progbar->setMaximum(treemain->topLevelItemCount());			
				for(i=0;i<treemain->topLevelItemCount();i++)
				{
				    pfrm->progbar->setValue(i+1);
					QTreeWidgetItem* item = treemain->topLevelItem(i);
				    QString qstr2 = QString("SELECT ID, date, refnr, address, code, description, amount FROM "+query1.value(1).toString()+" WHERE `refnr` = '%1' AND `amount` = '%2';").arg(item->text(3)).arg(item->text(7));
				    QSqlQuery query2(qstr2);
				    if(query2.size() > 0)
						item->setCheckState(1, Qt::Checked);	
				}
			}
	    }
	}    
	
	if(cfrm->chkbox_1->isChecked()) //completed
	{
	    int i;
	    pfrm->txtcomments->setText(tr("Eintries will be completed..."));
	    pfrm->progbar->setMaximum(treemain->topLevelItemCount());
	    QTreeWidgetItem *typeitem = treeindex->currentItem();
	    for(i=0;i<treemain->topLevelItemCount();i++)
	    {
			pfrm->progbar->setValue(i+1);
			QTreeWidgetItem *item = treemain->topLevelItem(i);
			if(item->checkState(1) == Qt::Checked)
			{
			    QString qstr = QString("INSERT INTO `ietabarchiv` (`ID`, `refnr`, `type`, `state`, `date`, `address`, `description`, `code`, `amount`) VALUES (NULL, '%1', '%2', '1', '%4', '%5', '%6', '%7', '%8');").arg(item->text(3)).arg(typeitem->text(1)).arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(item->text(4)+" "+item->text(8)).arg(item->text(6)).arg(item->text(5)).arg(item->text(7));
			    QSqlQuery query1(qstr);
			    qstr = QString("DELETE FROM `ietab` WHERE `ID` = '%2';").arg(item->text(0));
			    QSqlQuery query2(qstr);
			}
	    }
	}
	pfrm->close();	    
	if(cfrm->chkbox_1->isChecked())
	    loaddetails();
    }
}
//
void accountsfrm::datatransfer()
{
    QTreeWidgetItem* item = treeindex->currentItem();    
    if(item!=0)
    {    
		accountsimpexpfrm *impexp = new accountsimpexpfrm;
		impexp->setFixedSize(impexp->width(), impexp->height());
		if(item->text(7)!="11" || username != "Administrator")
		{
		    if(item->text(2).left(7) != "account")
				impexp->rdbtn_1->setEnabled(FALSE);
		}
		if(impexp->exec())
		{
		    if(impexp->rdbtn_1->isChecked())
		    {
				esrimport();
				loaddetails();
		    }
		    if(impexp->rdbtn_2->isChecked())
				csvexport();
		}
    }
}
//
void accountsfrm::csvexport()
{
    QString filestr = QFileDialog::getSaveFileName ( this, tr ( "Save file as..." ),
	                   QDir::homePath(),
	                   tr("CSV-File (*.csv)") );
    if(filestr.mid(filestr.length()-4).toLower() != ".csv")
		filestr += ".csv";
    if(filestr!="")
    {   
		int i, ii;
		progfrm *pfrm = new progfrm;
		pfrm->setFixedSize(pfrm->width(), pfrm->height());
		pfrm->txtcomments->setText(tr("Data will be exported..."));
		pfrm->progbar->setMaximum(treemain->topLevelItemCount());
		pfrm->show();        
    
		QFile file(filestr);
		if(file.open(QIODevice::WriteOnly))	    
		{
		    QTextStream stream(&file);
			for(i=0;i<treemain->topLevelItemCount();i++)
			{
			    QTreeWidgetItem *item = treemain->topLevelItem(i);
			    for(ii=0;ii<treemain->columnCount()-1;ii++)
					stream << "\"" << item->text(ii) << "\";";
			    stream << item->text(ii+1) << "\n";
			    pfrm->progbar->setValue(i+1);
			}
		    file.close();
		    pfrm->close();
		}
    }
}
//
void accountsfrm::esrimport()
{
    QString filestr = QFileDialog::getOpenFileName ( this, tr("Open File..."),
	                   QDir::homePath(),
	                   tr("ESR-File (*.*)") );
    if(filestr!="")
    {   
		int i;
		progfrm *pfrm = new progfrm;
		pfrm->setFixedSize(pfrm->width(), pfrm->height());
		pfrm->txtcomments->setText(tr("Data will be imported..."));
		pfrm->show();
    
		QFile file(filestr);
		if(file.open( QIODevice::ReadOnly ) )
		{
		    QTextStream stream( &file );
		    QStringList lines;
	    
		    while(!stream.atEnd())
				lines << stream.readLine();
		    file.close();
	    
		    pfrm->progbar->setMaximum(lines.count());
		    QString negamount;
		    QString refnr, address, adrID, comments, amount, date;
		    for(i=0;i<lines.count()-1;i++)
		    {
				refnr = lines[i].mid(19, 20);
				QString qstr = QString("SELECT address FROM ietab WHERE `refnr` = '%1';").arg(lines[i].mid(24, 15));
				QSqlQuery query(qstr);
				if(query.size()>0)
				{
				    query.next();
				    address = query.value(0).toString().section(" (", 0, 0);
				    adrID = query.value(0).toString().section(" (", 1, 1).section(")", 0, 0);
				    refnr  = lines[i].mid(24, 15);
				    comments = tr("Payment for Invoice: ")+lines[i].mid(19, 20);
				}
				else
				{
				    address = tr("Unknow");
				    adrID = "";
				    comments  = tr("Unknow");
				}	
				if(lines[i].mid(1, 2) == "05" || lines[i].mid(1, 2) == "15")
				    negamount = "-";
				else
				    negamount = "";		
				amount = negamount + QString("%1").arg(lines[i].mid(40, 9).toDouble()/100, 0, 'f', 2);
				date = "20" + lines[i].mid(71, 6);
				date = date.left(4)+"-"+date.mid(4,2)+"-"+date.right(2);
				if(lines[i].mid(97, 3) != "000")
				    comments = comments+"\n"+tr("Post office taxes: %1").arg(lines[i].mid(97, 3).toDouble()/100, 0, 'f', 2);
			
				qstr = QString("INSERT INTO `%1` (`ID`, `date`, `refnr`, `address`, `description`, `code`, `amount`) VALUES (NULL, '%2', '%3', '%4', '%5', '', '%7');").arg(accountid).arg(date).arg(refnr).arg(address+" ("+adrID+")").arg(comments).arg(amount);
				QSqlQuery queryadd(qstr);
				pfrm->progbar->setValue(i);
		    }
		    pfrm->close();
		}
    }
}
//
void accountsfrm::print()
{
    printfrm *pfrm = new printfrm;
    pfrm->rdbtn_2->setEnabled(FALSE);
    pfrm->rdbtn_4->setEnabled(FALSE);
    if(pfrm->exec())
    {
		if(pfrm->rdbtn_1->isChecked())
		    this->writetexfile(0);
		else if(pfrm->rdbtn_3->isChecked())
		    this->writetexfile(2);
    }
}
//
void accountsfrm::writetexfile(int type)
{
    int i, ii;
    QString tabhead = "";
    for(i=2;i<treemain->columnCount();i++)
		tabhead += treemain->headerItem()->text(i) += " & ";
    tabhead = tabhead.mid(0, tabhead.length()-3);
    QString tabcontent = "";
    
    switch(type)
    {
	    case 0:
			for(i=0;i<treemain->topLevelItemCount();i++)
			{
			    QTreeWidgetItem *item = treemain->topLevelItem(i);
			    for(ii=2;ii<treemain->columnCount();ii++)
					tabcontent += item->text(ii).replace("&", "").replace("_", "\\_") + " & ";
			    tabcontent = tabcontent.mid(0, tabcontent.length()-3) + "\\\\ \\hline \n";
			}
			break;
	    case 2:
			for(i=0;i<treemain->topLevelItemCount();i++)
			{
			    QTreeWidgetItem *item = treemain->topLevelItem(i);
			    if(item->isSelected())
			    {
					for(ii=2;ii<treemain->columnCount();ii++)
					    tabcontent += item->text(ii).replace("&", "").replace("_", "\\_") + " & ";
					tabcontent = tabcontent.mid(0, tabcontent.length()-3) + "\\\\ \\hline \n";
			    }
			}
			break;
	}

    QString templatestr = loadtemplatedata();
    QTime now = QTime::currentTime();
	QDate today = QDate::currentDate();
    QFile output(QDir::homePath()+"/.first4/tmp/"+username+"-"+today.toString("yyyyMMdd")+now.toString("hhmmsszzz")+".tex");
		
	if ( output.open( QIODevice::WriteOnly ) )
	{
	    QTextStream outstream( &output );
		templatestr = templatestr.replace("+++TITLE+++", lblname->text());
		templatestr = templatestr.replace("+++TABHEAD+++", tabhead);
		templatestr = templatestr.replace("+++TABCONTENT+++", tabcontent);
		templatestr = templatestr.replace("+++ACCOUNTNR+++", lblaccountnr->text());
		templatestr = templatestr.replace("+++BANK+++", lblbank->text());
		templatestr = templatestr.replace("+++CLEARING+++", lblclearing->text());
		templatestr = templatestr.replace("+++CURRENCY+++", lblcurrency->text());
		templatestr = templatestr.replace("+++AMOUNT+++", tot->text());
		templatestr = templatestr.replace("+++IN+++", totin->text());
		templatestr = templatestr.replace("+++OUT+++", totout->text());
		outstream << templatestr << "\n";
	    output.close();
	} else {
	    QMessageBox::critical(0,"Error...",tr("Can't write ouputfile!"));
	}
    
    //converting text to dvi
    vars v;
    QString tool = v.get_tool("TEX2DVI");
    QProcess *procdvi = new QProcess( this );
    QStringList args;
    args << "-output-directory="+QDir::homePath()+"/.first4/tmp/" << output.fileName();
    procdvi->start(tool, args);
    if ( procdvi->exitStatus() == QProcess::CrashExit )
		QMessageBox::critical(0,"Error...", tr("Error during convertion from TEXT to DVI!"));
    
	tool = v.get_tool("DVIVIEWER");
    QProcess *procshow = new QProcess( this );
    args.clear();
    args << output.fileName().replace(".tex", ".dvi");
    procshow->start(tool, args);
    if ( procdvi->exitStatus() == QProcess::CrashExit ) 
		QMessageBox::critical(0,"Error...", tr("Can't find DVI-File."));
}
//
QString accountsfrm::loadtemplatedata()
{
	QString answ;
	QSqlQuery query("SELECT data FROM templatestab WHERE `name`='sys_ieoverview';");
	if ( query.isActive())
	{
		query.next();
		answ = query.value(0).toString();
	}
	else
	{
		QSqlError qerror = query.lastError();
		QMessageBox::warning ( 0, tr ( "Can't load template data..." ), qerror.text() );
	}
	return answ;
}

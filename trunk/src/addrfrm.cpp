#include <QMessageBox>
#include <QCloseEvent>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>
#include <QInputDialog>
#include <QDate>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMenu>
//
#include "addrfrm.h"
#include "vars.h"
#include "doceditfrm.h"
#include "addrimpexpfrm.h"
//
QString lastadrtab, rev_currency, lastaddr, wintitle;
QStringList adrnamelist, rightslist;
//
extern QString username, templatefolder, docfolder, dbname;
//
addrfrm::addrfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
void addrfrm::init()
{
    vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
        if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
   	}
   	
    adrnamelist.clear();
    rightslist.clear();
    
    mainlistview->header()->setResizeMode(QHeaderView::Interactive);
    mainlistview->headerItem()->setText(0, QApplication::translate("addrfrm", "Company", 0, QApplication::UnicodeUTF8));
    mainlistview->headerItem()->setText(1, QApplication::translate("addrfrm", "Lastname", 0, QApplication::UnicodeUTF8));
    mainlistview->headerItem()->setText(2, QApplication::translate("addrfrm", "Firstname", 0, QApplication::UnicodeUTF8));
    mainlistview->headerItem()->setText(3, QApplication::translate("addrfrm", "ID", 0, QApplication::UnicodeUTF8));
    mainlistview->hideColumn(3);

	int i;
	QStringList colwidth = v.loadcolwidth(this->objectName(), "mainlistview" );
	if ( colwidth.size() > 0	)
	{
		for(i=0; i<colwidth.size(); i++)
			mainlistview->setColumnWidth(i, colwidth[i].toInt());
	}
    
    lbluser->setText(username);
    QString permissions;
    QString qstr = QString("SELECT * FROM directories WHERE users LIKE '%%1 [1%';").arg(username);
    QSqlQuery query1(qstr);
    if ( query1.isActive())
    {
		while ( query1.next())
		{
		    cmbdir->addItem(query1.value(2).toString());
		    adrnamelist.append(query1.value(1).toString());
		    rightslist.append(query1.value(3).toString().section(username, 1, 1).section(" ", 1, 1));
		}
    }
    
    QSqlQuery query2("SELECT value FROM `maincfgtab` WHERE `var` = 'def_currency';");
    if(query2.isActive())
    {
		query2.next();
		rev_currency = query2.value(0).toString();
    }
    
    listdocs->headerItem()->setText(0, QApplication::translate("addrfrm", "Clientdata", 0, QApplication::UnicodeUTF8));
    listdocs->headerItem()->setText(1, QApplication::translate("addrfrm", "docID", 0, QApplication::UnicodeUTF8));
    listdocs->headerItem()->setText(2, QApplication::translate("addrfrm", "data", 0, QApplication::UnicodeUTF8));
    listdocs->headerItem()->setText(3, QApplication::translate("addrfrm", "status", 0, QApplication::UnicodeUTF8));
	listdocs->hideColumn(1);
	listdocs->hideColumn(2);
	listdocs->hideColumn(3);

    listproc->headerItem()->setText(0, QApplication::translate("addrfrm", "State", 0, QApplication::UnicodeUTF8));
    listproc->headerItem()->setText(1, QApplication::translate("addrfrm", "Description", 0, QApplication::UnicodeUTF8));
    listproc->headerItem()->setText(2, QApplication::translate("addrfrm", "Date", 0, QApplication::UnicodeUTF8));
    listproc->setColumnWidth(0, 100);
    listproc->setColumnWidth(2, 100);
    listproc->header()->setStretchLastSection(FALSE);
    listproc->header()->setResizeMode (1, QHeaderView::Stretch);
    
    connect(cmbdir, SIGNAL(activated(int)), this, SLOT(loadaddrs()));
    connect(mainlistview, SIGNAL(itemClicked ( QTreeWidgetItem*, int)), this, SLOT(loadaddrdetail()));
    connect(listdocs, SIGNAL(itemClicked ( QTreeWidgetItem*, int)), this, SLOT(loaddocsdata()));
    connect(listproc, SIGNAL(itemDoubleClicked ( QTreeWidgetItem*, int)), this, SLOT(openauftrag()));
    connect(btnadrcust1, SIGNAL(released()), this, SLOT(changecust1()));
    connect(btnadrcust2, SIGNAL(released()), this, SLOT(changecust2()));
    connect(btnadrcust3, SIGNAL(released()), this, SLOT(changecust3()));
    connect(btnadrcust4, SIGNAL(released()), this, SLOT(changecust4()));
    connect(btnadrcust5, SIGNAL(released()), this, SLOT(changecust5()));
    connect(btnnew, SIGNAL(released()), this, SLOT(newaddr()));
    connect(btnsave, SIGNAL(released()), this, SLOT(saveaddr()));
    connect(btndelete, SIGNAL(released()), this, SLOT(deladdr()));
    connect(btnclear, SIGNAL(released()), this, SLOT(clearsearch()));
    connect(btnsearch, SIGNAL(released()), this, SLOT(search()));
    connect(txtsearch, SIGNAL(returnPressed()), this, SLOT(search()));
    connect(btnprint, SIGNAL(released()), this, SLOT(printaddr()));
    connect(btnimpexp, SIGNAL(released()), this, SLOT(impexp()));
    connect(listdocs, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));
    connect(mainlistview, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenuaddr()));
    
    wintitle = this->windowTitle();
    
    if(cmbdir->count() > 0)
    {
		lastadrtab = "";
		lastaddr = "";
		loadaddrs();
    }
}
//
void addrfrm::closeEvent(QCloseEvent* ce )
{
	QSqlDatabase::database().rollback();
	int cols;
	QStringList colwidth;
	for(cols=0; cols < mainlistview->columnCount(); cols++)
			colwidth << QString("%1").arg(mainlistview->columnWidth(cols));
	vars v;
	v.savecolwidth(this->objectName(), "mainlistview", colwidth);
	v.unlockrow(lastaddr.section("_", 0, 0), lastaddr.section("_", 1, 1));
	
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void addrfrm::checkrights()
{
    if(lbluser->text() == "Administrator" || rightslist[cmbdir->currentIndex()]=="[11]")
    {
		adr3->setReadOnly(FALSE);
		adr4->setReadOnly(FALSE);
		adr5->setReadOnly(FALSE);
		adr6->setReadOnly(FALSE);
		adr7->setReadOnly(FALSE);
		adr8->setReadOnly(FALSE);
		adr9a->setReadOnly(FALSE);
		adr9b->setReadOnly(FALSE);
		adr31->setReadOnly(FALSE);
		adr10->setReadOnly(FALSE);
		adr11->setReadOnly(FALSE);
		adr12->setReadOnly(FALSE);
		adr13->setReadOnly(FALSE);
		adr14->setReadOnly(FALSE);
		adr15->setReadOnly(FALSE);
		adr16->setReadOnly(FALSE);
		adr17->setReadOnly(FALSE);
		adr18->setReadOnly(FALSE);
		adr19->setReadOnly(FALSE);
		adr22->setReadOnly(FALSE);
		adr23->setReadOnly(FALSE);
		adr24->setReadOnly(FALSE);
		adr25->setReadOnly(FALSE);
		adr26->setReadOnly(FALSE);
		adr27->setReadOnly(FALSE);
		adr28->setReadOnly(FALSE);
	
		btnnew->setEnabled(TRUE);
		btnsave->setEnabled(TRUE);
		btndelete->setEnabled(TRUE);
		btncancel->setEnabled(TRUE);
		btnimpexp->setEnabled(TRUE);
	
		btnadrcust1->setEnabled(TRUE);
		btnadrcust2->setEnabled(TRUE);
		btnadrcust3->setEnabled(TRUE);
		btnadrcust4->setEnabled(TRUE);
		btnadrcust5->setEnabled(TRUE);	
    } else {
		adr3->setReadOnly(TRUE);
		adr4->setReadOnly(TRUE);
		adr5->setReadOnly(TRUE);
		adr6->setReadOnly(TRUE);
		adr7->setReadOnly(TRUE);
		adr8->setReadOnly(TRUE);
		adr9a->setReadOnly(TRUE);
		adr9b->setReadOnly(TRUE);
		adr31->setReadOnly(TRUE);
		adr10->setReadOnly(TRUE);
		adr11->setReadOnly(TRUE);
		adr12->setReadOnly(TRUE);
		adr13->setReadOnly(TRUE);
		adr14->setReadOnly(TRUE);
		adr15->setReadOnly(TRUE);
		adr16->setReadOnly(TRUE);
		adr17->setReadOnly(TRUE);
		adr18->setReadOnly(TRUE);
		adr19->setReadOnly(TRUE);
		adr22->setReadOnly(TRUE);
		adr23->setReadOnly(TRUE);
		adr24->setReadOnly(TRUE);
		adr25->setReadOnly(TRUE);
		adr26->setReadOnly(TRUE);
		adr27->setReadOnly(TRUE);
		adr28->setReadOnly(TRUE);
	
		btnnew->setEnabled(FALSE);
		btnsave->setEnabled(FALSE);
		btndelete->setEnabled(FALSE);
		btncancel->setEnabled(FALSE);
		btnimpexp->setEnabled(FALSE);
	
		btnadrcust1->setEnabled(FALSE);
		btnadrcust2->setEnabled(FALSE);
		btnadrcust3->setEnabled(FALSE);
		btnadrcust4->setEnabled(FALSE);
		btnadrcust5->setEnabled(FALSE);
    }
}
//
void addrfrm::loadaddrs()
{
	this->setWindowTitle(wintitle);
	vars v;
	v.unlockrow(lastaddr.section("_", 0, 0), lastaddr.section("_", 1, 1));
    if(cmbdir->currentText() != lastadrtab)
    { 
		checkrights();
		QString connstr = "SELECT ID, company, lastname, firstname FROM ";
		connstr += adrnamelist[cmbdir->currentIndex()];
		connstr += ";";
		mainlistview->clear();
		QSqlQuery query(connstr);
		if ( query.isActive())
		{
		    progbar->setValue(0);
		    progbar->setMaximum(query.size());
		    int count = 0;
		    while ( query.next())
		    {
				progbar->setValue(++count);
				QTreeWidgetItem *item = new QTreeWidgetItem(mainlistview);
				item->setText(0, query.value(1).toString());
				item->setText(1, query.value(2).toString());
				item->setText(2, query.value(3).toString());
				item->setText(3, query.value(0).toString());
		    }
		}
	lastadrtab = cmbdir->currentText();
    }
}
//
void addrfrm::loadaddrdetail()
{
	vars v;
	v.unlockrow(lastaddr.section("_", 0, 0), lastaddr.section("_", 1, 1));
    QTreeWidgetItem *tmpitem = mainlistview->currentItem();
    if(tmpitem!=0 && tmpitem->text(3) != "")
    {
		QString qstr;
		QString userlock = v.checklockstate(adrnamelist[cmbdir->currentIndex()], tmpitem->text(3));
		if(userlock != "")
		{
			this->setWindowTitle(wintitle+QString(" ( Locked by User: %1 )").arg(userlock));
			btnsave->setEnabled(FALSE);
			btndelete->setEnabled(FALSE);
			qstr = QString("SELECT ID, clientid, company, lastname, firstname, nameadd, pobox, street_nr, location, zip, country, tel_b, tel_direct , fax_b, tel_p, fax_p, mobile, email1, email2, email3, homepage, revenueaj, revenuelj, discount, comments, custom1, custom2, custom3, custom4, custom5, created, modified FROM %1 WHERE ID='%2';").arg(adrnamelist[cmbdir->currentIndex()]).arg(tmpitem->text(3));
		}
		else
		{
			this->setWindowTitle(wintitle);
			qstr = QString("SELECT ID, clientid, company, lastname, firstname, nameadd, pobox, street_nr, location, zip, country, tel_b, tel_direct , fax_b, tel_p, fax_p, mobile, email1, email2, email3, homepage, revenueaj, revenuelj, discount, comments, custom1, custom2, custom3, custom4, custom5, created, modified FROM %1 WHERE ID='%2' FOR UPDATE;").arg(adrnamelist[cmbdir->currentIndex()]).arg(tmpitem->text(3));
			v.lockrow(adrnamelist[cmbdir->currentIndex()], tmpitem->text(3));
			btnsave->setEnabled(TRUE);
			btndelete->setEnabled(TRUE);
		}
	
		QSqlQuery query(qstr);
		if(query.isActive())
		{
		    progbar->setValue(0);
		    query.next();
		    adr1->setText(query.value(0).toString());
		    adr2->setText(query.value(1).toString());
		    adr3->setText(query.value(2).toString());
		    adr5->setText(query.value(3).toString());
		    adr4->setText(query.value(4).toString());
		    adr6->setText(query.value(5).toString());
		    adr7->setText(query.value(6).toString());
		    adr8->setText(query.value(7).toString());
		    adr9b->setText(query.value(8).toString());
		    adr9a->setText(query.value(9).toString());
		    adr31->setText(query.value(10).toString());
		    adr10->setText(query.value(11).toString());
		    adr11->setText(query.value(12).toString());
		    adr12->setText(query.value(13).toString());
		    adr13->setText(query.value(14).toString());
		    adr14->setText(query.value(15).toString());
		    adr15->setText(query.value(16).toString());
		    adr16->setText(query.value(17).toString());
		    adr17->setText(query.value(18).toString());
		    adr18->setText(query.value(19).toString());
		    adr19->setText(query.value(20).toString());	
		    progbar->setValue(25);
		
			listrevenue->clear();
	    	QTreeWidgetItem *item = new QTreeWidgetItem(listrevenue);
	    	item->setText(0, query.value(21).toString().section(";", 0, 0));
	    	item->setText(1, query.value(21).toString().section(";", 1, 1));
	    	int i;
		    for(i=0; i<query.value(22).toString().count("#");i++)
		    {
		    	QTreeWidgetItem *item = new QTreeWidgetItem(listrevenue);
		    	item->setText(0, query.value(22).toString().section("#", i+1, i+1).section(";", 0, 0));
		    	item->setText(1, query.value(22).toString().section("#", i+1, i+1).section(";", 1, 1));
		    }
		    progbar->setValue(50);
	    
		    adr22->setText(query.value(23).toString());
		    if(adr22->text()=="")
		    	adr22->setText("0");
		    	
		    adr23->setText(query.value(24).toString());		
		
		    QStringList custom = query.value(25).toString().split(":#:");
		    if(custom.count()>1)
		    {
				lbladr24->setText(custom[0]);
				adr24->setText(custom[1]);
	    	}
		    custom = query.value(26).toString().split(":#:");
		    if(custom.count()>1)
		    {
			    lbladr25->setText(custom[0]);
			    adr25->setText(custom[1]);
	    	}
		    custom = query.value(27).toString().split(":#:");
		    if(custom.count()>1)
		    {
		    	lbladr26->setText(custom[0]);
			    adr26->setText(custom[1]);
		    }
		    custom = query.value(28).toString().split(":#:");
		    if(custom.count()>1)
		    {
		    	lbladr27->setText(custom[0]);
			    adr27->setText(custom[1]);
		    }
		    custom = query.value(29).toString().split(":#:");
		    if(custom.count()>1)
		    {
		    	lbladr28->setText(custom[0]);
			    adr28->setText(custom[1]);
		    }
		
		    progbar->setValue(75);
		
		    adr29->setText(query.value(30).toString());
		    adr30->setText(query.value(31).toString());
		    progbar->setValue(100);
		}
		
		loaddocs(adr1->text());
	
		if(tmpitem->text(3).mid(0,1)!="*")
		    loadauftr(tmpitem->text(3));
		    
		lastaddr = adrnamelist[cmbdir->currentIndex()] + "_" +tmpitem->text(3);
	}
}
//
void addrfrm::loaddocs(QString dbID)
{
    listdocs->clear();
    QTreeWidgetItem *itemof = new QTreeWidgetItem(listdocs);
    itemof->setText(0, tr("Offers"));
    QTreeWidgetItem *itemab = new QTreeWidgetItem(listdocs);
    itemab->setText(0, tr("Order confirmations"));
    QTreeWidgetItem *itemli = new QTreeWidgetItem(listdocs);
    itemli->setText(0, tr("Deliverynotes"));
    QTreeWidgetItem *itemre = new QTreeWidgetItem(listdocs);
    itemre->setText(0, tr("Invoices"));

    QString connstr = QString("SELECT ID, doctyp, date, client, comments, amount, docID FROM docs WHERE client = '%1_%2';").arg(adrnamelist[cmbdir->currentIndex()].mid(3)).arg(dbID);
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		while(query.next())
		{	    
		    QTreeWidgetItem *itemdoc = new QTreeWidgetItem();
		    if(query.value(1).toString()== "1 offer")
		    {
				itemdoc->setText(0, tr("Offer %1 - %2").arg(query.value(7).toString()).arg(query.value(2).toString()));
				itemdoc->setText(1, query.value(0).toString());
				itemof->addChild(itemdoc);
		    }
		    else if(query.value(1).toString()=="2 orderconf")
		    {
				itemdoc->setText(0, tr("Order confirmation %1 - %2").arg(query.value(7).toString()).arg(query.value(2).toString()));
				itemdoc->setText(1, query.value(0).toString());
				itemab->addChild(itemdoc);
		    }
		    else if(query.value(1).toString()=="3 deliverynote")
		    {
				itemdoc->setText(0, tr("Deliverynote %1 - %2").arg(query.value(7).toString()).arg(query.value(2).toString()));
				itemdoc->setText(1, query.value(0).toString());
				itemli->addChild(itemdoc);
		    }
		    else if(query.value(1).toString()=="4 invoice")
		    {
				QString status = "";
				//Prfe ob Rechnung bezahlt
				QString connstr2 = "SELECT status, date FROM ietabarchiv WHERE `refnr`='"+query.value(6).toString()+"' AND `address` LIKE '%("+adrnamelist[cmbdir->currentIndex()].mid(3)+"_"+dbID+")%';";
				QSqlQuery query2(connstr2);
				query2.next();
				if(query2.size()>0)
				    status = tr("Paid ")+query2.value(1).toString().section("-", 2, 2)+"."+query2.value(1).toString().section("-", 1, 1)+"."+query2.value(1).toString().section("-", 0, 0);
				else
				{
				    //Prfe ob Rechnung Pendent
				    QString connstr3 = "SELECT status, date FROM ietab WHERE `refnr`='"+query.value(6).toString()+"' AND `address` LIKE '%("+adrnamelist[cmbdir->currentIndex()].mid(3)+"_"+dbID+")%';";
				    QSqlQuery query3(connstr3);
				    query3.next();
				    if(query2.size()>0)
						status = tr("Pendent");
				    else
						status = tr("Completed");
				    ///
				}
			    
				itemdoc->setText(0, tr("Invoice %1 - %2").arg(query.value(6).toString()).arg(query.value(2).toString()));
				itemdoc->setText(1, query.value(0).toString());
				itemdoc->setText(3, status);		    
				itemre->addChild(itemdoc);
		    }
		}
    }
}
//
void addrfrm::loaddocsdata()
{
    QTreeWidgetItem *itemdoc = listdocs->currentItem();
    if(itemdoc->text(1)!="")
    {
		while(itemdoc->childCount()>0)
		    itemdoc->takeChild(0);
		if(itemdoc->text(3)!="")
		{
		    QTreeWidgetItem *statusitem = new QTreeWidgetItem(itemdoc, 0);
		    statusitem->setText(0, tr("Status: %1").arg(itemdoc->text(3)));
		}
	
		QString qstr = QString("SELECT description FROM docpositions WHERE `docid`='%1';").arg(itemdoc->text(1));
		QSqlQuery docpos(qstr);
		while(docpos.next())
		{
		    QTreeWidgetItem *itemchild = new QTreeWidgetItem(itemdoc);
		    itemchild->setText(0, docpos.value(0).toString());
		}
    }
}
//
void addrfrm::loadauftr(QString dbID)
{
    listproc->clear();
    QStringList statusname;
    statusname << tr("Incoming orders") << tr("Offers") << tr("Open orders") << tr("Completed orders") << tr("Deliverynotes") << tr("Invoices");
    QTreeWidgetItem *tmpitem = mainlistview->currentItem();   
    while(tmpitem->childCount()>0)
		tmpitem->takeChild(0);
    QString connstr = "SELECT status, description, date, ID FROM proceduretab WHERE client LIKE '%";
    connstr += "("+adrnamelist[cmbdir->currentIndex()].mid(3)+"_"+dbID+")";
    connstr += "%';";
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		while(query.next())
		{
		    QTreeWidgetItem *item = new QTreeWidgetItem(listproc);
		    item->setText(0, statusname[query.value(0).toString().toInt()]);
		    item->setText(1, query.value(1).toString());
		    item->setText(2, query.value(2).toString());
		}
    }
}
//
void addrfrm::openauftrag()
{
    //ablauf *auftr = new ablauf;
    QTreeWidgetItem *tmpitem = listproc->currentItem();
    if(tmpitem != 0)
    {
		if(tmpitem->text(3).mid(0,1)=="*")
		{
		    //auftr->initfrm();
		    //auftr->editauftrag(tmpitem->text(3).mid(1));
		    tmpitem = tmpitem->parent();
		    loadauftr(tmpitem->text(3));
		}
    }
}
//
void addrfrm::changecust1()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("New Label:"), QLineEdit::Normal,
                                          lbladr24->text(), &ok);
    if(ok)
		lbladr24->setText(text);
}
//
void addrfrm::changecust2()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("New Label:"), QLineEdit::Normal,
                                          lbladr25->text(), &ok);
    if(ok)
		lbladr25->setText(text);
}
//
void addrfrm::changecust3()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("New Label:"), QLineEdit::Normal,
                                          lbladr26->text(), &ok);
    if(ok)
		lbladr26->setText(text);
}
//
void addrfrm::changecust4()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("New Label:"), QLineEdit::Normal,
                                          lbladr27->text(), &ok);
    if(ok)
		lbladr27->setText(text);
}
//
void addrfrm::changecust5()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("New Label:"), QLineEdit::Normal,
                                          lbladr28->text(), &ok);
    if(ok)
		lbladr28->setText(text);
}
//
void addrfrm::newaddr()
{
	QSqlDatabase::database().transaction();
    maintab->setCurrentIndex(0);
    
    QString qstr1 = QString("SELECT idcounter FROM directories WHERE `name` = '%1';").arg(adrnamelist[cmbdir->currentIndex()]);
    QSqlQuery querycheckid(qstr1);
    querycheckid.next();
    adr2->setText(QString("%1").arg(querycheckid.value(0).toInt()+1, 0, 10));
    
    QString qstr2 = QString("UPDATE `directories` SET `idcounter` = '%1' WHERE `name` = '%2' LIMIT 1;").arg(adr2->text()).arg(adrnamelist[cmbdir->currentIndex()]);
    QSqlQuery queryupdateid(qstr2);
    //queryupdateid.exec();
    
    QString s = QDate::currentDate().toString("dd.MM.yyyy");
    QString conn1 = "INSERT INTO `";
    conn1 += adrnamelist[cmbdir->currentIndex()];
    conn1 += "` ( `ID`, `clientid`, `company`, `lastname`, `firstname`, `nameadd`, `pobox`, `street_nr`, `location`, `zip`, `country`, `tel_b`, `tel_direct`, `fax_b`, `tel_p`, `fax_p`, `mobile`, `email1`, `email2`, `email3`, `homepage`, `revenueaj`, `revenuelj`, `discount`, `clienttyp`, `comments`, `custom1`, `custom2`, `custom3`, `custom4`, `custom5`, `created`, `modified`)VALUES ('', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '"+s+"', '');";
    QSqlQuery queryadrnew1(conn1);
	
    QString conn4 = "SELECT ID, clientid, company, lastname, firstname, nameadd, pobox, street_nr, `location`, `zip`, `country`, tel_b, tel_direct , fax_b, tel_p, fax_p, mobile, email1, email2, email3, homepage, revenueaj, revenuelj, discount, clienttyp, comments, custom1, custom2, custom3, custom4, custom5, created, modified FROM ";
    conn4 += adrnamelist[cmbdir->currentIndex()];
    conn4 += ";";
    QSqlQuery queryadrnew4(conn4);
    if ( queryadrnew4.isActive())
    {
		queryadrnew4.last();
		adr1->setText(queryadrnew4.value(0).toString());
		adr29->setText(queryadrnew4.value(26).toString());
		adr30->setText(queryadrnew4.value(26).toString());
    }
    adr3->setText("");
    adr4->setText("");
    adr5->setText("");
    adr6->setText("");
    adr7->setText("");
    adr8->setText("");
    adr9a->setText("");
    adr9b->setText("");
    adr31->setText("");
    adr10->setText("");
    adr11->setText("");
    adr12->setText("");
    adr13->setText("");
    adr14->setText("");
    adr15->setText("");
    adr16->setText("");
    adr17->setText("");
    adr18->setText("");
    adr19->setText("");
    adr22->setText("0");	
    adr23->setText("");		
    lbladr24->setText("");
    adr24->setText("");
    lbladr25->setText("");
    adr25->setText("");
    lbladr26->setText("");
    adr26->setText("");
    lbladr27->setText("");
    adr27->setText("");
    lbladr28->setText("");
    adr28->setText("");
    QSqlDatabase::database().commit();
	
    lastadrtab = "";
    loadaddrs();
	
    mainlistview->setEnabled(false);
    btnnew->setEnabled(false);
    cmbdir->setEnabled(false);
    btnclose->setEnabled(false);
    btncancel->setEnabled(false);
    btndelete->setEnabled(false);
}
//
void addrfrm::saveaddr()
{
	QSqlDatabase::database().transaction();
    mainlistview->setEnabled(true);
    btnnew->setEnabled(true);
    cmbdir->setEnabled(true);
    btnclose->setEnabled(true);	 
    btncancel->setEnabled(true);
    btndelete->setEnabled(true);
    
    QString s = QDate::currentDate().toString("dd.MM.yyyy");    

    QString conn1 = "UPDATE `" + adrnamelist[cmbdir->currentIndex()] + "` SET `clientid` = '"+adr2->text()+"', `company` = '"+ adr3->text()+"', `lastname` = '"+ adr5->text()+"',`firstname` = '"+ adr4->text()+"',`nameadd` = '"+ adr6->text()+"',`pobox` = '"+ adr7->text()+"',`street_nr` = '"+ adr8->text()+"',`location` = '"+ adr9b->text()+"',`zip` = '"+ adr9a->text()+"',`country` = '"+ adr31->text()+"',`tel_b` = '"+ adr10->text()+"',`tel_direct` = '"+ adr11->text()+"',`fax_b` = '"+ adr12->text()+"',`tel_p` = '"+ adr13->text()+"',`fax_p` = '"+ adr14->text()+"',`mobile` = '"+ adr15->text()+"',`email1` = '"+ adr16->text()+"',`email2` = '"+ adr17->text()+"',`email3` = '"+ adr18->text()+"',`homepage` = '"+ adr19->text()+"', `discount` = '"+adr22->text()+"', `comments` = '"+ adr23->toPlainText()+"',`custom1` = '"+lbladr24->text() +":#:"+adr24->text()+"',`custom2` = '"+lbladr25->text() +":#:"+ adr25->text()+"',`custom3` = '"+lbladr26->text() +":#:"+ adr26->text()+"',`custom4` = '"+lbladr27->text() +":#:"+ adr27->text()+"',`custom5` = '"+lbladr28->text() +":#:"+ adr28->text()+"',`modified` = '"+s+"' WHERE `ID` = '" + adr1->text() + "' LIMIT 1;";	
	
    QSqlQuery queryadrsave(conn1);
    if( !queryadrsave.exec() ) {
		QSqlError err = queryadrsave.lastError();
		QMessageBox::critical( this, tr( "Error" ), err.driverText() + "\n\nMessage:\t" + err.databaseText() );
		return;
    }
	QSqlDatabase::database().commit();
    lastadrtab = "";
    loadaddrs();
}
//
void addrfrm::deladdr()
{
    int exit=QMessageBox::warning(this, "Info...", tr("Delete %1 %2 %3?").arg(adr3->text()).arg(adr5->text()).arg(adr4->text()),QMessageBox::Yes, QMessageBox::No);
    if(exit == QMessageBox::Yes)
    {
		QString conn = "DELETE FROM `";
		conn += adrnamelist[cmbdir->currentIndex()];
		conn += "` WHERE `ID` = '";
		conn += adr1->text();
		conn +=  "';";
		QSqlQuery queryadrdel(conn);				
		lastadrtab = "";
		loadaddrs();
	    
		adr1->setText("");
		adr2->setText("");
		adr3->setText("");
		adr4->setText("");
		adr5->setText("");
		adr6->setText("");
		adr7->setText("");
		adr8->setText("");
		adr9a->setText("");
		adr9b->setText("");
		adr10->setText("");
		adr11->setText("");
		adr12->setText("");
		adr13->setText("");
		adr14->setText("");
		adr15->setText("");
		adr16->setText("");
		adr17->setText("");
		adr18->setText("");
		adr19->setText("");
		adr22->setText("");	
		adr23->setText("");		
		lbladr24->setText("");
		adr24->setText("");
		lbladr25->setText("");
		adr25->setText("");
		lbladr26->setText("");
		adr26->setText("");
		lbladr27->setText("");
		adr27->setText("");
		lbladr28->setText("");
		adr28->setText("");	  
		adr29->setText("");	
		adr30->setText("");		
    }
}
//
void addrfrm::clearsearch()
{
    txtsearch->setText("");
    lastadrtab = "";
    loadaddrs();    
}
//
void addrfrm::search()
{
    QSqlQuery target;
    QString connstr = "SELECT ID, company, lastname, firstname FROM ";
    connstr += adrnamelist[cmbdir->currentIndex()];
    connstr += " WHERE company LIKE '%"+txtsearch->text()+"%' OR lastname LIKE '%"+txtsearch->text()+"%' OR firstname LIKE '%"+txtsearch->text()+"%';";
    mainlistview->clear();
    QSqlQuery query(connstr);
    if ( query.isActive())
    {
		progbar->setValue(0);
		progbar->setMaximum(query.size());
		while(query.next())
		{
		    progbar->setValue(query.at()+1);
		    QTreeWidgetItem *item = new QTreeWidgetItem(mainlistview);
		    item->setText(0, query.value(1).toString());
		    item->setText(1, query.value(2).toString());
		    item->setText(2, query.value(3).toString());
		    item->setText(3, query.value(0).toString());
		}
    }
    lastadrtab = cmbdir->currentText();
}
//
void addrfrm::printaddr()
{
    QString document = writetexfile();

	vars v;
	QString tool = v.get_tool("DVIVIEWER");
	
    //Show Report
    QStringList args;
    args << document;
    QProcess *procshow = new QProcess( this );
    procshow->start(tool, args);
	if(procshow->exitStatus() != QProcess::NormalExit ) 
			QMessageBox::critical(0,"Error...", tr("Can't show DVI file."));
    QFile file(document);
    file.remove();
}
//
QString addrfrm::writetexfile()
{
    QString tabhead = "";
    QString tabcontent = "";
    
    QString templatestr = loadtemplatedata();
    QTime now = QTime::currentTime();
	QDate today = QDate::currentDate();
    QFile output(QDir::homePath()+"/.first4/tmp/"+username+"-"+today.toString("yyyyMMdd")+now.toString("hhmmsszzz")+".tex");
	if ( output.open(QIODevice::WriteOnly) )
	{
	    QTextStream outstream( &output );
	    if(adr3->text() != "")
			templatestr = templatestr.replace("+++TITLE+++", adr3->text());
	    else
			templatestr = templatestr.replace("+++TITLE+++", adr5->text() +", " +adr4->text());

	    QString tmpstr = "";
	    tmpstr += "\\textbf{ID:} & " + adr2->text() + " & & \\\\ \n \\hline \n";
	    tmpstr += "\\textbf{"+tr("Company")+":} & " + adr3->text() + " & & \\\\ \n \\hline \n";
	    tmpstr += "\\textbf{"+tr("Salutation")+":} & " + adr6->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("Name")+":} & " + adr5->text() + "& \\textbf{Vorname:} & " + adr4->text() + " \\\\ \n";
	    tmpstr += "\\textbf{"+tr("P.O. Box")+":} & " + adr7->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("Street \\& Nr.")+":} & " + adr8->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("ZIP, Location")+":} & " + adr9a->text() +" "+adr9b->text()+ " & & \\\\ \n \\hline \n";
	    tmpstr += "\\textbf{"+tr("Business phone")+":} & " + adr10->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("Direct phone")+":} & " + adr11->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("Business fax")+":} & " + adr12->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("Private phone")+":} & " +  adr13->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("Private fax")+":} & " + adr14->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("Mobile")+":} & " + adr15->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("E-Mail 1")+":} & " + adr16->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("E-Mail 2")+":} & " + adr17->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("E-Mail 3")+":} & " + adr18->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{"+tr("Website")+":} & " + adr19->text() + " & & \\\\ \n  \\hline \n";
		QTreeWidgetItem *item = listrevenue->topLevelItem(0);
		if(item != 0)
		{
			int i;
			for(i=0;i<listrevenue->topLevelItemCount();i++)
			{
				tmpstr += "\\textbf{"+tr("Revenue")+":} & "+item->text(0)+": "+item->text(1)+" "+rev_currency+" & & \\\\ \n";	
			}
		}
		else
			tmpstr += "\\textbf{"+tr("Revenue")+":} & - "+rev_currency+" & & \\\\ \n";
		tmpstr += "\\textbf{"+tr("Discount")+":} & " + adr22->text() + "\\% & & \\\\ \n \\hline \n";
	    tmpstr += "\\textbf{"+tr("Comments")+":} & " + adr23->toPlainText() + " & & \\\\ \n";
	    tmpstr += "\\textbf{" + lbladr24->text() + "} & " + adr24->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{" + lbladr25->text() + "} & " + adr25->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{" + lbladr26->text() + "} & " + adr26->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{" + lbladr27->text() + "} & " + adr27->text() + " & & \\\\ \n";
	    tmpstr += "\\textbf{" + lbladr28->text() + "} & " + adr28->text() + " & & \\\\ \n \\hline \n";
	    tmpstr += "\\textbf{"+tr("Created")+":} &" + adr29->text() + " & \\textbf{"+tr("Modified")+":} & " + adr30->text() + " \\\\ \n";
	    outstream << templatestr.replace("+++DATA+++", tmpstr);
	    output.close();
	} else {
	    QMessageBox::critical(0,"Error...",tr("Can't write ouputfile!"));
	}

    //converting text to dvi
    QStringList args;
    args << "-output-directory="+QDir::homePath()+"/.first4/tmp/" << output.fileName();
    QProcess *procdvi = new QProcess( this );
    procdvi->start("latex", args);
    if(procdvi->exitCode()!=0)
		QMessageBox::critical(0,"Error...", tr("Error during convertion from TEXT to DVI!"));
		
	return output.fileName().replace(".tex", ".dvi");
}
//
void addrfrm::opendoc()
{
    QTreeWidgetItem *item = listdocs->currentItem();
    if(item->text(1) != "")
    {
		doceditfrm *doc = new doceditfrm;
		doc->init();
		doc->opendocfromid("docs", item->text(1));
		doc->btnnew->setEnabled(FALSE);
		doc->btnsave->setEnabled(FALSE);
		doc->btnprint->setEnabled(TRUE);
		doc->btncomplete->setEnabled(FALSE);
		doc->btnopen->setEnabled(FALSE);
		doc->show();
    }
}
//
void addrfrm::deletedoc()
{
    QTreeWidgetItem *itemdoc = listdocs->currentItem();
    if(itemdoc->text(1)!="")
    {
		QString connstr = "SELECT ID, docart, docID FROM docs WHERE ID = '"+itemdoc->text(1)+"';";
		QSqlQuery query(connstr);
		query.next();
		int r = QMessageBox::information(this, tr("Delete Document..."), tr("Delete %1 %2?").arg(query.value(1).toString()).arg(query.value(2).toString()),QMessageBox::Yes, QMessageBox::No);
		if(r == QMessageBox::Yes)
		{
		    connstr = "DELETE FROM docs WHERE `ID` = '"+itemdoc->text(1)+"';";
		    QSqlQuery query2(connstr);
		    QString filename=docfolder+"/"+adrnamelist[cmbdir->currentIndex()].mid(3)+"_"+adr1->text()+"/"+query.value(1).toString().toLower().mid(0,2)+query.value(2).toString()+".kud";
		    QFile delfile(filename);
		}
		loaddocs(adr1->text());
    }
}
//
void addrfrm::contmenu()
{
    QTreeWidgetItem *item = listdocs->currentItem();
    if(item->text(1) != "")
    {
	    QMenu* contextMenu = new QMenu( this );
	    Q_CHECK_PTR( contextMenu );

	    QAction* doc_open = new QAction( tr("&Open Document"), this );
		connect(doc_open , SIGNAL(triggered()), this, SLOT(opendoc()));
		contextMenu->addAction(doc_open);
	    QAction* doc_delete = new QAction( tr("&Delete Document"), this );
		connect(doc_delete , SIGNAL(triggered()), this, SLOT(deletedoc())); 
		contextMenu->addAction(doc_delete);
		
	    contextMenu->exec( QCursor::pos() );
	    delete contextMenu;
	}
}
//
void addrfrm::contmenuaddr()
{
    QMenu* submenucopy = new QMenu( this );
    QMenu* submenumove = new QMenu( this );
    int i;
    QStringList menuitemcopy, menuitemmove;
    for(i=0;i<cmbdir->count();i++)
    {
    	if(cmbdir->itemText(i) != lastadrtab)
    	{
	    	QAction* sub_copy = new QAction(cmbdir->itemText(i), this);
	    	connect(sub_copy , SIGNAL(triggered()), this, SLOT(copyaddr(adrnamelist[cmbdir->currentIndex()])));
	    	submenucopy->addAction(sub_copy);
			menuitemcopy << QString("cp;%1;%2").arg(adrnamelist[cmbdir->currentIndex()], 0, 10).arg(adrnamelist[i]);
   		}
    }
    
    for(i=0;i<cmbdir->count();i++)
    {
    	if(cmbdir->itemText(i) != lastadrtab)
    	{
			QAction* sub_move = new QAction(cmbdir->itemText(i), this);
			connect(sub_move , SIGNAL(triggered()), this, SLOT(moveaddr(adrnamelist[cmbdir->currentIndex()]))); 
	    	submenumove->addAction(sub_move);
			menuitemmove << QString("mv;%1;%2").arg(adrnamelist[cmbdir->currentIndex()], 0, 10).arg(adrnamelist[i]);
		}
    }    
    
	QMenu* contextMenu = new QMenu( this );
	Q_CHECK_PTR( contextMenu );

	submenucopy->setTitle(tr("Copy to"));
	contextMenu->addMenu(submenucopy);
	
	submenumove->setTitle(tr("Move to"));
	contextMenu->addMenu(submenumove);
		
    contextMenu->exec( QCursor::pos() );
    
    delete contextMenu;
}
//
void addrfrm::copyaddr(QString dest)
{
    QTreeWidgetItem *item = mainlistview->currentItem();
    if(item != 0)
    {
		int i;
		QString connstr = QString("SHOW COLUMNS FROM `%1`.`%2`;").arg(dbname).arg(dest);
		QSqlQuery checkcols(connstr);
		int cols = checkcols.size();
		QStringList result, colnames;
		connstr = QString("SELECT * FROM %1 WHERE ID = '%2';").arg(adrnamelist[cmbdir->currentIndex()]).arg(item->text(3));
		QSqlQuery query(connstr);
		if(query.isActive())
		{
		    query.next();
		    while(checkcols.next())
		    {
			colnames << checkcols.value(0).toString();
			result << query.value(checkcols.at()).toString();
		    }
		}
		connstr = QString("INSERT INTO `%1` (").arg(dest);
		for(i=0;i<cols;i++)
		    connstr += QString("`%1`, ").arg(colnames[i]); 
		connstr = connstr.left(connstr.length()-2);
		connstr += ") VALUES ('', ";     
		for(i=1;i<cols;i++)
		    connstr += QString("'%1', ").arg(result[i]); 
		connstr = connstr.left(connstr.length()-2);
		connstr += ");";
		QSqlQuery insertquery(connstr);
    }
}
//
void addrfrm::moveaddr(QString dest)
{
    copyaddr(dest);
    QTreeWidgetItem *item = mainlistview->currentItem();
    if(item != 0)
    {
		QString connstr = QString("DELETE FROM `%1` WHERE `ID` = '%2';").arg(adrnamelist[cmbdir->currentIndex()]).arg(item->text(3));
		QSqlQuery query(connstr);
		loadaddrs();
    }    
}
//
void addrfrm::impexp()
{
    addrimpexpfrm *addrimpexp = new addrimpexpfrm;
    addrimpexp->init();
    if(addrimpexp->exec())
    {
		lastadrtab = "";
		loadaddrs();
	}
}
//
QString addrfrm::loadtemplatedata()
{
	QString answ;
	QSqlQuery query("SELECT data FROM templatestab WHERE `name`='sys_address';");
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

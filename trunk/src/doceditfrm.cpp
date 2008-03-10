#include <QSqlQuery>
#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QSqlError>
//
#include "doceditfrm.h"
#include "vars.h"
#include "addrselectfrm.h"
#include "stockselfrm.h"
#include "doccompletefrm.h"
#include "docopendraftsfrm.h"
#include "vatshowfrm.h"
#include "doceditposition.h"
#include "accountseditfrm.h"
#include "msgeditfrm.h"
//
extern int uid;
extern QString username, fullname, docfolder, templatefolder;
//
QString opendocID = "";
QString opendocSource = "";
QString b_text = "";
QString docprefix, tnr, companyaddress, location, docfile, currency;
QStringList vatlist, vatamount, docnames, doccount, docdef, temp_id;
//
doceditfrm::doceditfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
void doceditfrm::init()
{
    QDate date = QDate::currentDate();
    boxdate->setDate(date);
    
    lbluser->setText(username);
    
    docnames.clear();
    docnames << tr("Offer") << tr("Order confirmation") << tr("Delivery note") << tr("Invoice");
    
	readdoctab();
    initvat();
    loadmaincfg();
    
    tabmain->setColumnWidth(0,30);
    tabmain->setColumnWidth(1,90);
    tabmain->setColumnWidth(2,20);
    tabmain->setColumnWidth(3,225);
    tabmain->setColumnWidth(4,55);
    tabmain->setColumnWidth(5,50);
    tabmain->setColumnWidth(6,100);
    tabmain->setColumnWidth(7,100);
    tabmain->setColumnWidth(8,50);
    tabmain->setColumnWidth(9,0);
    tabmain->setColumnWidth(10,0);
    tabmain->setColumnWidth(11,0);
    tabmain->setRowCount(1);
    
    QTableWidgetItem *item = new QTableWidgetItem;
	item->setText("1");
	tabmain->setItem(0, 0, item);
	item = new QTableWidgetItem;
	item->setText("");
	tabmain->setItem(tabmain->rowCount()-1, 1, item);
	item = new QTableWidgetItem;
	item->setIcon(QIcon(QString::fromUtf8(":/viewmag2.png")));
	tabmain->setItem(0, 2, item);
	item = new QTableWidgetItem;
	item->setText("");
	tabmain->setItem(tabmain->rowCount()-1, 3, item);
	item = new QTableWidgetItem;
	item->setText("0");
	tabmain->setItem(tabmain->rowCount()-1, 4, item);
	item = new QTableWidgetItem;
	item->setText("0.00");
	tabmain->setItem(tabmain->rowCount()-1, 6, item);
	item = new QTableWidgetItem;
	item->setText("0.00");
	tabmain->setItem(tabmain->rowCount()-1, 7, item);
	item = new QTableWidgetItem;
	item->setText(" ");
	tabmain->setItem(tabmain->rowCount()-1, 9, item);
	if(vatlist.size() > 0)
	{
		item = new QTableWidgetItem;
		item->setText(vatlist[0]);
		tabmain->setItem(tabmain->rowCount()-1, 8, item);	
	} else {
		QMessageBox::information(0,tr("Stock..."), tr("Please define VAT first!"));
	}
    
    mainwidget->setCurrentIndex(1);
    
    opendocID = "";
    opendocSource = "";
    
    QMenu* btnprintmenu = new QMenu( this );
    Q_CHECK_PTR( btnprintmenu );

    QAction* print_preview = new QAction( tr("&Print pre&view"), this );
	connect(print_preview , SIGNAL(triggered()), this, SLOT(printpreview()));
	btnprintmenu->addAction(print_preview);
    QAction* print = new QAction( tr("&Print document"), this );
	connect(print , SIGNAL(triggered()), this, SLOT(print())); 
	btnprintmenu->addAction(print);
    QAction* printvesr = new QAction( tr("Paying-in &slip"), this );
	connect(printvesr , SIGNAL(triggered()), this, SLOT(printvesr())); 
	btnprintmenu->addAction(printvesr);		
	btnprint->setMenu(btnprintmenu);
	
	vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
	    if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
    }

    connect(btnclose, SIGNAL(released()), this, SLOT(close()));
    connect(btnsearchaddr, SIGNAL(released()), this, SLOT(selectaddress()));
    connect(cmbdoc, SIGNAL(activated(int)), this, SLOT(selecteddocument()));
    connect(tabmain, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));
	connect(tabmain, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(checkdb()));
	connect(btnclearsearch, SIGNAL(released()), this, SLOT(clearlblid()));
	connect(btncomplete, SIGNAL(released()), this, SLOT(completedoc()));
	connect(btnopen, SIGNAL(released()), this, SLOT(opendoc()));
	connect(btnsave, SIGNAL(released()), this, SLOT(savedoc()));
	connect(btncalc, SIGNAL(released()), this, SLOT(calc_tot()));
	connect(btnvat, SIGNAL(released()), this, SLOT(show_vat()));
	connect(boxtot_excl, SIGNAL(lostFocus()), this, SLOT(excl_vat()));
	connect(boxvat, SIGNAL(lostFocus()), this, SLOT(excl_vat()));
	navtabonoff(true);
	
}
//
void doceditfrm::closeEvent( QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void doceditfrm::readdoctab()
{
    cmbdoc->clear();
    temp_id.clear();
    doccount.clear();
    docdef.clear();
    
    QString qstr = "SELECT name, templateid, count, users FROM doctab ORDER BY ID;";
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		int tmpid;
		while(query.next())
		{
		    tmpid = query.value(0).toString().section(" ", 0, 0).toInt()-1;
		    if(query.value(3).toString().contains(username+" [11]"))
				cmbdoc->addItem(docnames[tmpid]);
		    else
				cmbdoc->addItem("*" + docnames[tmpid]);
		    docdef << query.value(0).toString();
		    temp_id << query.value(1).toString();
		    doccount << query.value(2).toString();
		}
    }
}
//
void doceditfrm::selecteddocument()
{
	QDate date = boxdate->date();
	bool ok;
	if(txtdoccount->text().mid(2).toInt(&ok, 10)<20000000)
	{
		if(cmbdoc->currentText().mid(0,1)!="*")
		{
			txtdoccount->setText(docprefix+date.toString("MMyy")+doccount[cmbdoc->currentIndex()]);
			switch(cmbdoc->currentIndex()) {
			case 0:
				docfile = "of"+txtdoccount->text()+".dvi"; 
				break;
			case 1:
				docfile = "oc"+txtdoccount->text()+".dvi"; 
				break;	    
			case 2:
				docfile = "dn"+txtdoccount->text()+".dvi"; 
				break;
			case 3:
				docfile = "in"+txtdoccount->text()+".dvi"; 
				break;    
	    	}
		    btnnew->setEnabled(TRUE);
		    btnsave->setEnabled(TRUE);
		    btnprint->setEnabled(TRUE);
		    btncomplete->setEnabled(TRUE);
		    //tabmain->setReadOnly(FALSE);
		}
		else
		{
		    btnnew->setEnabled(FALSE);
		    btnsave->setEnabled(FALSE);
		    btnprint->setEnabled(FALSE);
		    btncomplete->setEnabled(FALSE);
		    //tabmain->setReadOnly(TRUE);
		    QMessageBox::information(0,"Error...",tr("You are not authorized to provide the selected document"));
		}
	}
	else
	{
		switch(cmbdoc->currentIndex()) 
		{
		case 0:
			docfile = "of"+date.toString("ddMMyyyy")+txtdoccount->text().mid(2)+".dvi"; 
			break;
		case 1:
			docfile = "oc"+date.toString("ddMMyyyy")+txtdoccount->text().mid(2)+".dvi";
			break;	    
		case 2:
			docfile = "dn"+date.toString("ddMMyyyy")+txtdoccount->text().mid(2)+".dvi"; 
			break;
		case 3:
			docfile = "in"+date.toString("ddMMyyyy")+txtdoccount->text().mid(2)+".dvi"; 
			break;    
		}      
	}
}
//
void doceditfrm::contmenu()
{
    QMenu* contextMenu = new QMenu( this );
    Q_CHECK_PTR( contextMenu );

    QAction* editentry = new QAction( tr("&Edit Entry"), this );
	connect(editentry , SIGNAL(triggered()), this, SLOT(editposition()));
	contextMenu->addAction(editentry);
    QAction* del_row = new QAction( tr("&Delete Row"), this );
	connect(del_row , SIGNAL(triggered()), this, SLOT(removerow()));
	contextMenu->addAction(del_row);
		
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}
//
void doceditfrm::removerow()
{
	disconnect(tabmain, SIGNAL(cellChanged(int, int)), this, SLOT(navtable()));
	tabmain->removeRow(tabmain->currentRow());
    int i;
    if(tabmain->rowCount() == 0)
    {
    	addrow();
		QTableWidgetItem *item = new QTableWidgetItem;
		item->setIcon(QIcon(QString::fromUtf8(":/viewmag2.png")));
		tabmain->setItem(0, 2, item);
   	}
    for(i=0;i<tabmain->rowCount();i++)
    {
    	QTableWidgetItem *item = new QTableWidgetItem;
    	item->setText(QString("%1").arg(i+1,0,10));
    	tabmain->setItem(i, 0, item);
    }
    connect(tabmain, SIGNAL(cellChanged(int, int)), this, SLOT(navtable()));
}
//
void doceditfrm::navtable()
{  
	disconnect( tabmain, SIGNAL( cellChanged(int, int) ), this, SLOT( navtable() ) );
	int row = tabmain->currentRow();
	QTableWidgetItem *item;
    if(row == tabmain->rowCount() - 1)
		addrow();
	
    QTableWidgetItem *tmpitem = new QTableWidgetItem;
    tmpitem = tabmain->item(row, 4);
    QString tmpstr = tmpitem->text();
    double quantity = tmpstr.toDouble(); 
    tmpitem = new QTableWidgetItem;
    tmpitem = tabmain->item(row, 9);
    tmpstr = tmpitem->text();
    double actquantity = tmpstr.toDouble();
    if (tmpstr.simplified() != "" && tmpstr != "-")
    {
		if(quantity > actquantity)
		    QMessageBox::information(0,tr("Stock..."),tr("The entered quantity exceeds the stock!")); 
	}
	tmpitem = tabmain->item(row, 6);
    tmpstr = tmpitem->text();

    double p_single = tmpstr.toDouble();
    
	item = new QTableWidgetItem;
	item->setText(QString("%1").arg(p_single, 0, 'f',2));
	tabmain->setItem(row,6, item);
	
	item = new QTableWidgetItem;
	item->setText(QString("%1").arg(quantity*p_single, 0, 'f',2));
	tabmain->setItem(row,7, item);
	
	connect(tabmain, SIGNAL(cellChanged(int, int)), this, SLOT(navtable()));
}
//
void doceditfrm::addrow()
{
	disconnect( tabmain, SIGNAL( cellChanged(int, int) ), this, SLOT( navtable() ) );
	
	tabmain->setRowCount(tabmain->rowCount()+1);
	 
	QTableWidgetItem *item = new QTableWidgetItem;
	item->setText(QString("%1").arg(tabmain->rowCount(),0,10));
	tabmain->setItem(tabmain->rowCount()-1, 0, item);
		
	item = new QTableWidgetItem;
	tabmain->setItem(tabmain->rowCount()-1, 1, item);
		
	item = new QTableWidgetItem;
	item->setIcon(QIcon(QString::fromUtf8(":/viewmag2.png")));
	tabmain->setItem(tabmain->rowCount()-1, 2, item);

	item = new QTableWidgetItem;
	tabmain->setItem(tabmain->rowCount()-1, 3, item);
		
	item = new QTableWidgetItem;
	item->setText("0");
	tabmain->setItem(tabmain->rowCount()-1, 4, item);

	item = new QTableWidgetItem;
	item->setText("0.00");
	tabmain->setItem(tabmain->rowCount()-1, 6, item);

	item = new QTableWidgetItem;
	item->setText("0.00");
	tabmain->setItem(tabmain->rowCount()-1, 7, item);

	item = new QTableWidgetItem;
	item->setText(" ");
	tabmain->setItem(tabmain->rowCount()-1, 9, item);

	if(vatlist.size() > 0)
	{
		item = new QTableWidgetItem;
		item->setText(vatlist[0]);
		tabmain->setItem(tabmain->rowCount()-1, 8, item);	
	} else {
		QMessageBox::information(0,tr("Stock..."), tr("Please define VAT first!"));			
	}
	connect(tabmain, SIGNAL(cellChanged(int, int)), this, SLOT(navtable()));
}
//
void doceditfrm::checkdb()
{
	disconnect(tabmain, SIGNAL(cellChanged(int, int)), this, SLOT(navtable()));
	QTableWidgetItem *testitem1 = tabmain->item(tabmain->currentRow(),1);
	QTableWidgetItem *testitem2 = tabmain->item(tabmain->currentRow(),3);
	if(tabmain->currentColumn()==2 && testitem1->text()!="" && testitem2->text()=="")
    {
		stockselfrm *sfrm = new stockselfrm;
	    QSqlQuery query("SELECT name, description FROM datatabs WHERE `tabtyp` = 'stock' AND `users` LIKE '%"+username+"%';");
	    if(query.isActive())
	    {
			while(query.next())
			{
				QTableWidgetItem *checkitem = tabmain->item(tabmain->currentRow(), 1);
				QString qstr = QString("SELECT ID, col1, col2, col3, col5, col8, col12, col6 FROM %1 WHERE col1 LIKE '%%2%' AND `col13`='1' ORDER BY col1 ASC;").arg(query.value(0).toString()).arg(checkitem->text());
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
	    }
	    
	    if(sfrm->treemain->topLevelItemCount()>1)
	    {		
   			sfrm->init();	
			if(sfrm->exec())
			{
			    QTreeWidgetItem *item = sfrm->treemain->currentItem();
			    if(item!=0)
			    {
					QTableWidgetItem *tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(1));
					tabmain->setItem(tabmain->currentRow(), 1, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(2));
					tabmain->setItem(tabmain->currentRow(), 3, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(4));
					tabmain->setItem(tabmain->currentRow(), 5, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(5));
					tabmain->setItem(tabmain->currentRow(), 6, tabmainitem);
	
					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(6));
					tabmain->setItem(tabmain->currentRow(), 8, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(3));					
					tabmain->setItem(tabmain->currentRow(), 9, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(7));
					tabmain->setItem(tabmain->currentRow(), 10, tabmainitem);
					
					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(8));
					tabmain->setItem(tabmain->currentRow(), 11, tabmainitem);
			    }
			}
	    }
	    else
	    {
			QTreeWidgetItem *item = sfrm->treemain->topLevelItem(0);
			if(item!=0)
			{
				QTableWidgetItem *tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(1));
				tabmain->setItem(tabmain->currentRow(), 1, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(2));
				tabmain->setItem(tabmain->currentRow(), 3, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(4));
				tabmain->setItem(tabmain->currentRow(), 5, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(5));
				tabmain->setItem(tabmain->currentRow(), 6, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(6));
				tabmain->setItem(tabmain->currentRow(), 8, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(3));					
				tabmain->setItem(tabmain->currentRow(), 9, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(7));
				tabmain->setItem(tabmain->currentRow(), 10, tabmainitem);
					
				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(8));
				tabmain->setItem(tabmain->currentRow(), 11, tabmainitem);
			}
	    }
    }
	connect(tabmain, SIGNAL(cellChanged(int, int)), this, SLOT(navtable()));
}
//
void doceditfrm::clearlblid()
{
    lblID->setText("");
}
//
void doceditfrm::calc_tot()
{
   int i;
   double amount =0;
   double discount = boxdiscount->text().toDouble();
   for(i=0;i<tabmain->rowCount()-1;i++)
   {
   		QTableWidgetItem *item = tabmain->item(i, 7);
		amount += item->text().toDouble(); 
   }
   double tot = amount;
   double tot_excl = tot - (tot/100*discount);
   boxtot->setText(QString("%1").arg(tot, 0, 'f',2));
   boxtot_excl->setText(QString("%1").arg(tot_excl, 0, 'f',2));
   calc_vat();
   double tot_incl = tot_excl;
   for(i=0;i<vatlist.count();i++)
   {
       tot_incl += vatamount[i].toDouble() * (vatlist[i].toDouble()/100);
   }
   boxvat->setText(QString("%1").arg(tot_incl - tot_excl, 0, 'f',2));
   boxtot_incl->setText(QString("%1").arg(tot_incl, 0, 'f',2));
}
//
void doceditfrm::calc_vat()
{
    int i, rows;
    
    for(i=0;i<vatlist.count();i++)
		vatamount[i] = "0.00";       
    
    for(rows=0;rows<tabmain->rowCount()-1;rows++)
    {
		for(i=0;i<vatlist.count();i++)
		{
			QTableWidgetItem *item = tabmain->item(rows, 8);
		    if(item->text() == vatlist[i])
		    {
		    	item = tabmain->item(rows, 7);
				vatamount[i] = QString("%1").arg(vatamount[i].toDouble() + item->text().toDouble(), 0, 'f',2);
	    	}
		}
    }
}
//
void doceditfrm::show_vat()
{
    vatshowfrm *svat = new vatshowfrm;
    int i;
    for(i=0;i<vatlist.count();i++)
    {
		if(vatamount[i].toDouble() > 0)
		{
		    QTreeWidgetItem *item = new QTreeWidgetItem(svat->treemain);
		    item->setText(0, vatlist[i]);
		    item->setText(1, vatamount[i]);
		    item->setText(2, QString("%1").arg(vatamount[i].toDouble()/100*vatlist[i].toDouble(), 0, 'f',2));
		}
    }
    svat->exec();
}
//
void doceditfrm::initvat()
{
    vatlist.clear();
    vatamount.clear();
    QStringList tmplist;
    QString connstr = "SELECT col1 FROM vattab ORDER BY ID;";
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		while(query.next())
		{
		    vatlist << query.value(0).toString();
		    vatamount << "0.00";
		}
    }
}
//
void doceditfrm::loadmaincfg()
{
    QString connstr = QString("SELECT value FROM `maincfgtab` WHERE `var` = 'docpref' OR `var` = 'banktnr' OR `var` = 'def_currency' ORDER BY var;");
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		query.next();
		tnr = query.value(0).toString();
		query.next();
		currency = query.value(0).toString();
		query.next();
		docprefix = query.value(0).toString();
    }
    
    QStringList address;
    QStringList fields;
    fields << "company" << "companyaddress" << "companylocation" << "companyzip" << "companycountry"; 
    int i;
    companyaddress = "";
    for(i=0;i<fields.count();i++)
    {
    	QString qstr = QString("SELECT value FROM `maincfgtab` WHERE `var` = '%1';").arg(fields[i]);
    	QSqlQuery queryaddr(qstr);
    	queryaddr.next();
    	address << queryaddr.value(0).toString();
    }
    companyaddress = address[0]+"\n"+address[1]+"\n"+address[3]+"\n"+address[2]+"\n"+address[4]+"\n";
    location = address[2];
}
//
void doceditfrm::selectaddress()
{
    addrselectfrm *safrm = new addrselectfrm;
    safrm->init();
    if(safrm->exec())
    {
       QString answer = safrm->getaddress();
       boxdiscount->setText(safrm->getrabatt());
       QStringList fields = answer.split(":#:");
       boxaddress->setText(fields[0].replace("<BR>", "\n"));
       lblID->setText(fields[1]);
    }
}
//
void doceditfrm::completedoc()
{
	if(tabmain->rowCount()>1)
    {
		if(lblID->text()!="")
		{ 
		    doccompletefrm *complfrm = new doccompletefrm;
		    complfrm->init();
		    if(docdef[cmbdoc->currentIndex()] != "3 deliverynote" && docdef[cmbdoc->currentIndex()] != "4 invoice")
		    {
				complfrm->chkbox_2->setChecked(FALSE);
				complfrm->chkbox_2->setEnabled(FALSE);
				complfrm->chkbox_6->setChecked(FALSE);
				complfrm->chkbox_6->setEnabled(FALSE);
		    }	    
		    if(docdef[cmbdoc->currentIndex()] != "4 invoice")
		    {
				complfrm->chkbox_3->setChecked(FALSE);
				complfrm->chkbox_3->setEnabled(FALSE);
				complfrm->chkbox_4->setChecked(FALSE);
				complfrm->chkbox_4->setEnabled(FALSE);
		    }
		    if(complfrm->exec())
		    {
				if(complfrm->chkbox_1->isChecked())
				    calc_tot(); //Summe berechnen
				if(complfrm->chkbox_5->isChecked())		
				    printreport(TRUE);
		
				bool ok;
				if(txtdoccount->text().mid(2).toInt(&ok, 10)<20000000)
				{		
				    QString connstr = "SELECT ID, count FROM doctab WHERE `name` = '"+docdef[cmbdoc->currentIndex()]+"';";	  
				    QSqlQuery query(connstr);
				    query.next();
				    QString tmpID = query.value(0).toString();
				    QString tmpstr = query.value(1).toString();
				    bool ok;
				    int newcount = tmpstr.toInt(&ok, 10)+1;
				    tmpstr = QString("%1").arg(newcount,0,10);
				    tmpstr = tmpstr.rightJustified(4, '0');			
				    QString connstr2 = "UPDATE `doctab` SET `count` = '" + tmpstr + "' WHERE `ID` = '"+tmpID+"' LIMIT 1;";
				    QSqlQuery query2(connstr2);
				    doccount[cmbdoc->currentIndex()] = QString("%1").arg(newcount,0,10);
				}
				if(cmbdoc->currentIndex()==2)
				{
				    if(complfrm->chkbox_2->isChecked())
						refreshstockdb();
				}
		
				if(cmbdoc->currentIndex()==3)
				{
					if(complfrm->chkbox_3->isChecked())
						revenue(lblID->text(), boxtot_excl->text());
				}
		
				if(complfrm->chkbox_4->isChecked())
				    registeramount();
		
				savecompletedoc();
		
				QMessageBox::information(0, tr("Save..."), tr("Document completed and saved in Database"));
				newdocument();
			}
		}
	}
}
//
void doceditfrm::refreshstockdb()
{
	int i;
    for(i=0;i<tabmain->rowCount()-1;i++)
    {
    	QTableWidgetItem *item = tabmain->item(i, 11);
		if(item->text()!="")
		{
			item = tabmain->item(i, 9);
		    QString tmpstr = item->text();
		    double aktmenge = tmpstr.toInt();

		    //item = new QTableWidgetItem;
		    item = tabmain->item(i, 4);
		    tmpstr = item->text();
		    double neuemenge = tmpstr.toInt();
		    
		    item = tabmain->item(i, 11);
		    QStringList fields = item->text().split( ":#:");
		    QString connstr = "UPDATE `"+fields[0]+"` SET `col3` = '"+QString("%1").arg(aktmenge-neuemenge, 0, 'f',0)+"' WHERE `ID` = '"+fields[1]+"' LIMIT 1;";
		    QSqlQuery query(connstr);
		    query.exec();
		 
		 	item = tabmain->item(i, 8);
		    if((aktmenge - neuemenge) <= item->text().toInt())
		    {
				msgeditfrm *emsg = new msgeditfrm;
				emsg->init("sto");
				emsg->date->setDate(QDate::currentDate());
				QTableWidgetItem *defitem = tabmain->item(i, 1);
				emsg->sto_def->setText(defitem->text());
				emsg->checkstock();
				emsg->sto_onstock->setText(QString("%1").arg(aktmenge-neuemenge, 0, 'f',0));
				emsg->sto_min->setText(item->text());
				emsg->newentry();
		    }
		}
    }
}
//
void doceditfrm::revenue(QString dbID, QString amount)
{
    QString qstr = "SELECT revenueaj, revenuelj FROM adr"+dbID.section("_", 0, 0)+" WHERE `ID` = '"+dbID.section("_", 1, 1)+"';";
    QSqlQuery query(qstr);
    query.next();
    if(query.value(0).toString().section(";", 0, 0) == QDate::currentDate().toString("yyyy") || query.value(0).toString().section(";", 0, 0) == "")
    {
		double newamount = query.value(0).toString().section(";", 1, 1).toDouble() + amount.toDouble();
		QString qstr2 = "UPDATE `adr"+dbID.section("_", 0, 0)+"` SET `revenueaj` = '"+QDate::currentDate().toString("yyyy")+";"+QString("%1").arg(newamount,  0, 'f', 2 )+"' WHERE `ID` = '"+dbID.section("_", 1, 1)+"' LIMIT 1;";
		QSqlQuery query2(qstr2);
    }
    else
    {
		QString qstr2 = "UPDATE `adr"+dbID.section("_", 0, 0)+"` SET `revenueaj` = '"+QDate::currentDate().toString("yyyy")+";"+amount+"', `revenuelj` = '"+query.value(1).toString()+"#"+query.value(0).toString()+"' WHERE `ID` = '"+dbID.section("_", 1, 1)+"' LIMIT 1;";
		QSqlQuery query2(qstr2);
    }
}
//
void doceditfrm::registeramount()
{
    accountseditfrm *acc = new accountseditfrm;
    acc->init();
    QString refnr = txtdoccount->text().right(8);
    refnr = refnr.rightJustified(15, '0', TRUE);    
    acc->txtRefNr->setText(refnr);
    acc->date1->setDate(boxdate->date());
    acc->txtCode->setText("INV");
    acc->txtaddress->setText(boxaddress->toPlainText());
    acc->lbladdrID->setText(lblID->text());
    acc->txtdescription->setText(tr("Invoice %1").arg(txtdoccount->text()));
    acc->txtamount->setText(boxtot_incl->text());
    acc->setdbID("ietab");
    acc->newentry("ietab");
}
//
void doceditfrm::newdocument()
{
    opendocID = ""; 
    opendocSource = "";
    if(!btncomplete->isEnabled())
    {
		int r = QMessageBox::information(this, tr("New Document..."), tr("Take over existing data?"), QMessageBox::Yes, QMessageBox::No);
		if(r == QMessageBox::Yes)
		{
		    int tmp = cmbdoc->currentIndex();
		    readdoctab();
		    cmbdoc->setCurrentIndex(tmp);
		    selecteddocument();
		}
		else
		{
		    boxaddress->setText("");
		    lblID->setText("");
		    b_text = "";
		    txtdoccount->setText("");
		    boxcomments->setText("");
		    boxtot_excl->setText("0.00");
		    boxvat->setText("0.00");
		    boxtot_incl->setText("0.00");
		    boxtot->setText("0.00");
		    tabmain->setRowCount(0);
			addrow();
		}
		btncomplete->setEnabled(TRUE);
		btnsave->setEnabled(TRUE);
    }
    else
    {
	    QDate date = QDate::currentDate();
		boxdate->setDate(date);
	    mainwidget->setCurrentIndex(1);
	    opendocID = "";
	    opendocSource = "";
	    readdoctab();
		boxaddress->setText("");
		lblID->setText("");
		b_text = "";
		txtdoccount->setText("");
		boxcomments->setText("");
		boxtot_excl->setText("0.00");
		boxvat->setText("0.00");
		boxtot_incl->setText("0.00");	
    }
}
//
void doceditfrm::opendoc()
{
    docopendraftsfrm *docopen = new docopendraftsfrm;
    docopen->init();
    int answ = docopen->exec();
    if(answ)
		opendocfromid("docdrafts", QString("%1").arg(answ));
}
//
void doceditfrm::opendocfromid(QString source, QString dbID)
{
	disconnect( tabmain, SIGNAL( cellChanged(int, int) ), this, SLOT( navtable() ) );
    btncomplete->setEnabled(TRUE);
    this->newdocument();
    
	vars v;
	QString qstr;
	QString userlock = v.checklockstate(source, dbID);
	if(userlock != "")
	{
		this->setWindowTitle(this->windowTitle()+QString(" ( Locked by User: %1 )").arg(userlock));
		btnsave->setEnabled(FALSE);
		btncomplete->setEnabled(FALSE);
		qstr = QString("SELECT ID, doctyp, docID, date, client, amount, discount, comments, salutation, introduction FROM %1 WHERE ID = '%2';").arg(source).arg(dbID);
	}
	else
	{
		qstr = QString("SELECT ID, doctyp, docID, date, client, amount, discount, comments, salutation, introduction FROM %1 WHERE ID = '%2' FOR UPDATE;").arg(source).arg(dbID);
		v.lockrow(source, dbID);
	}

    QSqlQuery query(qstr);
    if(query.isActive())
    {
		query.next();
		opendocID = dbID;
		opendocSource = source;
		if(query.value(1).toString()=="1 offer")
		{
		    cmbdoc->setCurrentIndex(0);		
		}
		else if(query.value(1).toString()=="2 orderconf")
		{
		    cmbdoc->setCurrentIndex(1);
		}	
		else if(query.value(1).toString()=="3 deliverynote")
		{
		    cmbdoc->setCurrentIndex(2);
		}	
		else
		{
		    cmbdoc->setCurrentIndex(3);
		}
		selecteddocument();
		QString convdate = query.value(3).toString().section(".", 2, 2)+"-"+query.value(3).toString().section(".", 1, 1)+"-"+query.value(3).toString().section(".", 0, 0);
		boxdate->setDate(QDate::fromString(convdate,Qt::ISODate));	    
		if(query.value(2).toString()!="")
		{
			txtdoccount->setText(query.value(2).toString());
			switch(cmbdoc->currentIndex()) 
			{
				case 0:
					docfile = "of"+txtdoccount->text()+".dvi";
					break;
				case 1:
					docfile = "oc"+txtdoccount->text()+".dvi";
					break;	    
				case 2:
					docfile = "dn"+txtdoccount->text()+".dvi";
					break;
				case 3:
					docfile = "bi"+txtdoccount->text()+".dvi";
					break;    
			}
		}
		lblID->setText(query.value(4).toString());
		
		qstr = "SELECT company, lastname, firstname, nameadd, pobox, street_nr, zip_location FROM adr"+lblID->text().section("_", 0, 0)+" WHERE ID = '"+lblID->text().section("_", 1, 1)+"';";
		QSqlQuery query2(qstr);
		query2.next();
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
		boxaddress->setText(adresse.replace("<BR>", "\n"));
	
		boxcomments->setText(query.value(7).toString());
		txtsalutation->setText(query.value(8).toString());
		boxotherinfo->setText(query.value(9).toString());
		boxtot->setText(query.value(5).toString());
		boxdiscount->setText(query.value(6).toString());
		
		qstr = "SELECT ID, DOCID, STOCK, STOCK_ID, DOC_POSITION, LABEL, DESCRIPTION, QUANTITY, UNIT, PRICE, VAT FROM docpositions WHERE DOCID = '"+query.value(0).toString()+"' AND `TYPE`='"+source+"' ORDER BY DOC_POSITION;";
		QSqlQuery querypos(qstr);
		if(querypos.isActive())
		{
		    tabmain->setRowCount(querypos.size());
		    while(querypos.next())
		    {
		    	QTableWidgetItem *item = new QTableWidgetItem;
		    	item->setText(querypos.value(4).toString());
		    	tabmain->setItem(querypos.at(), 0, item);
		    	
		    	item = new QTableWidgetItem;
		    	item->setText(querypos.value(5).toString());
		    	tabmain->setItem(querypos.at(), 1, item);
		    	
		    	item = new QTableWidgetItem;
		    	item->setText(querypos.value(6).toString());
		    	tabmain->setItem(querypos.at(), 3, item);
		    	
		    	item = new QTableWidgetItem;
		    	item->setText(querypos.value(7).toString());
		    	tabmain->setItem(querypos.at(), 4, item);
		    	
		    	item = new QTableWidgetItem;
		    	item->setText(querypos.value(8).toString());
		    	tabmain->setItem(querypos.at(), 5, item);
		    	
		    	item = new QTableWidgetItem;
		    	item->setText(querypos.value(9).toString());
		    	tabmain->setItem(querypos.at(), 6, item);
		    	
		    	item = new QTableWidgetItem;
		    	item->setText(QString("%1").arg(querypos.value(7).toDouble() * querypos.value(9).toDouble(), 0, 'f',2));
		    	tabmain->setItem(querypos.at(), 7, item);
		    	
		    	item = new QTableWidgetItem;
		    	item->setText(querypos.value(10).toString());
		    	tabmain->setItem(querypos.at(), 8, item);
		    	
				//check act. quantity and min. quantity
				qstr = "SELECT col3, col4 FROM "+querypos.value(2).toString()+" WHERE `ID` = "+querypos.value(3).toString()+";";
				QSqlQuery querycheckdb(qstr);
				querycheckdb.next();

		    	item = new QTableWidgetItem;
		    	item->setText(querycheckdb.value(0).toString());
		    	tabmain->setItem(querypos.at(), 9, item);
		    	
		    	item = new QTableWidgetItem;
		    	item->setText(querycheckdb.value(1).toString());
		    	tabmain->setItem(querypos.at(), 10, item);
		    	
		    	item = new QTableWidgetItem;
		    	item->setText(querypos.value(2).toString()+":#:"+querypos.value(3).toString());
		    	tabmain->setItem(querypos.at(), 11, item);
		    }
		}
  
		//Beträge neu berechnen
		double rabatt = boxdiscount->text().toDouble();
		double tot = boxtot->text().toDouble();
		double tot_excl = tot - (tot/100*rabatt);
		double vat = (tot_excl * 1.076) - tot_excl;
		double tot_incl = tot_excl  * 1.076;      
		boxtot_excl->setText(QString("%1").arg(tot_excl, 0, 'f',2));
		boxvat->setText(QString("%1").arg(vat, 0, 'f',2));
		boxtot_incl->setText(QString("%1").arg(tot_incl, 0, 'f',2));
	}
	if(source == "docs")
	{
		btncomplete->setEnabled(FALSE);
		btnsave->setEnabled(FALSE);
	}
	addrow();
	calc_tot();
}
//
void doceditfrm::savedoc()
{ 
    QDate date = boxdate->date();
    QString s = date.toString("dd.MM.yyyy");
    int row;
    if(opendocID!="")
    {
		//UPDATE Draft
		QSqlQuery query;
		query.prepare( "UPDATE `docdrafts` SET `doctyp` = :doctype, `date` = :date, `client` = :client, `salutation` = :salutation, `introduction` = :introduction, `comments` = :comments, `amount` = amount, `discount` = :discount WHERE `ID` = :ID LIMIT 1;");
		query.bindValue( ":doctype", docdef[cmbdoc->currentIndex()]);
		query.bindValue( ":date", s);
		query.bindValue( ":client", lblID->text());
		query.bindValue( ":salutation", txtsalutation->text());
		query.bindValue( ":introduction", boxotherinfo->toPlainText());
		query.bindValue( ":comments", boxcomments->toPlainText());
		query.bindValue( ":amount", boxtot->text());
		query.bindValue( ":discount", boxdiscount->text());
		query.bindValue( ":ID", opendocID);
		query.exec();
	
		QSqlQuery query2;
		query2.prepare("DELETE FROM `docpositions` WHERE `DOCID` = :id;");
		query2.bindValue(":id", opendocID);
		query2.exec();
	
		QSqlQuery query3;
		for(row=0;row<tabmain->rowCount()-1;row++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			
		    query3.prepare("INSERT INTO `docpositions` (`ID`, `DOCID`, `STOCK`, `STOCK_ID`, `DOC_POSITION`, `LABEL`, `DESCRIPTION`, `QUANTITY`, `UNIT`, `PRICE`, `VAT`, `TYPE`) VALUES ('', :docid, :stock, :stock_id, :doc_pos, :label, :description, :quantity, :unit, :price, :vat, 'docdrafts');");
		    query3.bindValue( ":docid", opendocID);
		    
		    item = tabmain->item(row, 11);
		    query3.bindValue( ":stock", item->text().section(":#:", 0, 0));
		    query3.bindValue( ":stock_id", item->text().section(":#:", 1, 1));
		    item = tabmain->item(row, 0);
		    query3.bindValue( ":doc_pos", item->text());
		    item = tabmain->item(row, 1);
		    query3.bindValue( ":label", item->text());
		    item = tabmain->item(row, 3);
		    query3.bindValue( ":description", item->text());
		    item = tabmain->item(row, 4);
		    query3.bindValue( ":quantity", item->text());
		    item = tabmain->item(row, 5);
		    query3.bindValue( ":unit", item->text());
		    item = tabmain->item(row, 6);
		    query3.bindValue( ":price", item->text());
		    item = tabmain->item(row, 8);
		    query3.bindValue( ":vat", item->text());
		    query3.exec();
		}
    }
    else
    {
		//INSERT
		QSqlQuery query;
		query.prepare("INSERT INTO `docdrafts` ( `ID` , `doctyp` , `date` , `client` , `salutation`, `introduction`, `comments`, `amount`, `discount` ) VALUES ('', :doctype, :date, :client, :salutation, :introduction, :comments, :amount, :discount);");
		query.bindValue( ":doctype", docdef[cmbdoc->currentIndex()]);
		query.bindValue( ":date", s);
		query.bindValue( ":client", lblID->text());
		query.bindValue( ":salutation", txtsalutation->text());
		query.bindValue( ":introduction", boxotherinfo->toPlainText());
		query.bindValue( ":comments", boxcomments->toPlainText());
		query.bindValue( ":amount", boxtot->text());
		query.bindValue( ":discount", boxdiscount->text());
		query.exec();
	
		QSqlQuery query2;
		query2.prepare("SELECT ID FROM docdrafts WHERE doctyp = :doctype AND date = :date AND client = :client AND salutation = :salutation AND introduction = :introduction AND comments = :comments AND amount = :amount AND `discount` = :discount ORDER BY ID DESC;");
		query2.bindValue( ":doctype", docdef[cmbdoc->currentIndex()]);
		query2.bindValue( ":date", s);
		query2.bindValue( ":client", lblID->text());
		query2.bindValue( ":salutation", txtsalutation->text());
		query2.bindValue( ":introduction", boxotherinfo->toPlainText());
		query2.bindValue( ":comments", boxcomments->toPlainText());
		query2.bindValue( ":amount", boxtot->text());
		query2.bindValue( ":discount", boxdiscount->text());
		query2.exec();
		query2.next();  
		opendocID = query2.value(0).toString();
	
		QSqlQuery query3;
		for(row=0;row<tabmain->rowCount()-1;row++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			
		    query3.prepare("INSERT INTO `docpositions` (`ID`, `DOCID`, `STOCK`, `STOCK_ID`, `DOC_POSITION`, `LABEL`, `DESCRIPTION`, `QUANTITY`, `UNIT`, `PRICE`, `VAT`, `TYPE`) VALUES ('', :docid, :stock, :stock_id, :doc_pos, :label, :description, :quantity, :unit, :price, :vat, 'docdrafts');");
		    query3.bindValue( ":docid", opendocID);
		    
		    item = tabmain->item(row, 11);
		    query3.bindValue( ":stock", item->text().section(":#:", 0, 0));
		    query3.bindValue( ":stock_id", item->text().section(":#:", 1, 1));
		    item = tabmain->item(row, 0);
		    query3.bindValue( ":doc_pos", item->text());
		    item = tabmain->item(row, 1);
		    query3.bindValue( ":label", item->text());
		    item = tabmain->item(row, 3);
		    query3.bindValue( ":description", item->text());
		    item = tabmain->item(row, 4);
		    query3.bindValue( ":quantity", item->text());
		    item = tabmain->item(row, 5);
		    query3.bindValue( ":unit", item->text());
		    item = tabmain->item(row, 6);
		    query3.bindValue( ":price", item->text());
		    item = tabmain->item(row, 8);
		    query3.bindValue( ":vat", item->text());
		    query3.exec();
		}
    }
}
//
void doceditfrm::savecompletedoc()
{ 
    QDate date = boxdate->date();
    QString s = date.toString("dd.MM.yyyy");
    int row;

    QSqlQuery query;
    query.prepare("INSERT INTO `docs` ( `ID` , `doctyp` , `date` , `client` , `salutation`, `introduction`, `comments`, `amount`, `discount`, `docID` ) VALUES ('', :doctype, :date, :client, :salutation, :introduction, :comments, :amount, :discount, :docID);");
    query.bindValue( ":doctype", docdef[cmbdoc->currentIndex()]);
    query.bindValue( ":date", s);
    query.bindValue( ":client", lblID->text());
    query.bindValue( ":salutation", txtsalutation->text());
    query.bindValue( ":introduction", boxotherinfo->toPlainText());
    query.bindValue( ":comments", boxcomments->toPlainText());
    query.bindValue( ":amount", boxtot->text());
    query.bindValue( ":discount", boxdiscount->text());
    query.bindValue( ":docID", txtdoccount->text());
    query.exec();
    
    QSqlQuery querycheck;
    querycheck.prepare("SELECT ID FROM docs WHERE doctyp = :doctype AND date = :date AND client = :client AND salutation = :salutation AND introduction = :introduction AND comments = :comments AND amount = :amount AND `discount` = :discount ORDER BY ID DESC;");
    querycheck.bindValue( ":doctype", docdef[cmbdoc->currentIndex()]);
    querycheck.bindValue( ":date", s);
    querycheck.bindValue( ":client", lblID->text());
    querycheck.bindValue( ":salutation", txtsalutation->text());
    querycheck.bindValue( ":introduction", boxotherinfo->toPlainText());
    querycheck.bindValue( ":comments", boxcomments->toPlainText());
    querycheck.bindValue( ":amount", boxtot->text());
    querycheck.bindValue( ":discount", boxdiscount->text());
    querycheck.exec();
    querycheck.next();  
    opendocID = querycheck.value(0).toString();
    
    QSqlQuery query2;
    query2.prepare("DELETE FROM `docpositions` WHERE `DOCID` = :id;");
    query2.bindValue(":id", opendocID);
    query2.exec();
	
    QSqlQuery query3;
    for(row=0;row<tabmain->rowCount()-1;row++)
    {
		QTableWidgetItem *item = new QTableWidgetItem;
			
	    query3.prepare("INSERT INTO `docpositions` (`ID`, `DOCID`, `STOCK`, `STOCK_ID`, `DOC_POSITION`, `LABEL`, `DESCRIPTION`, `QUANTITY`, `UNIT`, `PRICE`, `VAT`, `TYPE`) VALUES ('', :docid, :stock, :stock_id, :doc_pos, :label, :description, :quantity, :unit, :price, :vat, 'docs');");
	    query3.bindValue( ":docid", opendocID);
		    
	    item = tabmain->item(row, 11);
	    query3.bindValue( ":stock", item->text().section(":#:", 0, 0));
	    query3.bindValue( ":stock_id", item->text().section(":#:", 1, 1));
	    item = tabmain->item(row, 0);
	    query3.bindValue( ":doc_pos", item->text());
	    item = tabmain->item(row, 1);
	    query3.bindValue( ":label", item->text());
	    item = tabmain->item(row, 3);
	    query3.bindValue( ":description", item->text());
	    item = tabmain->item(row, 4);
	    query3.bindValue( ":quantity", item->text());
	    item = tabmain->item(row, 5);
	    query3.bindValue( ":unit", item->text());
	    item = tabmain->item(row, 6);
	    query3.bindValue( ":price", item->text());
	    item = tabmain->item(row, 8);
	    query3.bindValue( ":vat", item->text());
	    query3.exec();
    }
    
    //if exists delete draft
    QString connstr4 = "DELETE FROM `docdrafts` WHERE `ID` = '"+opendocID+"';";
    QSqlQuery query4(connstr4);
    
    btncomplete->setEnabled(FALSE);
    btnsave->setEnabled(FALSE);
}
//
QString doceditfrm::writetexfile()
{
    int i;
    //Check DoG
    QSqlQuery querydays;
    querydays.prepare("SELECT value FROM maincfgtab WHERE `var`='DoG'");
    querydays.exec();
    querydays.next();
    
    QString tabhead = "";
    QString tabcontent = "";
    if(cmbdoc->currentIndex() != 2)
    {
		//TABHEAD erstellen
		tabhead = "\\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(0)->text() + "}\\end{footnotesize} & \\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(3)->text() + "}\\end{footnotesize} & \\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(4)->text() + "}\\end{footnotesize} & \\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(5)->text() + "}\\end{footnotesize} & \\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(6)->text() + "}\\end{footnotesize} & \\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(7)->text() + "}\\end{footnotesize} & \\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(8)->text() + "}\\end{footnotesize}";
    
		//TABCONTENT erstellen
		for(i=0;i<tabmain->rowCount()-1;i++)
		{
			QTableWidgetItem *item = tabmain->item(i, 0);
			tabcontent += item->text() + " & ";
			
			item = new QTableWidgetItem;
			item = tabmain->item(i, 3);
			tabcontent += item->text().simplified().replace("\n", "\\newline ") + " & ";
			
			item = new QTableWidgetItem;
			item = tabmain->item(i, 4);
			tabcontent += item->text() + " & ";
			
			item = new QTableWidgetItem;
			item = tabmain->item(i, 5);
			tabcontent += item->text() + " & ";
			
			item = new QTableWidgetItem;
			item = tabmain->item(i, 6);
			tabcontent += item->text() + " " + currency + " & ";
			
			item = new QTableWidgetItem;
			item = tabmain->item(i, 7);
			tabcontent += item->text() + " " + currency + " & ";
			
			item = new QTableWidgetItem;
			item = tabmain->item(i, 8);
			tabcontent += item->text() + " \\\\ \n";
		}
	} else {
		//TABHEAD erstellen
		tabhead = "\\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(0)->text() + "}\\end{footnotesize} & \\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(3)->text() + "}\\end{footnotesize} & \\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(4)->text() + "}\\end{footnotesize} & \\begin{footnotesize}\\textbf{" + tabmain->horizontalHeaderItem(5)->text() + "}\\end{footnotesize}";
    
		//TABCONTENT erstellen
		for(i=0;i<tabmain->rowCount()-1;i++)
		{
			QTableWidgetItem *item = tabmain->item(i, 0);
			tabcontent += item->text() + " & ";
			
			item = new QTableWidgetItem;
			item = tabmain->item(i, 3);
			tabcontent += item->text().simplified().replace("\n", "\\newline ") + " & ";
			
			item = new QTableWidgetItem;
			item = tabmain->item(i, 4);
			tabcontent += item->text() + " & ";
			
			item = new QTableWidgetItem;
			item = tabmain->item(i, 5);
			tabcontent += item->text() + " \\\\ \n";
		}
    }
    
    QDir d(docfolder+"/"+lblID->text());
    if ( !d.exists() )
		d.mkdir(docfolder+"/"+lblID->text());
    
    QString templatestr = loadtemplatedata(temp_id[cmbdoc->currentIndex()].toInt());

	QTime now = QTime::currentTime();
	QDate today = QDate::currentDate();
    QFile output(QDir::homePath()+"/.first4/tmp/"+username+"-"+today.toString("yyyyMMdd")+now.toString("hhmmsszzz")+".tex");
	if ( output.open( QIODevice::WriteOnly ) )
	{
	    //QString line;
	    QTextStream outstream( &output );
		templatestr = templatestr.replace("+++DATE+++", boxdate->date().toString("dd. MMMM yyyy"));
		templatestr = templatestr.replace("+++RECIPIENT+++", boxaddress->toPlainText().replace("\n", "\\newline "));
		templatestr = templatestr.replace("+++LOCATION+++", location);
		templatestr = templatestr.replace("+++DOCTYPE+++", cmbdoc->currentText());
		templatestr = templatestr.replace("+++DOCID+++", txtdoccount->text());
		templatestr = templatestr.replace("+++TABHEAD+++", tabhead);
		templatestr = templatestr.replace("+++TABCONTENT+++", tabcontent);
		templatestr = templatestr.replace("+++DoG+++", boxdate->date().addDays(querydays.value(0).toInt()).toString("dd.MM.yyyy"));
		if(templatestr.contains("+++DISCOUNT+++") > 0)
		{
		    if(boxdiscount->text().toDouble()>0)
		    {
				QString tmpdiscount = "\\multicolumn{2}{@{}l}{\\textbf{Total:}} & \\textbf{"+boxtot->text()+" "+currency+"} \\\\ \n";
				tmpdiscount += "\\begin{scriptsize}"+tr("Discount")+"\\end{scriptsize} & \\begin{scriptsize}"+boxdiscount->text()+"\\% \\end{scriptsize}  & \\begin{scriptsize}"+QString("%1").arg(boxtot->text().toDouble()/100*boxdiscount->text().toDouble(), 0, 'f',2)+" "+currency+" \\end{scriptsize} \\\\ \n";
				templatestr = templatestr.replace("+++DISCOUNT+++", tmpdiscount);
		    }
		    else
				templatestr = templatestr.replace("+++DISCOUNT+++", "");
		}
		templatestr = templatestr.replace("+++TOTEXCL_DESC+++", tr("Amount excl. VAT:"));
		templatestr = templatestr.replace("+++TOTEXCL+++", boxtot_excl->text()+ " "+currency);

		if(templatestr.contains("+++VAT+++") > 0)
		{
		    QString tmpvat = "\\begin{scriptsize}"+tr("VAT rate")+"\\end{scriptsize} &\\begin{scriptsize}"+tr("VAT amount")+"\\end{scriptsize} & \\begin{scriptsize}"+tr("VAT")+"\\end{scriptsize} \\\\ \n";
		    
		    double vattot = 0;
		    for(i=0;i<vatlist.count();i++)
		    {
				vattot += vatamount[i].toDouble() * (vatlist[i].toDouble() / 100);
				QString vattmp = QString("%1").arg(vatamount[i].toDouble() * (vatlist[i].toDouble() / 100), 0, 'f',2);
				if(vatamount[i].toDouble() > 0)
				    tmpvat += "\\begin{scriptsize}"+vatlist[i].replace("%", "\%")+"\\end{scriptsize} & \\begin{scriptsize}"+vatamount[i]+" "+currency+" \\end{scriptsize} & \\begin{scriptsize}"+vattmp+" "+currency+" \\end{scriptsize} \\\\ \n";
		    }
		    templatestr = templatestr.replace("+++VAT+++", tmpvat);
		}		

		templatestr = templatestr.replace("+++TOTINCL_DESC+++", tr("Net amount:"));		
		templatestr = templatestr.replace("+++TOTINCL+++", boxtot_incl->text()+ " "+currency);
		templatestr = templatestr.replace("+++KIND_REGARDS+++", tr("Kind regards"));
		templatestr = templatestr.replace("+++GENERAL+++", tr("General informations:"));
		templatestr = templatestr.replace("+++GENERAL_INFORMATIONS+++", loadgeneralinfo());
		templatestr = templatestr.replace("+++USER+++", fullname);
		templatestr = templatestr.replace("+++CUSTOMER+++", boxaddress->toPlainText().section("\n", 0, 0));
		
		if(txtsalutation->text() != "")
		    templatestr = templatestr.replace("+++SALUTATION+++", "\\begin{footnotesize} \\vspace{8mm} \\begin{tabular}{@{}l} \\textbf{"+txtsalutation->text()+"} \\\\ \\end{tabular} \\end{footnotesize}");
		else
		    templatestr = templatestr.replace("+++SALUTATION+++", "");
		
		if(boxotherinfo->toPlainText() != "")
		    templatestr = templatestr.replace("+++INTRODUCTION+++", "\\begin{footnotesize} \\vspace{6mm} \\begin{tabular}{@{}l} "+boxotherinfo->toPlainText().replace("\n", " \\\\ \n")+" \\\\ \\end{tabular} \\end{footnotesize}");
		else
		    templatestr = templatestr.replace("+++INTRODUCTION+++", "");

		if(templatestr.contains("+++COMMENTS+++") > 0)
		{
		    if(boxcomments->toPlainText() != "")
		    {
				QString tmpcomments = "\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n";
				tmpcomments += "\\textbf{"+tr("Comments:")+"}\\\\ \n";
				tmpcomments += boxcomments->toPlainText().replace("\n", " \\\\ \n") + " \\\\ \n";
				tmpcomments += "\\end{tabular*} \n \\vspace{5mm} \n";
				templatestr = templatestr.replace("+++COMMENTS+++", tmpcomments);
		    }
		    else
				templatestr = templatestr.replace("+++COMMENTS+++", "");
		}
		outstream << templatestr << "\n";
	    output.close();
	} else {
	    QMessageBox::critical(0,"Error...",tr("Can't write ouputfile!"));
	}
    
    //converting text to dvi   
    QProcess *procdvi = new QProcess( this );
    QStringList args;
    args << "-output-directory="+QDir::homePath()+"/.first4/tmp/" << output.fileName();
 	procdvi->start("latex", args);
 	if(procdvi->exitStatus() == QProcess::CrashExit ) 
				QMessageBox::critical(0,"Error...", tr("Can't convert TEX-File."));

	return output.fileName().replace(".tex", ".dvi");
}
//
void doceditfrm::printpreview()
{
	vars v;
	QString tool = v.get_tool("DVIVIEWER");
	if(tool != "")
	{
    	if(tabmain->rowCount()>1)
	    {
			if(lblID->text()!="")
			{
		    	QString document = writetexfile();
		    
				//Show Report
		    	QProcess *procshow = new QProcess( this );
			    QStringList args;
		    	args << document;
			    procshow->start(tool, args);
		    	if(procshow->exitStatus() == QProcess::CrashExit ) 
					QMessageBox::critical(0,"Error...", tr("Can't find DVI-File."));
			}
    	}
	}
	else
		QMessageBox::critical(0,"Error...", tr("You must first define a DVI-Viewer like KDVI or Okular in the settings module"));
}

void doceditfrm::print()
{
    if(boxaddress->toPlainText() != "" && lblID->text() != "-")
		printreport(FALSE);
    else
		QMessageBox::information(0, tr("Address..."), tr("Please select a receiver"));
}
//
void doceditfrm::printvesr()
{
    calc_tot();
    QStringList vesrcode = vesr();
    
    /*QFile file(docfolder+"/tmpesr.kud");
    if ( file.open( QIODevice::WriteOnly ) )
    {
		QTextStream stream( &file );	
		stream << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n";
		stream << "<!DOCTYPE KugarData [\n    <!ATTLIST KugarData\n        Template CDATA #REQUIRED>\n]>\n";
		stream << "<KugarData>\n";
		stream << "<Field level=\"0\"\n";
		stream << "esr1=\""+vesrcode[0]+"\"\n";
		stream << "esr2 = \""+vesrcode[1]+"\"\n";
		stream << "company = \""+companyaddress+"\"\n";
		stream << "date = \""+QDate::currentDate().toString("dd.MM.yyyy")+"\"\n";
		stream << "tnr = \""+tnr+"\"\n";
		stream << "client = \""+boxaddress->toPlainText()+"\"\n";
		stream << "amount = \""+boxtot_incl->text().section(".", 0, 0)+"\"\n";
		stream << "amountcents = \""+boxtot_incl->text().section(".", 1, 1)+"\"\n";
		stream << "/>\n\n</KugarData>";
		file.close();
    }
    file.remove();*/

    QString templatestr = loadtemplatedata();
    QTime now = QTime::currentTime();
	QDate today = QDate::currentDate();
    QFile output(QDir::homePath()+"/.first4/tmp/"+username+"-"+today.toString("yyyyMMdd")+now.toString("hhmmsszzz")+".tex");
	if ( output.open(QIODevice::WriteOnly) )
	{
	    QTextStream outstream( &output );	
	    templatestr = templatestr.replace("+++VESR1+++", vesrcode[0]);
	    templatestr = templatestr.replace("+++VESR2+++", vesrcode[1]);
		templatestr = templatestr.replace("+++COMPANY+++", companyaddress);
		templatestr = templatestr.replace("+++DATE+++", QDate::currentDate().toString("dd.MM.yyyy"));
		templatestr = templatestr.replace("+++TNR+++", tnr);
		templatestr = templatestr.replace("+++CUSTOMER+++", boxaddress->toPlainText());
		templatestr = templatestr.replace("+++AMOUNT+++", boxtot_incl->text().section(".", 0, 0));
		templatestr = templatestr.replace("+++AMOUNTCENTS+++", boxtot_incl->text().section(".", 1, 1));
		outstream << templatestr << "\n";
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
		
    now = QTime::currentTime();
	while(now.addSecs(2) >= QTime::currentTime()) ; //wait 2 secs
		    		  
	QString documentfile = output.fileName().replace(".tex", ".dvi");
    QString psfile = documentfile;
    QProcess *procps = new QProcess( this );
    args.clear();
    args << "-o" << psfile.replace(".dvi", ".ps") << documentfile;
    procps->start("dvips", args);
	if(procps->exitStatus() == QProcess::CrashExit ) 
		QMessageBox::critical(0,"Error...", tr("Can't convert to Postscript file."));
	else
	{
	    QProcess *procprint = new QProcess( this );
    	args.clear();
	    args << psfile;
	    procprint->start("kprinter", args);
	    if(procprint->exitStatus() != QProcess::NormalExit ) 
			QMessageBox::critical(0,"Error...", tr("Error during printing process."));
	}
}
//
QStringList doceditfrm::vesr()
{
    QStringList vesrarray, returnstrlist;
    vesrarray <<"0"<<"9"<<"4"<<"6"<<"8"<<"2"<<"7"<<"1"<<"3"<<"5";
    double betrag = boxtot_incl->text().toDouble() * 100;
    QString betragstring = QString("%1").arg(betrag, 0, 'f', 0);
    betragstring = betragstring.rightJustified(10, '0' );
    QString vesrcode = "01"+betragstring;
    QString R1 = 0;
    int i;
    QStringList tmplist(vesrcode.split(""));
    for(i = 0; i < vesrcode.length(); i++ )				//Schleife entsprechend der Anzahl Ziffer
    {	
		int Rbb = R1.toInt() + tmplist[i].toInt();		//Rest plus entspr. Ziffer - Ganzzahlen
		R1 = vesrarray[Rbb % 10];				//Modulo10 Algorithmus abarbeiten
    }
    QString P1 = QString("%1").arg((10 - R1.toInt()) % 10, 10, 0);
    
    QString refnr = txtdoccount->text().right(8);
    refnr = refnr.rightJustified(15, '0', TRUE);
    
    QStringList tmplist2(refnr.split(""));
    QString R2 = 0;
    for (i = 0; i < refnr.length(); i++ )			//Schleife entsprechend der Anzahl Ziffer	
    {	
		int Rpr = R2.toInt() + tmplist2[i].toInt();	//Rest plus entspr. Ziffer - Ganzzahlen
		R2 = vesrarray[Rpr % 10];			//Modulo10 Algorithmus abarbeiten
    }
    QString P2 = QString("%1").arg((10 - R2.toInt()) % 10, 10, 0);
    
    returnstrlist.append(refnr.mid(0, 1) +" "+refnr.mid(1, 5) +" "+refnr.mid(6, 5) +" "+refnr.mid(11, 5) + P2.simplified());
    
    returnstrlist.append(vesrcode+P1.simplified()+">"+refnr + P2.simplified()+"+ "+tnr.section("-", 0, 0).leftJustified(2, '.', TRUE )+tnr.section("-", 1, 1).leftJustified(6, '0', TRUE )+tnr.section("-", 2, 2).leftJustified(1, '.', TRUE )+">");
    return returnstrlist;
}
//
void doceditfrm::printreport(bool complete)
{
    if(tabmain->rowCount()>1)
    {
		if(lblID->text()!="")
		{
		    QString document = writetexfile();
		    
		    QTime now = QTime::currentTime();
			while(now.addSecs(2) >= QTime::currentTime()) ; //wait 2 secs
		    		    
		    QString psfile = document;
		    QProcess *procps = new QProcess( this );
		    QStringList args;
		    args << "-o" << psfile.replace(".dvi", ".ps") << document;
		
		    procps->start("dvips", args);
		    if(procps->exitStatus() == QProcess::CrashExit ) 
				QMessageBox::critical(0,"Error...", tr("Can't find DVI-File."));
    
		    QProcess *procprint = new QProcess( this );
		    args.clear();
		    args << psfile;
		    procprint->start("kprinter", args);
   		    if(procprint->exitStatus() == QProcess::CrashExit ) 
				QMessageBox::critical(0,"Error...", tr("Can't print File."));
	    
		    if(complete)
		    {
			    //move file in the correct folder
    			QFile dvifile(document);
    		
    			if(!dvifile.rename(docfolder+QDir::separator()+lblID->text()+QDir::separator()+docfile))
					QMessageBox::critical(0,"Error...", tr("Can't move file to customer folder."));
		    }
		}
    }
}
//
void doceditfrm::reject()
{
    QFile delfile(docfolder+"/"+lblID->text()+"/"+docfile);
    if(delfile.exists() && docfile!="" && opendocID!="")
    {
		int r=QMessageBox::information(this, tr("Document not saved..."), tr("Document %1 is not completed!\n\n Save as draft?").arg(docfile),QMessageBox::Yes, QMessageBox::No); 
		if(r==0)
		    savedoc();
    }

	QSqlDatabase::database().rollback();
	vars v;
	v.unlockrow(opendocSource, opendocID);

	this->close();
}
//
void doceditfrm::excl_vat()
{
    boxtot_incl->setText(QString("%1").arg(boxtot_excl->text().toDouble() + boxvat->text().toDouble(), 0, 'f',2));
}
//
void doceditfrm::editposition()
{
    int i;
    doceditposition *epos = new doceditposition;
    QTableWidgetItem *item = tabmain->item(tabmain->currentRow(),0);
    if(item)
	    epos->txtpos->setText(item->text());

    item = tabmain->item(tabmain->currentRow(),1);
    if(item)
	    epos->txtlabel->setText(item->text());
    
    item = tabmain->item(tabmain->currentRow(),3);
    if(item)
	    epos->txtdescription->setText(item->text().simplified());
    
    item = tabmain->item(tabmain->currentRow(),4);
    if(item)
	    epos->txtquantity->setText(item->text());
    
    item = tabmain->item(tabmain->currentRow(),5);
    if(item)
	    epos->txtunit->setText(item->text());
    
    epos->cmbvat->addItems(vatlist);
    for(i=0;i<vatlist.count();i++)
    {
    	item = tabmain->item(tabmain->currentRow(),8);
		if(item && vatlist[i] == item->text())
		    epos->cmbvat->setCurrentIndex(i);
    }
    if(tabmain->item(tabmain->currentRow(),6)->text()!="")
		epos->txtprice->setText(tabmain->item(tabmain->currentRow(),6)->text());
    else
		epos->txtprice->setText("0.00");
    
    if(epos->exec())
    {
    	item = new QTableWidgetItem;
    	item->setText(epos->txtlabel->text());
    	tabmain->setItem(tabmain->currentRow(), 1, item);
		
		item = new QTableWidgetItem;
    	item->setText(epos->txtdescription->toPlainText());
		item->setTextAlignment(Qt::AlignLeft | Qt::AlignBottom);
    	tabmain->setItem(tabmain->currentRow(), 3, item);
    	
    	item = new QTableWidgetItem;
    	item->setText(epos->txtquantity->text());
    	tabmain->setItem(tabmain->currentRow(), 4, item);
    	
    	item = new QTableWidgetItem;
    	item->setText(epos->txtunit->text());
    	tabmain->setItem(tabmain->currentRow(), 5, item);
    	
    	item = new QTableWidgetItem;
    	item->setText(epos->txtprice->text());
    	tabmain->setItem(tabmain->currentRow(), 6, item);
    	
    	item = new QTableWidgetItem;
    	item->setText(epos->cmbvat->currentText());
    	tabmain->setItem(tabmain->currentRow(), 8, item);
    	navtable();
    }
}
//
void doceditfrm::navtabonoff(bool state)
{
	if(state)
		connect(tabmain, SIGNAL(cellChanged(int, int)), this, SLOT(navtable()));
	else
		disconnect(tabmain, SIGNAL(cellChanged(int, int)), this, SLOT(navtable()));
}
//
QString doceditfrm::loadtemplatedata(int dbid)
{
	QString answ;
	QString qstr = QString("SELECT data FROM templatestab WHERE `ID`='%1';").arg(dbid);
	QSqlQuery query(qstr);
	if ( query.isActive())
	{
		query.next();
		answ = query.value(0).toString();
	}
	else
	{
		QSqlError qerror = query.lastError();
		QMessageBox::warning ( 0, tr ( "Can't load template description..." ), qerror.text() );
	}
	return answ;
}
//
QString doceditfrm::loadgeneralinfo()
{
	QSqlQuery query( "SELECT value FROM maincfgtab WHERE `var`='doc_generalinfo';" );
	query.next();
	return query.value(0).toString();
}
//
QString doceditfrm::loadtemplatedata()
{
	QString answ;
	QSqlQuery query("SELECT data FROM templatestab WHERE `name`='sys_vesr';");
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

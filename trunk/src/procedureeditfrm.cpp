#include <QSqlQuery>
#include <QMessageBox>
#include <QMenu>
//
#include "procedureeditfrm.h"
#include "addrselectfrm.h"
#include "stockselfrm.h"
#include "proceduretask.h"
#include "doceditposition.h"
//
extern QString username, fullname;
bool newentry;
QStringList ordervatlist;
//
procedureeditfrm::procedureeditfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void procedureeditfrm::init()
{
    this->setFixedSize(this->width(), this->height());    
    
    txtresponsible->setText(fullname);
    
    dateedit1->setDate(QDate::currentDate());
    dateedit2->setDate(QDate::currentDate());
    newentry = FALSE;
    
    //maintab initialisieren
    taborders->setColumnWidth(0,30);
    taborders->setColumnWidth(1,90);
    taborders->setColumnWidth(2,20);
    taborders->setColumnWidth(3,230);
    taborders->setColumnWidth(4,60);
    taborders->setColumnWidth(5,60);
    taborders->setColumnWidth(6,100);       
    taborders->setColumnWidth(7,100);
    taborders->hideColumn(8);
    taborders->hideColumn(9);
    taborders->hideColumn(10);

    taborders->setRowCount(1);
    
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setCheckState(Qt::Unchecked);
 	taborders->setItem(0, 0, item);
 	 
	item = new QTableWidgetItem;   
 	item->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
 	taborders->setItem(0, 2, item);
 	
 	item = new QTableWidgetItem;
 	taborders->setItem(0, 3, item);
    
 	item = new QTableWidgetItem;
 	item->setText("0");
 	taborders->setItem(0, 4, item);
 	
 	item = new QTableWidgetItem;
 	item->setText("0.00");
 	taborders->setItem(0, 6, item);
 	
 	item = new QTableWidgetItem;
 	item->setText("0.0");
 	taborders->setItem(0, 7, item);
    
    tabtasks->setColumnWidth(0, 30);
    tabtasks->setColumnWidth(1, 515);
    tabtasks->setColumnWidth(2, 100);

    tabtasks->setRowCount(1);
    item = new QTableWidgetItem;
    item->setCheckState(Qt::Unchecked);
 	tabtasks->setItem(0, 0, item);
 	
 	item = new QTableWidgetItem;
 	item->setText(QDate::currentDate().toString("dd.MM.yyyy"));
 	tabtasks->setItem(0, 2, item); 	
    
    cmbstate->setCurrentIndex(0);
    
    //auftragsid aus ablcfgtab laden
    
    QString qstr = "SELECT auftrid FROM procedurecfgtab;";
    QSqlQuery query(qstr);
    query.next();
    txtorderid->setText(query.value(0).toString());   
    initvat();
    
	connect(btnaccept, SIGNAL(released()), this, SLOT(acceptdata()));
	connect(btnaddr, SIGNAL(released()), this, SLOT(searchaddress()));
	connect(btncanceladdr, SIGNAL(released()), this, SLOT(clearaddress()));
    connect(taborders, SIGNAL(cellChanged(int, int)), this, SLOT(navordertabs(int)));
    connect(tabtasks, SIGNAL(cellChanged(int, int)), this, SLOT(navtasktab(int)));
    connect(taborders, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));
    connect(tabtasks, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));
    connect(taborders, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(checkdb()));
}
//
void procedureeditfrm::searchaddress()
{
    addrselectfrm *seladdr = new addrselectfrm;
    seladdr->init();
    if(seladdr->exec())
    {
       QString answer = seladdr->getadress();
       QStringList fields = answer.split(":#:");
       txtcustomer->setText(fields[0].replace("<BR>", "\n"));
       lblcustomerid->setText(fields[1]);
    }
}

void procedureeditfrm::initvat()
{
    ordervatlist.clear();
    QString connstr = "SELECT col1 FROM vattab ORDER BY ID;";
    QSqlQuery query(connstr);
    if ( query.isActive())
    {
	while(query.next())
	    ordervatlist.append(query.value(0).toString());
    }
}

void procedureeditfrm::clearaddress()
{
       txtcustomer->setText("");
       lblcustomerid->setText("");
}

void procedureeditfrm::acceptdata()
{
    if(newentry)
    {
		QString conn = "UPDATE `procedurecfgtab` SET `auftrid`='"+QString("%1").arg((txtorderid->text().toInt()+1), 0, 10)+"';"; 
		QSqlQuery query(conn);
		accept();    
    }
    else
		accept();
}
//
void procedureeditfrm::navtasktab(int row)
{
    if(row == tabtasks->rowCount()-1)
    {
	    QTableWidgetItem *item = tabtasks->item(row, 1);
	    if(item != 0)
	    {
	    	if(item->text() != "")
	    	{
	    		tabtasks->setRowCount(tabtasks->rowCount()+1);	
				item = new QTableWidgetItem;
			    item->setCheckState(Qt::Unchecked);
			 	tabtasks->setItem(tabtasks->rowCount()-1, 0, item);
 	
			 	item = new QTableWidgetItem;
			 	item->setText(QDate::currentDate().toString("dd.MM.yyyy"));
			 	tabtasks->setItem(tabtasks->rowCount()-1, 2, item); 
    		}
    	}
    }
}
 
void procedureeditfrm::navordertabs(int row)
{
	disconnect(taborders, SIGNAL(cellChanged(int, int)), this, SLOT(navordertabs(int)));
    QTableWidgetItem *item = new QTableWidgetItem;

    if(row == taborders->rowCount()-1)
    {
	    taborders->setRowCount(taborders->rowCount()+1);

	    item = new QTableWidgetItem;
	    item->setCheckState(Qt::Unchecked);
	 	taborders->setItem(taborders->rowCount()-1, 0, item);
	 	 
		item = new QTableWidgetItem;   
	 	item->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
	 	taborders->setItem(taborders->rowCount()-1, 2, item);
    
	 	item = new QTableWidgetItem;
	 	taborders->setItem(taborders->rowCount()-1, 3, item);
    
	 	item = new QTableWidgetItem;
	 	item->setText("0");
	 	taborders->setItem(taborders->rowCount()-1, 4, item);
 	
	 	item = new QTableWidgetItem;
	 	item->setText("0.00");
	 	taborders->setItem(taborders->rowCount()-1, 6, item);
 	
	 	item = new QTableWidgetItem;
	 	item->setText("0.0");
	 	taborders->setItem(taborders->rowCount()-1, 7, item);
    }
    item = new QTableWidgetItem;
    item = taborders->item(row,0);
    item->setText("");
    
    item = new QTableWidgetItem;
    item = taborders->item(row,2);
    item->setText("");
    
    item = new QTableWidgetItem;
    item = taborders->item(row,4);
    QString tmpstr = item->text();
    double quantity = tmpstr.toDouble(); 

    item = new QTableWidgetItem;
    item = taborders->item(row,8);
    if(item != 0)
	    tmpstr = item->text();
    else
	    tmpstr = "";
    double actquantity = tmpstr.toDouble();

    if (tmpstr != "")
    {
		if(quantity > actquantity)
		    QMessageBox::information(0,tr("Stock..."), tr("The entered quantity exceeds the stock!")); 
    }
    item = new QTableWidgetItem;
    item = taborders->item(row,6);
    tmpstr = item->text();
    double p_single = tmpstr.toDouble();

    item = new QTableWidgetItem;
    item->setText(QString("%1").arg(p_single, 0, 'f',2));
	taborders->setItem(row, 6, item);
	
	connect(taborders, SIGNAL(cellChanged(int, int)), this, SLOT(navordertabs(int)));
}


void procedureeditfrm::checkdb()
{
	disconnect(taborders, SIGNAL(cellChanged(int, int)), this, SLOT(navordertabs(int)));
	QTableWidgetItem *testitem1 = taborders->item(taborders->currentRow(),1);
	QTableWidgetItem *testitem2 = taborders->item(taborders->currentRow(),3);
	if(taborders->currentColumn()==2 && testitem1 != 0 && testitem1->text()!="" && testitem2->text().simplified()=="")
    {
		stockselfrm *sfrm = new stockselfrm;
	    QSqlQuery query("SELECT name, description FROM datatabs WHERE `tabtyp` = 'stock' AND `users` LIKE '%"+username+"%';");
	    if(query.isActive())
	    {
			while(query.next())
			{
				QString qstr = QString("SELECT ID, col1, col2, col3, col5, col8, col12, col6 FROM %1 WHERE col1 LIKE '%%2%' AND `col13`='1' ORDER BY col1 ASC;").arg(query.value(0).toString()).arg(testitem1->text());
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
					    item->setText(6, ordervatlist[query2.value(6).toInt()]);
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
					taborders->setItem(taborders->currentRow(), 1, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(2));
					taborders->setItem(taborders->currentRow(), 3, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(4));
					taborders->setItem(taborders->currentRow(), 5, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(5));
					taborders->setItem(taborders->currentRow(), 6, tabmainitem);
	
					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(6));
					taborders->setItem(taborders->currentRow(), 7, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(3));					
					taborders->setItem(taborders->currentRow(), 8, tabmainitem);

					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(7));
					taborders->setItem(taborders->currentRow(), 9, tabmainitem);
					
					tabmainitem = new QTableWidgetItem;
					tabmainitem->setText(item->text(8));
					taborders->setItem(taborders->currentRow(), 10, tabmainitem);
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
				taborders->setItem(taborders->currentRow(), 1, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(2));
				taborders->setItem(taborders->currentRow(), 3, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(4));
				taborders->setItem(taborders->currentRow(), 5, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(5));
				taborders->setItem(taborders->currentRow(), 6, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(6));
				taborders->setItem(taborders->currentRow(), 7, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(3));					
				taborders->setItem(taborders->currentRow(), 8, tabmainitem);

				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(7));
				taborders->setItem(taborders->currentRow(), 9, tabmainitem);
					
				tabmainitem = new QTableWidgetItem;
				tabmainitem->setText(item->text(8));
				taborders->setItem(taborders->currentRow(), 10, tabmainitem);
			}
	    }
    }
	connect(taborders, SIGNAL(cellChanged(int, int)), this, SLOT(navordertabs(int)));	
}

void procedureeditfrm::contmenu()
{
    QMenu* contextMenu = new QMenu( this );
    Q_CHECK_PTR( contextMenu );

    if(tabmain->currentIndex() == 2)
    {
	    QAction* checkstock = new QAction( tr("&Check stock"), this );
		connect(checkstock , SIGNAL(triggered()), this, SLOT(checkdb()));
		contextMenu->addAction(checkstock);
	    QAction* editrow = new QAction( tr("&Edit entry"), this );
		connect(editrow , SIGNAL(triggered()), this, SLOT(editorder()));
		contextMenu->addAction(editrow);
	    QAction* deleterow = new QAction( tr("&Delete Row"), this );
		connect(deleterow , SIGNAL(triggered()), this, SLOT(removerow()));
		contextMenu->addAction(deleterow); 
    } 
    else
    {
	    QAction* editrow = new QAction( tr("&Edit entry"), this );
		connect(editrow, SIGNAL(triggered()), this, SLOT(edittask()));
		contextMenu->addAction(editrow);
	    QAction* deleterow = new QAction( tr("&Delete Row"), this );
		connect(deleterow , SIGNAL(triggered()), this, SLOT(removerow()));
		contextMenu->addAction(deleterow);
    }
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;	
}

void procedureeditfrm::edittask()
{
    proceduretask *edtentry = new proceduretask;
    QTableWidgetItem *item = tabtasks->item(tabtasks->currentRow(), 1);
    edtentry->txtdescription->setText(item->text().simplified());
    
    item = tabtasks->item(tabtasks->currentRow(), 2);
    QString s = item->text();
    edtentry->date->setDate(QDate::QDate(s.section(".", 2, 2).toInt(), s.section(".", 1, 1).toInt(), s.section(".", 0, 0).toInt()));
	
    if(edtentry->exec())
    {
    	item = new QTableWidgetItem;
    	item->setText(edtentry->txtdescription->toPlainText().simplified());
    	tabtasks->setItem(tabtasks->currentRow(), 1, item);
		
		item = new QTableWidgetItem;
		item->setText(edtentry->date->date().toString("dd.MM.yyyy"));
		tabtasks->setItem(tabtasks->currentRow(), 2, item);
		
		navtasktab(tabtasks->currentRow());
    }
}

void procedureeditfrm::editorder()
{
    doceditposition *edtentry = new doceditposition;
    edtentry->txtpos->setEnabled(FALSE);
    
    QTableWidgetItem *item = new QTableWidgetItem;
    item = taborders->item(taborders->currentRow(),0);
    edtentry->txtpos->setText(item->text());
    
    item = new QTableWidgetItem;
    item = taborders->item(taborders->currentRow(),1);
    edtentry->txtlabel->setText(item->text());
    
    item = new QTableWidgetItem;
    item = taborders->item(taborders->currentRow(),3);
    edtentry->txtdescription->setText(item->text().simplified());
    
    item = new QTableWidgetItem;
    item = taborders->item(taborders->currentRow(),4);
    edtentry->txtquantity->setText(item->text());

    item = new QTableWidgetItem;
    item = taborders->item(taborders->currentRow(),5);
    edtentry->txtunit->setText(item->text());
    
    item = new QTableWidgetItem;
    item = taborders->item(taborders->currentRow(),6);
    if(item->text()!="" && item != 0)
		edtentry->txtprice->setText(item->text());
    else
		edtentry->txtprice->setText("0.00");

    edtentry->cmbvat->clear();
    edtentry->cmbvat->insertItems(0, ordervatlist);
    if(edtentry->exec())
    {
	    item = new QTableWidgetItem;
	    item->setText(edtentry->txtlabel->text());
	    taborders->setItem(taborders->currentRow(), 1, item);
    
	    item = new QTableWidgetItem;
	    item->setText(edtentry->txtdescription->toPlainText());
	    taborders->setItem(taborders->currentRow(), 3, item);
    
	    item = new QTableWidgetItem;
	    item->setText(edtentry->txtquantity->text());
	    taborders->setItem(taborders->currentRow(), 4, item);

	    item = new QTableWidgetItem;
	    item->setText(edtentry->txtunit->text());
	    taborders->setItem(taborders->currentRow(), 5, item);
    
	    item = new QTableWidgetItem;
	    item->setText(edtentry->txtprice->text());
	    taborders->setItem(taborders->currentRow(), 6, item);

		navordertabs(taborders->currentRow());
    }     
}

void procedureeditfrm::removerow()
{
    if(tabmain->currentIndex()==1)
    {
		if(tabtasks->rowCount()>0)
		    tabtasks->removeRow(tabtasks->currentRow());  
    }
    if(tabmain->currentIndex()==2)
    {
		if(taborders->rowCount()>0)
		    taborders->removeRow(taborders->currentRow());
    }
}

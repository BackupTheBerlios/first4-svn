#include <QTableView>
#include <QSqlQuery>
#include <QMenu>
#include <QMessageBox>
//
#include "dataeditfrm.h"
#include "addrselectfrm.h"
//
dataeditfrm::dataeditfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void dataeditfrm::init()
{
	this->setFixedSize(this->width(), this->height());
    txtsalesdate->setDate(QDate::currentDate());
    loadvat();
    
    //Felder initialisieren
    txtpurchaseprice->setText("0.00");
    txtsellprice->setText("0.00");
    
    //tabsuppliers->setColumnHidden(1, TRUE);
    tabsuppliers->setRowCount(tabsuppliers->rowCount()+1);
    
    connect(tabsuppliers, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));
    connect(tabsuppliers, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(acceptsp()));
	connect(btnok, SIGNAL(released()), this, SLOT(acceptdata()));
}
//
void dataeditfrm::loadentry(QString dbID)
{
    bool ok;
    this->setWindowTitle(tr("Edit entry..."));

    QString connstr = QString("SELECT ID, col1, col2, col3, col4, col5, col6, col7, col8, col9, col10, col11, col12, col13, col14, col15, col16, col17, col18, col19, col20, col21 FROM `%1` WHERE `ID` = '%2';").arg(dbID.section("_", 0, 0)).arg(dbID.section("_", 1, 1));
    QSqlQuery query(connstr);
    lbldatatab->setText(dbID.section("_", 0, 0));
    if(query.isActive())
    {
		query.next();
		lblID->setText(query.value(0).toString());
		txtlabel->setText(query.value(1).toString());
		txtdescription->setText(query.value(2).toString());
		txtstock->setText(query.value(3).toString());
		txtminquantity->setText(query.value(4).toString());
		txtunit->setText(query.value(5).toString());
		txtorderquantity->setText(query.value(6).toString());
		txtpurchaseprice->setText(query.value(7).toString());
		txtsellprice->setText(query.value(8).toString());
	
		int i;
		QStringList lines = query.value(9).toString().split(":##:");
		tabsuppliers->setRowCount(lines.count()-1);
		for(i=0;i<lines.count();i++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setText(lines[i].section(":#:",0,0));
			tabsuppliers->setItem(i, 0, item);

		    item = new QTableWidgetItem;
			item->setText(lines[i].section(":#:",1,1));
			tabsuppliers->setItem(i, 1, item);

			item = new QTableWidgetItem;
			item->setText(lines[i].section(":#:",2,2));
			tabsuppliers->setItem(i, 2, item);		    

			item = new QTableWidgetItem;
			item->setText(lines[i].section(":#:",3,3));
			tabsuppliers->setItem(i, 3, item);

			item = new QTableWidgetItem;
			item->setText(lines[i].section(":#:",4,4));
			tabsuppliers->setItem(i, 4, item);
		}

		txtpackage->setText(query.value(10).toString());
		txtweight->setText(query.value(11).toString());
		cmbvat->setCurrentIndex(query.value(12).toString().toInt(&ok, 10));
		if(query.value(13).toString()=="0")
		    chkactive->setChecked(FALSE);
		txtwebname->setText(query.value(14).toString());
		txtwebimage->setText(query.value(15).toString());
		txtweburl->setText(query.value(16).toString());
		QString d = query.value(17).toString();
		lblcreated->setText(d.section("-", 2, 2)+"."+d.section("-", 1, 1)+"."+d.section("-", 0, 0));
		d = query.value(18).toString();
		lblmodified->setText(d.section("-", 2, 2)+"."+d.section("-", 1, 1)+"."+d.section("-", 0, 0));
		d = query.value(19).toString();
		txtsalesdate->setDate(QDate::QDate(d.section("-", 0, 0).toInt(&ok, 10), d.section("-", 1, 1).toInt(&ok, 10), d.section("-", 2, 2).toInt(&ok, 10)));
		txtcomments->setText(query.value(20).toString());
		txtstockpos->setText(query.value(21).toString());
		calc_gw();
    }   
}
//
void dataeditfrm::loadvat()
{
    QString connstr = QString("SELECT col1, col2 FROM `taxtab` ORDER BY ID;");
    QSqlQuery query(connstr);
    if(query.isActive())
    {
	while(query.next())
	    cmbvat->addItem(query.value(0).toString());
    }   
}
//
void dataeditfrm::acceptdata()
{
    if(lblID->text()!="-")
		updateentry();
    else
		newentry();
}
//
void dataeditfrm::newentry()
{
    //prepare supplier entry
    int i, ii;
    QString supl = "";
    for(i=0;i<tabsuppliers->rowCount();i++)
    {
    	for(ii=0; ii<tabsuppliers->columnCount(); ii++)
    	{
    		QTableWidgetItem *item = new QTableWidgetItem;
    		item = tabsuppliers->item(i, ii);
    		if(item != 0)
    			supl += tabsuppliers->item(i, ii)->text() + ":#:";
			supl = supl.leftJustified(supl.length()-1, '.', true) + "#:";
   		}
   	}
    
    QString state = "0";
    if(chkactive->isChecked())
		state = "1";
    QString connstr = QString("INSERT INTO `"+lbldatatab->text()+"` (`ID`, `col1`, `col2`, `col3`, `col4`, `col5`, `col6`, `col7`, `col8`, `col9`, `col10`, `col11`, `col12`, `col13`, `col14`, `col15`, `col16`, `col17`, `col18`, `col19`, `col20`, `col21`) VALUES (NULL, '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9'").arg(txtlabel->text()).arg(txtdescription->toPlainText()).arg(txtstock->text()).arg(txtminquantity->text()).arg(txtunit->text()).arg(txtorderquantity->text()).arg(txtpurchaseprice->text()).arg(txtsellprice->text()).arg(supl);
    connstr += QString(", '%1', '%2', '%3', '%4', '%5', '%6'").arg(txtpackage->text()).arg(txtweight->text()).arg(cmbvat->currentIndex()).arg(state).arg(txtwebname->text()).arg(txtwebimage->text());
    connstr += QString(", '%1', '%2', '%3', '%4', '%5', '%6');").arg(txtweburl->text()).arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(txtsalesdate->date().toString("yyyy-MM-dd")).arg(txtcomments->toPlainText()).arg(txtstockpos->text());
    QSqlQuery query(connstr);
    this->accept();
}
//
void dataeditfrm::updateentry()
{
    //prepare supplier entry
    int i, ii;
    QString supl = "";
    for(i=0;i<tabsuppliers->rowCount();i++)
    {
    	for(ii=0; ii<tabsuppliers->columnCount(); ii++)
    	{
    		QTableWidgetItem *item = new QTableWidgetItem;
    		item = tabsuppliers->item(i, ii);
    		if(item != 0)
    			supl += tabsuppliers->item(i, ii)->text() + ":#:";
   		}
		supl = supl.leftJustified(supl.length()-1, '.', true) + "#:";
   	}

    QString state = "0";
    if(chkactive->isChecked())
		state = "1";    	
    QString connstr = QString("UPDATE `"+lbldatatab->text()+"` SET `col1`='%1', `col2`='%2', `col3`='%3', `col4`='%4', `col5`='%5', `col6`='%6', `col7`='%7', `col8`='%8', `col9`='%9', ").arg(txtlabel->text()).arg(txtdescription->toPlainText()).arg(txtstock->text()).arg(txtminquantity->text()).arg(txtunit->text()).arg(txtorderquantity->text()).arg(txtpurchaseprice->text()).arg(txtsellprice->text()).arg(supl);
    connstr += QString("`col10`='%1', `col11`='%2', `col12`='%3', `col13`='%4', `col14`='%5',").arg(txtpackage->text()).arg(txtweight->text()).arg(cmbvat->currentIndex()).arg(state).arg(txtwebname->text());
    connstr += QString("`col15`='%1', `col16`='%2', `col17`='%3', `col18`='%4', `col19`='%5', `col20`='%6', `col21`='%7'").arg(txtwebimage->text()).arg(txtweburl->text()).arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(txtsalesdate->date().toString("yyyy-MM-dd")).arg(txtcomments->toPlainText()).arg(txtstockpos->text());
    connstr += QString(" WHERE `ID`=%1 LIMIT 1;").arg(lblID->text());
    QSqlQuery query(connstr);
    this->accept();
}
//
void dataeditfrm::calc_gw()
{
    float ek,vk;
    ek = txtpurchaseprice->text().toFloat();
    vk = txtsellprice->text().toFloat();
    txtpurchaseprice->setText(QString("%1").arg(ek, 0, 'f',2));
    txtsellprice->setText(QString("%1").arg(vk, 0, 'f',2));
    lblprofit->setText(QString("%1").arg(vk-ek, 0, 'f',2));
    if(ek>0)
		lblmargin->setText(QString("%1").arg((100/ek*vk)-100, 0, 'f',0));
    else
		lblmargin->setText("100");
}
//
void dataeditfrm::seladdress()
{
    QString tmpstr = "";
    addrselectfrm *saddrfrm = new addrselectfrm;
	if(tabsuppliers->item(tabsuppliers->currentRow(), 0)->text() != "")
	    saddrfrm->txtsearch->setText(tabsuppliers->item(tabsuppliers->currentRow(), 0)->text().section(";", 0, 0));
    saddrfrm->init();
    if(saddrfrm->exec())
    {
       QString answer = saddrfrm->getadress();
       QStringList fields = answer.split(":#:");
       
       if(tabsuppliers->currentRow() != -1)
       {
       		QTableWidgetItem *item_1 = new QTableWidgetItem;
       		item_1->setText(fields[0]);
       		tabsuppliers->setItem(tabsuppliers->currentRow(), 0, item_1);
       		
       		QTableWidgetItem *item_2 = new QTableWidgetItem;
       		item_2->setText(fields[1]);
       		tabsuppliers->setItem(tabsuppliers->currentRow(), 1, item_2);
       }
    }
}
//
void dataeditfrm::contmenu()
{
    QMenu* contextMenu = new QMenu( this );
    Q_CHECK_PTR( contextMenu );

    QAction* checkaddr = new QAction( tr("&Check Address"), this );
	connect(checkaddr , SIGNAL(triggered()), this, SLOT(seladdress()));
	contextMenu->addAction(checkaddr);
    QAction* add_row = new QAction( tr("&Add Supplier"), this );
	connect(add_row , SIGNAL(triggered()), this, SLOT(addrow()));
	contextMenu->addAction(add_row);
    QAction* del_row = new QAction( tr("&Delete Supplier"), this );
	connect(del_row , SIGNAL(triggered()), this, SLOT(removerow()));
	contextMenu->addAction(del_row);
		
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}
//
void dataeditfrm::addrow()
{
    tabsuppliers->setRowCount(tabsuppliers->rowCount()+1);
/*    tabsuppliers->item(tabsuppliers->rowCount()-1, 0)->setText(" ");
    tabsuppliers->item(tabsuppliers->rowCount()-1, 1)->setText(" ");
    tabsuppliers->item(tabsuppliers->rowCount()-1, 2)->setText("0.00");
    tabsuppliers->item(tabsuppliers->rowCount()-1, 3)->setText("-");
    tabsuppliers->item(tabsuppliers->rowCount()-1, 4)->setText("-");*/
}
//
void dataeditfrm::removerow()
{
    tabsuppliers->removeRow(tabsuppliers->currentRow());
}
//
void dataeditfrm::acceptsp()
{
	if(tabsuppliers->item(tabsuppliers->currentRow(), 2)->text() != "")
	{
		txtpurchaseprice->setText(tabsuppliers->item(tabsuppliers->currentRow(), 2)->text());
		calc_gw();
	}
}

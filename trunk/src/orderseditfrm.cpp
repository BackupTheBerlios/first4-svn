#include <QSqlQuery>
#include <QDate>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QListView>
//
#include "orderseditfrm.h"
#include "vars.h"
#include "stockselfrm.h"
//
extern QString username;
QStringList stocklist, supprice;
//
orderseditfrm::orderseditfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void orderseditfrm::init()
{
    stocklist.clear();
    supprice.clear();
    
    QString qstr = QString("SELECT name, description FROM datatabs WHERE `tabtyp` = 'stock' AND `users` LIKE '%%1 [1%';").arg(username);
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		while(query.next())
		{
		    cmbstock->addItem(query.value(1).toString());
		    stocklist << query.value(0).toString();
		}
    }
    
    QSqlQuery querycount( "SELECT counter FROM orderscfgtab;");
    querycount.next();
    txtordernr->setText(querycount.value(0).toString());
      
    connect(btnok , SIGNAL( released() ), this, SLOT( newentry() ) );
    connect(btnsearch , SIGNAL( released() ), this, SLOT( checkstock() ) );
    connect(btnclearsearch , SIGNAL( released() ), this, SLOT( clearstock() ) );
    connect(cmbsupplier , SIGNAL( activated(int) ), this, SLOT( changeprice() ) );
}
//
void orderseditfrm::newentry()
{
	QString qstr = QString("INSERT INTO orderstab (ID, STATUS, ORDERED_BY, FOR_ORDER, STOCK, DATE1, DATE2, DATE3, DEF, DESCRIPTION, QUANTITY, SUPPLIER, PRICE, COMMENTS) VALUES ('', 0, '"+username+"', '%1', '%2', '%3', '', '', '%4', '%5', '%6', '%7', '%8', '%9');").arg(txtordernr->text()).arg(cmbstock->currentText()).arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(txtlabel->text()).arg(txtdescription->toPlainText()).arg(txtquantity->text()).arg(cmbsupplier->currentText()).arg(txtprice->text()).arg(txtcomments->toPlainText());
	QSqlQuery query(qstr);
  
	query.prepare( "UPDATE `orderscfgtab` SET `counter` = :counter LIMIT 1;");
	query.bindValue( ":counter", QString("%1").arg(txtordernr->text().toInt()+1, 0, 10));
	query.exec();
    
	this->accept();
}
//
void orderseditfrm::editentry(QString ID)
{
	QString qstr = QString("SELECT ID, STATUS, ORDERED_BY, FOR_ORDER, STOCK, DATE1, DATE2, DATE3, DEF, DESCRIPTION, QUANTITY, SUPPLIER, PRICE, COMMENTS FROM orderstab WHERE `ID`= '%1';").arg(ID);
	QSqlQuery query(qstr);
	query.next();
	lbldbid->setText(ID);
	txtordernr->setText(query.value(3).toString());
	txtlabel->setText(query.value(8).toString());
	txtdescription->setText(query.value(9).toString());
	txtquantity->setText(query.value(10).toString());
	cmbsupplier->addItem(query.value(11).toString());
	txtprice->setText(query.value(12).toString());
	txtcomments->setText(query.value(13).toString());
	
	txtordernr->setReadOnly(TRUE);
	txtlabel->setReadOnly(TRUE);
	txtdescription->setReadOnly(TRUE);
	txtquantity->setReadOnly(TRUE);
	txtprice->setReadOnly(TRUE);
	
	btnok->disconnect();
	connect(btnok, SIGNAL( released() ), this, SLOT( updentry() ) );
}
//
void orderseditfrm::updentry()
{
    QSqlQuery updquery;
    updquery.prepare("UPDATE `orderstab` SET `COMMENTS`= :comm WHERE `ID`=:ID LIMIT 1;");
    updquery.bindValue(":comm", txtcomments->toPlainText());
    updquery.bindValue(":ID", lbldbid->text());
    updquery.exec();
    this->accept();
}
//
void orderseditfrm::changeprice()
{
    txtprice->setText(supprice[cmbsupplier->currentIndex()]);
}
//
void orderseditfrm::clearstock()
{
    txtlabel->setText("");
    txtdescription->setText("");
    txtprice->setText("");
    cmbsupplier->clear();
}
//
void orderseditfrm::checkstock()
{
    stockselfrm *sfrm = new stockselfrm;
    QSqlQuery query("SELECT name, description FROM datatabs WHERE `tabtyp` = 'stock' AND `users` LIKE '%"+username+"%';");
    if(query.isActive())
    {
		while(query.next())
		{
			QString qstr = QString("SELECT ID, col1, col2, col3, col5, col8, col9, col6 FROM %1 WHERE col1 LIKE '%%2%' AND `col13`='1' ORDER BY col1 ASC;").arg(query.value(0).toString()).arg(txtlabel->text());
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
				    item->setText(6, query2.value(6).toString());
				    item->setText(7, query2.value(7).toString());
				    item->setText(8, query.value(0).toString()+""+query2.value(0).toString());
				}
		    }
		}
    }
    
    if(sfrm->treemain->topLevelItemCount()>1)
    {	
		sfrm->treemain->setColumnWidth(0, 0);
		sfrm->treemain->setColumnWidth(6, 0);
		sfrm->treemain->setColumnWidth(7, 0);
		sfrm->treemain->setColumnWidth(8, 0);
		
		if(sfrm->exec())
		{
		    QTreeWidgetItem *item = sfrm->treemain->currentItem();
		    if(item!=0)
		    {
				txtlabel->setText(item->text(1));
				txtdescription->setText(item->text(2));
				txtquantity->setText(item->text(7));
				supprice.clear();
				QStringList suplist = item->text(6).split(":##:");
				int i;
				for (i=0; i < suplist.count()-1; i++)
				{
				    QStringList tmplist = suplist[i].split(":#:");
				    cmbsupplier->addItem(tmplist[0].replace(";",""));
				    supprice << tmplist[2];
				}
		    }
		}
    }
    else
    {
		QTreeWidgetItem *item = sfrm->treemain->topLevelItem(0);
		if(item!=0)
		{
			txtlabel->setText(item->text(1));
			txtdescription->setText(item->text(2));
			txtquantity->setText(item->text(7));
			supprice.clear();
			QStringList suplist = item->text(6).split(":##:");
			int i;
			for (i=0; i < suplist.count(); i++)
			{
			    QStringList tmplist = suplist[i].split(":#:");
			    cmbsupplier->addItem(tmplist[0]);
			    supprice << tmplist[2];
			}
			cmbsupplier->removeItem(cmbsupplier->count()-1);
		}
    }
    changeprice();
}

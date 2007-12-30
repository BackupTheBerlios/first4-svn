#include <QSqlQuery>
#include <QMessageBox>
//
#include "accountseditfrm.h"
#include "addrselectfrm.h"
#include "stockselfrm.h"
//
extern QString username;
//
QStringList ietype;
QString dbID;
bool edit = FALSE;
//
accountseditfrm::accountseditfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void accountseditfrm::init()
{
    this->setFixedSize(this->width(), this->height());
    ietype << "inc" << "exp";
    
    connect(btnsearch, SIGNAL(released()), this, SLOT(selectaddr()));
    connect(btnclearsearch, SIGNAL(released()), this, SLOT(clearaddr()));
    connect(btncodecheck, SIGNAL(released()), this, SLOT(checkcode()));
    connect(btnaccept, SIGNAL(released()), this, SLOT(acceptdata()));
    connect(btncancel, SIGNAL(released()), this, SLOT(reject()));
    connect(txtamount, SIGNAL(editingFinished()), this, SLOT(formatamount()));    
}
//
void accountseditfrm::setdbID(QString tmpdbID)
{
    dbID = tmpdbID;
}
//
void accountseditfrm::loadentry(QString tmpdbID)
{   
    edit = TRUE;
    dbID = tmpdbID;
    if(dbID.section("_", 0, 0) == "ietab")
	{
		QString connstr = QString("SELECT ID, refnr, type, state, date, address, description, code, amount FROM ietab WHERE `ID` = '%1';").arg(dbID.section("_", 1, 1)); 
		QSqlQuery query(connstr);
		if ( query.isActive())
		{
		    query.next();
		    lblID->setText(query.value(0).toString());
		    txtRefNr->setText(query.value(1).toString());
		    if(query.value(2).toString()=="inc")
				cmbincexp->setCurrentIndex(0);
		    else
				cmbincexp->setCurrentIndex(0);
		    bool ok;
		    QString tmpstr = query.value(4).toString();
		    QDate s = QDate::QDate(tmpstr.section("-", 0, 0).toInt(&ok, 10), tmpstr.section("-", 1, 1).toInt(&ok, 10), tmpstr.section("-", 2, 2).toInt(&ok, 10));
		    date1->setDate(s);
		    txtaddress->setText(query.value(5).toString().section(" (", 0, 0));
		    lbladdrID->setText(query.value(5).toString().section(" (", 1, 1).section(")", 0, 0));
		    txtdescription->setText(query.value(6).toString());
		    txtCode->setText(query.value(7).toString());
		    txtamount->setText(query.value(8).toString());
		}	    
    }
    else
    {
		QString connstr = QString("SELECT ID, refnr, date, address, description, code, amount FROM %1 WHERE `ID` = '%2';").arg(dbID.section("_", 0, 0)).arg(dbID.section("_", 1, 1)); 
		QSqlQuery query(connstr);
		if ( query.isActive())
		{
		    query.next();
		    lblID->setText(query.value(0).toString());
		    txtRefNr->setText(query.value(1).toString());
		    bool ok;
		    QString tmpstr = query.value(2).toString();
		    QDate s = QDate::QDate(tmpstr.section("-", 0, 0).toInt(&ok, 10), tmpstr.section("-", 1, 1).toInt(&ok, 10), tmpstr.section("-", 2, 2).toInt(&ok, 10));
		    date1->setDate(s);
		    txtaddress->setText(query.value(3).toString().section(" (", 0, 0));
		    lbladdrID->setText(query.value(3).toString().section(" (", 1, 1).section(")", 0, 0));	
		    txtdescription->setText(query.value(4).toString());
		    txtCode->setText(query.value(5).toString());
		    txtamount->setText(query.value(6).toString());
		}
    }
}
//
void accountseditfrm::acceptdata()
{
    if(edit)
    {
		accountseditfrm::updateentry(dbID.section("_", 0, 0));
    }
    else
    {
		accountseditfrm::newentry(dbID.section("_", 0, 0));
    }
    edit = FALSE;
}
//
void accountseditfrm::updateentry(QString tab)
{
    QString qstr = "";
    if(tab == "ietab")
    {
		qstr = QString("UPDATE `%1` SET `date`='%2', `address` = '%3', `description`='%4', `code`='%5', `amount`='%6' WHERE `ID`=%7;").arg(tab).arg(date1->date().toString("yyyy/MM/dd")).arg(txtaddress->toPlainText()+" ("+lbladdrID->text()+")").arg(txtdescription->toPlainText()).arg(txtCode->text()).arg(txtamount->text()).arg(lblID->text());
    }
    else
    {
		qstr = QString("UPDATE `%1` SET `date`='%2', `address`='%3', `description`='%4', `code`='%5', `amount`='%6' WHERE `ID`=%7;").arg(tab).arg(date1->date().toString("yyyy/MM/dd")).arg(txtaddress->toPlainText()+" ("+lbladdrID->text()+")").arg(txtdescription->toPlainText()).arg(txtCode->text()).arg(txtamount->text()).arg(lblID->text());
    }
    QSqlQuery query(qstr);
    this->accept();    
}
//
void accountseditfrm::newentry(QString tab)
{
    QString qstr = "";
    if(tab == "ietab")
    {
		qstr = QString("INSERT INTO `%1` (`ID`, `refnr`, `type`, `state`, `date`, `address`, `description`, `code`, `amount`) VALUES (NULL, '%2', '%3', '0', '%5', '%6', '%7', '%8', '%9');").arg(tab).arg(txtRefNr->text()).arg(ietype[cmbincexp->currentIndex()]).arg(date1->date().toString("yyyy/MM/dd")).arg(txtaddress->toPlainText()+" ("+lbladdrID->text()+")").arg(txtdescription->toPlainText()).arg(txtCode->text()).arg(txtamount->text());
    }
    else
    {
		qstr = QString("INSERT INTO `%1` (`ID`, `date`, `refnr`, `address`, `description`, `code`, `amount`) VALUES (NULL, '%2', '%3', '%4', '%5', '%6', '%7');").arg(tab).arg(date1->date().toString("yyyy/MM/dd")).arg(txtRefNr->text()).arg(txtaddress->toPlainText()+" ("+lbladdrID->text()+")").arg(txtdescription->toPlainText()).arg(txtCode->text()).arg(txtamount->text());
    }
    QSqlQuery query(qstr);
    this->accept();
}
//
void accountseditfrm::selectaddr()
{
    addrselectfrm *saddr = new addrselectfrm;
    saddr->init();
    if(txtaddress->toPlainText()!="")
    {
		saddr->txtsearch->setText(txtaddress->toPlainText());
		saddr->searchaddress();
    }
    if(saddr->exec())
    {
		QString answer = saddr->getaddress();
		QStringList fields = answer.split( ":#:" );
		txtaddress->setText(fields[0]);
		lbladdrID->setText(fields[1]);
    }
}
//
void accountseditfrm::clearaddr()
{
       txtaddress->setText("");
       lbladdrID->setText("");
}
//
void accountseditfrm::checkcode()
{
    stockselfrm *selstock = new stockselfrm;
    QString connstr = "SELECT name,  description FROM datatabs WHERE `users` LIKE '%"+username+" [1%' AND `tabtyp` = 'iecode';";
    QString connstr2;
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		while(query.next())
		{
		    connstr2 = "SELECT col1, col2, col3, ID FROM "+query.value(0).toString()+" WHERE col1 LIKE '%"+txtCode->text()+"%' ORDER BY col1 ASC";
		    QSqlQuery query2(connstr2);
		    if ( query2.isActive())
		    {	
    	    	selstock->init();
				selstock->treemain->clear();
				selstock->treemain->setColumnCount(4);
				selstock->treemain->headerItem()->setText(0, tr("ID"));
				selstock->treemain->headerItem()->setText(0, tr("Code"));
				selstock->treemain->headerItem()->setText(0, tr("Text"));
				selstock->treemain->headerItem()->setText(0, tr("Comments"));
				
				selstock->treemain->hideColumn(0);
				selstock->treemain->setColumnWidth(1, 80);
				selstock->treemain->setColumnWidth(2, 200);
				selstock->treemain->setColumnWidth(3, 150);

				while (query2.next())
				{
				    QTreeWidgetItem *item = new QTreeWidgetItem(selstock->treemain);
				    item->setText(0, query2.value(3).toString());
				    item->setText(1, query2.value(0).toString());
				    item->setText(2, query2.value(1).toString());
				    item->setText(3, query2.value(2).toString());
				}
		    }
		}
    }
    if(selstock->treemain->topLevelItemCount() > 1)
    {
		if(selstock->exec())
		{
		    QTreeWidgetItem *item = selstock->treemain->currentItem();
		    txtdescription->setText(item->text(2));
		    txtCode->setText(item->text(1));
		}
    }
    else
    {
		QTreeWidgetItem *item = selstock->treemain->topLevelItem(0);
		if(item!=0)
		{
		    txtdescription->setText(item->text(2));
		    txtCode->setText(item->text(1));
		}
    } 
}
//
void accountseditfrm::formatamount()
{
    txtamount->setText(QString("%1").arg(txtamount->text().toDouble(), 0, 'f',2));
}

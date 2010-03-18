#include <QSqlQuery>
//
#include "accountseditfrm.h"
#include "addrselectfrm.h"
#include "stockselfrm.h"
#include "vars.h"
#include "progfrm.h"
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
    vars v;
    if(dbID.section("_", 0, 0) == "incexp")
	{
		QString qstr;
		QString userlock = v.checklockstate("incexp", dbID.section("_", 1, 1));
		if(userlock != "")
		{
			this->setWindowTitle(this->windowTitle()+QString(" ( Locked by User: %1 )").arg(userlock));
			btnaccept->setEnabled(FALSE);
			qstr = QString("SELECT ID, refnr, type, state, date, address, description, code, amount FROM incexp WHERE `ID` = '%1';").arg(dbID.section("_", 1, 1));
		}
		else
		{
			qstr = QString("SELECT ID, refnr, type, state, date, address, description, code, amount FROM incexp WHERE `ID` = '%1' FOR UPDATE;").arg(dbID.section("_", 1, 1));
			v.lockrow("incexp", dbID.section("_", 1, 1));
		}
	
		QSqlQuery query(qstr);
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
		QString qstr;
		QString userlock = v.checklockstate(dbID.section("_", 0, 0), dbID.section("_", 1, 1));
		if(userlock != "")
		{
			this->setWindowTitle(this->windowTitle()+QString(" ( Locked by User: %1 )").arg(userlock));
			btnaccept->setEnabled(FALSE);
			qstr = QString("SELECT ID, refnr, date, address, description, code, amount FROM %1 WHERE `ID` = '%2';").arg(dbID.section("_", 0, 0)).arg(dbID.section("_", 1, 1));
		}
		else
		{
			qstr = QString("SELECT ID, refnr, date, address, description, code, amount FROM %1 WHERE `ID` = '%2';").arg(dbID.section("_", 0, 0)).arg(dbID.section("_", 1, 1));
			v.lockrow(dbID.section("_", 0, 0), dbID.section("_", 1, 1));
		}
    	 
		QSqlQuery query(qstr);
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
	QSqlDatabase::database().transaction();
	vars v;
	QString qstr = "";
	if(tab == "incexp")
	{
		qstr = QString("UPDATE `%1` SET `date`='%2', `address` = '%3', `description`='%4', `code`='%5', `amount`='%6' WHERE `ID`=%7;").arg(tab).arg(date1->date().toString("yyyy/MM/dd")).arg(txtaddress->toPlainText()+" ("+lbladdrID->text()+")").arg(txtdescription->toPlainText()).arg(txtCode->text()).arg(txtamount->text()).arg(lblID->text());
	}
	else
	{
		qstr = QString("SELECT ID, amount, account_balance FROM %1 WHERE `ID` >= '%2' ORDER BY DATE, ID;").arg(tab).arg(lblID->text());
		QSqlQuery query_calc(qstr);
		progfrm *pfrm = new progfrm;
		pfrm->setFixedSize(pfrm->width(), pfrm->height());
		pfrm->txtcomments->setText(tr("Re-calculating account balance."));
		pfrm->progbar->setMaximum(query_calc.size());
		pfrm->show();
		double balance_diff;
		while(query_calc.next()) {
			if(query_calc.value(0).toString() == lblID->text())
				balance_diff = query_calc.value(1).toDouble() - txtamount->text().toDouble();
			qstr = QString("UPDATE %1 SET `account_balance` = '%2' WHERE `ID`='%3';").arg(tab).arg(query_calc.value(2).toDouble()-balance_diff, 0, 'f',2).arg(query_calc.value(0).toString());
			QSqlQuery query_balance(qstr);
			pfrm->progbar->setValue(query_calc.at());
		}
		qstr = QString("UPDATE `%1` SET `date`='%2', `address`='%3', `description`='%4', `code`='%5', `amount`='%6' WHERE `ID`=%7;").arg(tab).arg(date1->date().toString("yyyy/MM/dd")).arg(txtaddress->toPlainText()+" ("+lbladdrID->text()+")").arg(txtdescription->toPlainText()).arg(txtCode->text()).arg(txtamount->text()).arg(lblID->text());
		QSqlQuery query(qstr);
		pfrm->close();
	}
    QSqlDatabase::database().commit();
    v.unlockrow(tab, lblID->text());
    this->accept();    
}
//
void accountseditfrm::newentry(QString tab)
{
	QString qstr = "";
	if(tab == "incexp")
	{
		qstr = QString("INSERT INTO `%1` (`ID`, `refnr`, `type`, `state`, `date`, `address`, `description`, `code`, `amount`) VALUES (NULL, '%2', '%3', '0', '%5', '%6', '%7', '%8', '%9');").arg(tab).arg(txtRefNr->text()).arg(ietype[cmbincexp->currentIndex()]).arg(date1->date().toString("yyyy/MM/dd")).arg(txtaddress->toPlainText()+" ("+lbladdrID->text()+")").arg(txtdescription->toPlainText()).arg(txtCode->text()).arg(txtamount->text());
	}
	else
	{
		QSqlQuery query_balance("SELECT account_balance FROM "+tab+" ORDER BY ID DESC LIMIT 1;");
		query_balance.next();
		double balance = query_balance.value(0).toDouble()+txtamount->text().toDouble();
		qstr = QString("INSERT INTO `%1` (`ID`, `date`, `refnr`, `address`, `description`, `code`, `amount`, `account_balance`) VALUES (NULL, '%2', '%3', '%4', '%5', '%6', '%7', '%8');").arg(tab).arg(date1->date().toString("yyyy/MM/dd")).arg(txtRefNr->text()).arg(txtaddress->toPlainText()+" ("+lbladdrID->text()+")").arg(txtdescription->toPlainText()).arg(txtCode->text()).arg(txtamount->text()).arg(QString("%1").arg(balance, 0, 'f',2));
	}
	QSqlDatabase::database().transaction();
	QSqlQuery query(qstr);
	QSqlDatabase::database().commit();
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
    QString connstr = "SELECT name,  description FROM datatables WHERE `users` LIKE '%"+username+" [1%' AND `tabtyp` = 'iecode';";
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
//
void accountseditfrm::reject()
{
	QSqlDatabase::database().rollback();
	vars v;
	v.unlockrow(dbID.section("_", 0, 0), dbID.section("_", 1, 1));
	done(0);
}

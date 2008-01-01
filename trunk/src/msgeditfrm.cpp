#include <QDate>
#include <QSqlQuery>
#include <QHeaderView>
#include <QMessageBox>
//
#include "msgeditfrm.h"
#include "stockselfrm.h"
#include "addrselectfrm.h"
//
extern QString username;
//
QStringList msgvatlist;
//
msgeditfrm::msgeditfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void msgeditfrm::init(QString msgtype)
{
    this->setFixedSize(this->width(), this->height());
    
    if(msgtype=="per")
		cmbmsgtype->setCurrentIndex(0);
    else if(msgtype=="gen")
		cmbmsgtype->setCurrentIndex(1);
    else if(msgtype=="sto")
		cmbmsgtype->setCurrentIndex(2);
    else if(msgtype=="ord")
		cmbmsgtype->setCurrentIndex(3);
    else
		cmbmsgtype->setCurrentIndex(4);
    stackmain->setCurrentIndex(cmbmsgtype->currentIndex());
    
    date->setDate(QDate::currentDate());
    ord_date1->setDate(QDate::currentDate());
    ord_date2->setDate(QDate::currentDate());
    iem_date1->setDate(QDate::currentDate());
    
    gen_users->header()->setResizeMode(QHeaderView::Fixed);	
    gen_users->setColumnWidth(0, 45);
    gen_users->hideColumn(2);
    
    connect(btnaccept, SIGNAL(released()), this, SLOT(acceptdata()));
    connect(btncancel, SIGNAL(released()), this, SLOT(reject()));
    connect(sto_btncheck, SIGNAL(released()), this, SLOT(checkstock()));
    connect(cmbmsgtype, SIGNAL(currentIndexChanged(int)), this, SLOT(changetab()));
    connect(ord_btnclear, SIGNAL(released()), this, SLOT(clearaddress()));
    connect(iem_btnclear, SIGNAL(released()), this, SLOT(clearaddress()));
    connect(ord_btncheck, SIGNAL(released()), this, SLOT(seladdress()));
    connect(iem_btncheck, SIGNAL(released()), this, SLOT(seladdress()));
    loadusers();
}
//
void msgeditfrm::acceptdata()
{
    if(chknew->isChecked())
		newentry();
    else
		updateentry(lblID->text());
}
//
void msgeditfrm::loadusers()
{
    gen_users->clear();

    QString qstr = "SELECT username, fullname FROM `userstab` ORDER BY fullname ASC;";
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		while(query.next())
		{
			QTreeWidgetItem *item = new QTreeWidgetItem(gen_users);
			item->setCheckState(0, Qt::Unchecked);
			item->setText(1, query.value(1).toString());
			item->setText(2, query.value(0).toString());
		}
    }
}
//
void msgeditfrm::loadentry(QString dbID)
{
    int i;
    bool ok;
    chknew->setChecked(FALSE);
    lblID->setText(dbID);

    QString connstr = QString("SELECT ID, typ, user, date, msgtext, data1, data2, data3, data4, data5 FROM `msgtab` WHERE `ID` = '%1';").arg(lblID->text());
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		query.next();
		QString d = query.value(3).toString();
		date->setDate(QDate::QDate(d.section("-", 0, 0).toInt(&ok, 10), d.section("-", 1, 1).toInt(&ok, 10), d.section("-", 2, 2).toInt(&ok, 10)));
		switch(cmbmsgtype->currentIndex())
		{
			case 0:
	    		per_msg->setText(query.value(4).toString());
			    break;
			case 1:
    			for(i=0;i<gen_users->topLevelItemCount();i++)
			    {
			    	QTreeWidgetItem *item = gen_users->topLevelItem(i);
					if(query.value(2).toString().contains(item->text(2)) > 0)
						item->setCheckState(0, Qt::Checked);
			    }
	    		gen_msg->setText(query.value(4).toString());
			    break;
			case 2:
			{
		    	sto_def->setText(query.value(5).toString());
	    		sto_description->setText(query.value(6).toString());
			    sto_onstock->setText(query.value(7).toString());
	    		sto_min->setText(query.value(8).toString());
	    		QTreeWidgetItem *sup_item = new QTreeWidgetItem(sto_supplier);
	    		sup_item->setText(0, query.value(9).toString());
	    		sto_pprice->setText(query.value(4).toString().section("/", 0, 0));
			    sto_sprice->setText(query.value(4).toString().section("/", 1, 1));
	    		break;
			}
			case 3:
	    		ord_customer->setText(query.value(5).toString().section(" (", 0, 0));
			    ord_lbladdrid->setText(query.value(5).toString().section(" (", 1, 1).section(")", 0, 0));
	    		ord_ordernr->setText(query.value(6).toString());
			    d = query.value(7).toString();
	    		ord_date1->setDate(QDate::QDate(d.section("-", 0, 0).toInt(&ok, 10), d.section("-", 1, 1).toInt(&ok, 10), d.section("-", 2, 2).toInt(&ok, 10)));
			    d = query.value(8).toString();
	    		ord_date2->setDate(QDate::QDate(d.section("-", 0, 0).toInt(&ok, 10), d.section("-", 1, 1).toInt(&ok, 10), d.section("-", 2, 2).toInt(&ok, 10)));
			    break;
			case 4:
	    		iem_customer->setText(query.value(5).toString().section(" (", 0, 0));
			    iem_lbladdrid->setText(query.value(5).toString().section(" (", 1, 1).section(")", 0, 0));
	    		iem_ordernr->setText(query.value(6).toString());
			    d = query.value(7).toString();
	    		iem_date1->setDate(QDate::QDate(d.section("-", 0, 0).toInt(&ok, 10), d.section("-", 1, 1).toInt(&ok, 10), d.section("-", 2, 2).toInt(&ok, 10)));
			    iem_amount->setText(query.value(8).toString().section(" ", 0, 0));
				iem_currency->addItem(query.value(8).toString().section(" ", 1, 1));
	    		break;	       
		}
    }
}
//
void msgeditfrm::newentry()
{
    int i;
    QString usersstr = "";
    QString qstr = "";    
    
    switch(cmbmsgtype->currentIndex())
    {
    	case 0:
			qstr = QString("INSERT INTO `msgtab` (`ID`, `typ`, `user`, `date`, `msgtext`, `data1`, `data2`, `data3`, `data4`, `data5`) VALUES (NULL, 'per', '(%1)', '%2', '%3', '', '', '', '', '');").arg(username).arg(date->date().toString("yyyy-MM-dd")).arg(per_msg->toPlainText().replace("'", "\\'"));
			break;
	    case 1:
			for(i=0;i<gen_users->topLevelItemCount();i++)
			{
				QTreeWidgetItem *item = gen_users->topLevelItem(i);
				if(item->checkState(0) == Qt::Checked)
					usersstr += ", " + item->text(2);
			}
			qstr = QString("INSERT INTO `msgtab` (`ID`, `typ`, `user`, `date`, `msgtext`, `data1`, `data2`, `data3`, `data4`, `data5`) VALUES (NULL, 'gen', '%1', '%2', '%3', '', '', '', '', '');").arg("("+username+")"+usersstr).arg(date->date().toString("yyyy-MM-dd")).arg(gen_msg->toPlainText().replace("'", "\'"));
			break;
    	case 2:
    		{
    			QTreeWidgetItem *sup_item = sto_supplier->currentItem();
    			QString supplier = "";
	    		if(sup_item != 0)
    				supplier = sup_item->text(0);
				qstr = QString("INSERT INTO `msgtab` (`ID`, `typ`, `user`, `date`, `msgtext`, `data1`, `data2`, `data3`, `data4`, `data5`) VALUES (NULL, 'sto', '', '%1', '%7', '%2', '%3', '%4', '%5', '%6');").arg(date->date().toString("yyyy-MM-dd")).arg(sto_def->text()).arg(sto_description->toPlainText().replace("'", "\'")).arg(sto_onstock->text()).arg(sto_min->text()).arg(supplier).arg(sto_pprice->text()+"/"+sto_sprice->text());
				break;
			}
	    case 3:
			qstr = QString("INSERT INTO `msgtab` (`ID`, `typ`, `user`, `date`, `msgtext`, `data1`, `data2`, `data3`, `data4`, `data5`) VALUES (NULL, 'ord', '', '%1', '', '%2', '%3', '%4', '%5', '');").arg(date->date().toString("yyyy-MM-dd")).arg(ord_customer->toPlainText()+" ("+ord_lbladdrid->text()+")").arg(ord_ordernr->text()).arg(ord_date1->date().toString("yyyy-MM-dd")).arg(ord_date2->date().toString("yyyy-MM-dd"));
			break;
    	case 4:
			qstr = QString("INSERT INTO `msgtab` (`ID`, `typ`, `user`, `date`, `msgtext`, `data1`, `data2`, `data3`, `data4`, `data5`) VALUES (NULL, 'iem', '', '%1', '', '%2', '%3', '%4', '%5', '');").arg(date->date().toString("yyyy-MM-dd")).arg(iem_customer->toPlainText()+" ("+iem_lbladdrid->text()+")").arg(iem_ordernr->text()).arg(iem_date1->date().toString("yyyy-MM-dd")).arg(iem_amount->text() + " " + iem_currency->currentText());
			break;
    }
    QSqlQuery query(qstr);
    QMessageBox::information(this, tr("Delete entry..."), qstr);
    this->accept();
}
//
void msgeditfrm::updateentry(QString dbID)
{
    //update anpassen
    int i;
    QString usersstr = "";
    QString qstr = "";    

    switch(cmbmsgtype->currentIndex())
    {
    	case 0:
			qstr = QString("UPDATE `msgtab` SET `date`='%2', `msgtext`= '%3' WHERE `ID`=%1;").arg(dbID).arg(date->date().toString("yyyy-MM-dd")).arg(per_msg->toPlainText());
			break;
	    case 1:
			for(i=0;i<gen_users->topLevelItemCount();i++)
			{
				QTreeWidgetItem *item = gen_users->topLevelItem(i);
				if(item->checkState(0) == Qt::Checked)
					usersstr += ", " + item->text(2);
			}
			qstr = QString("UPDATE `msgtab` SET `date`='%2', `msgtext`= '%3', `user` = '%4' WHERE `ID`=%1;").arg(dbID).arg(date->date().toString("yyyy-MM-dd")).arg(gen_msg->toPlainText()).arg("("+username+")"+usersstr);
			break;
    	case 2:
    	{
			QTreeWidgetItem *sup_item = sto_supplier->currentItem();
   			QString supplier = "";
    		if(sup_item != 0)
   				supplier = sup_item->text(0);
			qstr = QString("UPDATE `msgtab` SET `date`='%2', `msgtext`= '%3', `data1` = '%4', `data2` = '%5', `data3` = '%6', `data4` = '%8', `data5` = '%9' WHERE `ID`=%1;").arg(dbID).arg(date->date().toString("yyyy-MM-dd")).arg(sto_pprice->text()+"/"+sto_sprice->text()).arg(sto_def->text()).arg(sto_description->toPlainText()).arg(sto_onstock->text()).arg(sto_min->text()).arg(supplier);
			break;
		}
	    case 3:
			qstr = QString("UPDATE `msgtab` SET `date`='%2', `data1` = '%3', `data2` = '%4', `data3` = '%5', `data4` = '%6' WHERE `ID`=%1;").arg(dbID).arg(date->date().toString("yyyy-MM-dd")).arg(ord_customer->toPlainText()+" ("+ord_lbladdrid->text()+")").arg(ord_ordernr->text()).arg(ord_date1->date().toString("yyyy-MM-dd")).arg(ord_date2->date().toString("yyyy-MM-dd"));
			break;
    	case 4:
			qstr = QString("UPDATE `msgtab` SET `date`='%2', `data1` = '%3', `data2` = '%4', `data3` = '%5', `data4` = '%6' WHERE `ID`=%1;").arg(dbID).arg(date->date().toString("yyyy-MM-dd")).arg(iem_customer->toPlainText()+" ("+iem_lbladdrid->text()+")").arg(iem_ordernr->text()).arg(iem_date1->date().toString("yyyy-MM-dd")).arg(iem_amount->text()+" "+iem_currency->currentText());
			break;
    }
    QSqlQuery query(qstr);
    this->accept();
}
//
void msgeditfrm::checkstock()
{
	if(sto_def->text()!="")
    {
		initvat();
		sto_supplier->clear();
		stockselfrm *sfrm = new stockselfrm;
	    QSqlQuery query("SELECT name, description FROM datatabs WHERE `tabtyp` = 'stock' AND `users` LIKE '%"+username+"%';");
	    if(query.isActive())
	    {
			while(query.next())
			{
				QString qstr = QString("SELECT ID, col1, col2, col3, col5, col8, col12, col6, col9 FROM %1 WHERE col1 LIKE '%%2%' AND `col13`='1' ORDER BY col1 ASC;").arg(query.value(0).toString()).arg(sto_def->text());
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
					    item->setText(6, msgvatlist[query2.value(6).toInt()]);
					    item->setText(7, query2.value(7).toString());
					    item->setText(8, query.value(0).toString()+":#:"+query2.value(0).toString());
					    item->setText(9, query2.value(8).toString());
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
		   			sto_def->setText(item->text(1));
			    	sto_description->setText(item->text(2));
		   			sto_onstock->setText(item->text(3));
			    	sto_min->setText(item->text(7));
		   			sto_sprice->setText(item->text(6));
			    	sto_pprice->setText(item->text(5));
				    QStringList sup_list = item->text(9).split(":##:");
				    QString supp;
				    foreach(supp, sup_list)
				    {
				    	QTreeWidgetItem *sup_item = new QTreeWidgetItem(sto_supplier);
			    		sup_item->setText(0, supp.section(":#:", 0, 0).replace("<BR>", ", "));
			    	}
			    }
			}
	    }
	    else
	    {
			QTreeWidgetItem *item = sfrm->treemain->topLevelItem(0);
			if(item!=0)
			{
	   			sto_def->setText(item->text(1));
			    sto_description->setText(item->text(2));
	   			sto_onstock->setText(item->text(3));
			    sto_min->setText(item->text(7));
	   			sto_sprice->setText(item->text(6));
			    sto_pprice->setText(item->text(5));
			    QStringList sup_list = item->text(9).split(":##:");
			    QString supp;
			    foreach(supp, sup_list)
			    {
			    	QTreeWidgetItem *sup_item = new QTreeWidgetItem(sto_supplier);
		    		sup_item->setText(0, supp.section(":#:", 0, 0).replace("<BR>", ", "));
		    	}
			}
	    }
    }
}
//
void msgeditfrm::changetab()
{
    stackmain->setCurrentIndex(cmbmsgtype->currentIndex());
}
//
void msgeditfrm::seladdress()
{
    addrselectfrm *seladdr = new addrselectfrm;
    seladdr->init();
    if(seladdr->exec())
    {
       QString answer = seladdr->getaddress();
       QStringList fields = answer.split(":#:");
       switch(cmbmsgtype->currentIndex())
       {
	       case 3:
				ord_customer->setText(fields[0].replace("<BR>", "\n"));
	   			ord_lbladdrid->setText(fields[1]);
				break;
			case 4:
			   	iem_customer->setText(fields[0]);
				iem_lbladdrid->setText(fields[1].replace("<BR>", "\n"));	    
	   			break;
       }
    }
}
//
void msgeditfrm::clearaddress()
{
       switch(cmbmsgtype->currentIndex())
       {
	       case 3:
    			ord_customer->setText("");
			    ord_lbladdrid->setText("");
				break;
			case 4:
    			iem_customer->setText("");
			    iem_lbladdrid->setText("");
	   			break;
       }
}
//
void msgeditfrm::initvat()
{
    msgvatlist.clear();
    QStringList tmplist;
    QString connstr = "SELECT col1 FROM vattab ORDER BY ID;";
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		while(query.next())
		    msgvatlist << query.value(0).toString();
    }
}

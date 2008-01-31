#include <QInputDialog>
#include <QSqlQuery>
#include <QMessageBox>

#include "newdatatabfrm.h"
#include "vars.h"

extern QString dbhost, dbname, dbuid, dbpwd, dbport;
//
newdatatabfrm::newdatatabfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void newdatatabfrm::init()
{
    this->setFixedSize(this->width(), this->height());    
    listcols->clear();
    grpcols->setEnabled(FALSE);
    
    connect(rdbstock, SIGNAL(clicked()), this, SLOT(change_rdb()));
    connect(rdbiecode, SIGNAL(clicked()), this, SLOT(change_rdb()));
    connect(rdbcustom, SIGNAL(clicked()), this, SLOT(change_rdb()));
    connect(btncreate, SIGNAL(released()), this, SLOT(createtable()));
}
void newdatatabfrm::on_btnadd_released()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("Rowname:"), QLineEdit::Normal,"", &ok);
    if ( ok && !text.isEmpty() ) 
		listcols->addItem(text);
}
//
void newdatatabfrm::on_btnremove_released()
{
	listcols->takeItem(listcols->currentRow());
}
//
void newdatatabfrm::on_btnup_released()
{
   if(listcols->currentRow() > 0)
   {
		QListWidgetItem *tmpitem = listcols->takeItem(listcols->currentRow());
		listcols->insertItem(listcols->currentRow(), tmpitem);
		listcols->setCurrentItem(tmpitem);
   }
}
//
void newdatatabfrm::on_btndown_released()
{
   if(listcols->currentRow() < listcols->count())
   {
		int pos = listcols->currentRow();
		QListWidgetItem *tmpitem = listcols->takeItem(listcols->currentRow());
		listcols->insertItem(++pos, tmpitem);
		listcols->setCurrentItem(tmpitem);
   }
}
//
void newdatatabfrm::change_rdb()
{
	grpcols->setEnabled(rdbcustom->isChecked());
}
//
void newdatatabfrm::createtable()
{
    if(txtname->text()!="")
    {
		if(rdbstock->isChecked() || rdbcustom->isChecked() || rdbiecode->isChecked())
		{
			int datacount = 1;
			QString dataname = "";
			QString conn1 = "SELECT * FROM datatabs ORDER BY name ASC;";	
			QSqlQuery querydatanew1(conn1);
			if ( querydatanew1.isActive())
			{
			    while ( querydatanew1.next())
			    {
					if(QString("data%1").arg(datacount,0,10) == querydatanew1.value(1).toString())
					    datacount++;
					else
					{
						if(dataname == "")
							dataname = QString("data%1").arg(datacount,0,10);
					}
			    }
		    }
		    
		    if(dataname == "")
				dataname = QString("data%1").arg(datacount++,0,10);
				
			QString conn2 = tr("INSERT INTO `datatabs` ( `ID` , `name` , `description` , `users` , `cols` , `tabtyp` ) VALUES ('', '%1', '%2").arg(dataname).arg(txtname->text());
			if(rdbstock->isChecked())
			    conn2 +=  "', '','Label:75#Description:75#Stock:75#Min. quantity:75#Unit:75#Order quantity:75#Purchase price:75#Selling price:75#Supplier:75#Package:75#Weight:75#Tax:75#Status:75#WebName:75#WebImage:75#WebURL:75#Create date:75#Last modification:75#Sales date:75#Comment:75#Stock position:75', 'stock');";
			else if(rdbiecode->isChecked())
			    conn2 +=  "', '','Code:75#Text:75#Comments:75','iecode');";
			else
			{
			    conn2 +=  "', '', '";
			    int i;
			    QListWidgetItem *item;
			    for(i=0;i<listcols->count();i++)
			    {
			    	item = listcols->item(i);
					conn2 += item->text() + ":75#";
		    	}
			    conn2.truncate(conn2.length()-1);
			    conn2 += "','userdef');";
			}
			QSqlQuery querydatanew2(conn2);
	
			QString conn5 = "CREATE TABLE `";
			conn5 += dataname;
			conn5 += "` (`ID` INT NOT NULL AUTO_INCREMENT,";       
			if(rdbstock->isChecked())
			    conn5 += "  `col1` text NOT NULL, `col2` text NOT NULL, `col3` text NOT NULL, `col4` text NOT NULL, `col5` text NOT NULL, `col6` text NOT NULL, `col7` text NOT NULL, `col8` text NOT NULL, `col9` text NOT NULL, `col10` text NOT NULL, `col11` text NOT NULL, `col12` text NOT NULL, `col13` text NOT NULL, `col14` text NOT NULL, `col15` text NOT NULL, `col16` text NOT NULL, `col17` date NOT NULL, `col18` date NOT NULL, `col19` date NOT NULL, `col20` text NOT NULL, `col21` text NOT NULL,";
			else if(rdbiecode->isChecked())
			    conn5 += "`col1` TEXT NOT NULL ,`col2` TEXT NOT NULL ,`col3` TEXT NOT NULL,";
			else
			{
			    int i;
			    for(i=0;i<listcols->count();i++)
					conn5 += QString("`col%1` TEXT NOT NULL,").arg(i+1,0,10);
			}
			conn5 += " PRIMARY KEY  (`ID`),  KEY `ID` (`ID`)) TYPE=InnoDB;";
			QSqlQuery querydatanew5(conn5);
			done(1);
	    }  
		else
		    QMessageBox::warning(0,"Error...",tr("Select kind of Datatable!"));
	}
	else
		QMessageBox::warning(0,"Error...",tr("Enter Datatablename!"));
}

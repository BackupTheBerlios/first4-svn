#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QHeaderView>
#include <QDate>
//
#include "dataimpexpfrm.h"
//
extern int uid;
extern QString username;
QStringList dataexplist, dataimplist;
//
dataimpexpfrm::dataimpexpfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void dataimpexpfrm::init()
{
	this->setFixedSize(this->width(), this->height());
	mainstack->setCurrentIndex(0);
	
	connect(btncancel, SIGNAL(released()), this, SLOT(reject()));
	connect(btnnext, SIGNAL(released()), this, SLOT(next()));
	connect(btnback, SIGNAL(released()), this, SLOT(back()));
	connect(btnexpcsvload, SIGNAL(released()), this, SLOT(loaddata_expcsv()));
	connect(btnimpcsvload, SIGNAL(released()), this, SLOT(loadfilecsv()));
	connect(btnimpcsvselectfile, SIGNAL(released()), this, SLOT(selectfilecsv()));
	dataexplist.clear();
	dataimplist.clear();
	cmbexpcsv->clear();
	
	treeexpcsv->setColumnCount(0);
	
	loadtabs();
}
//
void dataimpexpfrm::loadtabs()
{
	QString qstr = QString("SELECT * FROM datatables WHERE users LIKE '%%1 [1%';").arg(username);
	QSqlQuery query1(qstr);
	if ( query1.isActive())
	{
		while ( query1.next())
		{
			cmbexpcsv->addItem(query1.value(2).toString());
			dataexplist.append(query1.value(1).toString());
		}
	}
	
	qstr = QString("SELECT * FROM datatables WHERE users LIKE '%%1 [11%';").arg(username);
	QSqlQuery query2(qstr);
	if ( query2.isActive())
	{
		while ( query2.next())
		{
			cmbimpcsv->addItem(query2.value(2).toString());
			dataimplist.append(query2.value(1).toString());
		}
	}
}
//
void dataimpexpfrm::next()
{
	disconnect(btnnext, SIGNAL(released()), this, SLOT(next()));
	if(rbtn1->isChecked())
	{
		mainstack->setCurrentIndex(1);
		connect(btnnext, SIGNAL(released()), this, SLOT(impcsv()));
		btnnext->setText(tr("Import"));
		btnnext->setIcon(QIcon(QString::fromUtf8(":/button_ok.png")));
	}
	else if(rbtn2->isChecked())
	{
		mainstack->setCurrentIndex(2);
		connect(btnnext, SIGNAL(released()), this, SLOT(expcsv()));
		btnnext->setText(tr("Export"));
		btnnext->setIcon(QIcon(QString::fromUtf8(":/button_ok.png")));
	}
}
//
void dataimpexpfrm::loadcolumns(QString table)
{
	treeexpcsv->clear();
	tableimpcsv->clear();
	treeexpcsv->setColumnCount(0);
	tableimpcsv->setColumnCount(0);
	QString qstr = QString("SELECT cols FROM datatables WHERE name='%1';").arg(table);
	QSqlQuery query(qstr);
	if(query.isActive())
	{
		query.next();
		QStringList cols; 
		cols << "ID";
		QStringList tmpcols = query.value(0).toString().split("#");
		int i;
		for(i=0;i<tmpcols.count();i++)
			cols << tmpcols[i].section(":", 0, 0);
		treeexpcsv->setColumnCount(cols.count());
		if(mainstack->currentIndex() == 1)
			tableimpcsv->setHorizontalHeaderLabels(cols);
		else if(mainstack->currentIndex() == 2)
			treeexpcsv->setHeaderLabels(cols);
	}
	else
	{
		QSqlError sqlerror = query.lastError();
		QMessageBox::critical(0,"Error...", tr("Error during database access\n\n")+sqlerror.text());
	}
	treeexpcsv->hideColumn(0);
	tableimpcsv->hideColumn(0);
}
//
void dataimpexpfrm::back()
{
	mainstack->setCurrentIndex(0);
	btnnext->setText(tr("Next >>"));
	btnnext->setIcon(QIcon(QString("")));

	disconnect(btnnext, SIGNAL(released()), this, SLOT(impcsv()));
	disconnect(btnnext, SIGNAL(released()), this, SLOT(expcsv()));
	connect(btnnext, SIGNAL(released()), this, SLOT(next()));
}
//
void dataimpexpfrm::loaddata_expcsv()
{
	int i;
	loadcolumns(dataexplist[cmbexpcsv->currentIndex()]);
	
	QString qstr = QString("SELECT * FROM %1 ORDER BY col1;").arg(dataexplist[cmbexpcsv->currentIndex()]);
	QSqlQuery query(qstr);
	if(query.isActive())
	{
		while(query.next())
		{
			QTreeWidgetItem *item  = new QTreeWidgetItem(treeexpcsv);
			for(i=0;i<treeexpcsv->columnCount();i++)
				item->setText(i, query.value(i).toString());
		}
	}
	else
	{
		QSqlError sqlerror = query.lastError();
		QMessageBox::critical(0,"Error...", tr("Error during database access\n\n")+sqlerror.text());
	}
}
//
void dataimpexpfrm::expcsv()
{
	if(treeexpcsv->topLevelItemCount() > 0)
	{
		int i, ii;
		QString filestr = QFileDialog::getSaveFileName ( this, tr("Save CSV File..."),
						QDir::homePath(),
						tr("CSV-File (*.*)") );
		QFile file(filestr);
		progbar->setValue(0);
		progbar->setMaximum(treeexpcsv->topLevelItemCount());
		if(filestr != "")
		{
			if(file.open(QIODevice::WriteOnly))	    
			{
				QString tmpstr = "";
				QTextStream outstream( &file );
				QTreeWidgetItem *item = treeexpcsv->headerItem();
				for(i=0;i<treeexpcsv->columnCount();i++)
					tmpstr += "\"" + item->text(i) + "\",";
				outstream << tmpstr.leftJustified(tmpstr.length()-1, '.', true) << "\n";
				for(ii=0;ii<treeexpcsv->topLevelItemCount();ii++)
				{
					tmpstr = "";
					item = new QTreeWidgetItem; 
					item = treeexpcsv->topLevelItem(ii);
					if(rbtnexpcsvall->isChecked() || (rbtnexpcsvsel->isChecked() && item->isSelected()))
					{
						for(i=0;i<treeexpcsv->columnCount();i++)
						{
							if(item->text(i) != "")
								tmpstr += "\"" + item->text(i).simplified() + "\",";
							else
								tmpstr += ",";
						}

						outstream << tmpstr.leftJustified(tmpstr.length()-1, '.', true) << "\n";
					}
					progbar->setValue(ii+1); 
				}
				file.close();
				QMessageBox::information(0,"CSV export...", tr("Export finished."));
				this->accept();
			}
			else
				QMessageBox::critical(0,"CSV export...", tr("Can't export CVS-file."));
		}
	}
}
//
void dataimpexpfrm::selectfilecsv()
{
	QString filestr = QFileDialog::getOpenFileName ( this, tr("Open CSV-File..."),
					QDir::homePath(),
					tr("CSV-File (*.*)") );
	txtimpcsv->setText(filestr);
}
//
void dataimpexpfrm::loadfilecsv()
{
	QStringList cols; 
	QString qstr = QString("SELECT cols FROM datatables WHERE name='%1';").arg(dataimplist[cmbimpcsv->currentIndex()]);
	QSqlQuery query(qstr);
	if(query.isActive())
	{
		query.next();
		cols << "" << "ID";
		QStringList tmpcols = query.value(0).toString().split("#");
		int i;
		for(i=0;i<tmpcols.count();i++)
			cols << tmpcols[i].section(":", 0, 0);
	}
	else
	{
		QSqlError sqlerror = query.lastError();
		QMessageBox::critical(0,"Error...", tr("Error during database access\n\n")+sqlerror.text());
	}
	
	
	tableimpcsv->setRowCount(1);

	QStringList filestream;

	QFile file(txtimpcsv->text());
	if(file.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&file);
		while(!stream.atEnd())
			filestream.append(stream.readLine());
		file.close();
	}
	else
		QMessageBox::critical(0,"Error...", tr("Error during reading of the File!"));
		
	int i, ii;
	if(filestream.count() > 0)
	{
		progbar->setMaximum(filestream.count());
		tableimpcsv->setColumnCount(filestream[0].count(txtimpcsvseparator->text())+1);
		tableimpcsv->setRowCount(filestream.count()+1);
		for(i=0;i<filestream.count();i++)
		{
			progbar->setValue(i);
			QStringList fields; 
			QStringList tmpfields = filestream[i].split(txtimpcsvseparator->text());
			
			//Fields die irrtümlicherweise durch ein, getrennt wurden wieder zusammenführen
			for(ii=0;ii<tmpfields.count();ii++)
			{
				if((tmpfields[ii].mid(0,1) == "\"" && tmpfields[ii].mid(tmpfields[ii].length()-1,1) == "\"") || tmpfields[ii].length() == 0)
					fields << tmpfields[ii];
				else
				{
					QString tmpstr = tmpfields[ii];
					do {
						ii++;
						tmpstr += ","+tmpfields[ii];
					}while(!(tmpstr.trimmed().mid(0,1) == "\"" && tmpstr.trimmed().mid(tmpstr.trimmed().length()-1,1) == "\""));
					fields << tmpstr;
				}
			}
			////////

			for(ii=0;ii<fields.count();ii++)
			{
				QTableWidgetItem *item = new QTableWidgetItem;
				item->setText(fields[ii].replace("\"", ""));
				tableimpcsv->setItem(i+1, ii, item);
			}
		}
		progbar->setValue(progbar->maximum());
	}
	for(i=0;i<tableimpcsv->columnCount();i++)
	{
		QComboBox *cmbcols;
		cmbcols = new QComboBox(this);
		cmbcols->addItems(cols);
		
		QTableWidgetItem *item = tableimpcsv->item(1, i);
		if(item != 0)
			cmbcols->setCurrentIndex(cmbcols->findText(item->text()));

		tableimpcsv->setCellWidget(0,i,cmbcols);
	}
}
//
void dataimpexpfrm::impcsv()
{
	QString collabels = "";
	int i, ii;
	for(i=0;i<tableimpcsv->columnCount();i++)
	{
		QComboBox *readcombo = static_cast<QComboBox*>(tableimpcsv->cellWidget(0, i));
		if(readcombo->currentText() != "") 
			collabels += QString("`col%1`,").arg(readcombo->currentIndex()-1);
	}
	collabels = collabels.leftJustified(collabels.length()-1, '.', true).replace("col0","ID"); //col0 = ID

	QString tmpstr;
	QTableWidgetItem *item = new QTableWidgetItem;
	progbar->setValue(0);
	progbar->setMaximum(tableimpcsv->rowCount());
	for(i=spbimpcsv->value()-1;i<tableimpcsv->rowCount();i++)
	{
		item = new QTableWidgetItem();
		item = tableimpcsv->item(i, 0);
		
		if(rbtnimpcsvall->isChecked() || (rbtnimpcsvsel->isChecked() && item->isSelected()))
		{
			tmpstr = "";
			for(ii=0;ii<tableimpcsv->columnCount();ii++)
			{
				QComboBox *readcombo = static_cast<QComboBox*>(tableimpcsv->cellWidget(0, ii));
				if(readcombo->currentText() != "")
				{
					item = new QTableWidgetItem();
					item = tableimpcsv->item(i, ii);
					if(item!=0)
						tmpstr += "'"+item->text()+"',";
					else
						tmpstr += "'',";
				}
			}
			tmpstr = tmpstr.leftJustified(tmpstr.length()-1, '.', true);
			QString qstr = QString("INSERT INTO %1 (%2)VALUES(%3);").arg(dataimplist[cmbimpcsv->currentIndex()]).arg(collabels).arg(tmpstr);
			QSqlQuery ins_query(qstr);
			QSqlError sqlerror = ins_query.lastError();
			if(sqlerror.isValid())
				QMessageBox::critical(0,"Error...", tr("Can't insert dataset.\n\n")+sqlerror.text());
		}
		progbar->setValue(i);
	}
	progbar->setValue(progbar->maximum());
	QMessageBox::information(0,"CSV-File import...", tr("CSV import finished."));
	this->accept();
}

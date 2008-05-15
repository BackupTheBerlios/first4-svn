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
#include "addrimpexpfrm.h"
//
extern int uid;
extern QString username;
QStringList direxplist, dirimplist;
//
addrimpexpfrm::addrimpexpfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void addrimpexpfrm::init()
{
	this->setFixedSize(this->width(), this->height());
	mainstack->setCurrentIndex(0);
	
	connect(btncancel, SIGNAL(released()), this, SLOT(reject()));
	connect(btnnext, SIGNAL(released()), this, SLOT(next()));
	connect(btnback, SIGNAL(released()), this, SLOT(back()));
	connect(btnexpcsvload, SIGNAL(released()), this, SLOT(loaddir_expcsv()));
	connect(btnexpvcardload, SIGNAL(released()), this, SLOT(loaddir_expvcard()));
	connect(btnimpvcardload, SIGNAL(released()), this, SLOT(loadfilevcard()));
	connect(btnimpvcardselectfile, SIGNAL(released()), this, SLOT(selectfilevcard()));
	connect(btnimpcsvload, SIGNAL(released()), this, SLOT(loadfilecsv()));
	connect(btnimpcsvselectfile, SIGNAL(released()), this, SLOT(selectfilecsv()));
	direxplist.clear();
	dirimplist.clear();
	cmbexpcsv->clear();
	cmbexpvcard->clear();
	cmbimpvcard->clear();
	
	treeexpcsv->setColumnCount(0);
	treeexpvcard->setColumnCount(0);
	
	loaddirs();
}
//
void addrimpexpfrm::loaddirs()
{
    QString qstr = QString("SELECT * FROM directories WHERE users LIKE '%%1 [1%';").arg(username);
    QSqlQuery query1(qstr);
    if ( query1.isActive())
    {
		while ( query1.next())
		{
			cmbexpcsv->addItem(query1.value(2).toString());
			cmbexpvcard->addItem(query1.value(2).toString());
			direxplist.append(query1.value(1).toString());
		}
	}
	
    qstr = QString("SELECT * FROM directories WHERE users LIKE '%%1 [11%';").arg(username);
    QSqlQuery query2(qstr);
    if ( query2.isActive())
    {
		while ( query2.next())
		{
			cmbimpcsv->addItem(query2.value(2).toString());
			cmbimpvcard->addItem(query2.value(2).toString());
			dirimplist.append(query2.value(1).toString());
		}
	}
}
//
void addrimpexpfrm::next()
{
	if(rbtn1->isChecked())
	{
		mainstack->setCurrentIndex(1);
		connect(btnnext, SIGNAL(released()), this, SLOT(impvcard()));
		btnnext->setText(tr("Import"));
		btnnext->setIcon(QIcon(QString::fromUtf8(":/button_ok.png")));
	}
	else if(rbtn2->isChecked())
	{
		mainstack->setCurrentIndex(2);
		connect(btnnext, SIGNAL(released()), this, SLOT(expvcard()));
		btnnext->setText(tr("Export"));
		btnnext->setIcon(QIcon(QString::fromUtf8(":/button_ok.png")));
	}
	else if(rbtn3->isChecked())
	{
		mainstack->setCurrentIndex(3);
		connect(btnnext, SIGNAL(released()), this, SLOT(impcsv()));
		btnnext->setText(tr("Import"));
		btnnext->setIcon(QIcon(QString::fromUtf8(":/button_ok.png")));
	}
	else if(rbtn4->isChecked())
	{
		mainstack->setCurrentIndex(4);
		connect(btnnext, SIGNAL(released()), this, SLOT(expcsv()));
		btnnext->setText(tr("Export"));
		btnnext->setIcon(QIcon(QString::fromUtf8(":/button_ok.png")));
	}
}
//
void addrimpexpfrm::loadcolumns(QString table)
{
	treeexpcsv->clear();
	treeexpvcard->clear();
	tableimpvcard->clear();
	tableimpcsv->clear();
	QStringList collabels;
	QString qstr = QString("SHOW COLUMNS FROM %1").arg(table);
	QSqlQuery query(qstr);
	if(query.isActive())
	{
		treeexpcsv->setColumnCount(query.size());
		treeexpvcard->setColumnCount(query.size());
		tableimpvcard->setColumnCount(query.size());
		while(query.next())
			collabels << query.value(0).toString();
		if(mainstack->currentIndex() == 1)
			tableimpvcard->setHorizontalHeaderLabels(collabels);
		else if(mainstack->currentIndex() == 2)
			treeexpvcard->setHeaderLabels(collabels);
		else if(mainstack->currentIndex() == 3)
			tableimpcsv->setHorizontalHeaderLabels(collabels);
		else if(mainstack->currentIndex() == 4)
			treeexpcsv->setHeaderLabels(collabels);
	}
	else
	{
		QSqlError sqlerror = query.lastError();
		QMessageBox::critical(0,"Error...", tr("Error during database access\n\n")+sqlerror.text());
	}
	treeexpcsv->hideColumn(0);
	treeexpvcard->hideColumn(0);
	tableimpvcard->hideColumn(0);
	tableimpcsv->hideColumn(0);
}
//
void addrimpexpfrm::back()
{
	mainstack->setCurrentIndex(0);
	btnnext->setText(tr("Next >>"));
	btnnext->setIcon(QIcon(QString("")));

	disconnect(btnnext, SIGNAL(released()), this, SLOT(impvcard()));
	disconnect(btnnext, SIGNAL(released()), this, SLOT(expvcard()));
	disconnect(btnnext, SIGNAL(released()), this, SLOT(impcsv()));
	disconnect(btnnext, SIGNAL(released()), this, SLOT(expcsv()));
	
	connect(btnnext, SIGNAL(released()), this, SLOT(next()));
}
void addrimpexpfrm::loaddir_expcsv()
{
	int i;
	loadcolumns(direxplist[cmbexpcsv->currentIndex()]);
	
	QString qstr = QString("SELECT * FROM %1 ORDER BY company, lastname, firstname;").arg(direxplist[cmbexpcsv->currentIndex()]);
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
void addrimpexpfrm::expcsv()
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
								tmpstr += "\"" + item->text(i) + "\",";
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
void addrimpexpfrm::loaddir_expvcard()
{
	int i;
	loadcolumns(direxplist[cmbexpvcard->currentIndex()]);
	
	QString qstr = QString("SELECT * FROM %1 ORDER BY company, lastname, firstname;").arg(direxplist[cmbexpvcard->currentIndex()]);
	QSqlQuery query(qstr);
	if(query.isActive())
	{
		while(query.next())
		{
			QTreeWidgetItem *item  = new QTreeWidgetItem(treeexpvcard);
			for(i=0;i<treeexpvcard->columnCount();i++)
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
void addrimpexpfrm::expvcard()
{
	if(treeexpvcard->topLevelItemCount() > 0)
	{
		int i;
		QString filestr = QFileDialog::getExistingDirectory ( this, tr("Save as vCard..."),
						QDir::homePath(),
						QFileDialog::ShowDirsOnly  | QFileDialog::DontResolveSymlinks);

		progbar->setValue(0);
		progbar->setMaximum(treeexpvcard->topLevelItemCount());
		if(cmbexpvcardtype->currentIndex() == 0)
		{
			QFile file(filestr+"/"+cmbexpvcard->currentText()+".vcf");
			if(filestr != "")
			{
				if(file.open(QIODevice::WriteOnly))	    
				{
					QTextStream outstream( &file );
					for(i=0;i<treeexpvcard->topLevelItemCount();i++)
					{
						QTreeWidgetItem *item = treeexpvcard->topLevelItem(i);
						if(rbtnexpvcardall->isChecked() || (rbtnexpvcardsel->isChecked() && item->isSelected()))
						{
							outstream << "BEGIN:VCARD\nVERSION:3.0\n";
							outstream << "N:" << "" << item->text(3) << ";" << item->text(4) << ";;" << item->text(5) << ";\n";
							outstream << "FN:" << item->text(4) << " " << item->text(3) << "\n";
							outstream << "ORG:" << item->text(2) << "\n";
							outstream << "URL:" << item->text(20) << "\n";
							if(item->text(17) != "")
								outstream << "EMAIL;TYPE=INTERNET:" << item->text(17) << "\n";
							if(item->text(18) != "")
								outstream << "EMAIL;TYPE=INTERNET:" << item->text(18) << "\n";
							if(item->text(19) != "")
								outstream << "EMAIL;TYPE=INTERNET:" << item->text(19) << "\n";
							outstream << "TEL;TYPE=WORK,VOICE:" << item->text(11) << "\n";
							outstream << "TEL;TYPE=WORK,VOICE,PREF:" << item->text(12) << "\n";
							outstream << "TEL;TYPE=WORK,FAX:" << item->text(13) << "\n";
							outstream << "TEL;TYPE=HOME,VOICE:" << item->text(14) << "\n";
							outstream << "TEL;TYPE=HOME,FAX:" << item->text(15) << "\n";
							outstream << "TEL;TYPE=HOME,CELL:" << item->text(16) << "\n";
							outstream << "ADR;TYPE=WORK:" << item->text(6) << ";;" << item->text(7) << ";" << item->text(8) << ";;" << item->text(9) << ";" << item->text(10) <<"\n";
							outstream << "END:VCARD\n";
						}
						progbar->setValue(i+1); 
					}
					file.close();
					QMessageBox::information(0,"vCard export...", tr("Export in file '%1' finished.").arg(cmbexpvcard->currentText()+".vcf"));
					this->accept();
				}
				else
					QMessageBox::critical(0,"vCard export...", tr("Can't export vCard."));
			}
		}
		else
		{
			for(i=0;i<treeexpvcard->topLevelItemCount();i++)
			{
				QTreeWidgetItem *item = treeexpvcard->topLevelItem(i);
				if(rbtnexpvcardall->isChecked() || (rbtnexpvcardsel->isChecked() && item->isSelected()))
				{
					QFile file(filestr+"/"+cmbexpvcard->currentText()+"_"+item->text(2)+"_"+item->text(3)+"_"+item->text(4)+".vcf");
					if(filestr != "")
					{
						if(file.open(QIODevice::WriteOnly))	    
						{
							QTextStream outstream( &file );
							outstream << "BEGIN:VCARD\nVERSION:3.0\n";
							outstream << "N:" << "" << item->text(3) << ";" << item->text(4) << ";;" << item->text(5) << ";\n";
							outstream << "FN:" << item->text(4) << " " << item->text(3) << "\n";
							outstream << "ORG:" << item->text(2) << "\n";
							outstream << "URL:" << item->text(20) << "\n";
							if(item->text(17) != "")
								outstream << "EMAIL;TYPE=INTERNET:" << item->text(17) << "\n";
							if(item->text(18) != "")
								outstream << "EMAIL;TYPE=INTERNET:" << item->text(18) << "\n";
							if(item->text(19) != "")
								outstream << "EMAIL;TYPE=INTERNET:" << item->text(19) << "\n";
							outstream << "TEL;TYPE=WORK,VOICE:" << item->text(11) << "\n";
							outstream << "TEL;TYPE=WORK,VOICE,PREF:" << item->text(12) << "\n";
							outstream << "TEL;TYPE=WORK,FAX:" << item->text(13) << "\n";
							outstream << "TEL;TYPE=HOME,VOICE:" << item->text(14) << "\n";
							outstream << "TEL;TYPE=HOME,FAX:" << item->text(15) << "\n";
							outstream << "TEL;TYPE=HOME,CELL:" << item->text(16) << "\n";
							outstream << "ADR;TYPE=WORK:" << item->text(6) << ";;" << item->text(7) << ";" << item->text(8) << ";;" << item->text(9) << ";" << item->text(10) <<"\n";
							outstream << "END:VCARD\n";
							file.close();
						}
						else
							QMessageBox::critical(0,"vCard export...", tr("Can't export vCard."));
					}
				}
				progbar->setValue(i+1); 
			}
			QMessageBox::information(0,"vCard export...", tr("Export of '%1' finished.").arg(cmbexpvcard->currentText()));
			this->accept();
		}
	}
}
void addrimpexpfrm::selectfilevcard()
{
	QString filestr = QFileDialog::getOpenFileName ( this, tr("Open vCard..."),
					QDir::homePath(),
					tr("vCard (*.vcf)") );
	txtimpvcard->setText(filestr);
}
//
void addrimpexpfrm::loadfilevcard()
{
	loadcolumns(dirimplist[cmbimpvcard->currentIndex()]);
	tableimpvcard->setRowCount(0);

	bool ok;
	QStringList vcfrows, filestream, filteredfile;
	vcfrows << "ORG:" << "N:" << "ADR;TYPE=WORK:" << "TEL;TYPE=WORK,VOICE:" << "TEL;TYPE=WORK,VOICE,PREF:" << "TEL;TYPE=WORK,FAX:" << "TEL;TYPE=HOME," << "TEL;TYPE=HOME,FAX:" << "CELL" << "EMAIL" << "URL:";

	filteredfile << "" << "" << "" << "" << "" << "" << "" << "" << "" << "" << "";

	QFile file(txtimpvcard->text());
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
	progbar->setValue(0);
	progbar->setMaximum(filestream.size());
	for(i=0;i<filestream.size();i++)
	{
		if(filestream[i].contains("BEGIN:VCARD"))
			ok = TRUE;
		if(TRUE)
		{
			for(ii=0;ii<vcfrows.size();ii++)
			{
				if(filestream[i].startsWith(vcfrows[ii]))
					filteredfile[ii] = filestream[i].section(":", 1, 10);
			}
		}
		if(filestream[i].contains("END:VCARD") && ok)
		{
			tableimpvcard->setRowCount(tableimpvcard->rowCount()+1);

			QTableWidgetItem *item = new QTableWidgetItem;

			item->setText(filteredfile[0]);
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 2, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[1].section(";",0,0));
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 3, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[1].section(";",1,1));
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 4, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[1].section(";",3,3));
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 5, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[2].section(";",0,0));
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 6, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[2].section(";",2,2));
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 7, item);
			
			item = new QTableWidgetItem();
			item->setText(filteredfile[2].section(";",3,3));
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 8, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[2].section(";",5,5));
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 9, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[2].section(";",6,6));
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 10, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[3]);
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 11, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[4]);
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 12, item);
			
			item = new QTableWidgetItem();
			item->setText(filteredfile[5]);
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 13, item);
			
			item = new QTableWidgetItem();
			item->setText(filteredfile[6]);
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 14, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[7]);
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 15, item);
			
			item = new QTableWidgetItem();
			item->setText(filteredfile[8]);
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 16, item);

			item = new QTableWidgetItem();
			item->setText(filteredfile[9]);
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 17, item);
			
			item = new QTableWidgetItem();
			item->setText(filteredfile[10]);
			tableimpvcard->setItem(tableimpvcard->rowCount()-1, 20, item);
			
			ok = FALSE;
			filteredfile.clear();
			filteredfile << "" << "" << "" << "" << "" << "" << "" << "" << "" << "" << "";
		}
		progbar->setValue(i);
	}
	progbar->setValue(progbar->maximum());
}
//
void addrimpexpfrm::impvcard()
{
	QString collabels = "";
	QString qstr = QString("SHOW COLUMNS FROM %1").arg(dirimplist[cmbimpvcard->currentIndex()]);
	QSqlQuery query(qstr);
	if(query.isActive())
	{
		while(query.next())
			collabels += "`"+query.value(0).toString()+"`,";
		collabels = collabels.leftJustified(collabels.length()-1, '.', true);
	}
	else
	{
		QSqlError sqlerror = query.lastError();
		QMessageBox::critical(0,"Error...", tr("Error during database access\n\n")+sqlerror.text());
	}
	
	int i, ii;
	QTableWidgetItem *item = new QTableWidgetItem;
	progbar->setValue(0);
	progbar->setMaximum(tableimpvcard->rowCount());
	for(i=0;i<tableimpvcard->rowCount();i++)
	{
		qstr = QString("INSERT INTO %1 ("+collabels+")VALUES('',").arg(dirimplist[cmbimpvcard->currentIndex()]);
		for(ii=1;ii<tableimpvcard->columnCount()-2;ii++)
		{
			item = new QTableWidgetItem();
			item = tableimpvcard->item(i, ii);
			if(item!=0)
				qstr += "'"+item->text()+"',";
			else
				qstr += "'',";
		}
		qstr = qstr + QString("'%1','');").arg(QDate::currentDate().toString("dd.MM.yyyy"));
		QSqlQuery ins_query(qstr);
		progbar->setValue(i);
	}
	progbar->setValue(progbar->maximum());
	QMessageBox::information(0,"vCard import...", tr("vCard import finished."));
	this->accept();
}
//
void addrimpexpfrm::selectfilecsv()
{
	QString filestr = QFileDialog::getOpenFileName ( this, tr("Open CSV-File..."),
					QDir::homePath(),
					tr("CSV-File (*.*)") );
	txtimpcsv->setText(filestr);
}
//
void addrimpexpfrm::loadfilecsv()
{
	QStringList columns;
	columns << "";

	QSqlQuery query(QString("SHOW COLUMNS FROM %1").arg(dirimplist[cmbimpvcard->currentIndex()]));
	if(query.isActive())
	{
		while(query.next())
			columns << query.value(0).toString();
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
		tableimpcsv->setColumnCount(filestream[0].count(txtimpcsvseparator->text())+1);
		tableimpcsv->setRowCount(filestream.count()+1);
		for(i=0;i<filestream.count();i++)
		{
			//QStringList fields = filestream[i].split("\""+txtimpcsvseparator->text()+"\"");
			QStringList fields = filestream[i].split(txtimpcsvseparator->text());
			for(ii=0;ii<fields.count();ii++)
			{
				QTableWidgetItem *item = new QTableWidgetItem;
				item->setText(fields[ii].replace("\"", ""));
				tableimpcsv->setItem(i+1, ii, item);
			}
		}
	}
	for(i=0;i<tableimpcsv->columnCount();i++)
	{
		QComboBox *cmbcols;
		cmbcols = new QComboBox(this);
		cmbcols->addItems(columns);
		
		QTableWidgetItem *item = tableimpcsv->item(1, i);
		if(item != 0)
			cmbcols->setCurrentIndex(cmbcols->findText(item->text()));

		tableimpcsv->setCellWidget(0,i,cmbcols);
	}
}
//
void addrimpexpfrm::impcsv()
{
	QString collabels = "";
	int i, ii;
	for(i=0;i<tableimpcsv->columnCount();i++)
	{
		QComboBox *readcombo = static_cast<QComboBox*>(tableimpcsv->cellWidget(0, i));
		if(readcombo->currentText() != "") 
			collabels += "`"+readcombo->currentText()+"`,";
	}
	collabels = collabels.leftJustified(collabels.length()-1, '.', true);

	QString tmpstr;
	QTableWidgetItem *item = new QTableWidgetItem;
	progbar->setValue(0);
	progbar->setMaximum(tableimpcsv->rowCount());
	for(i=spbimpcsv->value();i<tableimpcsv->rowCount();i++)
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
			QString qstr = QString("INSERT INTO %1 (%2)VALUES(%3);").arg(dirimplist[cmbimpcsv->currentIndex()]).arg(collabels).arg(tmpstr);
			QSqlQuery ins_query(qstr);
		}
		progbar->setValue(i);
	}
	progbar->setValue(progbar->maximum());
	QMessageBox::information(0,"CSV-File import...", tr("CSV import finished."));
	this->accept();
}

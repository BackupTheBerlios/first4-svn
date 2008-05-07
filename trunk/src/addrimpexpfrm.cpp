#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QHeaderView>
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
    QString qstr = QString("SELECT * FROM adrtabs WHERE users LIKE '%%1 [1%';").arg(username);
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
	
    qstr = QString("SELECT * FROM adrtabs WHERE users LIKE '%%1 [11%';").arg(username);
    QSqlQuery query2(qstr);
    if ( query2.isActive())
    {
		while ( query2.next())
		{
			//cmbexpcsv->addItem(query1.value(2).toString());
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
		btnnext->setText(tr("Import"));
	}
	else if(rbtn2->isChecked())
	{
		mainstack->setCurrentIndex(2);
		connect(btnnext, SIGNAL(released()), this, SLOT(expvcard()));
		btnnext->setText(tr("Export"));
	}
	else if(rbtn3->isChecked())
	{
		mainstack->setCurrentIndex(3);
	}
	else if(rbtn4->isChecked())
	{
		mainstack->setCurrentIndex(4);
		connect(btnnext, SIGNAL(released()), this, SLOT(expcsv()));
		btnnext->setText(tr("Export"));
	}
	btnnext->setIcon(QIcon(QString::fromUtf8(":/button_ok.png")));
}
//
void addrimpexpfrm::loadcolumns(QString table)
{
	treeexpcsv->clear();
	treeexpvcard->clear();
	treeimpvcard->clear();
	QStringList collabels;
	QString qstr = QString("SHOW COLUMNS FROM %1").arg(table);
	QSqlQuery query(qstr);
	if(query.isActive())
	{
		treeexpcsv->setColumnCount(query.size());
		treeexpvcard->setColumnCount(query.size());
		treeimpvcard->setColumnCount(query.size());
		while(query.next())
			collabels << query.value(0).toString();
		if(mainstack->currentIndex() == 1)
			treeimpvcard->setHeaderLabels(collabels);
		else if(mainstack->currentIndex() == 2)
			treeexpvcard->setHeaderLabels(collabels);
		else if(mainstack->currentIndex() == 3)
			treeexpcsv->setHeaderLabels(collabels);
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
	treeimpvcard->hideColumn(0);
}
//
void addrimpexpfrm::back()
{
	mainstack->setCurrentIndex(0);
	btnnext->setText(tr("Next >>"));
	btnnext->setIcon(QIcon(QString("")));
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
			{
				item->setText(i, query.value(i).toString());
			}
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
				QTextStream outstream( &file );
				QTreeWidgetItem *item = treeexpcsv->headerItem();
				for(i=0;i<treeexpcsv->columnCount();i++)
					outstream << item->text(i) << ";";
				outstream << "\n";
				for(ii=0;ii<treeexpcsv->topLevelItemCount();ii++)
				{
					item = new QTreeWidgetItem; 
					item = treeexpcsv->topLevelItem(ii);
					if(rbtnexpcsvall->isChecked() || (rbtnexpcsvsel->isChecked() && item->isSelected()))
					{
						for(i=0;i<treeexpcsv->columnCount();i++)
							outstream << item->text(i) << ";";
						outstream << "\n";
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
			{
				item->setText(i, query.value(i).toString());
			}
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
							outstream << "URL:" << item->text(18) << "\n";
							outstream << "EMAIL;TYPE=INTERNET:" << item->text(15) << "\n";
							outstream << "EMAIL;TYPE=INTERNET:" << item->text(16) << "\n";
							outstream << "EMAIL;TYPE=INTERNET:" << item->text(17) << "\n";
							outstream << "TEL;TYPE=WORK,VOICE:" << item->text(9) << "\n";
							outstream << "TEL;TYPE=WORK,VOICE,PREF:" << item->text(10) << "\n";
							outstream << "TEL;TYPE=WORK,FAX:" << item->text(11) << "\n";
							outstream << "TEL;TYPE=HOME,VOICE:" << item->text(12) << "\n";
							outstream << "TEL;TYPE=HOME,FAX:" << item->text(13) << "\n";
							outstream << "TEL;TYPE=HOME,CELL:" << item->text(14) << "\n";
							outstream << "ADR;TYPE=WORK:" << item->text(6) << ";;" << item->text(7) << ";" << item->text(8).section(" ",1,10) << ";;" << item->text(8).section(" ",0,0) << ";" << "\n";
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
							outstream << "URL:" << item->text(18) << "\n";
							outstream << "EMAIL;TYPE=INTERNET:" << item->text(15) << "\n";
							outstream << "EMAIL;TYPE=INTERNET:" << item->text(16) << "\n";
							outstream << "EMAIL;TYPE=INTERNET:" << item->text(17) << "\n";
							outstream << "TEL;TYPE=WORK,VOICE:" << item->text(9) << "\n";
							outstream << "TEL;TYPE=WORK,VOICE,PREF:" << item->text(10) << "\n";
							outstream << "TEL;TYPE=WORK,FAX:" << item->text(11) << "\n";
							outstream << "TEL;TYPE=HOME,VOICE:" << item->text(12) << "\n";
							outstream << "TEL;TYPE=HOME,FAX:" << item->text(13) << "\n";
							outstream << "TEL;TYPE=HOME,CELL:" << item->text(14) << "\n";
							outstream << "ADR;TYPE=WORK:" << item->text(6) << ";;" << item->text(7) << ";" << item->text(8).section(" ",1,10) << ";;" << item->text(8).section(" ",0,0) << ";" << "\n";
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
	QFile file(txtimpvcard->text());	
}
//
void addrimpexpfrm::impvcard()
{
	
}

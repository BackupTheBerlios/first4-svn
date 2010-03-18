#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
//
#include "loginconfserversfrm.h"
#include "dbwizzardfrm.h"
//
loginconfserversfrm::loginconfserversfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void loginconfserversfrm::init()
{
	this->setFixedSize ( this->width(), this->height() );
	connect ( btnclose, SIGNAL ( released() ), this, SLOT ( accept() ) );
	connect ( btnadddb, SIGNAL ( released() ), this, SLOT ( addservers() ) );
	connect ( btndeldb, SIGNAL ( released() ), this, SLOT ( delservers() ) );
	
	loadservers();
}
//
void loginconfserversfrm::loadservers()
{
	listservers->clear();
    QStringList tmp;
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QString line;
		QTextStream stream ( &file );
		while(stream.readLine() != "[SERVERS]" && !stream.atEnd());
		do {
			line = stream.readLine();
			if(line != "")
				listservers->insertItem ( -1, line );
		} while (line != "" && !stream.atEnd());
		file.close();
	}
}
//
void loginconfserversfrm::addservers()
{
	dbwizzardfrm* wiz = new dbwizzardfrm;
	wiz->init();
	if ( wiz->exec() )
		loadservers();
}
//
void loginconfserversfrm::delservers()
{
	if ( listservers->currentItem() )
		listservers->takeItem ( listservers->currentRow() );
		
	QStringList lines;
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QTextStream stream ( &file );
		while(!stream.atEnd())
			lines << stream.readLine();
	}
	file.close();
    
	if ( file.open ( QIODevice::WriteOnly ) )
	{
		int i, ii;
		QTextStream stream(&file);
		bool foundsec = FALSE;
		for(i=0;i<lines.count();i++)
		{
			if(lines[i] == "[SERVERS]")
			{
				foundsec = TRUE;
				stream << "[SERVERS]" << "\n";
				for (ii=0;ii<listservers->count();ii++ )
				{
					listservers->setCurrentRow ( ii );
					QListWidgetItem *item = listservers->currentItem();
					stream << item->text() << "\n";
				}
				while(lines[i].simplified() != "")
					i++;
				while(i<lines.count())
				{
					stream << lines[i] << "\n";	
					i++;
				}
			}
			else
			{
				stream << lines[i] << "\n";	
			}
		}
		if(!foundsec)
		{
			stream << "\n" << "[SERVERS]" << "\n";
			for (ii=0;ii<listservers->count();ii++ )
			{
				listservers->setCurrentRow ( ii );
				QListWidgetItem *item = listservers->currentItem();
				stream << item->text() << "\n";
			}
			stream << "\n";
		}
		file.close();
	}
	else
		QMessageBox::warning(0, "Databases...", "Can't write to configuration file.");
	loadservers();
}

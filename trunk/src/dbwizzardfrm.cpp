#include <QPushButton>
//
#include "dbwizzardfrm.h"
//
dbwizzardfrm::dbwizzardfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void dbwizzardfrm::init()
{
	connect(rbtnmysqlex, SIGNAL(clicked()), this, SLOT(enable_next()));
	connect(rbtnmysqlnew, SIGNAL(clicked()), this, SLOT(enable_next()));
	connect(btnnext, SIGNAL(clicked()), this, SLOT(next()));
	connect(btnback, SIGNAL(clicked()), this, SLOT(back()));
}
//
void dbwizzardfrm::next()
{
	int minindex, maxindex = 0;
	if(rbtnmysqlex->isChecked())
	{
		minindex = 1;
		maxindex = 2;
	}
	else if(rbtnmysqlnew->isChecked())
	{
		minindex = 3;
		maxindex = 7;
	}

	if(mainstackwidget->currentIndex() < maxindex)
	{
		if(mainstackwidget->currentIndex() < minindex)
			mainstackwidget->setCurrentIndex(minindex-1);
		mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()+1);
		if(mainstackwidget->currentIndex() == maxindex)
			btnnext->setText(QApplication::translate("dbwizzardfrm", "&Finish", 0, QApplication::UnicodeUTF8));
		else
			btnnext->setText(QApplication::translate("dbwizzardfrm", "&Next >>", 0, QApplication::UnicodeUTF8));
	}
}
//
void dbwizzardfrm::back()
{
	btnnext->setText(QApplication::translate("dbwizzardfrm", "&Next >>", 0, QApplication::UnicodeUTF8));
	int minindex, maxindex = 0;
	if(rbtnmysqlex->isChecked())
	{
		minindex = 1;
		maxindex = 2;
	}
	else if(rbtnmysqlnew->isChecked())
	{
		minindex = 3;
		maxindex = 7;
	}

	if(mainstackwidget->currentIndex() > minindex)
	{
		mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()-1);
	}
	else
		mainstackwidget->setCurrentIndex(0);
}
void dbwizzardfrm::enable_next()
{
	btnnext->setEnabled(TRUE);
}
//

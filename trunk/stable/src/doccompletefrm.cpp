#include <QFile>
#include <QTextStream>
//
#include "doccompletefrm.h"
//
doccompletefrm::doccompletefrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void doccompletefrm::init()
{
    this->setFixedSize(this->width(), this->height());
    QFile file( ".first/completedoc.conf" );
    if(file.open(QIODevice::ReadOnly))
    {
	QTextStream stream(&file);
	QString streamline;
	streamline = stream.readLine();
	if(streamline.mid(0, 1)=="1")
	    chkbox_1->setChecked(TRUE);
	if(streamline.mid(1, 1)=="1")
	    chkbox_2->setChecked(TRUE);
	if(streamline.mid(2, 1)=="1")
	    chkbox_3->setChecked(TRUE);
	if(streamline.mid(3, 1)=="1")
	    chkbox_4->setChecked(TRUE);
	if(streamline.mid(4, 1)=="1")
	    chkbox_5->setChecked(TRUE);
	if(streamline.mid(5, 1)=="1")
	    chkbox_6->setChecked(TRUE);	
	file.close();
    }	
}
//
void doccompletefrm::acceptdata()
{
    QFile file( ".first/completedoc.conf");
    if(file.open(QIODevice::WriteOnly))
    {
	QTextStream stream(&file);	
	if(chkbox_1->isChecked())
	    stream << "1" ;
	else
	    stream << "0" ;
	if(chkbox_2->isChecked())
	    stream << "1" ;
	else
	    stream << "0" ;
	if(chkbox_3->isChecked())
	    stream << "1" ;
	else
	    stream << "0" ;
	if(chkbox_4->isChecked())
	    stream << "1" ;
	else
	    stream << "0" ;
	if(chkbox_5->isChecked())
	    stream << "1" ;
	else
	    stream << "0" ;	
	if(chkbox_6->isChecked())
	    stream << "1" ;
	else
	    stream << "0" ;	
	stream <<"\n";
	
	file.close();   
    }    
    this->accept();
}

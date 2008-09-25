#include <QMessageBox>
//
#include "cashpoint_main.h"
//
extern QString username, fullname, firstver;
//
CashPoint *cashpoint_instance = NULL;
CashPoint::CashPoint( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
	cashpoint_instance = this;
}
//
void CashPoint::init(QStringList parameters)
{
	username=parameters[0];
	fullname=parameters[1];
	firstver=parameters[2];
	QString dbhost = parameters[3];
	QString dbname = parameters[4];
	this->setWindowTitle(QString("first4 Cashpoint-Plugin / User: %1 (%2) connected to %3@%4").arg(fullname).arg(username).arg(dbname).arg(dbhost));
}

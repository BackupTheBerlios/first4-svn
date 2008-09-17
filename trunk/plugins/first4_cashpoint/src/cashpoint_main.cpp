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
	QMessageBox::warning ( 0, tr ( "Check DB-Lock..." ), username);
}

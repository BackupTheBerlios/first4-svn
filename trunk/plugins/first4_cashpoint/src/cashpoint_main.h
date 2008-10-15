#ifndef CASHPOINT_MAIN_H
#define CASHPOINT_MAIN_H
//
#include <QWidget>
#include "ui_cashpoint.h"
//
class CashPoint;
extern CashPoint *cashpoint_instance;
//
class CashPoint : public QWidget, public Ui::cashpoint_main
{
Q_OBJECT
public:
	CashPoint( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init(QStringList parameters);
private slots:
	void checkdb();
private:
	void initvat();
	void closeEvent( QCloseEvent* ce );
};
#endif






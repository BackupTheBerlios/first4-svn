#ifndef ACCOUNTSEDITFRM_H
#define ACCOUNTSEDITFRM_H
//
#include "ui_accountseditfrm.h"
//
class accountseditfrm : public QDialog, public Ui::accountseditfrm
{
Q_OBJECT
private:
	void updateentry(QString tab);
public:
	accountseditfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
	void loadentry(QString tmpdbID);
	void setdbID(QString tmpdbID);
	void newentry(QString tab);
private slots:
	void acceptdata();
	void selectaddr();
	void clearaddr();
	void checkcode();
	void formatamount();
};
#endif






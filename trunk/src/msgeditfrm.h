#ifndef MSGEDITFRM_H
#define MSGEDITFRM_H
//
#include "ui_msgeditfrm.h"
//
class msgeditfrm : public QDialog, public Ui::msgeditfrm
{
Q_OBJECT
public:
	msgeditfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init(QString msgtype);
	void loadentry(QString dbID);
	void newentry();
private slots:
	void acceptdata();
	void changetab();
	void seladdress();
	void clearaddress();
private:
	void loadusers();
	void updateentry(QString dbID);
	void initvat();
public slots:
	void checkstock();
};
#endif






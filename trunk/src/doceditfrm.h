#ifndef DOCEDITFRM_H
#define DOCEDITFRM_H
//
#include "ui_doceditfrm.h"
//
class doceditfrm : public QWidget, public Ui::doceditfrm
{
Q_OBJECT
private:
	void closeEvent( QCloseEvent* ce );
	void readdoctab();
private slots:
	void selectaddress();
	void printpreview();
	void printesr();
public:
	doceditfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
    void initvat();
    void loadmaincfg();
	void opendocfromid(QString source, QString dbID);
public slots:
	void selecteddocument();
	void calc_tot();
	void print();
};
#endif






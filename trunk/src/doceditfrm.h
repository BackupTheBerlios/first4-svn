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
	void addrow();
private slots:
	void selectaddress();
	void printpreview();
	void printesr();
	void contmenu();
	void removerow();
	void navtable();
	void checkdb();
	void clearlblid();
	void completedoc();
	void printreport(bool complete);
	void registeramount();
	void revenue(QString dbID, QString amount);
	void refreshstockdb();
	void savecompletedoc();
	void newdocument();
	void opendoc();
	void savedoc();
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






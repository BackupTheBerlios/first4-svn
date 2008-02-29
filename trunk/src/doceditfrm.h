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
	QString writetexfile();
	QString loadtemplatedata(int dbid);
	QString loadgeneralinfo();
	QString loadtemplatedata();
private slots:
	void selectaddress();
	void printpreview();
	void printvesr();
	void contmenu();
	void removerow();
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
	void show_vat();
	QStringList vesr();
	void reject();
	void excl_vat();
	void editposition();
public:
	doceditfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
    void initvat();
    void loadmaincfg();
	void opendocfromid(QString source, QString dbID);
	void navtabonoff(bool state);
	void addrow();
public slots:
	void selecteddocument();
	void calc_tot();
	void calc_vat();
	void print();
	void navtable();
};
#endif






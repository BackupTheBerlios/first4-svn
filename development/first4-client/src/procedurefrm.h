#ifndef PROCEDUREFRM_H
#define PROCEDUREFRM_H
//
#include "ui_procedurefrm.h"
//
class procedurefrm : public QWidget, public Ui::procedurefrm
{
Q_OBJECT
public:
	procedurefrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	int init();
public slots:
	void neworder();
private slots:
	void settable();
	void editorder(QString dbID);
	void editarchiveorder(QString dbID);
	void deleteorder(QString dbID);
	void deletearchivorder(QString dbID);
	void completeorder();
	void createdoc_1(QString dbID);
	void createdoc_2(int doctype, QString docid);
	void updatedatabase();
	void search();
	void contmenu();
	void createoffer();
	void createorderconf();
	void createdeliverynote();
	void createinvoice();
	void checkeditID();
	void checkdeleteID();
private:
	int checkrights();
	void countabl();
	void filltable(int state);
	void closeEvent( QCloseEvent* ce );
};
#endif






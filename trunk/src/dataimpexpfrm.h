#ifndef DATAIMPEXPFRM_H
#define DATAIMPEXPFRM_H
//
#include <QDialog>
#include "ui_dataimpexpfrm.h"
//
class dataimpexpfrm : public QDialog, public Ui::dataimpexpfrm
{
Q_OBJECT
public:
	dataimpexpfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
private slots:
	void next();
	void back();
	void loadcolumns(QString table);
	void loaddata_expcsv();
	void expcsv();
	void selectfilecsv();
	void loadfilecsv();
	void impcsv();
private:
	void loadtabs();
};
#endif






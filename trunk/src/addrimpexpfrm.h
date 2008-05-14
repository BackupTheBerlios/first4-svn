#ifndef ADDRIMPEXPFRM_H
#define ADDRIMPEXPFRM_H
//
#include <QDialog>
#include "ui_addrimpexpfrm.h"
//
class addrimpexpfrm : public QDialog, public Ui::addrimpexp
{
Q_OBJECT
public:
	addrimpexpfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
private slots:
	void next();
	void back();
	void loaddir_expcsv();
	void loaddir_expvcard();
	void expcsv();
	void expvcard();
	void impvcard();
	void loadfilevcard();
	void selectfilevcard();
	void selectfilecsv();
	void loadfilecsv();
	void impcsv();
private:
	void loadcolumns(QString table);
	void loaddirs();
};
#endif






#ifndef TEMPLATEEDITFRM_H
#define TEMPLATEEDITFRM_H
//
#include "ui_templateeditfrm.h"
//
class templateeditfrm : public QWidget, public Ui::templateeditfrm
{
Q_OBJECT
public:
	templateeditfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
	void opentemplate(int dbid);
private slots:
};
#endif






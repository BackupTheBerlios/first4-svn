#ifndef ADDRIMPEXP_H
#define ADDRIMPEXP_H
//
#include <QWidget>
#include "ui_addrimpexp.h"
//
class addrimpexp : public QWidget, public Ui::addrimpexp
{
Q_OBJECT
public:
	addrimpexp( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
};
#endif






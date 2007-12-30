#include <QtCore>

#include "aboutfrm.h"
//
aboutfrm::aboutfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
	QString info = QString( "" );

	info += "Copyright (C) 2007 LINUX-BOX.ch";
	info += "\n\n";
	info += "Application: Orlando Procopio\n";
	info += "Plugins: Alexander Saal\n";
	label_2->setText( info );


    QFile lic( QString::fromUtf8( ":/COPYING" ) );
    if ( !lic.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        return ;
    }

    QTextStream LicIn( &lic );
    QString lineLic = LicIn.readAll();
	lic.close();

	textEditLicense->setPlainText( lineLic );
}
//

#include <QFile>
#include <QTextStream>
//
#include "aboutfrm.h"
//
aboutfrm::aboutfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
	QString info = QString( "" );

    QFile lic( QString::fromUtf8( ":/license/COPYING" ) );
    if ( !lic.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        return ;
    }

    QTextStream LicIn( &lic );
    QString lineLic = LicIn.readAll();
	lic.close();

	textEditLicense->setPlainText( lineLic );
}
//

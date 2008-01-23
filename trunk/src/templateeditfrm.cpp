#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QCloseEvent>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
//
#include "templateeditfrm.h"
#include "vars.h"
#include "progfrm.h"
//
QString templateid;
extern QString username;
//
templateeditfrm::templateeditfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
void templateeditfrm::init() 
{
	vars v;
	QStringList sgeo = v.loadgeo ( this->objectName() );
	if ( sgeo.size() > 0	)
	{
		if ( sgeo[0] == "1" )
			this->setWindowState ( this->windowState() ^ Qt::WindowMaximized );
		this->setGeometry ( sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt() );
	}
	
	templateid = "";
	
	connect ( btnimport, SIGNAL ( released() ), this, SLOT ( importfile() ) );
	connect ( btncancel, SIGNAL ( released() ), this, SLOT ( close() ) );
	connect ( btnaccept, SIGNAL ( released() ), this, SLOT ( savetemplate() ) );
}
//
void templateeditfrm::closeEvent ( QCloseEvent* ce )
{
	vars v;
	v.savegeo ( this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height() );
	ce->accept();
}
//
void templateeditfrm::opentemplate(QString dbid) 
{
	QString qstr = QString("SELECT ID, name, description, data FROM templatestab WHERE `ID`='%1';").arg(dbid);
	QSqlQuery query(qstr);
	query.next();
	txtname->setText(query.value(1).toString());
	txtdescription->setText(query.value(2).toString());
	txtdata->setText(query.value(3).toString());
	templateid = dbid;
}
//
void templateeditfrm::importfile()
{
	QString filename = QFileDialog::getOpenFileName ( this, tr ( "Import Tex-Template" ),
	                   QDir::homePath(),
	                   tr ( "All files (*.*)" ) );
	QFile file ( filename );
	progfrm pfrm;
	pfrm.progbar->setMaximum(0);
	pfrm.txtcomments->setText(tr("Importing template..."));
	pfrm.show();
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		txtdata->setText("");
		QTextStream stream ( &file );
		while(!stream.atEnd())
			txtdata->setText(txtdata->toPlainText()+"\n"+stream.readLine());
		file.close();
	}
	pfrm.close();
}
//
void templateeditfrm::savetemplate()
{
	if(templateid != "")
		updatetemplate();
	else
		inserttemplate();
}
//
void templateeditfrm::inserttemplate()
{
	QString qstr = QString("INSERT INTO `templatestab` ( `ID` , `name` , `description` , `data` , `created_by` , `created` ) VALUES ('', '%1', '%2', '%3', '%4', '%5');").arg(txtname->text()).arg(txtdescription->toPlainText()).arg(txtdata->toPlainText().replace("\\", "\\\\")).arg(username).arg(QDate::currentDate().toString("yyyy-MM-dd"));
	QSqlQuery query(qstr);
	QSqlError qerror = query.lastError();
	if(qerror.isValid())
		QMessageBox::warning ( 0, tr ( "Template not saved..." ), qerror.text());
	QMessageBox::information( 0, tr ( "Template saved..." ), tr ( "Template successfully saved in the database." ) );
	this->close();
}
//
void templateeditfrm::updatetemplate()
{
	QString qstr = QString("UPDATE templatestab SET `name` = '%1', `description`='%2', `data`='%3' , `modificated_by`='%4', `modificated`='%5' WHERE `ID`='%6';").arg(txtname->text()).arg(txtdescription->toPlainText()).arg(txtdata->toPlainText().replace("\\", "\\\\")).arg(username).arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(templateid);
	QSqlQuery query(qstr);
	QSqlError qerror = query.lastError();
	if(qerror.isValid())
		QMessageBox::warning ( 0, tr ( "Template not saved..." ), qerror.text());
	QMessageBox::information( 0, tr ( "Template saved..." ), tr ( "Template successfully saved in the database." ) );
	templateid = "";
	this->close();
}

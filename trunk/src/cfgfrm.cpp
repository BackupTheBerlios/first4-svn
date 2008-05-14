#include <QByteArray>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QListView>
#include <QCloseEvent>
#include <QInputDialog>
#include <QTreeWidget>
#include <QHeaderView>
#include <QStringList>
#include <QTableWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAction>

#include "cfgfrm.h"
#include "vars.h"
#include "newdatatabfrm.h"
#include "dbwizzardfrm.h"
#include "templateeditfrm.h"

extern int uid;
extern QString username, fullname, firstver, docfolder, build;
extern QString dbhost, dbname, dbuid, dbpwd, dbport;

QString cfgdbver;
QStringList listallusers, templateids;

cfgfrm::cfgfrm ( QWidget * parent, Qt::WFlags f )
		: QWidget ( parent, f )
{
	setupUi ( this );
}
//
void cfgfrm::init()
{
	progbar->setValue ( 0 );
	this->setFixedSize ( this->width(), this->height() );
	vars v;
	QStringList sgeo = v.loadgeo ( this->objectName() );
	if ( sgeo.size() > 0	)
	{
		if ( sgeo[0] == "1" )
			this->setWindowState ( this->windowState() ^ Qt::WindowMaximized );
		this->setGeometry ( sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt() );
	}
	lbluser->setText ( username );
	txtuser->setText ( username );
	
	maintab->setCurrentIndex( 0 );
	cfgtab->setCurrentIndex( 0 );
	usertab->setCurrentIndex ( 0 );

	//init listresoureces
	listresources->header()-> setClickable ( FALSE );
	listresources->header()->setResizeMode ( QHeaderView::Fixed );
	listresources->headerItem()->setText ( 0, QApplication::translate ( "cfgfrm", "Resources", 0, QApplication::UnicodeUTF8 ) );
	listresources->headerItem()->setText ( 1, QApplication::translate ( "cfgfrm", "ID", 0, QApplication::UnicodeUTF8 ) );
	listresources->headerItem()->setText ( 2, QApplication::translate ( "cfgfrm", "name", 0, QApplication::UnicodeUTF8 ) );
	listresources->headerItem()->setText ( 3, QApplication::translate ( "cfgfrm", "users", 0, QApplication::UnicodeUTF8 ) );
	listresources->headerItem()->setText ( 4, QApplication::translate ( "cfgfrm", "details", 0, QApplication::UnicodeUTF8 ) );
	listresources->hideColumn ( 1 );
	listresources->hideColumn ( 2 );
	listresources->hideColumn ( 3 );
	listresources->hideColumn ( 4 );

	listpermissions->setColumnWidth ( 0, 300 );
	listpermissions->setColumnWidth ( 1, 40 );
	listpermissions->setColumnWidth ( 2, 40 );

	tem_tree->hideColumn(2);

	//init functions

	loadlangfile();
	progbar->setValue ( 10 );
	loaddbinfo();
	progbar->setValue ( 20 );
	loadservers();
	progbar->setValue ( 30 );
	loadsettings();
	progbar->setValue ( 40 );
	loadowndata();
	progbar->setValue ( 50 );
	load_local_tools();
	progbar->setValue ( 60 );
	if ( username != "Administrator" )
		cfgtab->setEnabled ( false );
	else
	{
		loadusers();
		progbar->setValue ( 70 );
		load_db_tools();
		progbar->setValue ( 75 );
		loadresources();
		progbar->setValue ( 80 );
		locks_loaduserlocks();
		progbar->setValue ( 85 );
		templates_load();
	}
	
	progbar->setValue ( 85 );
	resdefframe->setCurrentIndex ( 3 );

	txtdocpath->setText ( docfolder );

	//slot connections
	connect ( btnchangepwd, SIGNAL ( released() ), this, SLOT ( changepwd() ) );
	connect ( btnsellangfile, SIGNAL ( released() ), this, SLOT ( selectlangfile() ) );
	connect ( btnadddb, SIGNAL ( released() ), this, SLOT ( addservers() ) );
	connect ( btndeldb, SIGNAL ( released() ), this, SLOT ( delservers() ) );
	connect ( listusers, SIGNAL ( itemClicked ( QListWidgetItem* ) ), this, SLOT ( selectuser() ) );
	connect ( btn_users_new, SIGNAL ( released() ), this, SLOT ( newuser() ) );
	connect ( btn_users_save, SIGNAL ( released() ), this, SLOT ( saveuserchange() ) );
	connect ( btn_users_delete, SIGNAL ( released() ), this, SLOT ( deluser() ) );
	connect ( btn_users_cancel, SIGNAL ( released() ), this, SLOT ( canceluser() ) );
	connect ( listresources, SIGNAL ( itemClicked ( QTreeWidgetItem*,int ) ), this, SLOT ( loadresourcesdetails() ) );
	connect ( listpermissions, SIGNAL ( itemClicked ( QTreeWidgetItem*, int ) ), this, SLOT ( applyresourcesdetails() ) );
	connect ( btnsavepermissions, SIGNAL ( released() ), this, SLOT ( saveresourcesdetails() ) );
	connect ( txtstartid, SIGNAL ( textChanged ( QString ) ), this, SLOT ( applyresourcesdetails() ) );
	connect ( txtboxbank, SIGNAL ( textEdited ( QString ) ), this, SLOT ( applyresourcesdetails() ) );
	connect ( txtboxaccountnr, SIGNAL ( textEdited ( QString ) ), this, SLOT ( applyresourcesdetails() ) );
	connect ( txtboxclearing, SIGNAL ( textEdited ( QString ) ), this, SLOT ( applyresourcesdetails() ) );
	connect ( txtboxcurrency, SIGNAL ( textEdited ( QString ) ), this, SLOT ( applyresourcesdetails() ) );
	connect ( listresources, SIGNAL ( customContextMenuRequested ( QPoint ) ), this, SLOT ( contmenu() ) );
	connect ( btndocpath, SIGNAL ( released() ), this, SLOT ( selectdocpath() ) );
	connect ( btnsavepath, SIGNAL ( released() ), this, SLOT ( savedocsettings() ) );
	connect ( btnsavesettings, SIGNAL ( released() ), this, SLOT ( savesettings() ) );
	connect ( btnowndata, SIGNAL ( released() ), this, SLOT ( saveowndata() ) );
	connect ( cmbtemplatename, SIGNAL ( activated(int) ), this, SLOT ( applyresourcesdetails() ) );
	
	connect ( btn_tools_save_local, SIGNAL ( released() ), this, SLOT ( save_local_tools() ) );
	connect ( btn_tools_save_db, SIGNAL ( released() ), this, SLOT ( save_db_tools() ) );
	connect ( btn_tools_reload_local, SIGNAL ( released() ), this, SLOT ( load_local_tools() ) );
	connect ( btn_tools_reload_db, SIGNAL ( released() ), this, SLOT ( load_db_tools() ) );
	
	connect ( btn_tool_tex2dvi, SIGNAL ( released() ), this, SLOT ( tools_filedialog() ) );
	connect ( btn_tool_dviviewer, SIGNAL ( released() ), this, SLOT ( tools_filedialog() ) );
	connect ( btn_tool_dvi2ps, SIGNAL ( released() ), this, SLOT ( tools_filedialog() ) );
	connect ( btn_tool_print, SIGNAL ( released() ), this, SLOT ( tools_filedialog() ) );
	connect ( btn_tool_db_tex2dvi, SIGNAL ( released() ), this, SLOT ( tools_filedialog() ) );
	connect ( btn_tool_db_dviviewer, SIGNAL ( released() ), this, SLOT ( tools_filedialog() ) );
	connect ( btn_tool_db_dvi2ps, SIGNAL ( released() ), this, SLOT ( tools_filedialog() ) );
	connect ( btn_tool_db_print, SIGNAL ( released() ), this, SLOT ( tools_filedialog() ) );
	
	connect ( btnnewtemplate, SIGNAL ( released() ), this, SLOT ( templates_new() ) );
	connect ( btnedittemplate, SIGNAL ( released() ), this, SLOT ( templates_edit() ) );
	connect ( btndeletetemplate, SIGNAL ( released() ), this, SLOT ( templates_delete() ) );
	connect ( btnrefreshtempaltes, SIGNAL ( released() ), this, SLOT ( templates_load() ) );
	connect ( tem_tree, SIGNAL ( itemClicked ( QTreeWidgetItem*, int ) ), this, SLOT ( templates_loaddetails() ) );
	connect ( chksystemplates, SIGNAL ( stateChanged(int)), this, SLOT ( templates_load() ) );

	connect ( lock_btnunlock, SIGNAL ( released()), this, SLOT ( locks_unlockentry() ) );
	connect ( lock_btnrefresh, SIGNAL ( released()), this, SLOT ( locks_loaduserlocks() ) );

	progbar->setValue ( 100 );
}
//
void cfgfrm::closeEvent ( QCloseEvent* ce )
{
	vars v;
	v.savegeo ( this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height() );
	ce->accept();
}
//
QString cfgfrm::cryptpwd ( QString pwd )
{
	int i;;
	QString cpwd = "";
	QByteArray pass;
	pass.append ( pwd );
	for ( i=0;i<pass.size();i++ )
	{
		cpwd += tr ( "%1" ).arg ( pass[i] ^ pass[pass.size()-i], 0, 16 );
	}
	return cpwd;
}
//
void cfgfrm::changepwd()
{
	if ( txtnewpwd1->text() == txtnewpwd2->text() )
	{
		// lese aktuelles Passwort aus Datenbank
		QSqlQuery query;
		query.prepare ( "SELECT ID FROM userstab WHERE username=:username AND userpass=:userpass;" );
		query.bindValue ( ":username", txtuser->text() );
		query.bindValue ( ":userpass", cryptpwd ( txtoldpwd->text() ) );
		query.exec();
		if ( query.size() >0 )
		{
			query.next();
			QSqlQuery queryupdate;
			queryupdate.prepare ( "UPDATE `userstab` SET `userpass` = :userpass WHERE `ID` = :ID LIMIT 1;" );
			queryupdate.bindValue ( ":userpass", cryptpwd ( txtnewpwd1->text() ) );
			queryupdate.bindValue ( ":ID", query.value ( 0 ).toString() );
			queryupdate.exec();
			QMessageBox::information ( 0, tr ( "Change password..." ), tr ( "Password was changed!" ) );
			txtoldpwd->setText ( "" );
			txtnewpwd1->setText ( "" );
			txtnewpwd2->setText ( "" );
			txtuser->setFocus();
		}
		else
		{
			QMessageBox::warning ( 0, tr ( "Changing password..." ), tr ( "Actual password wrong." ) );
			txtoldpwd->setFocus();
		}
	}
	else
	{
		QMessageBox::warning ( 0, tr ( "Change password..." ), tr ( "New password does not agree with password confirmation!" ) );
		txtnewpwd1->setFocus();
	}
}
//
void cfgfrm::loadlangfile()
{
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QString line;
		QTextStream stream ( &file );
		while(!stream.atEnd())
		{
			line = stream.readLine();
			if(line.section("=",0,0) == "TRANSLATION")
				txtlang->setText(line.section("=", 1, 1));
		}
		file.close();
	}
}
//
void cfgfrm::selectlangfile()
{
	bool found = FALSE;
	QString filename = QFileDialog::getOpenFileName ( this, tr ( "Open Lang-File" ),
	                   QDir::homePath(),
	                   tr ( "Lang-File (*.qm)" ) );
	
	QStringList lines;
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QTextStream stream ( &file );
		while(!stream.atEnd())
			lines << stream.readLine();
		file.close();
	}
	
	if ( file.open ( QIODevice::WriteOnly ) )
	{
		int i;
		QTextStream stream ( &file );
		for(i=0;i<lines.count();i++)
		{
			if(lines[i].section("=",0,0) == "TRANSLATION")
			{
				stream << "TRANSLATION=" << filename << "\n";
				found = TRUE;
			}
			else
				stream << lines[i] << "\n";
		}
		if(!found)
			stream << "TRANSLATION=" << filename << "\n";
		txtlang->setText ( filename );
		QMessageBox::information ( 0,"Info...", tr ( "Please restart the application." ) );
		file.close();
	}
	else
		QMessageBox::critical ( 0,"Error...", tr ( "Language-File cannot be written!" ) );
}
//
void cfgfrm::loaddbinfo()
{
	lbldbname->setText ( dbname );
	lbldbname_2->setText ( dbname );
	lbldbhost->setText ( dbhost );
	lbldbhost_2->setText ( dbhost );
	lblfirstversion->setText ( firstver );
	lblfirstversion_2->setText ( firstver );
	lblbuild->setText( build );
	lblbuild_2->setText( build );

	QString connstr = "SELECT value FROM maincfgtab WHERE var = 'dbversion';";
	QSqlQuery query ( connstr );
	if ( query.isActive() )
	{
		query.next();
		cfgdbver = query.value ( 0 ).toString();
		lbldbversion->setText ( query.value ( 0 ).toString() );
		lbldbversion_2->setText ( query.value ( 0 ).toString() );
	}
}
//
void cfgfrm::addservers()
{
	dbwizzardfrm* wiz = new dbwizzardfrm;
	wiz->init();
	if ( wiz->exec() )
		loadservers();
}
//
void cfgfrm::delservers()
{
	if ( listservers->currentItem() )
		listservers->takeItem ( listservers->currentRow() );
		
	QStringList lines;
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QTextStream stream ( &file );
		while(!stream.atEnd())
			lines << stream.readLine();
	}
	file.close();
    
	if ( file.open ( QIODevice::WriteOnly ) )
	{
		int i, ii;
		QTextStream stream(&file);
		bool foundsec = FALSE;
		for(i=0;i<lines.count();i++)
		{
			if(lines[i] == "[SERVERS]")
			{
				foundsec = TRUE;
				stream << "[SERVERS]" << "\n";
				for (ii=0;ii<listservers->count();ii++ )
				{
					listservers->setCurrentRow ( ii );
					QListWidgetItem *item = listservers->currentItem();
					stream << item->text() << "\n";
				}
				while(lines[i].simplified() != "")
					i++;
				while(i<lines.count())
				{
					stream << lines[i] << "\n";	
					i++;
				}
			}
			else
			{
				stream << lines[i] << "\n";	
			}
		}
		if(!foundsec)
		{
			stream << "\n" << "[SERVERS]" << "\n";
			for (ii=0;ii<listservers->count();ii++ )
			{
				listservers->setCurrentRow ( ii );
				QListWidgetItem *item = listservers->currentItem();
				stream << item->text() << "\n";
			}
			stream << "\n";
		}
		file.close();
	}
	else
		QMessageBox::warning(0, "Window positions...", "Can't write to configuration file.");
	loadservers();
}
//
void cfgfrm::loadservers()
{
	listservers->clear();
    QStringList tmp;
	QFile file ( QDir::homePath() +"/.first4/local.first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QString line;
		QTextStream stream ( &file );
		while(stream.readLine() != "[SERVERS]" && !stream.atEnd());
		do {
			line = stream.readLine();
			if(line != "")
				listservers->insertItem ( -1, line.section(":", 1, 10) );
		} while (line != "" && !stream.atEnd());
		file.close();
	}
}
//
void cfgfrm::loadusers()
{
	if ( lbluser->text() == "Administrator" )
	{
		QSqlQuery querybenutzer ( "SELECT username, fullname FROM userstab;" ); //Lade Benutzer
		listallusers.clear();
		listusers->clear();
		while ( querybenutzer.next() )
		{
			listusers->insertItem ( -1, querybenutzer.value ( 1 ).toString() +" ("+querybenutzer.value ( 0 ).toString() +")" );
			listallusers << querybenutzer.value ( 0 ).toString() +":#:"+querybenutzer.value ( 1 ).toString();
		}
	}
}
//
void cfgfrm::selectuser()
{
	QListWidgetItem *item = listusers->currentItem();
	QString seluser = item->text().section ( " (", 1, 1 ).section ( ")", 0, 0 );
	txt_users_user->setText ( seluser.simplified() );
	QString qstr = QString ( "SELECT ID,  userpass,  fullname,  firstname,  lastname,  dob,  p_street,  p_zip,  p_location,  p_country,  b_street,  b_zip,  b_location,  b_country,  profession,  org_unit,  position,  emp_type, p_tel,  p_fax,  p_mobile,  p_pager,  p_ip,  email1,  email2,  email3,  p_web,  b_tel,  b_teldir,  b_fax,  b_mobile,  b_pager,  b_ip,  email4,  email5,  email6,  notes,  emp_grade FROM userstab WHERE username='%1'" ).arg ( seluser );
	QSqlQuery query ( qstr );
	if ( query.isActive() )
	{
		query.next();
		txt_users_fullname->setText ( query.value ( 2 ).toString().simplified() );
		txt_users_id->setText ( query.value ( 0 ).toString().simplified() );

		txt_users_pwd1->setText("");
		txt_users_pwd2->setText("");
		txt_users_firstname->setText ( query.value ( 3 ).toString().simplified() );
		txt_users_lastname->setText ( query.value ( 4 ).toString().simplified() );
		QString s = query.value ( 5 ).toString();
		txtdob->setDate ( QDate::QDate ( s.section ( "-", 0, 0 ).toInt(), s.section ( "-", 1, 1 ).toInt(), s.section ( "-", 2, 2 ).toInt() ) );
		if (s == "")
			txtdob->setDate ( QDate::QDate(1970, 01, 01 ));
			
		txt_users_privat_street->setText ( query.value ( 6 ).toString() );
		txt_users_privat_zip->setText ( query.value ( 7 ).toString() );
		txt_users_privat_location->setText ( query.value ( 8 ).toString() );
		txt_users_privat_country->setText ( query.value ( 9 ).toString() );
		txt_users_business_street->setText ( query.value ( 10 ).toString() );
		txt_users_business_zip->setText ( query.value ( 11 ).toString() );
		txt_users_business_location->setText ( query.value ( 12 ).toString() );
		txt_users_business_country->setText ( query.value ( 13 ).toString() );
		txt_users_business_prof->setText ( query.value ( 14 ).toString() );
		txt_users_business_unit->setText ( query.value ( 15 ).toString() );
		txt_users_business_position->setText ( query.value ( 16 ).toString() );
		txt_users_business_type->setEditText ( query.value ( 17 ).toString() );
		txt_users_business_grade->setText ( query.value ( 37 ).toString() );
		txt_users_private_tel->setText ( query.value ( 18 ).toString() );
		txt_users_private_fax->setText ( query.value ( 19 ).toString() );
		txt_users_private_mobile->setText ( query.value ( 20 ).toString() );
		txt_users_private_pager->setText ( query.value ( 21 ).toString() );
		txt_users_private_voip->setText ( query.value ( 22 ).toString() );
		txt_users_private_email1->setText ( query.value ( 23 ).toString() );
		txt_users_private_email2->setText ( query.value ( 24 ).toString() );
		txt_users_private_email3->setText ( query.value ( 25 ).toString() );
		txt_users_private_website->setText ( query.value ( 26 ).toString() );
		txt_users_business_tel->setText ( query.value ( 27 ).toString() );
		txt_users_business_teldir->setText ( query.value ( 28 ).toString() );
		txt_users_business_fax->setText ( query.value ( 29 ).toString() );
		txt_users_business_mobile->setText ( query.value ( 30 ).toString() );
		txt_users_business_pager->setText ( query.value ( 31 ).toString() );
		txt_users_business_voip->setText ( query.value ( 32 ).toString() );
		txt_users_business_email1->setText ( query.value ( 33 ).toString() );
		txt_users_business_email2->setText ( query.value ( 34 ).toString() );
		txt_users_business_email3->setText ( query.value ( 35 ).toString() );
		txtnotes->setText ( query.value ( 36 ).toString() );
	}
}
//
void cfgfrm::newuser()
{
	bool ok;
	QString text = QInputDialog::getText ( this, tr ( "QInputDialog::getText()" ),
	                                       tr ( "User name:" ), QLineEdit::Normal,
	                                       "", &ok );
	if ( ok && !text.isEmpty() )
	{
		txt_users_user->setText ( text );
		QString connstr = "SELECT * FROM userstab WHERE USERNAME='"+txt_users_user->text() +"';";
		QSqlQuery query ( connstr );
		if ( query.isActive() )
		{
			while ( query.next() )
			{
				QMessageBox::critical ( 0, tr ( "New User..." ), tr ( "User already exists!" ) );
				txt_users_user->setText ( "" );
			}
		}
	}
	if ( txt_users_user->text() != "" )
	{
		QString conn = "INSERT INTO `userstab` ( `ID` , `username` , `userpass` ) VALUES ('', '"+txt_users_user->text() +"', '');";
		QSqlQuery query ( conn );
		loadusers();
	}
}
//
void cfgfrm::saveuserchange()
{
	if ( txt_users_pwd1->text() == txt_users_pwd1->text() )
	{
		QString tmpstr = "";
		QSqlQuery queryupdate;
		if ( txt_users_pwd1->text() != "" )
			tmpstr = "`userpass` = '"+cryptpwd ( txt_users_pwd1->text() ) +"', ";
		queryupdate.prepare ( "UPDATE `userstab` SET `username`=:username ,  "+tmpstr+" `fullname`=:fullname ,  `firstname`=:firstname,  `lastname`=:lastname,  `dob`=:dob,  `p_street`=:p_street ,  `p_zip`=:p_zip ,  `p_location`=:p_location ,  `p_country`=:p_country,  `b_street`=:b_street ,  `b_zip`=:b_zip ,  `b_location`=:b_location ,  `b_country`=:b_country ,  `profession`=:profession,  `org_unit`=:org_unit ,  `position`=:position ,  `emp_type`=:emp_type ,  `emp_grade`=:emp_grade , `p_tel`=:p_tel ,  `p_fax`=:p_fax,  `p_mobile`=:p_mobile ,  `p_pager`=:p_pager ,  `p_ip`=:p_ip ,  `email1`=:email1 ,  `email2`=:email2 ,  `email3`=:email3 ,  `p_web`=:p_web , `b_tel`=:b_tel ,  `b_teldir`=:b_teldir ,  `b_fax`=:b_fax ,  `b_mobile`=:b_mobile ,  `b_pager`=:b_pager ,  `b_ip`=:b_ip ,  `email4`=:email4 ,  `email5`=:email5 ,  `email6`=:email6 ,  `notes`=:notes WHERE `ID` = :ID LIMIT 1;" );
		queryupdate.bindValue ( ":username" ,  txt_users_user->text() );
		queryupdate.bindValue ( ":fullname" ,  txt_users_fullname	->text() );
		queryupdate.bindValue ( ":firstname", txt_users_firstname->text() );
		queryupdate.bindValue ( ":lastname",  txt_users_lastname->text() );
		queryupdate.bindValue ( ":dob",  txtdob->date().toString ( "yyyy-MM-dd" ) );
		queryupdate.bindValue ( ":p_street" ,  txt_users_privat_street->text() );
		queryupdate.bindValue ( ":p_zip" ,  txt_users_privat_zip->text() );
		queryupdate.bindValue ( ":p_location" ,  txt_users_privat_location->text() );
		queryupdate.bindValue ( ":p_country",  txt_users_privat_country->text() );
		queryupdate.bindValue ( ":b_street" ,  txt_users_business_street->text() );
		queryupdate.bindValue ( ":b_zip" ,  txt_users_business_zip->text() );
		queryupdate.bindValue ( ":b_location" ,  txt_users_business_location->text() );
		queryupdate.bindValue ( ":b_country" ,  txt_users_business_country->text() );
		queryupdate.bindValue ( ":profession",  txt_users_business_prof->text() );
		queryupdate.bindValue ( ":org_unit" ,  txt_users_business_unit->text() );
		queryupdate.bindValue ( ":position" ,  txt_users_business_position->text() );
		queryupdate.bindValue ( ":emp_type" ,  txt_users_business_type->currentText() );
		queryupdate.bindValue ( ":emp_grade" ,  txt_users_business_grade->text() );
		queryupdate.bindValue ( ":p_tel" ,  txt_users_private_tel->text() );
		queryupdate.bindValue ( ":p_fax",  txt_users_private_fax->text() );
		queryupdate.bindValue ( ":p_mobile" , txt_users_private_mobile->text() );
		queryupdate.bindValue ( ":p_pager" ,  txt_users_private_pager->text() );
		queryupdate.bindValue ( ":p_ip" ,  txt_users_private_voip->text() );
		queryupdate.bindValue ( ":email1" ,  txt_users_private_email1->text() );
		queryupdate.bindValue ( ":email2" ,  txt_users_private_email2->text() );
		queryupdate.bindValue ( ":email3" ,  txt_users_private_email3->text() );
		queryupdate.bindValue ( ":p_web", txt_users_private_website->text() );
		queryupdate.bindValue ( ":b_tel" ,  txt_users_business_tel->text() );
		queryupdate.bindValue ( ":b_teldir" ,  txt_users_business_teldir->text() );
		queryupdate.bindValue ( ":b_fax" ,  txt_users_business_fax->text() );
		queryupdate.bindValue ( ":b_mobile" ,  txt_users_business_mobile->text() );
		queryupdate.bindValue ( ":b_pager" ,  txt_users_business_pager->text() );
		queryupdate.bindValue ( ":b_ip" ,  txt_users_business_voip->text() );
		queryupdate.bindValue ( ":email4" ,  txt_users_business_email1->text() );
		queryupdate.bindValue ( ":email5" ,  txt_users_business_email2->text() );
		queryupdate.bindValue ( ":email6" ,  txt_users_business_email3->text() );
		queryupdate.bindValue ( ":notes" , txtnotes->toPlainText() );
		queryupdate.bindValue ( ":ID", txt_users_id->text() );
		queryupdate.exec();
		QSqlQuery test ( "UPDATE `userstab` SET `p_street`=:p_street WHERE `ID` = 8 LIMIT 1;" );
		test.exec();
		QMessageBox::information ( 0, tr ( "Change personal data..." ), tr ( "Personal data successfully changed." ) );
		loadusers();
	}
	else
	{
		QMessageBox::warning ( 0, tr ( "Change password..." ), tr ( "New password does not agree with password confirmation!" ) );
		txt_users_pwd1->selectAll();
		txt_users_pwd1->setFocus();
	}
}
//
void cfgfrm::canceluser()
{
    selectuser();
}

void cfgfrm::deluser()
{
	QListWidgetItem *item = listusers->currentItem();
    if(item->text() != "Administrator")
    {
		int answ = QMessageBox::warning(this, tr("Delete User..."), tr("Delete User '%1' ?").arg(item->text()),QMessageBox::Yes, QMessageBox::No);
		if(answ == QMessageBox::Yes)
		{
	    	QString conn = "DELETE FROM `userstab` WHERE `ID` = '"+txt_users_id->text()+"';";
		    QSqlQuery query(conn);
		    loadusers();
		    listusers->setCurrentRow(0);
	    	selectuser();
		}
    }
    else
		QMessageBox::warning(0,"Fehler...", tr("Administrator cannot be deleted!"));
}
//
void cfgfrm::loadresources()
{
	listresources->clear();
	QTreeWidgetItem *item = new QTreeWidgetItem ( listresources );
	item->setText ( 0, tr ( "Directories" ) );
	item = new QTreeWidgetItem ( listresources, item );
	item->setText ( 0,  tr ( "Data & Stock" ) );
	item = new QTreeWidgetItem ( listresources, item );
	item->setText ( 0,  tr ( "Inventory" ) );
	item = new QTreeWidgetItem ( listresources, item );
	item->setText ( 0,  tr ( "Purchase orders" ) );
	item = new QTreeWidgetItem ( listresources, item );
	item->setText ( 0, tr ( "Orders" ) );
	item = new QTreeWidgetItem ( listresources, item );
	item->setText ( 0, tr ( "Documents" ) );
	item = new QTreeWidgetItem ( listresources, item );
	item->setText ( 0, tr ( "Accounts" ) );
	item = new QTreeWidgetItem ( listresources, item );
	item->setText ( 0, tr ( "Messages" ) );

	QTreeWidgetItemIterator it ( listresources );
	item = *it;
	QSqlQuery queryadr ( "SELECT ID, name, description, users, idcounter FROM directories ORDER BY ID ASC;" );
	if ( queryadr.isActive() )
	{
		while ( queryadr.next() )
		{
			QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
			childitem->setText ( 0, queryadr.value ( 2 ).toString() );
			childitem->setText ( 1, queryadr.value ( 0 ).toString() );
			childitem->setText ( 2, queryadr.value ( 1 ).toString() );
			childitem->setText ( 3, queryadr.value ( 3 ).toString() );
			childitem->setText ( 4, queryadr.value ( 4 ).toString() );
		}
	}
	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery querydata ( "SELECT ID, name, description, users FROM datatabs ORDER BY ID ASC;" );
	if ( querydata.isActive() )
	{
		while ( querydata.next() )
		{
			QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
			childitem->setText ( 0, querydata.value ( 2 ).toString() );
			childitem->setText ( 1, querydata.value ( 0 ).toString() );
			childitem->setText ( 2, querydata.value ( 1 ).toString() );
			childitem->setText ( 3, querydata.value ( 3 ).toString() );
		}
	}

	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery queryinv ( "SELECT ID, USERS FROM invcfgtab;" );
	if ( queryinv.isActive() )
	{
		while ( queryinv.next() )
		{
			QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
			childitem->setText ( 0, tr ( "General" ) );
			childitem->setText ( 1, queryinv.value ( 0 ).toString() );
			childitem->setText ( 2, "inv_general" );
			childitem->setText ( 3, queryinv.value ( 1 ).toString() );
		}
	}

	QSqlQuery queryinv2 ( "SELECT ID, NAME, DATATABLE, TABLENAME, DATE, USERS FROM invtab ORDER BY ID ASC;" );
	if ( queryinv2.isActive() )
	{
		while ( queryinv2.next() )
		{
			QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
			childitem->setText ( 0, queryinv2.value ( 3 ).toString() +" - "+queryinv2.value ( 4 ).toString() );
			childitem->setText ( 1, queryinv2.value ( 0 ).toString() );
			childitem->setText ( 2, queryinv2.value ( 1 ).toString() );
			childitem->setText ( 3, queryinv2.value ( 5 ).toString() );
		}
	}

	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery queryorders ( "SELECT ID, USERS, COUNTER FROM orderscfgtab;" );
	if ( queryorders.isActive() )
	{
		while ( queryorders.next() )
		{
			QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
			childitem->setText ( 0, tr ( "General" ) );
			childitem->setText ( 1, queryorders.value ( 0 ).toString() );
			childitem->setText ( 2, "p_orders" );
			childitem->setText ( 3, queryorders.value ( 1 ).toString() );
			childitem->setText ( 4, queryorders.value ( 2 ).toString() );
		}
	}

	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery queryabl ( "SELECT ID, users, auftrid FROM procedurecfgtab;" );
	if ( queryabl.isActive() )
	{
		queryabl.next();
		QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
		childitem->setText ( 0, tr ( "General" ) );
		childitem->setText ( 1, queryabl.value ( 0 ).toString() );
		childitem->setText ( 2, "orders" );
		childitem->setText ( 3, queryabl.value ( 1 ).toString() );
		childitem->setText ( 4, queryabl.value ( 2 ).toString() );
	}

	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery querydoc ( "SELECT ID, name, users, templateid FROM doctab ORDER BY ID ASC;" );
	if ( querydoc.isActive() )
	{
		int tmpid;
		QStringList cfgdocnames;
		cfgdocnames << tr ( "Offer" ) << tr ( "Order confirmation" ) << tr ( "Delivery note" ) << tr ( "Invoice" );
		while ( querydoc.next() )
		{
			QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
			tmpid = querydoc.value ( 1 ).toString().section ( " ", 0, 0 ).toInt()-1;
			childitem->setText ( 0, cfgdocnames[tmpid] );
			childitem->setText ( 1, querydoc.value ( 0 ).toString() );
			childitem->setText ( 2, "doc" );
			childitem->setText ( 3, querydoc.value ( 2 ).toString() );
			childitem->setText ( 4, querydoc.value ( 3 ).toString() );
		}
	}

	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery querykon2 ( "SELECT ID, name, description, users, bank, accountnr, blz, currency, type FROM accounttab WHERE `name` LIKE '%account%' ORDER BY ID ASC;" );
	if ( querykon2.isActive() )
	{
		while ( querykon2.next() )
		{
			QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
			childitem->setText ( 0, querykon2.value ( 2 ).toString() );
			childitem->setText ( 1, querykon2.value ( 0 ).toString() );
			childitem->setText ( 2, querykon2.value ( 1 ).toString() );
			childitem->setText ( 3, querykon2.value ( 3 ).toString() );
			childitem->setText ( 4, querykon2.value ( 4 ).toString() +";"+querykon2.value ( 5 ).toString() +";"+querykon2.value ( 6 ).toString() +";"+querykon2.value ( 7 ).toString()+";"+querykon2.value ( 8 ).toString() );
		}
	}

	QSqlQuery querykon1 ( "SELECT ID, name, description, users, bank, accountnr, blz, currency FROM accounttab WHERE `name` = 'ietab' ORDER BY ID ASC;" );
	if ( querykon1.isActive() )
	{
		while ( querykon1.next() )
		{
			QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
			childitem->setText ( 0, querykon1.value ( 2 ).toString() );
			childitem->setText ( 1, querykon1.value ( 0 ).toString() );
			childitem->setText ( 2, querykon1.value ( 1 ).toString() );
			childitem->setText ( 3, querykon1.value ( 3 ).toString() );
			childitem->setText ( 4, querykon1.value ( 4 ).toString() +";"+querykon1.value ( 5 ).toString() +";"+querykon1.value ( 6 ).toString() +";"+querykon1.value ( 7 ).toString() );
		}
	}

	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery querymsg ( "SELECT ID, name, description, users FROM msgcfgtab ORDER BY ID ASC;" );
	if ( querymsg.isActive() )
	{
		int tmpid;
		QStringList cfgmsgnames;
		cfgmsgnames << tr ( "General message" ) << tr ( "Stockmessage" ) << tr ( "Ordermessage" ) << tr ( "Inc/Exp-Message" );
		while ( querymsg.next() )
		{
			QTreeWidgetItem* childitem = new QTreeWidgetItem ( item );
			tmpid = querymsg.value ( 2 ).toString().section ( " ", 0, 0 ).toInt()-1;
			childitem->setText ( 0, cfgmsgnames[tmpid] );
			childitem->setText ( 1, querymsg.value ( 0 ).toString() );
			childitem->setText ( 2, "msg_"+querymsg.value ( 1 ).toString() );
			childitem->setText ( 3, querymsg.value ( 3 ).toString() );
		}
	}
}
//
void cfgfrm::loadresourcesdetails()
{
	QTreeWidgetItem* item = listresources->currentItem();
	if ( item->childCount() == 0 )
	{
		listpermissions->clear();
		QString tmpstr = item->text ( 3 );
		int i;
		for ( i=0;i<listallusers.count();i++ )
		{
			QTreeWidgetItem *tmpitem = new QTreeWidgetItem ( listpermissions );
			tmpitem->setText ( 0, listallusers[i].section ( ":#:", 1, 1 ) );
			if ( listallusers[i].section ( ":#:", 0, 0 ) != "Administrator" )
			{
				QString tmprights = tmpstr.section ( listallusers[i].section ( ":#:", 0, 0 ) +" [", 1, 1 );
				if ( tmprights.mid ( 0, 1 ) =="1" )
					tmpitem->setCheckState ( 1, Qt::Checked );
				else
					tmpitem->setCheckState ( 1, Qt::Unchecked );

				if ( tmprights.mid ( 1, 1 ) =="1" )
					tmpitem->setCheckState ( 2, Qt::Checked );
				else
					tmpitem->setCheckState ( 2, Qt::Unchecked );
			}
		}
		if ( item->text ( 2 ) =="doc" ) //Dokumentvorlage laden
		{
			if(templateids.indexOf(item->text(4)) != -1 )
				cmbtemplatename->setCurrentIndex(templateids.indexOf(item->text(4)));
			resdefframe->setCurrentIndex ( 0 );
		}
		else if ( item->text ( 2 ).left ( 7 ) =="account" )
		{
			txtboxbank->setText ( item->text ( 4 ).section ( ";", 0, 0 ) );
			txtboxaccountnr->setText ( item->text ( 4 ).section ( ";", 1, 1 ) );
			txtboxclearing->setText ( item->text ( 4 ).section ( ";", 2, 2 ) );
			txtboxcurrency->setText ( item->text ( 4 ).section ( ";", 3, 3 ) );
			if(item->text ( 4 ).section ( ";", 4, 4 ) == "local")
			{
				txtboxbank->setText ( "" );
				txtboxaccountnr->setText ( "" );
				txtboxclearing->setText ( "" );
				txtboxbank->setEnabled(FALSE);
				txtboxaccountnr->setEnabled (FALSE);
				txtboxclearing->setEnabled(FALSE);
			}
			else
			{
				txtboxbank->setEnabled(TRUE);
				txtboxaccountnr->setEnabled (TRUE);
				txtboxclearing->setEnabled(TRUE);
			}
			resdefframe->setCurrentIndex ( 1 );
		}
		else if ( item->text ( 2 ).left ( 3 ) == "dir" || item->text ( 2 ) == "p_orders" || item->text ( 2 ) == "orders" )
		{
			txtstartid->setText ( item->text ( 4 ) );
			resdefframe->setCurrentIndex ( 2 );
		}
		else
			resdefframe->setCurrentIndex ( 3 );
	}
	else
	{
		listpermissions->clear();
	}
}
//
void cfgfrm::applyresourcesdetails()
{
	int i;
	QString tmpstr = "";
	QTreeWidgetItem* item = listresources->currentItem();
	if ( item->childCount() ==0 )
	{
		QTreeWidgetItemIterator it ( listpermissions );
		QTreeWidgetItem *tmpitem;
		for ( i=0;i<listpermissions->topLevelItemCount();i++ )
		{
			tmpitem = *it;
			if ( tmpitem->text ( 0 ) != "Administrator" )
			{
				tmpstr += listallusers[i].section ( ":#:", 0, 0 ) + " [";
				if ( tmpitem->checkState ( 1 ) )
					tmpstr += "1";
				else
					tmpstr += "0";

				if ( tmpitem->checkState ( 2 ) )
					tmpstr += "1";
				else
					tmpstr += "0";
				tmpstr += "] , ";
			}
			else
			{
				tmpstr = "Administrator [11] , ";
			}
			++it;
		}
		item->setText ( 3, tmpstr );
		if ( item->text ( 2 ).left ( 3 ) =="dir" || item->text ( 2 ) =="p_orders" || item->text ( 2 ) =="orders" )
			item->setText ( 4, txtstartid->text() );
		if ( item->text ( 2 ) =="doc" )
		{
			templates_loaddescription();
			item->setText ( 4, templateids[cmbtemplatename->currentIndex()]);
		}
		if ( item->text ( 2 ).left ( 7 ) =="account" )
			item->setText ( 4, txtboxbank->text() +";"+txtboxaccountnr->text() +";"+txtboxclearing->text() +";"+txtboxcurrency->text() );
	}
}
//
void cfgfrm::saveresourcesdetails()
{
	//Adressbcher speichern
	QTreeWidgetItemIterator it ( listresources );
	QTreeWidgetItem *item;
	while ( *it )
	{
		item = *it;
		if ( item->text ( 2 ).mid ( 0,3 ) == "dir" )
		{
			QSqlQuery querysave;
			querysave.prepare ( "UPDATE `directories` SET `users` = :users, `idcounter` = :idcounter WHERE `ID` = :ID LIMIT 1;" );
			querysave.bindValue ( ":users", item->text ( 3 ) );
			querysave.bindValue ( ":idcounter", item->text ( 4 ) );
			querysave.bindValue ( ":ID", item->text ( 1 ) );
			querysave.exec();
		}
		else if ( item->text ( 2 ).mid ( 0,4 ) == "data" || item->text ( 2 ) == "vattab" )
		{
			QSqlQuery querysave;
			querysave.prepare ( "UPDATE `datatabs` SET `users` = :users WHERE `ID` = :ID LIMIT 1;" );
			querysave.bindValue ( ":users", item->text ( 3 ) );
			querysave.bindValue ( ":ID", item->text ( 1 ) );
			querysave.exec();
		}
		else if ( item->text ( 2 ).mid ( 0,3 ) == "inv" )
		{
			QSqlQuery querysave;
			if ( item->text ( 2 ) == "inv_general" )
			{
				querysave.prepare ( "UPDATE `invcfgtab` SET `users` = :users WHERE `ID` = :ID LIMIT 1;" );
				querysave.bindValue ( ":users", item->text ( 3 ) );
				querysave.bindValue ( ":ID", item->text ( 1 ) );
			}
			else
			{
				querysave.prepare ( "UPDATE `invtab` SET `users` = :users WHERE `ID` = :ID LIMIT 1;" );
				querysave.bindValue ( ":users", item->text ( 3 ) );
				querysave.bindValue ( ":ID", item->text ( 1 ) );
			}
			querysave.exec();
		}
		else if ( item->text ( 2 ) == "p_orders" )
		{
			QSqlQuery querysave;
			querysave.prepare ( "UPDATE `orderscfgtab` SET `users` = :users, `counter` = :counter WHERE `ID` = :ID LIMIT 1;" );
			querysave.bindValue ( ":users", item->text ( 3 ) );
			querysave.bindValue ( ":counter", item->text ( 4 ) );
			querysave.bindValue ( ":ID", item->text ( 1 ) );
			querysave.exec();
		}
		else if ( item->text ( 2 ) == "orders" )
		{
			QSqlQuery querysave;
			querysave.prepare ( "UPDATE `procedurecfgtab` SET `users` = :users, `auftrid` = :auftrid WHERE `ID` = :ID LIMIT 1;" );
			querysave.bindValue ( ":users", item->text ( 3 ) );
			querysave.bindValue ( ":auftrid", item->text ( 4 ) );
			querysave.bindValue ( ":ID", item->text ( 1 ) );
			querysave.exec();
		}
		else if ( item->text ( 2 ) == "doc" )
		{
			QSqlQuery querysave;
			querysave.prepare ( "UPDATE `doctab` SET `users` = :users, `templateid` = :templateid WHERE `ID` = :ID LIMIT 1;" );
			querysave.bindValue ( ":users", item->text ( 3 ) );
			querysave.bindValue ( ":templateid", item->text ( 4 ) );
			querysave.bindValue ( ":ID", item->text ( 1 ) );
			querysave.exec();
		}
		else if ( item->text ( 2 ) == "ietab" || item->text ( 2 ).left ( 7 ) == "account" )
		{
			QSqlQuery querysave;
			querysave.prepare ( "UPDATE `accounttab` SET `users`=:users, `bank`=:bank, `accountnr`=:accountnr, `blz`=:blz, `currency`=:currency WHERE `ID`=:ID LIMIT 1;" );
			querysave.bindValue ( ":users", item->text ( 3 ) );
			querysave.bindValue ( ":bank", item->text ( 4 ).section ( ";", 0, 0 ) );
			querysave.bindValue ( ":accountnr", item->text ( 4 ).section ( ";", 1, 1 ) );
			querysave.bindValue ( ":blz", item->text ( 4 ).section ( ";", 2, 2 ) );
			querysave.bindValue ( ":currency", item->text ( 4 ).section ( ";", 3, 3 ) );
			querysave.bindValue ( ":ID", item->text ( 1 ) );
			querysave.exec();
		}
		else if ( item->text ( 2 ).mid ( 0,3 ) == "msg" )
		{
			QSqlQuery querysave;
			querysave.prepare ( "UPDATE `msgcfgtab` SET `users`= :users WHERE `ID` = :ID LIMIT 1;" );
			querysave.bindValue ( ":users", item->text ( 3 ) );
			querysave.bindValue ( ":ID", item->text ( 1 ) );
			querysave.exec();
		}
		++it;
	}
	QMessageBox::information ( 0, tr ( "Permissions..." ), tr ( "New settings are saved and now active." ) );
}
//
void cfgfrm::contmenu()
{
	QTreeWidgetItem* item = listresources->currentItem();
	QMenu* contextMenu = new QMenu ( this );
	Q_CHECK_PTR ( contextMenu );
	if ( item->text(1) == "" )
	{
		QAction* cnt_newaddr = new QAction ( tr ( "New directory" ), this );
		connect ( cnt_newaddr , SIGNAL ( triggered() ), this, SLOT ( newaddr() ) );
		QAction* cnt_newdata = new QAction ( tr ( "New datatable" ), this );
		connect ( cnt_newdata , SIGNAL ( triggered() ), this, SLOT ( newdata() ) );
		QAction* cnt_newaccount = new QAction ( tr ( "New banc account" ), this );
		connect ( cnt_newaccount , SIGNAL ( triggered() ), this, SLOT ( newaccount() ) );
		QAction* cnt_newlocalaccount = new QAction ( tr ( "New local account" ), this );
		connect ( cnt_newlocalaccount , SIGNAL ( triggered() ), this, SLOT ( newlocalaccount() ) );
		contextMenu->addAction ( cnt_newaddr );
		contextMenu->addAction ( cnt_newdata );
		contextMenu->addAction ( cnt_newaccount );
		contextMenu->addAction ( cnt_newlocalaccount );
		contextMenu->exec ( QCursor::pos() );
	}
	else
	{
		if ( item->text(0)!= tr("General") && item->text(2)!="ietab" && item->text(2)!="taxtab" && item->text(2)!="doc" && item->text(2).mid(0, 4)!="msg_")
		{
			QAction* cnt_rename = new QAction ( tr ( "Rename \'%1\'" ).arg ( item->text ( 0 ) ), this );
			connect ( cnt_rename , SIGNAL ( triggered() ), this, SLOT ( rentab() ) );
			QAction* cnt_delete = new QAction ( tr ( "Delete \'%1\'" ).arg ( item->text ( 0 ) ), this );
			connect ( cnt_delete , SIGNAL ( triggered() ), this, SLOT ( deltab() ) );
			contextMenu->addAction ( cnt_rename );
			contextMenu->addAction ( cnt_delete );
			contextMenu->exec ( QCursor::pos() );
		}
	}
	delete contextMenu;
}
//
void cfgfrm::newaddr()
{
	bool ok;
	QString adrdesc = QInputDialog::getText ( this, tr ( "QInputDialog::getText()" ),
	                  tr ( "Directory:" ), QLineEdit::Normal,"", &ok );

	if ( ok && !adrdesc.isEmpty() )
	{
		int adrcount = 1;
		QString adrname = "";
		QString qstr1 = "SELECT * FROM directories ORDER BY name ASC;";
		QSqlQuery queryadrnew1 ( qstr1 );
		if ( queryadrnew1.isActive() )
		{
			while ( queryadrnew1.next() )
			{
				if ( QString ( "dir%1" ).arg ( adrcount,0,10 ) == queryadrnew1.value ( 1 ).toString() )
					adrcount++;
				else
				{
					if ( adrname == "" )
						adrname = QString ( "dir%1" ).arg ( adrcount,0,10 );
				}
			}
			if ( adrname == "" )
				adrname = QString ( "dir%1" ).arg ( adrcount++,0,10 );
		}

		QString qstr2 = "INSERT INTO `directories` ( `ID` , `name` , `description` , `users` ) VALUES ('', '";
		qstr2 += adrname;
		qstr2 += "', '";
		qstr2 += adrdesc;
		qstr2 +=  "', '');";
		QSqlQuery queryadrnew2 ( qstr2 );
		QString qstr3 = "CREATE TABLE `" + QString( adrname ) + "` (  `ID` int(11) NOT NULL auto_increment, `clientid` text NOT NULL, `company` text NOT NULL, `lastname` text NOT NULL, `firstname` text NOT NULL, `nameadd` text NOT NULL, `pobox` text NOT NULL, `street_nr` text NOT NULL, `location` text NOT NULL, `zip` text NOT NULL, `country` text NOT NULL, `tel_b` text NOT NULL, `tel_direct` text NOT NULL, `fax_b` text NOT NULL, `tel_p` text NOT NULL, `fax_p` text NOT NULL, `mobile` text NOT NULL, `email1` text NOT NULL, `email2` text NOT NULL, `email3` text NOT NULL, `homepage` text NOT NULL, `revenueaj` text NOT NULL, `revenuelj` text NOT NULL, `discount` text NOT NULL, `clienttyp` text NOT NULL, `comments` text NOT NULL, `custom1` text NOT NULL, `custom2` text NOT NULL, `custom3` text NOT NULL, `custom4` text NOT NULL, `custom5` text NOT NULL, `created` text NOT NULL, `modified` text NOT NULL, KEY `ID` (`ID`)) ENGINE=InnoDB CHARSET=latin1;";
		QSqlQuery queryadrnew3 ( qstr3 );
		loadresources();
	}
}
//
void cfgfrm::newdata()
{
	newdatatabfrm newtab;
	newtab.init();
	if ( newtab.exec() )
		loadresources();
}
//
void cfgfrm::newaccount()
{
	bool ok;
	QString accountdesc = QInputDialog::getText ( this, tr ( "QInputDialog::getText()" ),
	                      tr ( "Accountname:" ), QLineEdit::Normal,"", &ok );
	if ( ok && !accountdesc.isEmpty() )
	{
		int accountcount = 1;
		QString accountname = "";
		QString qstr1 = "SELECT name FROM accounttab ORDER BY name ASC;";
		QSqlQuery querykontonew1 ( qstr1 );
		if ( querykontonew1.isActive() )
		{
			while ( querykontonew1.next() )
			{
				if ( QString ( "account%1" ).arg ( accountcount,0,10 ) == querykontonew1.value ( 0 ).toString() )
					accountcount++;
				else
				{
					if ( accountname == "" )
						accountname = QString ( "account%1" ).arg ( accountcount,0,10 );
				}
			}
			if ( accountname == "" )
				accountname = QString ( "account%1" ).arg ( accountcount++,0,10 );
		}
		QString qstr2 = QString ( "INSERT INTO `accounttab` (`ID`, `name`, `description`, `accountnr`, `bank`, `currency`, `users`, `type`) VALUES (NULL, '%1', '%2', '', '', '', '', 'banc')" ).arg ( accountname ).arg ( accountdesc );
		QSqlQuery querykontonew2 ( qstr2 );

		QString qstr3 = tr ( "CREATE TABLE `%1` (`ID` int NOT NULL AUTO_INCREMENT , `refnr` text NOT NULL, `date` date NOT NULL default '0000-00-00' , `address` text NOT NULL, `description` text NOT NULL , `code` text NOT NULL , `amount` text NOT NULL , PRIMARY KEY (`ID`))" ).arg ( accountname );
		QSqlQuery querykontonew5 ( qstr3 );
		loadresources();
	}
}
//
void cfgfrm::newlocalaccount()
{
	bool ok;
	QString accountdesc = QInputDialog::getText ( this, tr ( "QInputDialog::getText()" ),
	                      tr ( "Local accountname:" ), QLineEdit::Normal,"", &ok );
	if ( ok && !accountdesc.isEmpty() )
	{
		int accountcount = 1;
		QString accountname = "";
		QString qstr1 = "SELECT name FROM accounttab ORDER BY name ASC;";
		QSqlQuery querykontonew1 ( qstr1 );
		if ( querykontonew1.isActive() )
		{
			while ( querykontonew1.next() )
			{
				if ( QString ( "account%1" ).arg ( accountcount,0,10 ) == querykontonew1.value ( 0 ).toString() )
					accountcount++;
				else
				{
					if ( accountname == "" )
						accountname = QString ( "account%1" ).arg ( accountcount,0,10 );
				}
			}
			if ( accountname == "" )
				accountname = QString ( "account%1" ).arg ( accountcount++,0,10 );
		}
		QString qstr2 = QString ( "INSERT INTO `accounttab` (`ID`, `name`, `description`, `accountnr`, `bank`, `currency`, `users`, `type`) VALUES (NULL, '%1', '%2', '-', '-', '', '', 'local')" ).arg ( accountname ).arg ( accountdesc );
		QSqlQuery querykontonew2 ( qstr2 );

		QString qstr3 = tr ( "CREATE TABLE `%1` (`ID` int NOT NULL AUTO_INCREMENT , `refnr` text NOT NULL, `date` date NOT NULL default '0000-00-00' , `address` text NOT NULL, `description` text NOT NULL , `code` text NOT NULL , `amount` text NOT NULL , PRIMARY KEY (`ID`))" ).arg ( accountname );
		QSqlQuery querykontonew5 ( qstr3 );
		loadresources();
	}
}
//
void cfgfrm::rentab()
{
	QTreeWidgetItem* item = listresources->currentItem();
	if ( item->text ( 2 ) !="" )
	{
		bool ok;
		QString newdesc = QInputDialog::getText ( this, tr ( "QInputDialog::getText()" ),
		                  tr ( "Rename '%1' to:" ).arg ( item->text ( 0 ) ), QLineEdit::Normal,"", &ok );
		if ( ok && !newdesc.isEmpty() )
		{
			if ( item->text ( 2 ).mid ( 0, 3 ) == "dir" )
			{
				QString qstr = tr ( "UPDATE `directories` SET `description` = '%1' WHERE ID='%2' LIMIT 1;" ).arg ( newdesc ).arg ( item->text ( 1 ) );
				QSqlQuery queryadrren ( qstr );
				item->setText ( 0, newdesc );
			}
			else if ( item->text ( 2 ).mid ( 0, 4 ) == "data" )
			{
				QString qstr = tr ( "UPDATE `datatabs` SET `description` = '%1' WHERE ID='%2' LIMIT 1;" ).arg ( newdesc ).arg ( item->text ( 1 ) );
				QSqlQuery querydataren ( qstr );
				item->setText ( 0, newdesc );
			}
			else if ( item->text ( 2 ).left ( 7 ) =="account" )
			{
				QString qstr = tr ( "UPDATE `accounttab` SET `description` = '%1' WHERE ID='%2' LIMIT 1;" ).arg ( newdesc ).arg ( item->text ( 1 ) );
				QSqlQuery querykontoren ( qstr );
				item->setText ( 0, newdesc );
			}
		}
	}
}
//
void cfgfrm::deltab()
{
	QTreeWidgetItem* item = listresources->currentItem();
	if ( item->text ( 2 ) !="" )
	{
		int r = QMessageBox::warning ( this, tr ( "Deleting..." ),tr ( "Delete '%1'?" ).arg ( item->text ( 0 ) ), QMessageBox::Yes, QMessageBox::No );
		if ( r == QMessageBox::Yes )
		{
			if ( item->text ( 2 ).mid ( 0, 3 ) == "dir" )
			{
				QString conn2 = QString ( "DELETE FROM `directories` WHERE `ID` = '%1';" ).arg ( item->text ( 1 ) );
				QSqlQuery queryadrdel2 ( conn2 );

				QString conn3 = QString ( "DROP TABLE `%1`;" ).arg ( item->text ( 2 ) );
				QSqlQuery queryadrdel3 ( conn3 );
				loadresources();
			}
			else if ( item->text ( 2 ).mid ( 0, 4 ) == "data" )
			{
				QString conn2 = QString ( "DELETE FROM `datatabs` WHERE `ID` = '%1';" ).arg ( item->text ( 1 ) );
				QSqlQuery querydatadel2 ( conn2 );

				QString conn3 = QString ( "DROP TABLE `%1`;" ).arg ( item->text ( 2 ) );
				QSqlQuery querydatadel3 ( conn3 );
				loadresources();
			}
			else if ( item->text ( 2 ).left ( 7 ) =="account" )
			{
				QString conn2 = QString ( "DELETE FROM `accounttab` WHERE `ID` = '%1';" ).arg ( item->text ( 1 ) );
				QSqlQuery querykontodel2 ( conn2 );

				QString conn3 = QString ( "DROP TABLE `%1`;" ).arg ( item->text ( 2 ) );
				QSqlQuery querykontodel3 ( conn3 );
				loadresources();
			}
			else if ( item->text ( 2 ).mid ( 0, 3 ) == "inv" )
			{
				QString conn2 = QString ( "DELETE FROM `invtab` WHERE `ID` = '%1';" ).arg ( item->text ( 1 ) );
				QSqlQuery querykontodel2 ( conn2 );

				QString conn3 = QString ( "DROP TABLE `%1`;" ).arg ( item->text ( 2 ) );
				QSqlQuery querykontodel3 ( conn3 );
				loadresources();
			}
		}
	}
}
//
void cfgfrm::selectdocpath()
{
	QString dir = QFileDialog::getExistingDirectory ( this, tr ( "Docfolder..." ),
	              QDir::homePath(),
	              QFileDialog::ShowDirsOnly
	              | QFileDialog::DontResolveSymlinks );
	txtdocpath->setText ( dir );
}
//
void cfgfrm::savedocsettings()
{
	QSqlQuery savesettings_1;
	savesettings_1.prepare ( "UPDATE maincfgtab SET `value` = :value WHERE var = 'docfolder';" );
	savesettings_1.bindValue ( ":value", txtdocpath->text() );
	savesettings_1.exec();
	docfolder=txtdocpath->text();
	
	QSqlQuery savesettings_2;
	savesettings_2.prepare ( "UPDATE maincfgtab SET `value`=:prefix WHERE `var`='docpref';" );
	savesettings_2.bindValue ( ":prefix", txtdocprefix->text() );
	savesettings_2.exec();

	QSqlQuery savesettings_3;
	savesettings_3.prepare ( "UPDATE maincfgtab SET `value`=:prefix WHERE `var`='doc_generalinfo';" );
	savesettings_3.bindValue ( ":prefix", txtgeneralinfo->toPlainText().replace("\\", "\\\\" ) );
	savesettings_3.exec();

	QMessageBox::information ( 0, tr ( "Documents settings..." ), tr ( "New settings are saved and now active." ) );
}
//
void cfgfrm::loadsettings()
{
	QSqlQuery loadsettings_1 ( "SELECT value FROM maincfgtab WHERE `var`='DoG';" );
	loadsettings_1.next();
	if(loadsettings_1.size()>0)
		daysofgrace->setValue ( loadsettings_1.value ( 0 ).toInt() );
	else
		QSqlQuery insertsetting("INSERT INTO maincfgtab (`var`, `value`)VALUES('DoG', '');");

	QSqlQuery loadsettings_2 ( "SELECT value FROM maincfgtab WHERE `var`='docpref';" );
	loadsettings_2.next();
	if(loadsettings_2.size()>0)
		txtdocprefix->setText ( loadsettings_2.value ( 0 ).toString() );
	else
		QSqlQuery insertsetting("INSERT INTO maincfgtab (`var`, `value`)VALUES('docpref', '');");
		
	QSqlQuery loadsettings_3 ( "SELECT value FROM maincfgtab WHERE `var`='def_currency';" );
	loadsettings_3.next();
	if(loadsettings_3.size()>0)
		txtdefcurrency->setText ( loadsettings_3.value ( 0 ).toString() );
	else
		QSqlQuery insertsetting("INSERT INTO maincfgtab (`var`, `value`)VALUES('def_currency', '');");
		
	QSqlQuery loadsettings_4 ( "SELECT value FROM maincfgtab WHERE `var`='doc_generalinfo';" );
	loadsettings_4.next();
	if(loadsettings_4.size()>0)
		txtgeneralinfo->setText ( loadsettings_4.value ( 0 ).toString() );
	else
		QSqlQuery insertsetting("INSERT INTO maincfgtab (`var`, `value`)VALUES('doc_generalinfo', '');");
}
//
void cfgfrm::savesettings()
{
	QSqlQuery savesettings_1;
	savesettings_1.prepare ( "UPDATE maincfgtab SET `value`=:dog WHERE `var`='DoG';" );
	savesettings_1.bindValue ( ":dog", daysofgrace->cleanText() );
	savesettings_1.exec();
	QSqlQuery savesettings_2;
	savesettings_2.prepare ( "UPDATE maincfgtab SET `value`=:def_currency WHERE `var`='def_currency';" );
	savesettings_2.bindValue ( ":prefix", txtdefcurrency->text() );
	savesettings_2.exec();
	QMessageBox::information ( 0, tr ( "Settings..." ), tr ( "New settings are saved and now active." ) );
}
//
void cfgfrm::saveowndata()
{
	QStringList fields;
	fields << txtcompany->text() << txtaddress->toPlainText() << txtlocation->text() << txtzip->text() << txtcountry->text() << txt_bank_name->text() << txt_bank_addr->text() << txt_bank_clearing->text() << txt_bank_accountnr->text() << txt_bank_usrnr->text();
	QStringList rowname;
	rowname << "company" << "companyaddress" << "companylocation" << "companyzip" << "companycountry" << "bankname" << "bankaddress" << "bankblz" << "bankaccountnr" << "banktnr";
	int i;
	QString qstr;
	for ( i=0; i<rowname.count(); i++ )
	{
		qstr = QString ( "SELECT ID FROM `maincfgtab` WHERE `var` = '%1';" ).arg ( rowname[i] );
		QSqlQuery querycheck ( qstr );
		if ( querycheck.size() >0 )
		{
			querycheck.next();
			qstr = QString ( "UPDATE `maincfgtab` SET `value`='%1' WHERE `ID`=%2;" ).arg ( fields[i] ).arg ( querycheck.value ( 0 ).toString() );
		}
		else
			qstr = QString ( "INSERT INTO `maincfgtab` (`ID`, `var`, `value`) VALUES ('', '%1', '%2');" ).arg ( rowname[i] ).arg ( fields[i] );
		QSqlQuery querysetvar ( qstr );
	}
	QMessageBox::information ( 0, tr ( "Own data..." ), tr ( "New settings are saved and now active." ) );
}
//
void cfgfrm::loadowndata()
{
	QStringList fields;
	QStringList rowname;
	rowname << "company" << "companyaddress" << "companylocation" << "companyzip" << "companycountry" << "bankname" << "bankaddress" << "bankblz" << "bankaccountnr" << "banktnr";
	int i;
	QString qstr;
	for ( i=0;i<rowname.count(); i++ )
	{
		qstr = QString ( "SELECT value FROM `maincfgtab` WHERE `var` = '%1';" ).arg ( rowname[i] );
		QSqlQuery query ( qstr );
		query.next();
		fields.append ( query.value ( 0 ).toString() );
	}
	txtcompany->setText ( fields[0] );
	txtaddress->setText ( fields[1] );
	txtlocation->setText ( fields[2] );
	txtzip->setText ( fields[3] );
	txtcountry->setText ( fields[4] );
	txt_bank_name->setText ( fields[5] );
	txt_bank_addr->setText ( fields[6] );
	txt_bank_clearing->setText ( fields[7] );
	txt_bank_accountnr->setText ( fields[8] );
	txt_bank_usrnr->setText ( fields[9] );
}
//
void cfgfrm::load_local_tools()
{
	QFile file ( QDir::homePath() +"/.first4/"+username+".first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QTextStream stream ( &file );
		QString line;
		while(stream.readLine() != "[EXT_TOOLS]" && !stream.atEnd());
		do {
			line = stream.readLine();
			if(line.section("=", 0, 0) == "DVI2PS")
				txt_tool_dvi2ps->setText(line.section("=", 1, 1));
			if(line.section("=", 0, 0) == "DVIVIEWER")
				txt_tool_dviviewer->setText(line.section("=", 1, 1));
			if(line.section("=", 0, 0) == "PRINT")
				txt_tool_print->setText(line.section("=", 1, 1));
			if(line.section("=", 0, 0) == "TEX2DVI")
				txt_tool_tex2dvi->setText(line.section("=", 1, 1));
		} while (line != "");
		file.close();
	}
}
//
void cfgfrm::load_db_tools()
{
	QString os = "";
	#ifdef Q_OS_LINUX
		os="lnx";
	#endif
	#ifdef Q_OS_WIN32
		os="win";
	#endif
	#ifdef Q_OS_MAC
		os="mac";
	#endif
	QString qstr1 = QString("SELECT var, value FROM maincfgtab WHERE `var`='tool_%1_tex2dvi' OR `var`='tool_%1_dviviewer' OR `var`='tool_%1_dvi2ps' OR `var`='tool_%1_print' ORDER BY var;").arg(os);
	QSqlQuery querytools(qstr1);
	if ( querytools.isActive())
	{
		querytools.next();
		txt_tool_db_dvi2ps->setText(querytools.value(1).toString());
		querytools.next();
		txt_tool_db_dviviewer->setText(querytools.value(1).toString());
		querytools.next();
		txt_tool_db_print->setText(querytools.value(1).toString());
		querytools.next();
		txt_tool_db_tex2dvi->setText(querytools.value(1).toString());
	}
	else
	{
		QSqlError sqlerror = querytools.lastError();
		QMessageBox::critical(0,"Error...",tr("Unable to read settings from database!")+"\n\n"+sqlerror.text());
	}
}
//
void cfgfrm::save_local_tools()
{
	QStringList lines;
	QFile file ( QDir::homePath() +"/.first4/"+username+".first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QTextStream stream ( &file );
		while(!stream.atEnd())
			lines << stream.readLine();
	}
	file.close();
	
	if ( file.open ( QIODevice::WriteOnly ) )
	{
		int i;
		bool found = FALSE;
		QTextStream stream ( &file );
		for(i=0;i<lines.count();i++)
		{
			if(lines[i] != "[EXT_TOOLS]")
				stream << lines[i] << "\n";
			else
			{
				stream << lines[i] << "\n"; // write [EXT_TOOLS]
				stream << "DVI2PS=" << txt_tool_dvi2ps->text() << "\n";
				stream << "DVIVIEWER=" << txt_tool_dviviewer->text() << "\n";
				stream << "PRINT=" << txt_tool_print->text() << "\n";
				stream << "TEX2DVI=" << txt_tool_tex2dvi->text() << "\n";
				while(lines[i] != "")
					i++;
				stream << "\n";
				found = TRUE;
			}
		}
		if(!found)
		{
			stream << "[EXT_TOOLS]" << "\n";
			stream << "DVI2PS=" << txt_tool_dvi2ps->text() << "\n";
			stream << "DVIVIEWER=" << txt_tool_dviviewer->text() << "\n";
			stream << "PRINT=" << txt_tool_print->text() << "\n";
			stream << "TEX2DVI=" << txt_tool_tex2dvi->text() << "\n";
			stream << "\n";
		}
		file.close();
	}
	else
		QMessageBox::warning(0,"External tools...", tr("Can't write to configuration file."));
}
//
void cfgfrm::save_db_tools()
{
	QString os = "";
	#ifdef Q_OS_LINUX
		os="lnx";
	#endif
	#ifdef Q_OS_WIN32
		os="win";
	#endif
	#ifdef Q_OS_MAC
		os="mac";
	#endif
	
	//First cleanup
	QString qstr = QString("DELETE FROM maincfgtab WHERE `var` LIKE '%tool_%1_%';").arg(os);
	QSqlQuery querycleanup(qstr);
	
	// SAVE DVI2PS
	QString qstr1 = QString("INSERT INTO maincfgtab (`var`, `value`) VALUES ('%1', '%2');").arg("tool_"+os+"_dvi2ps").arg(txt_tool_db_dvi2ps->text());
	QSqlQuery querytools1(qstr1);
	
	// SAVE DVIVIEWER
	QString qstr2 = QString("INSERT INTO maincfgtab (`var`, `value`) VALUES ('%1', '%2');").arg("tool_"+os+"_dviviewer").arg(txt_tool_db_dviviewer->text());
	QSqlQuery querytools2(qstr2);
	
	// SAVE PRINTCMD
	QString qstr3 = QString("INSERT INTO maincfgtab (`var`, `value`) VALUES ('%1', '%2');").arg("tool_"+os+"_print").arg(txt_tool_db_print->text());
	QSqlQuery querytools3(qstr3);
	
	// SAVE TEX2DVI
	QString qstr4 = QString("INSERT INTO maincfgtab (`var`, `value`) VALUES ('%1', '%2');").arg("tool_"+os+"_tex2dvi").arg(txt_tool_db_tex2dvi->text());
	QSqlQuery querytools4(qstr4);
}
//
void cfgfrm::tools_filedialog()
{
	QObject *toolobj = QObject::sender();

	QString toolname = QFileDialog::getOpenFileName ( this, tr ( "Application..." ),
	                   QDir::rootPath(),
	                   tr ( "All files (*.*)" ) );
	
	if(toolobj->objectName() == "btn_tool_tex2dvi")
		txt_tool_tex2dvi->setText(toolname);
	else if(toolobj->objectName() == "btn_tool_dviviewer")
		txt_tool_dviviewer->setText(toolname);
	else if(toolobj->objectName() == "btn_tool_dvi2ps")
		txt_tool_dvi2ps->setText(toolname);
	else if(toolobj->objectName() == "btn_tool_print")
		txt_tool_print->setText(toolname);
	else if(toolobj->objectName() == "btn_tool_db_tex2dvi")
		txt_tool_db_tex2dvi->setText(toolname);
	else if(toolobj->objectName() == "btn_tool_db_dviviewer")
		txt_tool_db_dviviewer->setText(toolname);
	else if(toolobj->objectName() == "btn_tool_db_dvi2ps")
		txt_tool_db_dvi2ps->setText(toolname);
	else if(toolobj->objectName() == "btn_tool_db_print")
		txt_tool_db_print->setText(toolname);
}
//
void cfgfrm::templates_load()
{
	cmbtemplatename->clear();
	templateids.clear();
	tem_tree->clear();
	QString qstr;
	if(chksystemplates->checkState() == Qt::Unchecked)
		qstr = "SELECT name, description, ID FROM templatestab WHERE name NOT LIKE 'sys_%' ORDER BY name";
	else			
		qstr = "SELECT name, description, ID FROM templatestab ORDER BY name";
	QSqlQuery query(qstr);
	if ( query.isActive())
	{
		while(query.next())
		{
			QTreeWidgetItem *item = new QTreeWidgetItem(tem_tree);
			item->setText(0, query.value(0).toString());
			item->setText(1, query.value(1).toString());
			item->setText(2, query.value(2).toString());
						
			cmbtemplatename->addItem(query.value(0).toString());
			templateids << query.value(2).toString();
		}
	}
	else
	{
		QSqlError qerror = query.lastError();
		QMessageBox::warning ( 0, tr ( "Can't load templates..." ), qerror.text() );
	}
}
//
void cfgfrm::templates_new()
{
	templateeditfrm* tfrm = new templateeditfrm;
	tfrm->init();
	tfrm->show();
}
//
void cfgfrm::templates_edit()
{
	QTreeWidgetItem *item = tem_tree->currentItem();
	if(item != 0)
	{
		templateeditfrm* tfrm = new templateeditfrm;
		tfrm->init();
		tfrm->opentemplate(item->text(2));
		tfrm->show();
	}
}
//
void cfgfrm::templates_delete()
{
	QTreeWidgetItem *item = tem_tree->currentItem();
	if(item != 0)
	{
		int r = QMessageBox::warning ( this, tr ( "Deleting..." ),tr ( "Delete template '%1'?" ).arg ( item->text(0) ), QMessageBox::Yes, QMessageBox::No );
		if ( r == QMessageBox::Yes )
		{
			QString qstr = QString("DELETE FROM templatestab WHERE `ID`='%1';").arg(item->text(2));
			QSqlQuery query(qstr);
			QSqlError qerror = query.lastError();
			if(qerror.isValid())
				QMessageBox::warning ( 0, tr ( "Template not deleted..." ), qerror.text());
			else
				templates_load();
		}
	}
}
//
void cfgfrm::templates_loaddetails()
{
	QTreeWidgetItem *item = tem_tree->currentItem();
	if(item != 0)
	{
		QString qstr = QString("SELECT name, description, created_by, created, modificated_by, modificated FROM templatestab WHERE `ID`='%1';").arg(item->text(2));
		QSqlQuery query(qstr);
		if ( query.isActive())
		{
			query.next();
			tem_name->setText(query.value(0).toString());
			tem_description->setText(query.value(1).toString());
			QString s  = query.value(3).toString();
			tem_created->setText(s.section("-", 2, 2)+"."+s.section("-", 1, 1)+"."+s.section("-", 0, 0));
			tem_createdby->setText(query.value(2).toString());
			s  = query.value(5).toString();
			tem_modification->setText(s.section("-", 2, 2)+"."+s.section("-", 1, 1)+"."+s.section("-", 0, 0));
			tem_modificatedby->setText(query.value(4).toString());
		}
		else
		{
			QSqlError qerror = query.lastError();
			QMessageBox::warning ( 0, tr ( "Can't load templates..." ), qerror.text() );
		}	
	}
}
//
void cfgfrm::templates_loaddescription()
{
	QString qstr = QString("SELECT description FROM templatestab WHERE `ID`='%1';").arg(templateids[cmbtemplatename->currentIndex()]);
	QSqlQuery query(qstr);
	if ( query.isActive())
	{
		query.next();
		templatedescription->setText(query.value(0).toString());
	}
	else
	{
		QSqlError qerror = query.lastError();
		QMessageBox::warning ( 0, tr ( "Can't load template description..." ), qerror.text() );
	}
}
//
void cfgfrm::locks_loaduserlocks()
{
	lock_tree->clear();
	lock_tree->hideColumn(0);
	lock_tree->setColumnWidth(2, 80);
	QSqlQuery query("SELECT `ID`, `table`, `tabid`, `user`, `timestamp` FROM userlocktab ORDER BY `table`, `ID`;");
	if(query.isActive())
	{
		while(query.next())
		{
			QTreeWidgetItem *item = new QTreeWidgetItem(lock_tree);
			item->setText(0, query.value(0).toString());
			item->setText(1, query.value(1).toString());
			item->setText(2, query.value(2).toString());
			item->setText(3, query.value(3).toString());
			item->setText(4, query.value(4).toString().replace("T", " "));
			if(query.value(1).toString().mid(0, 3) == "dir")
			{
				QSqlQuery query2(QString("SELECT lastname, firstname FROM %1 WHERE `ID`='%2';").arg(query.value(1).toString()).arg(query.value(2).toString()));
				query2.next();
				item->setText(5, query2.value(0).toString()+", "+query2.value(1).toString());
			}
			else if(query.value(1).toString().mid(0, 4) == "data")
			{
				QSqlQuery query2(QString("SELECT col1 FROM %1 WHERE `ID`='%2';").arg(query.value(1).toString()).arg(query.value(2).toString()));
				query2.next();
				item->setText(5, query2.value(0).toString());
			}
			else if(query.value(1).toString().mid(0, 9) == "procedure")
			{
				QSqlQuery query2(QString("SELECT client FROM %1 WHERE `ID`='%2';").arg(query.value(1).toString()).arg(query.value(2).toString()));
				query2.next();
				item->setText(5, query2.value(0).toString());
			}
			else if(query.value(1).toString().mid(0, 3) == "doc")
			{
				QSqlQuery query2(QString("").arg(query.value(1).toString()).arg(query.value(2).toString()));
				query2.next();
				item->setText(5, query2.value(0).toString().section(" ", 1, 1)+", "+query2.value(1).toString());
			}
			else if(query.value(1).toString().mid(0, 7) == "account" || query.value(1).toString() == "ietab")
			{
				QSqlQuery query2(QString("SELECT refnr, description FROM %1 WHERE `ID`='%2';").arg(query.value(1).toString()).arg(query.value(2).toString()));
				query2.next();
				item->setText(5, query2.value(0).toString()+", "+query2.value(1).toString());
			}
		}
	}
	else
	{
		QSqlError qerror = query.lastError();
		QMessageBox::warning ( 0, tr ( "Can't load userlocks..." ), qerror.text() );
	}	
}
//
void cfgfrm::locks_unlockentry()
{
	QTreeWidgetItem *item = lock_tree->currentItem();
	if(item)
	{
		int r = QMessageBox::warning ( this, tr ( "Unlocking..." ),tr("Do you want to unlock the selected entry?" ) , QMessageBox::Yes, QMessageBox::No );
		if ( r == QMessageBox::Yes )
		{
			QSqlQuery query(QString("DELETE FROM userlocktab WHERE `ID`='%1'").arg(item->text(0)));
			locks_loaduserlocks();
		}
	}
}

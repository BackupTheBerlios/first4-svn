#include <QByteArray>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
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
#include "newdbfrm.h"
#include "vars.h"
#include "newdatatabfrm.h"

extern QString username, fullname, firstver, templatefolder, docfolder;
extern QString dbhost, dbname, dbuid, dbpwd, dbport;

QString cfgdbver;
QStringList listallusers;

cfgfrm::cfgfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
void cfgfrm::initfrm()
{
    this->setFixedSize(this->width(), this->height());
    vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
	    if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
    }
    lbluser->setText(username);
    txtuser->setText(username);
    
    if(username != "Administrator")
		cfgtab->setEnabled(false);
    
    maintab->setCurrentIndex(0);
    cfgtab->setCurrentIndex(0);

    //init listressoureces
    listressources->header()-> setClickable(FALSE);
    listressources->header()->setResizeMode(QHeaderView::Fixed);
    listressources->headerItem()->setText(0, QApplication::translate("cfgfrm", "Ressources", 0, QApplication::UnicodeUTF8));    
    listressources->headerItem()->setText(1, QApplication::translate("cfgfrm", "ID", 0, QApplication::UnicodeUTF8));
    listressources->headerItem()->setText(2, QApplication::translate("cfgfrm", "name", 0, QApplication::UnicodeUTF8));
    listressources->headerItem()->setText(3, QApplication::translate("cfgfrm", "users", 0, QApplication::UnicodeUTF8));
    listressources->headerItem()->setText(4, QApplication::translate("cfgfrm", "details", 0, QApplication::UnicodeUTF8));
    listressources->hideColumn(1);
    listressources->hideColumn(2);
    listressources->hideColumn(3);
    listressources->hideColumn(4);
    
    listpermissions->setColumnWidth(0, 300);
    listpermissions->setColumnWidth(1, 40);
    listpermissions->setColumnWidth(2, 40);
    
    //init functions
    loadlangfile();
    loaddbinfo();
    loadservers();
    loadusers();
    loadressources();
    loadsettings();
    loadowndata();
    
    resdefframe->setCurrentIndex(3);
    
    txtdocpath->setText(docfolder);
    txttemplatepath->setText(templatefolder);
    
    //slot connections
    connect(btnchangepwd, SIGNAL(released()), this, SLOT(changepwd()));
    connect(btnsellangfile, SIGNAL(released()), this, SLOT(selectlangfile()));
    connect(btnadddb, SIGNAL(released()), this, SLOT(addservers()));
    connect(btndeldb, SIGNAL(released()), this, SLOT(delservers()));
    connect(btnopensqlfile, SIGNAL(released()), this, SLOT(opendbspec()));
    connect(btndbapply, SIGNAL(released()), this, SLOT(opendbspec()));
    connect(listusers, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectuser()));
    connect(btn_users_new, SIGNAL(released()), this, SLOT(newuser()));
    connect(btn_users_save, SIGNAL(released()), this, SLOT(saveuserchange()));
    connect(listressources, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(loadressourcesdetails()));
    connect(btndoctemplate, SIGNAL(released()), this, SLOT(seldoctemplate()));
    connect(listpermissions, SIGNAL(itemClicked ( QTreeWidgetItem*, int)), this, SLOT(applyresourcesdetails()));
    connect(btnsavepermissions, SIGNAL(released()), this, SLOT(saveresourcesdetails()));
    connect(txtstartid, SIGNAL(textChanged(QString)), this, SLOT(applyresourcesdetails()));
    connect(txt_doctemplate, SIGNAL(textChanged(QString)), this, SLOT(applyresourcesdetails()));
    connect(txtboxbank, SIGNAL(textEdited(QString)), this, SLOT(applyresourcesdetails()));
    connect(txtboxaccountnr, SIGNAL(textEdited(QString)), this, SLOT(applyresourcesdetails()));
    connect(txtboxclearing, SIGNAL(textEdited(QString)), this, SLOT(applyresourcesdetails()));
    connect(txtboxcurrency, SIGNAL(textEdited(QString)), this, SLOT(applyresourcesdetails()));
    connect(listressources, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));
    connect(btndocpath, SIGNAL(released()), this, SLOT(selectdocpath()));
    connect(btntemplpath, SIGNAL(released()), this, SLOT(selecttemplpath()));
    connect(btnsavepath, SIGNAL(released()), this, SLOT(savedefaultpath()));
    connect(btnsavesettings, SIGNAL(released()), this, SLOT(savesettings()));
    connect(btnowndata, SIGNAL(released()), this, SLOT(saveowndata()));
}
//
void cfgfrm::closeEvent(QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
QString cfgfrm::cryptpwd(QString pwd)
{
    int i;;
    QString cpwd = "";
    QByteArray pass;
    pass.append(pwd);
    for(i=0;i<pass.size();i++)
    {
		cpwd += tr("%1").arg(pass[i] ^ pass[pass.size()-i], 0, 16);
    }
    return cpwd;
}
//
void cfgfrm::changepwd()
{
    if(txtnewpwd1->text() == txtnewpwd2->text())
    {    
		// lese aktuelles Passwort aus Datenbank
		QSqlQuery query;
		query.prepare( "SELECT ID FROM userstab WHERE username=:username AND userpass=:userpass;");
		query.bindValue( ":username", txtuser->text());
		query.bindValue( ":userpass", cryptpwd(txtoldpwd->text()));
		query.exec();
	    if(query.size()>0)
	    {
			query.next();
			QSqlQuery queryupdate;
			queryupdate.prepare( "UPDATE `userstab` SET `userpass` = :userpass WHERE `ID` = :ID LIMIT 1;");
			queryupdate.bindValue( ":userpass", cryptpwd(txtnewpwd1->text()));
			queryupdate.bindValue( ":ID", query.value(0).toString());
			queryupdate.exec();		
			QMessageBox::information(0, tr("Change password..."), tr("Password was changed!"));
			txtoldpwd->setText("");
			txtnewpwd1->setText("");
			txtnewpwd2->setText("");
			txtuser->setFocus();		    
	    }
	    else
	    {
			QMessageBox::warning(0, tr("Changing password..."), tr("Actual password wrong."));
			txtoldpwd->setFocus();
	    }
    }
    else
    {
		QMessageBox::warning(0, tr("Change password..."), tr("New password does not agree with password confirmation!"));
		txtnewpwd1->setFocus();
    }
}
//
void cfgfrm::loadlangfile()
{
    QFile file(QDir::homePath()+"/.first4/lang.conf");
    if(file.open(QIODevice::ReadOnly))
    {
		QTextStream stream(&file);
		QString streamline;
		streamline = stream.readLine();
		txtlang->setText(streamline);
		file.close();    
    }
    else
		QMessageBox::critical(0,"Error...", tr("Error during Language-File reading!"));
}
//
void cfgfrm::selectlangfile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Lang-File"),
                                                QDir::homePath()+"/.first4",
                                                tr("Lang-File (*.qm)"));
    QFile file(QDir::homePath()+"/.first4/lang.conf");
    if(file.open(QIODevice::WriteOnly))
    {
		QTextStream stream(&file);
		stream << filename;
		txtlang->setText(filename);
		QMessageBox::information(0,"Info...", tr("Please restart the application."));
		file.close();
    }
    else
		QMessageBox::critical(0,"Error...", tr("Language-File cannot be written!"));
}
//
void cfgfrm::loaddbinfo()
{
    lbldbname->setText(dbname);
    lbldbname_2->setText(dbname);
    lbldbhost->setText(dbhost);
    lbldbhost_2->setText(dbhost);
    lblfirstversion->setText(firstver);
    lblfirstversion_2->setText(firstver);

    QString connstr = "SELECT value FROM maincfgtab WHERE var = 'dbversion';";
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		query.next();
		cfgdbver = query.value(0).toString();
		lbldbversion->setText(query.value(0).toString());
		lbldbversion_2->setText(query.value(0).toString());
    }
}
//
void cfgfrm::addservers()
{
    newdbfrm* ndb = new newdbfrm;
    ndb->init();
    if(ndb->exec())
		loadservers();
}
//
void cfgfrm::delservers()
{
    if(listservers->currentItem())
		listservers->takeItem(listservers->currentRow());
    QFile file(QDir::homePath()+"/.first4/servers.conf");
    if(file.open(QIODevice::WriteOnly))
    {
		int i;
		for(i=0;i<listservers->count();i++)
		{
			listservers->setCurrentRow(i);
			QListWidgetItem *item = listservers->currentItem();
		    QTextStream stream(&file);	
		    stream << item->text() << "\n";
		}
    }
    file.close();
    loadservers();
}
//
void cfgfrm::loadservers()
{
	listservers->clear();
    QFile file(QDir::homePath()+"/.first4/servers.conf" );
    if(file.open(QIODevice::ReadOnly))
    {
		QTextStream stream(&file);
		QString streamline;
		while(!stream.atEnd())
		{
		    streamline = stream.readLine();
		    listservers->insertItem(-1, streamline);
		}
		file.close();
    }
}
//
void cfgfrm::opendbspec()
{
   QString filename = QFileDialog::getOpenFileName(this, tr("Select DB-Structurfile..."),
                                                QDir::homePath(),
                                                tr("DB-Structurfile (*.fdb)"));
   boxdbsqlfile->setText(filename);
}
//
void cfgfrm::applydbspec()
{
    QFile file(boxdbsqlfile->text());
    if(file.open(QIODevice::ReadOnly))
    {
		bool ok;	
		QTextStream stream(&file);
		QString ver = stream.readLine();
		ver = ver.mid(1, ver.length()-2);
		int a1, b1, c1, a2, b2, c2, d1, d2;
		a1 = ver.section(".", 0, 0).toInt(&ok, 10);
		b1 = ver.section(".", 1, 1).toInt(&ok, 10);
		c1 = ver.section(".", 2, 2).section("-", 0, 0).toInt(&ok, 10);
		d1 = ver.section(".", 2, 2).section("-", 1, 1).toInt(&ok, 10);
		a2 = cfgdbver.section(".", 0, 0).toInt(&ok, 10);
		b2 = cfgdbver.section(".", 1, 1).toInt(&ok, 10);
		c2 = cfgdbver.section(".", 2, 2).section("-", 0, 0).toInt(&ok, 10);
		d2 = cfgdbver.section(".", 2, 2).section("-", 1, 1).toInt(&ok, 10);
		
		if((a1>a2) || (a1==a2 && b1>b2) || (a1==a2 && b1==b2 && c1>c2) || (a1==a2 && b1==b2 && c1==c2 && d1>d2))
		{
		    if(QMessageBox::warning(this, tr("Update Database..."), tr("Update Database?"),QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
		    {
				while(!stream.atEnd())
				{
				    QString connstr =  stream.readLine();
				    QSqlQuery query(connstr.simplified());
				}		    
				QString conn =  "UPDATE `maincfgtab` SET `value`='"+ver+"' WHERE `var`='dbversion';";
				QSqlQuery query(conn);
				QMessageBox::information(0, tr("Update..."), tr("Database was updated."));
				cfgfrm::loaddbinfo();
		    }
		}
		else
		    QMessageBox::information(0,"Update not possible...", "Current version is newer than file specification!\n\nUpdate not possible....");
		file.close();	
	}    
}
//
void cfgfrm::loadusers()
{
   	if(lbluser->text() == "Administrator")
    {
		progbar->setValue(10);
		QSqlQuery querybenutzer("SELECT username, fullname FROM userstab;"); //Lade Benutzer
		listallusers.clear();
		listusers->clear();
	    while(querybenutzer.next())
	    {
			listusers->insertItem(-1, querybenutzer.value(1).toString()+" ("+querybenutzer.value(0).toString()+")");
			listallusers << querybenutzer.value(0).toString()+":#:"+querybenutzer.value(1).toString();
		}
	}
}
//
void cfgfrm::selectuser()
{
	QListWidgetItem *item = listusers->currentItem();
    QString seluser = item->text().section(" (", 1, 1).section(")", 0, 0);
    txt_users_user->setText(seluser.simplified());
    QString qstr = QString("SELECT ID,  userpass,  fullname,  firstname,  lastname,  dob,  p_street,  p_zip,  p_location,  p_country,  b_street,  b_zip,  b_location,  b_country,  profession,  org_unit,  position,  emp_type, p_tel,  p_fax,  p_mobile,  p_pager,  p_ip,  email1,  email2,  email3,  p_web,  b_tel,  b_teldir,  b_fax,  b_mobile,  b_pager,  b_ip,  email4,  email5,  email6,  notes,  emp_grade FROM userstab WHERE username='%1'").arg(seluser);
    QSqlQuery query(qstr);
    if(query.isActive()) {
		query.next();
		txt_users_fullname->setText(query.value(2).toString().simplified());
		txt_users_id->setText(query.value(0).toString().simplified());
		if(seluser == "Administrator")
		    cfgtab->setEnabled(FALSE);
		else {
			cfgtab->setEnabled(TRUE);
		    txt_users_firstname->setText(query.value(3).toString().simplified());
		    txt_users_lastname->setText(query.value(4).toString().simplified());
		    QString s = query.value(5).toString();
		    txtdob->setDate(QDate::QDate(s.section("-", 0, 0).toInt(), s.section("-", 1, 1).toInt(), s.section("-", 2, 2).toInt()));
		    txt_users_privat_street->setText(query.value(6).toString());
		    txt_users_privat_zip->setText(query.value(7).toString());
		    txt_users_privat_location->setText(query.value(8).toString());
		    txt_users_privat_country->setText(query.value(9).toString());
		    txt_users_business_street->setText(query.value(10).toString());
		    txt_users_business_zip->setText(query.value(11).toString());
		    txt_users_business_location->setText(query.value(12).toString());
		    txt_users_business_country->setText(query.value(13).toString());
		    txt_users_business_prof->setText(query.value(14).toString());
		    txt_users_business_unit->setText(query.value(15).toString());
		    txt_users_business_position->setText(query.value(16).toString());
		    txt_users_business_type->setEditText(query.value(17).toString());
		    txt_users_business_grade->setText(query.value(37).toString());
		    txt_users_private_tel->setText(query.value(18).toString());
		    txt_users_private_fax->setText(query.value(19).toString());
		    txt_users_private_mobile->setText(query.value(20).toString());
		    txt_users_private_pager->setText(query.value(21).toString());
		    txt_users_private_voip->setText(query.value(22).toString());
		    txt_users_private_email1->setText(query.value(23).toString());
		    txt_users_private_email2->setText(query.value(24).toString());
		    txt_users_private_email3->setText(query.value(25).toString());
		    txt_users_private_website->setText(query.value(26).toString());
		    txt_users_business_tel->setText(query.value(27).toString());
		    txt_users_business_teldir->setText(query.value(28).toString());
		    txt_users_business_fax->setText(query.value(29).toString());
		    txt_users_business_mobile->setText(query.value(30).toString());
		    txt_users_business_pager->setText(query.value(31).toString());
		    txt_users_business_voip->setText(query.value(32).toString());
		    txt_users_business_email1->setText(query.value(33).toString());
		    txt_users_business_email2->setText(query.value(34).toString());
		    txt_users_business_email3->setText(query.value(35).toString());
		    txtnotes->setText(query.value(36).toString());
		}
	}
}
//
void cfgfrm::newuser()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("User name:"), QLineEdit::Normal,
                                          QDir::home().dirName(), &ok);
    if ( ok && !text.isEmpty() ) 
    {
		txt_users_user->setText(text);
		QString connstr = "SELECT * FROM userstab WHERE USERNAME='"+txt_users_user->text()+"';";			    
		QSqlQuery query(connstr);
		if ( query.isActive())
		{
		    while ( query.next())
		    {
				QMessageBox::critical(0, tr("New User..."), tr("User already exists!"));
				txt_users_user->setText("");
		    }
		}
    }    
    if(txt_users_user->text() != "")
    {
		QString conn = "INSERT INTO `userstab` ( `ID` , `username` , `userpass` ) VALUES ('', '"+txt_users_user->text()+"', '');";	
		QSqlQuery query(conn);
		loadusers();	 
    }
}
//
void cfgfrm::saveuserchange()
{  
    if(txt_users_pwd1->text() == txt_users_pwd1->text())
    {
		QString tmpstr = "";
		QSqlQuery queryupdate;
		if(txt_users_pwd1->text() != "")
		    tmpstr = "`userpass` = '"+cryptpwd(txt_users_pwd1->text())+"', ";
		queryupdate.prepare("UPDATE `userstab` SET `username`=:username ,  "+tmpstr+" `fullname`=:fullname ,  `firstname`=:firstname,  `lastname`=:lastname,  `dob`=:dob,  `p_street`=:p_street ,  `p_zip`=:p_zip ,  `p_location`=:p_location ,  `p_country`=:p_country,  `b_street`=:b_street ,  `b_zip`=:b_zip ,  `b_location`=:b_location ,  `b_country`=:b_country ,  `profession`=:profession,  `org_unit`=:org_unit ,  `position`=:position ,  `emp_type`=:emp_type ,  `emp_grade`=:emp_grade , `p_tel`=:p_tel ,  `p_fax`=:p_fax,  `p_mobile`=:p_mobile ,  `p_pager`=:p_pager ,  `p_ip`=:p_ip ,  `email1`=:email1 ,  `email2`=:email2 ,  `email3`=:email3 ,  `p_web`=:p_web , `b_tel`=:b_tel ,  `b_teldir`=:b_teldir ,  `b_fax`=:b_fax ,  `b_mobile`=:b_mobile ,  `b_pager`=:b_pager ,  `b_ip`=:b_ip ,  `email4`=:email4 ,  `email5`=:email5 ,  `email6`=:email6 ,  `notes`=:notes WHERE `ID` = :ID LIMIT 1;");
		queryupdate.bindValue(":username" ,  txt_users_user->text());
		queryupdate.bindValue(":fullname" ,  txt_users_fullname	->text());
		queryupdate.bindValue(":firstname", txt_users_firstname->text() );
		queryupdate.bindValue(":lastname",  txt_users_lastname->text());
		queryupdate.bindValue(":dob",  txtdob->date().toString("yyyy-MM-dd"));
		queryupdate.bindValue(":p_street" ,  txt_users_privat_street->text());
		queryupdate.bindValue(":p_zip" ,  txt_users_privat_zip->text());
		queryupdate.bindValue(":p_location" ,  txt_users_privat_location->text());
		queryupdate.bindValue(":p_country",  txt_users_privat_country->text());
		queryupdate.bindValue(":b_street" ,  txt_users_business_street->text());
		queryupdate.bindValue(":b_zip" ,  txt_users_business_zip->text());
		queryupdate.bindValue(":b_location" ,  txt_users_business_location->text());
		queryupdate.bindValue(":b_country" ,  txt_users_business_country->text());
		queryupdate.bindValue(":profession",  txt_users_business_prof->text());
		queryupdate.bindValue(":org_unit" ,  txt_users_business_unit->text());
		queryupdate.bindValue(":position" ,  txt_users_business_position->text());
		queryupdate.bindValue(":emp_type" ,  txt_users_business_type->currentText());
		queryupdate.bindValue(":emp_grade" ,  txt_users_business_grade->text());
		queryupdate.bindValue(":p_tel" ,  txt_users_private_tel->text());
		queryupdate.bindValue(":p_fax",  txt_users_private_fax->text());
		queryupdate.bindValue(":p_mobile" , txt_users_private_mobile->text());
		queryupdate.bindValue(":p_pager" ,  txt_users_private_pager->text());
		queryupdate.bindValue(":p_ip" ,  txt_users_private_voip->text());
		queryupdate.bindValue(":email1" ,  txt_users_private_email1->text());
		queryupdate.bindValue(":email2" ,  txt_users_private_email2->text());
		queryupdate.bindValue(":email3" ,  txt_users_private_email3->text());
		queryupdate.bindValue(":p_web", txt_users_private_website->text());
		queryupdate.bindValue(":b_tel" ,  txt_users_business_tel->text());
		queryupdate.bindValue(":b_teldir" ,  txt_users_business_teldir->text());
		queryupdate.bindValue(":b_fax" ,  txt_users_business_fax->text());
		queryupdate.bindValue(":b_mobile" ,  txt_users_business_mobile->text());
		queryupdate.bindValue(":b_pager" ,  txt_users_business_pager->text());
		queryupdate.bindValue(":b_ip" ,  txt_users_business_voip->text());
		queryupdate.bindValue(":email4" ,  txt_users_business_email1->text());
		queryupdate.bindValue(":email5" ,  txt_users_business_email2->text());
		queryupdate.bindValue(":email6" ,  txt_users_business_email3->text());
		queryupdate.bindValue(":notes" , txtnotes->toPlainText());
		queryupdate.bindValue(":ID", txt_users_id->text());
		queryupdate.exec();
		QSqlQuery test("UPDATE `userstab` SET `p_street`=:p_street WHERE `ID` = 8 LIMIT 1;");
		test.exec();
		QMessageBox::information(0, tr("Change personal data..."), tr("Personal data successfully changed."));
		loadusers();
    }
    else
    {
		QMessageBox::warning(0, tr("Change password..."), tr("New password does not agree with password confirmation!"));
		txt_users_pwd1->selectAll();	 
		txt_users_pwd1->setFocus();
    }
}
//
void cfgfrm::loadressources()
{
    listressources->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem(listressources);
    item->setText( 0, tr("Directories"));
    item = new QTreeWidgetItem( listressources, item );
    item->setText( 0,  tr("Data & Stock"));
    item = new QTreeWidgetItem( listressources, item );
    item->setText( 0,  tr("Inventory"));
    item = new QTreeWidgetItem( listressources, item );
    item->setText( 0,  tr("Purchase orders"));
    item = new QTreeWidgetItem( listressources, item );
    item->setText( 0, tr("Orders" ));
    item = new QTreeWidgetItem( listressources, item );
    item->setText( 0, tr("Documents"));
    item = new QTreeWidgetItem( listressources, item );
    item->setText( 0, tr("Accounts"));
    item = new QTreeWidgetItem( listressources, item );
    item->setText( 0, tr("Messages"));
    
    QTreeWidgetItemIterator it(listressources);
    item = *it;
	QSqlQuery queryadr("SELECT ID, name, description, users, idcounter FROM adrtabs ORDER BY ID ASC;");
	if(queryadr.isActive())
	{
	    while ( queryadr.next())
	    {
			QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
			childitem->setText(0, queryadr.value(2).toString());
			childitem->setText(1, queryadr.value(0).toString());
			childitem->setText(2, queryadr.value(1).toString());
			childitem->setText(3, queryadr.value(3).toString());
			childitem->setText(4, queryadr.value(4).toString());
	    }
	}
	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery querydata("SELECT ID, name, description, users FROM datatabs ORDER BY ID ASC;");
	if(querydata.isActive())
	{
	    while ( querydata.next())
	    {
		QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
		childitem->setText(0, querydata.value(2).toString());
		childitem->setText(1, querydata.value(0).toString());
		childitem->setText(2, querydata.value(1).toString());
		childitem->setText(3, querydata.value(3).toString());		    
	    }
	}
	
	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery queryinv("SELECT ID, USERS FROM invcfgtab;");
	if(queryinv.isActive())
	{
	    while ( queryinv.next())
	    {
		QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
		childitem->setText(0, tr("General"));
		childitem->setText(1, queryinv.value(0).toString());
		childitem->setText(2, "inv_general");
		childitem->setText(3, queryinv.value(1).toString());		    
	    }
	}
	
	QSqlQuery queryinv2("SELECT ID, NAME, DATATABLE, TABLENAME, DATE, USERS FROM invtab ORDER BY ID ASC;");
	if(queryinv2.isActive())
	{
	    while ( queryinv2.next())
	    {
		QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
		childitem->setText(0, queryinv2.value(3).toString()+" - "+queryinv2.value(4).toString());
		childitem->setText(1, queryinv2.value(0).toString());
		childitem->setText(2, queryinv2.value(1).toString());
		childitem->setText(3, queryinv2.value(5).toString());		    
	    }
	}
	
	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery queryorders("SELECT ID, USERS, COUNTER FROM orderscfgtab;");
	if(queryorders.isActive())
	{
	    while ( queryorders.next())
	    {
		QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
		childitem->setText(0, tr("General"));
		childitem->setText(1, queryorders.value(0).toString());
		childitem->setText(2, "p_orders");
		childitem->setText(3, queryorders.value(1).toString());
		childitem->setText(4, queryorders.value(2).toString());
	    }
	}  
	
	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery queryabl("SELECT ID, users, auftrid FROM procedurecfgtab;"); 
	if(queryabl.isActive())
	{
	    queryabl.next();
	    QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
	    childitem->setText(0, tr("General"));
	    childitem->setText(1, queryabl.value(0).toString());
	    childitem->setText(2, "orders");
	    childitem->setText(3, queryabl.value(1).toString());
	    childitem->setText(4, queryabl.value(2).toString());
	}

	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery querydoc("SELECT ID, name, users, filename FROM doctab ORDER BY ID ASC;"); 
	if(querydoc.isActive())
	{
	    int tmpid;
	    QStringList cfgdocnames;
	    cfgdocnames << tr("Offer") << tr("Order confirmation") << tr("Delivery note") << tr("Bill");
	    while(querydoc.next())
	    {
		QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
		tmpid = querydoc.value(1).toString().section(" ", 0, 0).toInt()-1;
		childitem->setText(0, cfgdocnames[tmpid]);
		childitem->setText(1, querydoc.value(0).toString());
		childitem->setText(2, "doc");
		childitem->setText(3, querydoc.value(2).toString());
		childitem->setText(4, querydoc.value(3).toString());
	    }
	}
		
	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery querykon2("SELECT ID, name, description, users, bank, accountnr, blz, currency FROM accounttab WHERE `name` LIKE '%account%' ORDER BY ID ASC;"); 
	if(querykon2.isActive())
	{
	    while(querykon2.next())
	    {
		QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
		childitem->setText(0, querykon2.value(2).toString());
		childitem->setText(1, querykon2.value(0).toString());
		childitem->setText(2, querykon2.value(1).toString());
		childitem->setText(3, querykon2.value(3).toString());
		childitem->setText(4, querykon2.value(4).toString()+";"+querykon2.value(5).toString()+";"+querykon2.value(6).toString()+";"+querykon2.value(7).toString());
	    }
	}
	    
	QSqlQuery querykon1("SELECT ID, name, description, users, bank, accountnr, blz, currency FROM accounttab WHERE `name` = 'ietab' ORDER BY ID ASC;"); 
	if(querykon1.isActive())
	{
	    while(querykon1.next())
	    {
		QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
		childitem->setText(0, querykon1.value(2).toString());
		childitem->setText(1, querykon1.value(0).toString());
		childitem->setText(2, querykon1.value(1).toString());
		childitem->setText(3, querykon1.value(3).toString());
		childitem->setText(4, querykon1.value(4).toString()+";"+querykon1.value(5).toString()+";"+querykon1.value(6).toString()+";"+querykon1.value(7).toString());
	    }
	}

	it += item->childCount();
	++it;
	item = *it;
	QSqlQuery querymsg("SELECT ID, name, description, users FROM msgcfgtab ORDER BY ID ASC;"); 
	if(querymsg.isActive())
	{
	    int tmpid;
	    QStringList cfgmsgnames;
	    cfgmsgnames << tr("General message") << tr("Stockmessage") << tr("Ordermessage") << tr("Inc/Exp-Message");		
	    while(querymsg.next())
	    {
			QTreeWidgetItem* childitem = new QTreeWidgetItem(item);
			tmpid = querymsg.value(2).toString().section(" ", 0, 0).toInt()-1;
			childitem->setText(0, cfgmsgnames[tmpid]);
			childitem->setText(1, querymsg.value(0).toString());
			childitem->setText(2, "msg_"+querymsg.value(1).toString());
			childitem->setText(3, querymsg.value(3).toString());
	    }
	}
}
//
void cfgfrm::loadressourcesdetails()
{
    QTreeWidgetItem* item = listressources->currentItem();
    if(item->childCount() == 0)
    {
		listpermissions->clear();
		QString tmpstr = item->text(3);
		int i;
		for(i=0;i<listallusers.count();i++)
		{
			QTreeWidgetItem *tmpitem = new QTreeWidgetItem(listpermissions);
			tmpitem->setText(0, listallusers[i].section(":#:", 1, 1));
		    if(listallusers[i].section(":#:", 0, 0) != "Administrator")
		    {
				QString tmprights = tmpstr.section(listallusers[i].section(":#:", 0, 0)+" [", 1, 1);
				if(tmprights.mid(0, 1)=="1")
				    tmpitem->setCheckState(1, Qt::Checked);
				else
					tmpitem->setCheckState(1, Qt::Unchecked);
		
				if(tmprights.mid(1, 1)=="1")
				    tmpitem->setCheckState(2, Qt::Checked);
				else
					tmpitem->setCheckState(2, Qt::Unchecked);		
		    }
		}
		if(item->text(2)=="doc") //Dokumentvorlage laden
		{
		    txt_doctemplate->setText(item->text(4));
		    resdefframe->setCurrentIndex(0);
		}
		else if(item->text(2).left(7)=="account")
		{
		    txtboxbank->setText(item->text(4).section(";", 0, 0));
		    txtboxaccountnr->setText(item->text(4).section(";", 1, 1));
		    txtboxclearing->setText(item->text(4).section(";", 2, 2));
		    txtboxcurrency->setText(item->text(4).section(";", 3, 3));
		    resdefframe->setCurrentIndex(1);
		}
		else if(item->text(2).left(3) == "adr" || item->text(2) == "p_orders" || item->text(2) == "orders")
		{
		    txtstartid->setText(item->text(4));
		    resdefframe->setCurrentIndex(2);
		}
		else
		    resdefframe->setCurrentIndex(3);
	} else {
		listpermissions->clear();
	}
}
//
void cfgfrm::seldoctemplate()
{
   QString filename = QFileDialog::getOpenFileName(this, tr("Select Template..."),
                                                templatefolder,
                                                tr("Template (*.tex)"));
   txt_doctemplate->setText(filename);
   applyresourcesdetails();
}
//
void cfgfrm::applyresourcesdetails()
{
    int i;
    QString tmpstr = "";
    QTreeWidgetItem* item = listressources->currentItem();
    if(item->childCount()==0)
    {
    	QTreeWidgetItemIterator it(listpermissions);
    	QTreeWidgetItem *tmpitem;
		for(i=0;i<listpermissions->topLevelItemCount();i++)
		{
			tmpitem = *it;
		    if(tmpitem->text(0) != "Administrator")
		    {
				tmpstr += listallusers[i].section(":#:", 0, 0) + " [";
				if(tmpitem->checkState(1))
				    tmpstr += "1";
				else
				    tmpstr += "0";

				if(tmpitem->checkState(2))
				    tmpstr += "1";
				else
				    tmpstr += "0";
				tmpstr += "] , ";
		    } else {
				tmpstr = "Administrator [11] , ";
		    }
		    ++it;
		}
		item->setText(3, tmpstr);
		if(item->text(2).left(3)=="adr" || item->text(2)=="p_orders" || item->text(2)=="orders")
		    item->setText(4, txtstartid->text());
		if(item->text(2)=="doc")
		    item->setText(4, txt_doctemplate->text());
		if(item->text(2).left(7)=="account")
		    item->setText(4, txtboxbank->text()+";"+txtboxaccountnr->text()+";"+txtboxclearing->text()+";"+txtboxcurrency->text());
    }
}
//
void cfgfrm::saveresourcesdetails()
{
    //Adressbcher speichern
    QTreeWidgetItemIterator it(listressources);
    QTreeWidgetItem *item;
    while (*it) {
   	    item = *it;
        if(item->text(2).mid(0,3) == "adr") {
			QSqlQuery querysave;
			querysave.prepare( "UPDATE `adrtabs` SET `users` = :users, `idcounter` = :idcounter WHERE `ID` = :ID LIMIT 1;");
			querysave.bindValue( ":users", item->text(3));
			querysave.bindValue( ":idcounter", item->text(4));
			querysave.bindValue( ":ID", item->text(1));
			querysave.exec();
	    } else if(item->text(2).mid(0,4) == "data") {
			QSqlQuery querysave;
			querysave.prepare( "UPDATE `datatabs` SET `users` = :users WHERE `ID` = :ID LIMIT 1;");
			querysave.bindValue( ":users", item->text(3));
			querysave.bindValue( ":ID", item->text(1));
			querysave.exec();
	   	} else if(item->text(2).mid(0,3) == "inv") {
   			QSqlQuery querysave;
	   		if(item->text(2) == "inv_general") {
			    querysave.prepare( "UPDATE `invcfgtab` SET `users` = :users WHERE `ID` = :ID LIMIT 1;");
			    querysave.bindValue( ":users", item->text(3));
			    querysave.bindValue( ":ID", item->text(1));
   			} else {
   				querysave.prepare( "UPDATE `invtab` SET `users` = :users WHERE `ID` = :ID LIMIT 1;");
				querysave.bindValue( ":users", item->text(3));
				querysave.bindValue( ":ID", item->text(1));
  			}
		    querysave.exec();
   		} else if(item->text(2) == "p_orders") {
   			QSqlQuery querysave;
   			querysave.prepare( "UPDATE `orderscfgtab` SET `users` = :users, `counter` = :counter WHERE `ID` = :ID LIMIT 1;");
		    querysave.bindValue( ":users", item->text(3));
		    querysave.bindValue( ":counter", item->text(4));
		    querysave.bindValue( ":ID", item->text(1));
		    querysave.exec();
  		} else if(item->text(2) == "orders") {
		 	QSqlQuery querysave;
			querysave.prepare( "UPDATE `procedurecfgtab` SET `users` = :users, `auftrid` = :auftrid WHERE `ID` = :ID LIMIT 1;");
			querysave.bindValue( ":users", item->text(3));
			querysave.bindValue( ":auftrid", item->text(4));
			querysave.bindValue( ":ID", item->text(1));
			querysave.exec(); 			
 		} else if(item->text(2) == "doc") {
 			QSqlQuery querysave;
			querysave.prepare( "UPDATE `doctab` SET `users` = :users, `filename` = :filename WHERE `ID` = :ID LIMIT 1;");
			querysave.bindValue( ":users", item->text(3));
			querysave.bindValue( ":filename", item->text(4));
			querysave.bindValue( ":ID", item->text(1));
			querysave.exec();	
		} else if(item->text(2) == "ietab" || item->text(2).left(7) == "account") {
			QSqlQuery querysave;
			querysave.prepare( "UPDATE `accounttab` SET `users`=:users, `bank`=:bank, `accountnr`=:accountnr, `blz`=:blz, `currency`=:currency WHERE `ID`=:ID LIMIT 1;");
			querysave.bindValue( ":users", item->text(3));
			querysave.bindValue( ":bank", item->text(4).section(";", 0, 0));
			querysave.bindValue( ":accountnr", item->text(4).section(";", 1, 1));
			querysave.bindValue( ":blz", item->text(4).section(";", 2, 2));
			querysave.bindValue( ":currency", item->text(4).section(";", 3, 3));
			querysave.bindValue( ":ID", item->text(1));
			querysave.exec();
	    } else if(item->text(2).mid(0,3) == "msg") {
			QSqlQuery querysave;
			querysave.prepare( "UPDATE `msgcfgtab` SET `users`= :users WHERE `ID` = :ID LIMIT 1;");
			querysave.bindValue( ":users", item->text(3));
			querysave.bindValue( ":ID", item->text(1));
			querysave.exec();
        }
	    ++it;
    }
    QMessageBox::information(0, tr("Permissions..."), tr("New settings are saved and now active."));
}
//
void cfgfrm::contmenu()
{
    QTreeWidgetItem* item = listressources->currentItem();    
    QMenu* contextMenu = new QMenu( this );
    Q_CHECK_PTR( contextMenu );
    if(item->childCount() > 0)
    {
     	QAction* cnt_newaddr = new QAction( tr( "New Directory" ), this );
	    connect(cnt_newaddr , SIGNAL(triggered()), this, SLOT(newaddr())); 
     	QAction* cnt_newdata = new QAction( tr( "New Datatable" ), this );
	    connect(cnt_newdata , SIGNAL(triggered()), this, SLOT(newdata())); 
     	QAction* cnt_newaccount = new QAction( tr( "New Account" ), this );
	    connect(cnt_newaccount , SIGNAL(triggered()), this, SLOT(newaccount())); 
	    contextMenu->addAction(cnt_newaddr);
	    contextMenu->addAction(cnt_newdata);
		contextMenu->addAction(cnt_newaccount);
    } else {
		if(item->text(0)!= tr("General") && item->text(2)!="ietab" && item->text(2)!="taxtab" && item->text(2)!="*doc*")
		{
	     	QAction* cnt_rename = new QAction( tr( "Rename \'%1\'" ).arg(item->text(0)), this );
		    connect(cnt_rename , SIGNAL(triggered()), this, SLOT(rentab())); 
	     	QAction* cnt_delete = new QAction( tr( "Delete \'%1\'" ).arg(item->text(0)), this );
		    connect(cnt_delete , SIGNAL(triggered()), this, SLOT(deltab())); 
		    contextMenu->addAction(cnt_rename);
		    contextMenu->addAction(cnt_delete);
		}
    }
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}
//
void cfgfrm::newaddr()
{
    bool ok;
    QString adrdesc = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("Directory:"), QLineEdit::Normal,"", &ok);
    
    if(ok && !adrdesc.isEmpty()) 
    {
	int adrcount = 1;
	QString adrname = "";
	QString qstr1 = "SELECT * FROM adrtabs ORDER BY name ASC;";	
	QSqlQuery queryadrnew1(qstr1);
	if(queryadrnew1.isActive())
	{
	    while ( queryadrnew1.next())
	    {
			if(QString("adr%1").arg(adrcount,0,10) == queryadrnew1.value(1).toString())
			    adrcount++;
			else
			{
			    if(adrname == "")
					adrname = QString("adr%1").arg(adrcount,0,10);
			}
	    }
	    if(adrname == "")
			adrname = QString("adr%1").arg(adrcount++,0,10);
	}
			
	QString qstr2 = "INSERT INTO `adrtabs` ( `ID` , `name` , `description` , `users` ) VALUES ('', '";
	qstr2 += adrname;
	qstr2 += "', '";
	qstr2 += adrdesc;
	qstr2 +=  "', '');";
	QSqlQuery queryadrnew2(qstr2);
	QString qstr3 = tr("CREATE TABLE `%1` (  `ID` int(11) NOT NULL auto_increment, `clientid` text NOT NULL, `company` text NOT NULL, `lastname` text NOT NULL, `firstname` text NOT NULL, `nameadd` text NOT NULL, `pobox` text NOT NULL, `street_nr` text NOT NULL, `zip_location` text NOT NULL, `tel_b` text NOT NULL, `tel_direct` text NOT NULL, `fax_b` text NOT NULL, `tel_p` text NOT NULL, `fax_p` text NOT NULL, `mobile` text NOT NULL, `email1` text NOT NULL, `email2` text NOT NULL, `email3` text NOT NULL, `homepage` text NOT NULL, `revenueaj` text NOT NULL, `revenuelj` text NOT NULL, `discount` text NOT NULL, `clienttyp` text NOT NULL, `comments` text NOT NULL, `custom1` text NOT NULL, `custom2` text NOT NULL, `custom3` text NOT NULL, `custom4` text NOT NULL, `custom5` text NOT NULL, `created` text NOT NULL, `modified` text NOT NULL, KEY `ID` (`ID`)) ENGINE=InnoDB CHARSET=latin1;").arg(adrname);
	QSqlQuery queryadrnew3(qstr3);
	cfgfrm::loadressources();
    }
}
//
void cfgfrm::newdata()
{
    newdatatabfrm newtab;
    newtab.init();
    if(newtab.exec())
	  loadressources();
}
//
void cfgfrm::newaccount()
{
    bool ok;
    QString accountdesc = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("Accountname:"), QLineEdit::Normal,"", &ok);
    if(ok && !accountdesc.isEmpty()) 
    {
		int accountcount = 1;
		QString accountname = "";
		QString qstr1 = "SELECT name FROM accounttab ORDER BY name ASC;";	
		QSqlQuery querykontonew1(qstr1);
		if(querykontonew1.isActive())
		{
		    while (querykontonew1.next())
		    {
				if(QString("account%1").arg(accountcount,0,10) == querykontonew1.value(0).toString())
				    accountcount++;
				else
				{
				    if(accountname == "")
						accountname = QString("account%1").arg(accountcount,0,10);
				}
		    }
		    if(accountname == "")
				accountname = QString("konto%1").arg(accountcount++,0,10);
		}
		QString qstr2 = QString("INSERT INTO `accounttab` (`ID`, `name`, `description`, `accountnr`, `bank`, `currency`, `users`) VALUES (NULL, '%1', '%2', '', '', '', '')").arg(accountname).arg(accountdesc);
		QSqlQuery querykontonew2(qstr2);
	    
		QString qstr3 = tr("CREATE TABLE `%1` (`ID` int NOT NULL AUTO_INCREMENT , `refnr` text NOT NULL, `date` date NOT NULL DEFAULT '' , `address` text NOT NULL, `description` text NOT NULL , `code` text NOT NULL , `amount` text NOT NULL , PRIMARY KEY (`ID`))").arg(accountname);
		QSqlQuery querykontonew5(qstr3);
		loadressources();
    }
}
//
void cfgfrm::rentab()
{
	QTreeWidgetItem* item = listressources->currentItem();
    if(item->text(2)!="")
    {
		bool ok;
	    QString newdesc = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                          tr("Rename '%1' to:").arg(item->text(0)), QLineEdit::Normal,"", &ok);
		if(ok && !newdesc.isEmpty())
		{
			if(item->text(2).mid(0, 3) == "adr")
			{
			    QString qstr = tr("UPDATE `adrtabs` SET `description` = '%1' WHERE ID='%2' LIMIT 1;").arg(newdesc).arg(item->text(1));
			    QSqlQuery queryadrren(qstr);
			    item->setText(0, newdesc);
			} else if(item->text(2).mid(0, 4) == "data") {
			    QString qstr = tr("UPDATE `datatabs` SET `description` = '%1' WHERE ID='%2' LIMIT 1;").arg(newdesc).arg(item->text(1));
			    QSqlQuery querydataren(qstr);
			    item->setText(0, newdesc);
			} else if(item->text(2).left(7)=="account") {
			    QString qstr = tr("UPDATE `accounttab` SET `description` = '%1' WHERE ID='%2' LIMIT 1;").arg(newdesc).arg(item->text(1));
			    QSqlQuery querykontoren(qstr);
			    item->setText(0, newdesc);
			}
		}
    }
}
//
void cfgfrm::deltab()
{
	QTreeWidgetItem* item = listressources->currentItem();
    if(item->text(2)!="")
    {
	    int r = QMessageBox::warning(this, tr("Deleting..."),tr("Delete '%1'?").arg(item->text(0)), QMessageBox::Yes, QMessageBox::No);
		if(r == QMessageBox::Yes)
		{
			if(item->text(2).mid(0, 3) == "adr")
			{
			    QString conn2 = QString("DELETE FROM `adrtabs` WHERE `ID` = '%1';").arg(item->text(1));
			    QSqlQuery queryadrdel2(conn2);
	  
			    QString conn3 = QString("DROP TABLE `%1`;").arg(item->text(2));
			    QSqlQuery queryadrdel3(conn3);
			    loadressources();
			} else if(item->text(2).mid(0, 4) == "data") {
			    QString conn2 = QString("DELETE FROM `datatabs` WHERE `ID` = '%1';").arg(item->text(1));
			    QSqlQuery querydatadel2(conn2);
	  
			    QString conn3 = QString("DROP TABLE `%1`;").arg(item->text(2));
			    QSqlQuery querydatadel3(conn3);
			    loadressources();
			} else if(item->text(2).left(7)=="account") {
			    QString conn2 = QString("DELETE FROM `accounttab` WHERE `ID` = '%1';").arg(item->text(1));
			    QSqlQuery querykontodel2(conn2);
	  
			    QString conn3 = QString("DROP TABLE `%1`;").arg(item->text(2));
			    QSqlQuery querykontodel3(conn3);
			    loadressources();
			} else if(item->text(2).mid(0, 3) == "inv") {
			    QString conn2 = QString("DELETE FROM `invtab` WHERE `ID` = '%1';").arg(item->text(1));
			    QSqlQuery querykontodel2(conn2);
	  
			    QString conn3 = QString("DROP TABLE `%1`;").arg(item->text(2));
			    QSqlQuery querykontodel3(conn3);
			    loadressources();
			}
		}
    }
}
//
void cfgfrm::selectdocpath()
{
	//QString s = QFileDialog::getExistingDirectory("/", 0, 0, tr("Docfolder..."), TRUE, TRUE);
	QString dir = QFileDialog::getExistingDirectory(this, tr("Docfolder..."),
                                                 QDir::homePath(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
	txtdocpath->setText(dir);
}
//
void cfgfrm::selecttemplpath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Templatefolder..."),
                                                 QDir::homePath(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
	txttemplatepath->setText(dir);
}
//
void cfgfrm::savedefaultpath()
{
    QSqlQuery query;
    query.prepare( "UPDATE maincfgtab SET `value` = :value WHERE var = 'docfolder';");
    query.bindValue( ":value", txtdocpath->text() );
    query.exec();
    docfolder=txtdocpath->text();
    
    query.prepare( "UPDATE maincfgtab SET `value` = :value WHERE var = 'templatefolder';");
    query.bindValue( ":value", txttemplatepath->text());
    query.exec();
    QMessageBox::information(0, tr("Default paths..."), tr("New settings are saved and now active."));
    templatefolder=txttemplatepath->text();
}
//
void cfgfrm::loadsettings()
{
	QString qstr = "SELECT value FROM maincfgtab WHERE `var`='DoG';";
    QSqlQuery loadsettings_1(qstr);
    loadsettings_1.next();
    daysofgrace->setValue(loadsettings_1.value(0).toInt());
    
    qstr = "SELECT value FROM maincfgtab WHERE `var`='docpref';";
    QSqlQuery loadsettings_2(qstr);
    loadsettings_2.next();
    txtdocprefix->setText(loadsettings_2.value(0).toString());
}
//
void cfgfrm::savesettings()
{
    QSqlQuery savesettings_1;
    savesettings_1.prepare("UPDATE maincfgtab SET `value`=:dog WHERE `var`='DoG';");
    savesettings_1.bindValue(":dog", daysofgrace->cleanText());
    savesettings_1.exec();
    QSqlQuery savesettings_2;
    savesettings_2.prepare("UPDATE maincfgtab SET `value`=:prefix WHERE `var`='docpref';");
    savesettings_2.bindValue(":prefix", txtdocprefix->text());
    savesettings_2.exec();
    QMessageBox::information(0, tr("Settings..."), tr("New settings are saved and now active."));
}
//
void cfgfrm::saveowndata()
{
    QStringList fields;
    fields << txtcompany->text() << txtaddress->toPlainText()  << txt_bank_name->text() << txt_bank_addr->text() << txt_bank_clearing->text() << txt_bank_accountnr->text() << txt_bank_usrnr->text();
    QStringList rowname;
    rowname << "company" << "companyaddress" << "bankname" << "bankaddress" << "bankblz" << "bankaccountnr" << "banktnr";
    int i;
    QString qstr;
    for(i=0; i<rowname.count(); i++)
    {
		qstr = QString("SELECT ID FROM `maincfgtab` WHERE `var` = '%1';").arg(rowname[i]);
		QSqlQuery querycheck(qstr);
		if(querycheck.size()>0)
		{
		    querycheck.next();
		    qstr = QString("UPDATE `maincfgtab` SET `value`='%1' WHERE `ID`=%2;").arg(fields[i]).arg(querycheck.value(0).toString());
		}
		else
		    qstr = QString("INSERT INTO `maincfgtab` (`ID`, `var`, `value`) VALUES ('', '%1', '%2');").arg(rowname[i]).arg(fields[i]);
		QSqlQuery querysetvar(qstr);
    }
    QMessageBox::information(0, tr("Own data..."), tr("New settings are saved and now active."));
}
//
void cfgfrm::loadowndata()
{
    QStringList fields;
    QStringList rowname;
    rowname << "company" << "companyaddress" << "bankname" << "bankaddress" << "bankblz" << "bankaccountnr" << "banktnr";
    int i;
    QString qstr;
    for(i=0;i<rowname.count(); i++)
    {
		qstr = QString("SELECT value FROM `maincfgtab` WHERE `var` = '%1';").arg(rowname[i]);
		QSqlQuery query(qstr);
		query.next();
		fields.append(query.value(0).toString());
    }
    txtcompany->setText(fields[0]);
    txtaddress->setText(fields[1]);
    txt_bank_name->setText(fields[2]);
    txt_bank_addr->setText(fields[3]);
    txt_bank_clearing->setText(fields[4]);
    txt_bank_accountnr->setText(fields[5]);
    txt_bank_usrnr->setText(fields[6]);
}

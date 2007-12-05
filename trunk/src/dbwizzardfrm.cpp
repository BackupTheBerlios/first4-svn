#include <QPushButton>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
//
#include "dbwizzardfrm.h"
#include "vars.h"
#include "cfgfrm.h"
#include "progfrm.h"
//
extern QString firstver;
//
dbwizzardfrm::dbwizzardfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void dbwizzardfrm::init()
{
	connect(rbtnmysqlex, SIGNAL(clicked()), this, SLOT(enable_next()));
	connect(rbtnmysqlnew, SIGNAL(clicked()), this, SLOT(enable_next()));
	connect(rbtnsqliteex, SIGNAL(clicked()), this, SLOT(enable_next()));
	connect(rbtnsqlitenew, SIGNAL(clicked()), this, SLOT(enable_next()));
	connect(btnnext, SIGNAL(clicked()), this, SLOT(next()));
	connect(btnback, SIGNAL(clicked()), this, SLOT(back()));
	connect(btncheckdb, SIGNAL(released()), this, SLOT(checkdbs()));
	connect(btncancel, SIGNAL(released()), this, SLOT(reject()));  
	connect(btnlitenewdb, SIGNAL(released()), this, SLOT(openfd()));
	connect(btnliteopendb, SIGNAL(released()), this, SLOT(openfd()));
	
	mainstackwidget->setCurrentIndex(0);
}
//
void dbwizzardfrm::next()
{
	int minindex = 0;
	int maxindex = 0;
	if(rbtnmysqlex->isChecked())
	{
		minindex = 1;
		maxindex = 2;
	}
	else if(rbtnmysqlnew->isChecked())
	{
		minindex = 3;
		maxindex = 7;
	}
	else if(rbtnsqliteex->isChecked())
	{
		minindex = 8;
		maxindex = 9;		
	}
	else if(rbtnsqlitenew->isChecked())
	{
		minindex = 10;
		maxindex = 11;
	}
	
	if(mainstackwidget->currentIndex() == maxindex)
	{
		if(rbtnmysqlex->isChecked())
		{
			writeconffile();
		}
		else if(rbtnmysqlnew->isChecked())
		{
			createnewmysql();
		}
		else if(rbtnsqliteex->isChecked())
		{
			writeconffile();	
		}
		else if(rbtnsqlitenew->isChecked())
		{
			createnewsqlite();
		}
	}

	if(mainstackwidget->currentIndex() < maxindex)
	{
		if(mainstackwidget->currentIndex() < minindex)
			mainstackwidget->setCurrentIndex(minindex-1);
		mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()+1);
		if(mainstackwidget->currentIndex() == maxindex)
		{
			btnnext->setText(QApplication::translate("dbwizzardfrm", "&Finish", 0, QApplication::UnicodeUTF8));	
			if(rbtnmysqlex->isChecked())
			{
				lblexhost->setText(txtexhost->text());
				lblexport->setText(txtexport->text());
				lblexuser->setText(txtexuser->text());
				lblexdbname->setText(cmbexdb->currentText().section(" (", 0, 0));
				lblexdbversion->setText(cmbexdb->currentText().section(" (", 1, 1).section(")", 0, 0));
			}
			else if(rbtnmysqlnew->isChecked())
			{
				lblnewhost->setText(txtnewhost->text());
				lblnewport->setText(txtnewport->text());
				lblnewdbname->setText(txtnewdbname->text());
				lblnewuser->setText(txtnewfirstuser->text());
				lblnewuserpass->setText(txtnewfirstpwd->text());
				lblnewadministrators->setText(txtnewadminuser->text());
				lblnewadministratorspass->setText(txtnewfadminpwd->text());
			}
			else if(rbtnsqliteex->isChecked())
			{
				//writeconffile();	
			}
			else if(rbtnsqlitenew->isChecked())
			{
				//createnewsqlite();
			}
		}
		else
		{
			btnnext->setText(QApplication::translate("dbwizzardfrm", "&Next >>", 0, QApplication::UnicodeUTF8));	
		}
	}
}
//
void dbwizzardfrm::back()
{
	int minindex = 0;
	int maxindex = 0;
	btnnext->setText(QApplication::translate("dbwizzardfrm", "&Next >>", 0, QApplication::UnicodeUTF8));
	if(rbtnmysqlex->isChecked())
	{
		minindex = 1;
		maxindex = 2;
	}
	else if(rbtnmysqlnew->isChecked())
	{
		minindex = 3;
		maxindex = 7;
	}
	else if(rbtnsqliteex->isChecked())
	{
		minindex = 8;
		maxindex = 9;		
	}
	else if(rbtnsqlitenew->isChecked())
	{
		minindex = 10;
		maxindex = 11;
	}
	
	if(mainstackwidget->currentIndex() > minindex)
	{
		mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()-1);
	}
	else
		mainstackwidget->setCurrentIndex(0);
}
void dbwizzardfrm::enable_next()
{
	btnnext->setEnabled(TRUE);
}
//
void dbwizzardfrm::checkdbs()
{
    QSqlDatabase checkDB = QSqlDatabase::addDatabase("QMYSQL", "checkdb");
    checkDB.setUserName(txtexuser->text());
    checkDB.setPassword(txtexpwd->text());
    checkDB.setHostName(txtexhost->text());
    checkDB.setPort(txtexport->text().toInt());
    if(checkDB.open())
    {
		// Database successfully opened;
		QSqlQuery query("SHOW DATABASES", checkDB);
		if(query.isActive())
		{
		    while(query.next())
		    {
				QString qstr = "SELECT value FROM maincfgtab WHERE var = 'dbversion';";
				QSqlQuery query2(qstr, checkDB);
				query2.next();
				QString firstversion = query2.value(0).toString();
				if(firstversion == "")
					firstversion = "ERR";
				cmbexdb->insertItem(-1, query.value(0).toString()+" ("+firstversion+")");	
	    	}	
		}
		checkDB.close();
	}
    else
    {
    	QSqlError sqlerror = checkDB.lastError();
		QMessageBox::critical(0,"Error...",tr("Unable to connect to server!")+"\n\n"+sqlerror.text());
    }
	QSqlDatabase::removeDatabase ( "checkdb" );
}
//
void dbwizzardfrm::writeconffile()
{
	QString writestr;
	if(rbtnmysqlex->isChecked() || rbtnmysqlnew->isChecked())
	{
	    if(rbtnmysqlex->isChecked())
			writestr = lblexuser->text() + ":" + txtexpwd->text() + "@" + lblexhost->text() + "/" + lblexdbname->text() + ":" + lblexport->text() + "\n";
		else if(rbtnmysqlnew->isChecked())
			writestr = txtnewfirstuser->text() + ":" + txtnewfirstpwd->text() + "@" + txtnewhost->text() + "/" + txtnewdbname->text() + ":" + txtnewport->text() + "\n";
	}
	else if(rbtnsqliteex->isChecked() || rbtnsqlitenew->isChecked())
	{
		if(rbtnsqliteex->isChecked())
			writestr = txtliteopendb->text();
		else if(rbtnsqlitenew->isChecked())
			writestr = txtnewdbfolder_sqllite->text().replace("\\", "/")+"/"+txtnewdbname_sqllite->text()+".db";
	}
	QMessageBox::critical(0,"Error...", writestr);
    QDir d(QDir::homePath()+"/.first4");
    if(!d.exists() )
	{
		if(!d.mkdir(QDir::homePath()+"/.first4"))
	    	QMessageBox::critical(0,"Error...", tr("Error when storing the server list!"));
    }    
       
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
		int i;
		QTextStream stream(&file);
		bool foundsec = FALSE;
		for(i=0;i<lines.count();i++)
		{
			if(lines[i] == "[SERVERS]")
			{
				foundsec = TRUE;
				stream << lines[i] << "\n";

	    		stream << writestr << "\n";
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
	    	if(rbtnmysqlex->isChecked())
		    	stream << writestr << "\n";
		    else if(rbtnmysqlnew->isChecked())
		    	stream << writestr << "\n";
			stream << "\n";
		}
		file.close();
	}
	else
		QMessageBox::warning(0, "Databases...", "Can't write to configuration file.");
    
    this->accept();
}
//
//
void dbwizzardfrm::createnewmysql()
{
	cfgfrm cfrm;
//Set SqlArray
QStringList mysqsqlcreatelist;
mysqsqlcreatelist << "CREATE TABLE `accounttab` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL,`accountnr` text NOT NULL,`bank` text NOT NULL,`blz` text NOT NULL,`currency` text NOT NULL,`users` text NOT NULL, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `adrtabs` (`ID` int(11) unsigned NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,`idcounter` int(10) unsigned NOT NULL default '0', PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `datatabs` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,`cols` text NOT NULL,`tabtyp` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `docdrafts` (`ID` int(11) NOT NULL auto_increment,`doctyp` text NOT NULL,`date` text NOT NULL,`client` text NOT NULL,`comments` text NOT NULL,`amount` text NOT NULL,`discount` text NOT NULL,`docID` text NOT NULL,`salutation` text NOT NULL,`introduction` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `docpositions` (`ID` int(11) NOT NULL auto_increment,`DOCID` text NOT NULL,`STOCK` text NOT NULL,`STOCK_ID` text NOT NULL,`DOC_POSITION` int(11) NOT NULL default '0',`LABEL` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` float NOT NULL default '0',`UNIT` text NOT NULL,`PRICE` float NOT NULL default '0',`VAT` float NOT NULL default '0',`TYPE` char(10) default NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `docs` (`ID` int(11) NOT NULL auto_increment,`doctyp` text NOT NULL,`date` text NOT NULL,`client` text NOT NULL,`comments` text NOT NULL,`amount` text NOT NULL,`discount` text NOT NULL,`docID` text NOT NULL,`salutation` text NOT NULL,`introduction` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `doctab` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`filename` text NOT NULL,`count` text NOT NULL,`users` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `doctab` WRITE;";
mysqsqlcreatelist << "INSERT INTO `doctab` VALUES (1,'1 offer','','0001',''),(2,'2 orderconf','','0001',''),(3,'3 deliverynote','/','0001',''),(4,'4 bill','','0002','');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `invcfgtab` (`ID` int(11) NOT NULL auto_increment,`USERS` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `invcfgtab` WRITE;";
mysqsqlcreatelist << "INSERT INTO `invcfgtab` VALUES (1,'');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `invtab` (`ID` int(11) NOT NULL auto_increment,`NAME` text NOT NULL,`DATATABLE` text NOT NULL,`TABLENAME` text NOT NULL,`DATE` text NOT NULL,`USERS` text NOT NULL,`FINISHED` text NOT NULL,`COMMENTS` text,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `maincfgtab` (`ID` int(11) NOT NULL auto_increment,`var` text NOT NULL,`value` text NOT NULL, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `maincfgtab` WRITE;";
mysqsqlcreatelist << "INSERT INTO `maincfgtab` VALUES (1,'docfolder',''),(2,'templatefolder',''),(3,'dbversion','"+firstver+"'),(4,'company','"+txtcompany->text()+"'),(5,'companyaddress','"+txtstreetnr->text()+"'),(6,'bankname',''),(7,'bankaddress',''),(8,'bankblz',''),(9,'bankaccountnr',''),(10,'banktnr',''),(11,'docpref',''),(12,'DoG','');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `msgcfgtab` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `msgcfgtab` WRITE;";
mysqsqlcreatelist << "INSERT INTO `msgcfgtab` VALUES (1,'gen','1 general',''),(2,'sto','2 stock',''),(3,'ord','3 order',''),(4,'iem','4 incexp','');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `orderscfgtab` (`ID` int(11) NOT NULL auto_increment,`USERS` text NOT NULL,`COUNTER` int(11) NOT NULL default '0',PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `orderscfgtab` WRITE;";
mysqsqlcreatelist << "INSERT INTO `orderscfgtab` VALUES (1,'',5000);";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `orderstab` (`ID` int(11) NOT NULL auto_increment,`STATUS` int(11) NOT NULL default '0',`ORDERED_BY` text NOT NULL,`FOR_ORDER` int(11) NOT NULL default '0',`STOCK` text NOT NULL,`DATE1` date NOT NULL default '0000-00-00',`DATE2` date NOT NULL default '0000-00-00',`DATE3` date NOT NULL default '0000-00-00',`DEF` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` int(11) NOT NULL default '0',`SUPPLIER` text NOT NULL,`PRICE` text NOT NULL,`COMMENTS` text NOT NULL, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `procedurearchiv` (`ID` int(11) NOT NULL auto_increment,`status` text NOT NULL,`completed` text NOT NULL,`priority` text NOT NULL,`date` date NOT NULL default '0000-00-00',`client` text NOT NULL,`contactperson` text NOT NULL,`orderid` text NOT NULL,`description` text NOT NULL,`resp_person` text NOT NULL,`complete_until` date NOT NULL default '0000-00-00',`tasks` text NOT NULL,`orders` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `procedurecfgtab` (`ID` int(11) NOT NULL auto_increment,`users` text NOT NULL,`auftrid` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `procedurecfgtab` WRITE;";
mysqsqlcreatelist << "INSERT INTO `procedurecfgtab` VALUES (1,'','0');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `procedureorders` (`ID` int(11) NOT NULL auto_increment,`PROC_ID` text NOT NULL,`STOCK` text NOT NULL,`STOCK_ID` text NOT NULL,`STATE` char(1) NOT NULL default '0',`LABEL` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` float NOT NULL default '0',`UNIT` text NOT NULL,`PRICE` float NOT NULL default '0',`VAT` float NOT NULL default '0',PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `proceduretab` (`ID` int(11) NOT NULL auto_increment,`status` text NOT NULL,`completed` text NOT NULL,`priority` text NOT NULL,`date` date NOT NULL default '0000-00-00',`client` text NOT NULL,`contactperson` text NOT NULL,`orderid` text NOT NULL,`description` text NOT NULL,`resp_person` text NOT NULL,`complete_until` date NOT NULL default '0000-00-00', PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `proceduretasks` (`ID` int(11) NOT NULL auto_increment,`PROC_ID` text,`STATE` int(11) default NULL,`TASK` text,`DATE` text,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `userstab` (`ID` int(11) NOT NULL auto_increment,`username` text character set latin1 NOT NULL,`userpass` text character set latin1 NOT NULL,`fullname` text character set latin1 NOT NULL,`firstname` text character set latin1 NOT NULL,`lastname` text character set latin1 NOT NULL,`dob` date NOT NULL default '0000-00-00',`p_street` text character set latin1 NOT NULL,`p_zip` text character set latin1 NOT NULL,`p_location` text character set latin1 NOT NULL,`p_country` text character set latin1 NOT NULL,`b_street` text character set latin1 NOT NULL,`b_zip` text character set latin1 NOT NULL,`b_location` text character set latin1 NOT NULL,`b_country` text character set latin1 NOT NULL,`profession` text character set latin1 NOT NULL,`org_unit` text character set latin1 NOT NULL,`position` text character set latin1 NOT NULL,`emp_type` text character set latin1 NOT NULL,`p_tel` text character set latin1 NOT NULL,`p_fax` text character set latin1 NOT NULL,`p_mobile` text character set latin1 NOT NULL,`p_pager` text character set latin1 NOT NULL,`p_ip` text character set latin1 NOT NULL,`email1` text character set latin1 NOT NULL,`email2` text character set latin1 NOT NULL,`email3` text character set latin1 NOT NULL,`p_web` text character set latin1 NOT NULL,`b_tel` text character set latin1 NOT NULL,`b_teldir` text character set latin1 NOT NULL,`b_fax` text character set latin1 NOT NULL,`b_mobile` text character set latin1 NOT NULL,`b_pager` text character set latin1 NOT NULL,`b_ip` text character set latin1 NOT NULL,`email4` text character set latin1 NOT NULL,`email5` text character set latin1 NOT NULL,`email6` text character set latin1 NOT NULL,`notes` text character set latin1 NOT NULL,`emp_grade` text character set latin1 NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `userstab` WRITE;";
mysqsqlcreatelist << "INSERT INTO `userstab` VALUES (11,'Administrator','"+cfrm.cryptpwd(txtnewfadminpwd->text())+"','Administrator','','','0000-00-00','','','','0','','','','','','','','','','','','','','','','','','','','','','','','','','','','');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `vattab` (`ID` int(11) NOT NULL auto_increment,`col1` text NOT NULL,`col2` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "INSERT INTO datatabs (name, description, users, cols, tabtyp) VALUES ('vattab', 'VAT-Table', '"+txtnewadminuser->text()+" [11] , ', 'Tax:70#Comments:200', 'vattab');";
//	

	QSqlError sqlerror;
    QSqlDatabase checkDB = QSqlDatabase::addDatabase("QMYSQL");
    checkDB.setDatabaseName("mysql");
    checkDB.setHostName(txtnewhost->text());
    checkDB.setUserName(txtnewuser->text());
    checkDB.setPassword(txtnewpwd->text());
    checkDB.setPort(txtnewport->text().toInt());
    if(checkDB.open())
    {
    	QString qstr_newdb = QString("CREATE DATABASE %1").arg(txtnewdbname->text()); //creating database
		QSqlQuery query_newdb(qstr_newdb);
		sqlerror = query_newdb.lastError();
		if(sqlerror.isValid())
			QMessageBox::critical(0,"Error...",sqlerror.text());
			
    	QString qstr_privileges = QString("GRANT ALL PRIVILEGES ON %1.* TO '%2'@'%' IDENTIFIED BY '%3'").arg(txtnewdbname->text()).arg(txtnewfirstuser->text()).arg(txtnewfirstpwd->text()); //grant privileges
		QSqlQuery query_privileges(qstr_privileges);
		QMessageBox::critical(0,"Error...",qstr_privileges);
		sqlerror = query_privileges.lastError();
		if(sqlerror.isValid())
			QMessageBox::critical(0,"Error...",sqlerror.text());
		checkDB.close();
	}
    else
    {
    	QSqlError sqlerror = checkDB.lastError();
		QMessageBox::critical(0,"Error...",tr("Unable to connect to server!")+"\n\n"+sqlerror.text());
    }
	checkDB.setDatabaseName(txtnewdbname->text());
    if(checkDB.open() && !sqlerror.isValid())
    {
		//Creating tables;
		int i;
		for(i=0;i<mysqsqlcreatelist.size();i++)
		{
			QSqlQuery query_newtables(mysqsqlcreatelist[i]);
			sqlerror = query_newtables.lastError();
			if(sqlerror.isValid())
				QMessageBox::critical(0,"Error...",sqlerror.text());	
		}
		QMessageBox::information(0,"Database created...",tr("Database successfully created."));
		checkDB.close();
	}
	writeconffile(); //schreibe conffile
	this->accept();
}
//
void dbwizzardfrm::createnewsqlite()
{
	cfgfrm cfrm;
	//SQLite Scripts
QStringList sqlitecreatelist;
sqlitecreatelist << "CREATE TABLE `accounttab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`description` text NOT NULL,`accountnr` text NOT NULL,`bank` text NOT NULL,`blz` text NOT NULL,`currency` text NOT NULL,`users` text NOT NULL );";
sqlitecreatelist << "CREATE TABLE `adrtabs` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,`idcounter` integer(10) NOT NULL default '0');";
sqlitecreatelist << "CREATE TABLE `datatabs` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,`cols` text NOT NULL,`tabtyp` text NOT NULL );";
sqlitecreatelist << "CREATE TABLE `docdrafts` (`ID` integer PRIMARY KEY AUTOINCREMENT,`doctyp` text NOT NULL,`date` text NOT NULL,`client` text NOT NULL,`comments` text NOT NULL,`amount` text NOT NULL,`discount` text NOT NULL,`docID` text NOT NULL,`salutation` text NOT NULL,`introduction` text NOT NULL );";
sqlitecreatelist << "CREATE TABLE `docpositions` (`ID` integer PRIMARY KEY AUTOINCREMENT,`DOCID` text NOT NULL,`STOCK` text NOT NULL,`STOCK_ID` text NOT NULL,`DOC_POSITION` int(11) NOT NULL default '0',`LABEL` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` float NOT NULL default '0',`UNIT` text NOT NULL,`PRICE` float NOT NULL default '0',`VAT` float NOT NULL default '0',`TYPE` char(10) default NULL);";

sqlitecreatelist << "CREATE TABLE `docs` (`ID` integer PRIMARY KEY AUTOINCREMENT,`doctyp` text NOT NULL,`date` text NOT NULL,`client` text NOT NULL,`comments` text NOT NULL,`amount` text NOT NULL,`discount` text NOT NULL,`docID` text NOT NULL,`salutation` text NOT NULL,`introduction` text NOT NULL );";
sqlitecreatelist << "CREATE TABLE `doctab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`filename` text NOT NULL,`count` text NOT NULL,`users` text NOT NULL );";

sqlitecreatelist << "INSERT INTO `doctab` VALUES (1,'1 offer','','0001','');";
sqlitecreatelist << "INSERT INTO `doctab` VALUES (2,'2 orderconf','','0001','');";
sqlitecreatelist << "INSERT INTO `doctab` VALUES (3,'3 deliverynote','/','0001','');";
sqlitecreatelist << "INSERT INTO `doctab` VALUES (4,'4 bill','','0002','');";

sqlitecreatelist << "CREATE TABLE `invcfgtab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`USERS` text NOT NULL );";
sqlitecreatelist << "INSERT INTO `invcfgtab` VALUES (1,'');";

sqlitecreatelist << "CREATE TABLE `invtab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`NAME` text NOT NULL,`DATATABLE` text NOT NULL,`TABLENAME` text NOT NULL,`DATE` text NOT NULL,`USERS` text NOT NULL,`FINISHED` text NOT NULL,`COMMENTS` text );";
sqlitecreatelist << "CREATE TABLE `maincfgtab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`var` text NOT NULL,`value` text NOT NULL );";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (1,'docfolder','');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (2,'templatefolder','');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (3,'dbversion','"+firstver+"');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (4,'company','"+txtcompany->text()+"');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (5,'companyaddress','"+txtstreetnr->text()+"');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (6,'bankname','');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (7,'bankaddress','');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (8,'bankblz','');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (9,'bankaccountnr','');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (10,'banktnr','');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (11,'docpref','');";
sqlitecreatelist << "INSERT INTO `maincfgtab` VALUES (12,'DoG','');";

sqlitecreatelist << "CREATE TABLE `msgcfgtab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL );";
sqlitecreatelist << "INSERT INTO `msgcfgtab` VALUES (1,'gen','1 general','');";
sqlitecreatelist << "INSERT INTO `msgcfgtab` VALUES (2,'sto','2 stock','');";
sqlitecreatelist << "INSERT INTO `msgcfgtab` VALUES (3,'ord','3 order','');";
sqlitecreatelist << "INSERT INTO `msgcfgtab` VALUES (4,'iem','4 incexp','');";

sqlitecreatelist << "CREATE TABLE `orderscfgtab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`USERS` text NOT NULL,`COUNTER` int(11) NOT NULL default '0' );";
sqlitecreatelist << "INSERT INTO `orderscfgtab` VALUES (1,'',5000);";

sqlitecreatelist << "CREATE TABLE `orderstab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`STATUS` integer(11) NOT NULL default '0',`ORDERED_BY` text NOT NULL,`FOR_ORDER` int(11) NOT NULL default '0',`STOCK` text NOT NULL,`DATE1` date NOT NULL default '0000-00-00',`DATE2` date NOT NULL default '0000-00-00',`DATE3` date NOT NULL default '0000-00-00',`DEF` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` int(11) NOT NULL default '0',`SUPPLIER` text NOT NULL,`PRICE` text NOT NULL,`COMMENTS` text NOT NULL);";
sqlitecreatelist << "CREATE TABLE `procedurearchiv` (`ID` integer PRIMARY KEY AUTOINCREMENT,`status` text NOT NULL,`completed` text NOT NULL,`priority` text NOT NULL,`date` date NOT NULL default '0000-00-00',`client` text NOT NULL,`contactperson` text NOT NULL,`orderid` text NOT NULL,`description` text NOT NULL,`resp_person` text NOT NULL,`complete_until` date NOT NULL default '0000-00-00',`tasks` text NOT NULL,`orders` text NOT NULL) ;";
sqlitecreatelist << "CREATE TABLE `procedurecfgtab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`users` text NOT NULL,`auftrid` text NOT NULL );";
sqlitecreatelist << "INSERT INTO `procedurecfgtab` VALUES (1,'','0');";

sqlitecreatelist << "CREATE TABLE `procedureorders` (`ID` integer PRIMARY KEY AUTOINCREMENT,`PROC_ID` text NOT NULL,`STOCK` text NOT NULL,`STOCK_ID` text NOT NULL,`STATE` char(1) NOT NULL default '0',`LABEL` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` float NOT NULL default '0',`UNIT` text NOT NULL,`PRICE` float NOT NULL default '0',`VAT` float NOT NULL default '0' );";
sqlitecreatelist << "CREATE TABLE `proceduretab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`status` text NOT NULL,`completed` text NOT NULL,`priority` text NOT NULL,`date` date NOT NULL default '0000-00-00',`client` text NOT NULL,`contactperson` text NOT NULL,`orderid` text NOT NULL,`description` text NOT NULL,`resp_person` text NOT NULL,`complete_until` date NOT NULL default '0000-00-00' ) ;";
sqlitecreatelist << "CREATE TABLE `proceduretasks` (`ID` integer PRIMARY KEY AUTOINCREMENT,`PROC_ID` text,`STATE` int(11) default NULL,`TASK` text,`DATE` text ) ;";
sqlitecreatelist << "CREATE TABLE `userstab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`username` text NOT NULL,`userpass` text NOT NULL,`fullname` text NOT NULL,`firstname` text NOT NULL,`lastname` text NOT NULL,`dob` date NOT NULL default '0000-00-00',`p_street` text NOT NULL,`p_zip` text NOT NULL,`p_location` text NOT NULL,`p_country` text NOT NULL,`b_street` text NOT NULL,`b_zip` text NOT NULL,`b_location` text NOT NULL,`b_country` text NOT NULL,`profession` text NOT NULL,`org_unit` text NOT NULL,`position` text NOT NULL,`emp_type` text NOT NULL,`p_tel` text NOT NULL,`p_fax` text NOT NULL,`p_mobile` text NOT NULL,`p_pager` text NOT NULL,`p_ip` text NOT NULL,`email1` text NOT NULL,`email2` text NOT NULL,`email3` text NOT NULL,`p_web` text NOT NULL,`b_tel` text NOT NULL,`b_teldir` text NOT NULL,`b_fax` text NOT NULL,`b_mobile` text NOT NULL,`b_pager` text NOT NULL,`b_ip` text NOT NULL,`email4` text NOT NULL,`email5` text NOT NULL,`email6` text NOT NULL,`notes` text NOT NULL,`emp_grade` text NOT NULL ) ;";
sqlitecreatelist << "INSERT INTO `userstab` VALUES (11,'Administrator','"+cfrm.cryptpwd(txtnewfadminpwd->text())+"','Administrator','','','0000-00-00','','','','0','','','','','','','','','','','','','','','','','','','','','','','','','','','','');";

sqlitecreatelist << "CREATE TABLE `vattab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`col1` text NOT NULL,`col2` text NOT NULL);";
sqlitecreatelist << "INSERT INTO datatabs (name, description, users, cols, tabtyp) VALUES ('vattab', 'VAT-Table', '"+txtnewadminuser->text()+" [11] , ', 'Tax:70#Comments:200', 'vattab');";

	progfrm pfrm;
	pfrm.progbar->setMaximum(sqlitecreatelist.count());
	pfrm.txtcomments->setText(tr("Initializing database..."));
	pfrm.show();

	QSqlError sqlerror;
    QSqlDatabase checkDB = QSqlDatabase::addDatabase("QSQLITE");
    checkDB.setDatabaseName(txtnewdbfolder_sqllite->text()+"/"+txtnewdbname_sqllite->text()+".db"); 
    
    if(checkDB.open())
    {
		//Creating tables;
		int i;
		for(i=0;i<sqlitecreatelist.size();i++)
		{
			QSqlQuery query_newtables(sqlitecreatelist[i]);
			sqlerror = query_newtables.lastError();
			if(sqlerror.isValid())
				QMessageBox::critical(0,"Error...", sqlitecreatelist[i] + "\n" + sqlerror.text());	
			pfrm.progbar->setValue(i);
		}
		pfrm.close();
		QMessageBox::information(0,"Database created...",tr("Database successfully created."));
		checkDB.close();
	}
    else
    {
    	QSqlError sqlerror = checkDB.lastError();
		QMessageBox::critical(0,"Error...",tr("Unable to connect to database!")+"\n\n"+sqlerror.text());
    }
    
	writeconffile(); //schreibe conffile
	this->accept();
}
//
void dbwizzardfrm::openfd()
{
	QObject *toolobj = QObject::sender();
	if(toolobj->objectName() == "btnlitenewdb")
	{
		QString foldername = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
								QDir::rootPath(),
								QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks); 
		txtnewdbfolder_sqllite->setText(foldername);
	}
	else if(toolobj->objectName() == "btnliteopendb")
	{
		QString filename = QFileDialog::getOpenFileName ( this, tr ( "Open SQLite DB-File" ),
							QDir::rootPath(),
							tr ( "SQLite3 File (*.db)" ) );
		txtliteopendb->setText(filename);
	}
}

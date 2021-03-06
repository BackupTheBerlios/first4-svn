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
	this->setFixedSize ( this->width(), this->height() );
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
		btnnext->setEnabled(FALSE);
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
		
		// Check if DB-Name, DB-firts4-User and DB-first4-password is defined	
		if(rbtnmysqlnew->isChecked() && mainstackwidget->currentIndex() == minindex+1)
		{
			if(txtnewdbname->text() != "" && txtnewfirstuser->text() != "")
			{
				if(txtnewfirstpwd->text() == "")
				{
					int answ = QMessageBox::information(0, tr("No password defined..."), tr("For security it is better to define a passwort for the connection.\n\nDo you like to define one?"), QMessageBox::Yes, QMessageBox::No);
					if(answ == QMessageBox::No)
						mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()+1); 
				}
				else
					mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()+1);	
			}
			else
				QMessageBox::critical(0,"Error...", tr("Please define the following settings:\nDB-Name, first4-User."));
		}
		else if(rbtnmysqlnew->isChecked() && mainstackwidget->currentIndex() == minindex) // Check if DB-Host, DB-Port, DB-User and DB-Password is defined
		{
			if(txtnewhost->text() != "" && txtnewport->text() != "" && txtnewuser->text() != "")
				mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()+1);
			else
				QMessageBox::critical(0,"Error...", tr("Please define the following settings:\nDB-Host, DB-Port and DB-User (normally root)\nIn some case you must also define a password."));
		}
		else
			mainstackwidget->setCurrentIndex(mainstackwidget->currentIndex()+1);
			
		if(mainstackwidget->currentIndex() == maxindex)
		{
			btnnext->setText(QApplication::translate("dbwizzardfrm", "&Finish", 0, QApplication::UnicodeUTF8));	
			if(rbtnmysqlex->isChecked())
			{
				btnnext->setEnabled(TRUE);
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
	{
		cmbexdb->clear();
		btnnext->setEnabled(FALSE);
		QSqlDatabase checkDB = QSqlDatabase::addDatabase("QMYSQL", "checkdb");
		checkDB.setUserName(txtexuser->text());
		checkDB.setPassword(txtexpwd->text());
		checkDB.setHostName(txtexhost->text());
		checkDB.setPort(txtexport->text().toInt());
		if(checkDB.isOpen ())
			 checkDB.close();
		if(checkDB.open())
		{
			// Database successfully opened;
			QSqlQuery query("SHOW DATABASES", checkDB);
			if(query.isActive())
			{
				while(query.next())
					cmbexdb->insertItem(-1, query.value(0).toString());
			}
		}
		else
		{
			QSqlError sqlerror = checkDB.lastError();
			QMessageBox::critical(0,"Error...",tr("Unable to connect to server!")+"\n\n"+sqlerror.text());
		}
		checkDB.close();
		if(cmbexdb->count() > 0)
			btnnext->setEnabled(TRUE);
	}
	QSqlDatabase::removeDatabase("checkdb");
}
//
void dbwizzardfrm::writeconffile()
{
	QString writestr;
	if(rbtnmysqlex->isChecked() || rbtnmysqlnew->isChecked())
	{
	    if(rbtnmysqlex->isChecked())
			writestr = "MYSQL:" + lblexuser->text() + ":" + txtexpwd->text() + "@" + lblexhost->text() + "/" + lblexdbname->text() + ":" + lblexport->text();
		else if(rbtnmysqlnew->isChecked())
			writestr = "MYSQL:" + txtnewfirstuser->text() + ":" + txtnewfirstpwd->text() + "@" + txtnewhost->text() + "/" + txtnewdbname->text() + ":" + txtnewport->text();
	}
	else if(rbtnsqliteex->isChecked() || rbtnsqlitenew->isChecked())
	{
		if(rbtnsqliteex->isChecked())
			writestr = "SQLITE:" + txtliteopendb->text();
		else if(rbtnsqlitenew->isChecked())
			writestr = "SQLITE:" + txtnewdbfolder_sqllite->text().replace("\\", "/")+"/"+txtnewdbname_sqllite->text()+".db";
	}

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
mysqsqlcreatelist << "CREATE TABLE `accounts` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL,`accountnr` text NOT NULL,`bank` text NOT NULL,`blz` text NOT NULL,`currency` text NOT NULL,`users` text NOT NULL, `type` TEXT, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "INSERT INTO accounts VALUES ('','incexp', 'Incomes / Expenditures','','','','','', 'local');";
mysqsqlcreatelist << "INSERT INTO accounts VALUES ('','incexparchive', 'Archive','','','','','', 'local');";
mysqsqlcreatelist << "CREATE TABLE `directories` (`ID` int(11) unsigned NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,`idcounter` int(10) unsigned NOT NULL default '0', PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `datatables` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,`cols` text NOT NULL,`tabtyp` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `documentdrafts` (`ID` int(11) NOT NULL auto_increment,`doctyp` text NOT NULL,`date` text NOT NULL,`client` text NOT NULL,`comments` text NOT NULL,`amount` text NOT NULL,`discount` text NOT NULL,`docID` text NOT NULL,`salutation` text NOT NULL,`introduction` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `documentpositions` (`ID` int(11) auto_increment,`DOCID` text,`STOCK` text, `STOCK_ID` text, `DOC_POSITION` int(11), `LABEL` text, `DESCRIPTION` text, `QUANTITY` float, `UNIT` text, `PRICE` float, `VAT` float, `TYPE` char(20) default NULL, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `documents` (`ID` int(11) NOT NULL auto_increment, `doctyp` text NOT NULL, `date` text NOT NULL, `client` text NOT NULL, `comments` text NOT NULL, `amount` text NOT NULL, `discount` text NOT NULL, `docID` text NOT NULL, `salutation` text NOT NULL, `introduction` text NOT NULL, `orderID` text, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `documentcfg` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`templateid` INT(11) NOT NULL,`count` text NOT NULL,`users` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `documentcfg` WRITE;";
mysqsqlcreatelist << "INSERT INTO `documentcfg` VALUES ('','1 offer','','0001',''),('','2 orderconf','','0001',''),('','3 deliverynote','/','0001',''),('','4 invoice','','0002','');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `incexp` (`ID` int(11) NOT NULL auto_increment, `refnr` text NOT NULL, `type` text NOT NULL, `state` text NOT NULL, `date` date NOT NULL default '0000-00-00', `address` text NOT NULL, `description` text NOT NULL, `code` text NOT NULL, `amount` text NOT NULL, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `incexparchive` (`ID` int(11) NOT NULL auto_increment, `refnr` text NOT NULL, `type` text NOT NULL, `state` text NOT NULL, `date` date NOT NULL default '0000-00-00', `address` text NOT NULL, `description` text NOT NULL, `code` text NOT NULL, `amount` text NOT NULL, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `inventorycfg` (`ID` int(11) NOT NULL auto_increment,`USERS` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `inventorycfg` WRITE;";
mysqsqlcreatelist << "INSERT INTO `inventorycfg` VALUES ('','');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `inventories` (`ID` int(11) NOT NULL auto_increment,`NAME` text NOT NULL,`DATATABLE` text NOT NULL,`TABLENAME` text NOT NULL,`DATE` text NOT NULL,`USERS` text NOT NULL,`FINISHED` text NOT NULL,`COMMENTS` text,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `maincfg` (`ID` int(11) NOT NULL auto_increment,`var` text NOT NULL,`value` text NOT NULL, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `maincfg` WRITE;";
mysqsqlcreatelist << "INSERT INTO `maincfg` VALUES ('','docfolder',''),('','dbversion','"+firstver+"'),('','company','"+txtcompany->text()+"'),('','companyaddress','"+txtstreetnr->text()+"'),('','companylocation','"+txtcity->text()+"'),('','companyzip','"+txtzip->text()+"'),('','companycountry',''),('','bankname',''),('','bankaddress',''),('','bankblz',''),('','bankaccountnr',''),('','banktnr',''),('','docpref',''),('','DoG',''),('','tool_lnx_dvi2ps','dvips'),('','tool_lnx_dviview','kdvi'),('','tool_lnx_print','kprint'),('','tool_lnx_tex2dvi','latex');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `messages` (`ID` int(11) NOT NULL auto_increment, `typ` text NOT NULL, `user` text NOT NULL,  `date` date NOT NULL default '0000-00-00',`msgtext` text NOT NULL,`data1` text NOT NULL,`data2` text NOT NULL,`data3` text NOT NULL,`data4` text NOT NULL,`data5` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `messagecfg` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `messagecfg` WRITE;";
mysqsqlcreatelist << "INSERT INTO `messagecfg` VALUES ('','gen','1 general',''),('','sto','2 stock',''),('','ord','3 order',''),('','iem','4 incexp','');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `ordercfg` (`ID` int(11) NOT NULL auto_increment,`USERS` text NOT NULL,`COUNTER` int(11) NOT NULL default '0',PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `ordercfg` WRITE;";
mysqsqlcreatelist << "INSERT INTO `ordercfg` VALUES (1,'',5000);";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `orders` (`ID` int(11) NOT NULL auto_increment,`STATUS` int(11) NOT NULL default '0',`ORDERED_BY` text NOT NULL,`FOR_ORDER` int(11) NOT NULL default '0',`STOCK` text NOT NULL,`DATE1` date NOT NULL default '0000-00-00',`DATE2` date NOT NULL default '0000-00-00',`DATE3` date NOT NULL default '0000-00-00',`DEF` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` int(11) NOT NULL default '0',`SUPPLIER` text NOT NULL,`PRICE` text NOT NULL,`COMMENTS` text NOT NULL, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `procedurearchive` (`ID` int(11) NOT NULL auto_increment,`status` text NOT NULL,`completed` text NOT NULL,`priority` text NOT NULL,`date` date NOT NULL default '0000-00-00',`client` text NOT NULL,`contactperson` text NOT NULL,`orderid` text NOT NULL,`description` text NOT NULL,`resp_person` text NOT NULL,`complete_until` date NOT NULL default '0000-00-00',`tasks` text NOT NULL,`orders` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `procedurecfg` (`ID` int(11) NOT NULL auto_increment,`users` text NOT NULL,`auftrid` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `procedurecfg` WRITE;";
mysqsqlcreatelist << "INSERT INTO `procedurecfg` VALUES (1,'','0');";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `procedureorders` (`ID` int(11) NOT NULL auto_increment, `PROC_ID` text, `STOCK` text, `STOCK_ID` text, `STATE` char(1), `LABEL` text, `DESCRIPTION` text, `QUANTITY` float, `UNIT` text, `PRICE` float, `VAT` float, PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `procedures` (`ID` int(11) NOT NULL auto_increment,`status` text NOT NULL,`completed` text NOT NULL,`priority` text NOT NULL,`date` date NOT NULL default '0000-00-00',`client` text NOT NULL,`contactperson` text NOT NULL,`orderid` text NOT NULL,`description` text NOT NULL,`resp_person` text NOT NULL,`complete_until` date NOT NULL default '0000-00-00', PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `proceduretasks` (`ID` int(11) NOT NULL auto_increment,`PROC_ID` text,`STATE` int(11) default NULL,`TASK` text,`DATE` text,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "CREATE TABLE `users` (`ID` int(11) NOT NULL auto_increment,`username` text character set latin1 NOT NULL,`userpass` text character set latin1 NOT NULL,`fullname` text character set latin1 NOT NULL,`firstname` text character set latin1 NOT NULL,`lastname` text character set latin1 NOT NULL,`dob` date NOT NULL default '0000-00-00',`p_street` text character set latin1 NOT NULL,`p_zip` text character set latin1 NOT NULL,`p_location` text character set latin1 NOT NULL,`p_country` text character set latin1 NOT NULL,`b_street` text character set latin1 NOT NULL,`b_zip` text character set latin1 NOT NULL,`b_location` text character set latin1 NOT NULL,`b_country` text character set latin1 NOT NULL,`profession` text character set latin1 NOT NULL,`org_unit` text character set latin1 NOT NULL,`position` text character set latin1 NOT NULL,`emp_type` text character set latin1 NOT NULL,`p_tel` text character set latin1 NOT NULL,`p_fax` text character set latin1 NOT NULL,`p_mobile` text character set latin1 NOT NULL,`p_pager` text character set latin1 NOT NULL,`p_ip` text character set latin1 NOT NULL,`email1` text character set latin1 NOT NULL,`email2` text character set latin1 NOT NULL,`email3` text character set latin1 NOT NULL,`p_web` text character set latin1 NOT NULL,`b_tel` text character set latin1 NOT NULL,`b_teldir` text character set latin1 NOT NULL,`b_fax` text character set latin1 NOT NULL,`b_mobile` text character set latin1 NOT NULL,`b_pager` text character set latin1 NOT NULL,`b_ip` text character set latin1 NOT NULL,`email4` text character set latin1 NOT NULL,`email5` text character set latin1 NOT NULL,`email6` text character set latin1 NOT NULL,`notes` text character set latin1 NOT NULL,`emp_grade` text character set latin1 NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `users` WRITE;";
mysqsqlcreatelist << "INSERT INTO `users` VALUES ('','Administrator','"+cfrm.cryptpwd(txtnewfadminpwd->text())+"','Administrator','','','0000-00-00','','','','0','','','','','','','','','','','','','','','','','','','','','','','','','','','','');";
mysqsqlcreatelist << "UPDATE users SET ID='0';";
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `templates` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL, `data` mediumtext NOT NULL,`created_by` text NOT NULL,`created` date NOT NULL default '0000-00-00',`modificated_by` text NOT NULL, `modificated` date NOT NULL default '0000-00-00',   PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "LOCK TABLES `templates` WRITE;";
mysqsqlcreatelist << QString("INSERT INTO `templates` VALUES ('','Offer','Default Offer template','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Offer}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n  \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline\\newline}\n    \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2cm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{70mm} r @{\\hspace{1mm}}l R{25mm} R{25mm} r}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushright}\n\\begin{small}\n\\begin{tabular}{ @{}l  r  r}\n+++DISCOUNT+++\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTEXCL_DESC+++}} & \\textbf{+++TOTEXCL+++} \\\\\n\\hline \n+++VAT+++\n\\hline\n \\\\\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTINCL_DESC+++}} & \\textbf{+++TOTINCL+++} \\\\\n\\hline\n\\hline\n\\end{tabular}\n\\end{small}\n\\end{flushright}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\\\\n &  \\\\\n &  \\\\\n &  \\\\\n------------------------------------------------------ & ------------------------------------------------------ \\\\\n+++USER+++ & +++CUSTOMER+++ \\\\\n\\end{tabular*}\n\\end{small}\n\n\\end{flushleft}\n\n\\end{document}','Administrator','0000-00-00','',''),('','Invoice','Default Invoice template','\n\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Invoice}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n     \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline}\n     \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n& & \\\\\n\\begin{footnotesize}Zahlbar bis: \n+++DoG+++\\end{footnotesize} \\\\\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2mm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{70mm} r @{\\hspace{1mm}}l R{25mm} R{25mm} r}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushright}\n\\begin{small}\n\\begin{tabular}{ @{}l  r  r}\n+++DISCOUNT+++\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTEXCL_DESC+++}} & \\textbf{+++TOTEXCL+++} \\\\\n\\hline \n+++VAT+++\n\\hline\n \\\\\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTINCL_DESC+++}} & \\textbf{+++TOTINCL+++} \\\\\n\\hline\n\\hline\n\\end{tabular}\n\\end{small}\n\\end{flushright}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\\\\n &  \\\\\n &  \\\\\n+++USER+++ & \\\\\n\\end{tabular*}\n\\end{small}\n\n\n\\end{flushleft}\n\n\\end{document}','Administrator','2008-01-23','',''),('','Deliverynote','Default Deliverynote template','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Deliverynote}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n    \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline}\n     \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2cm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{11.5cm} R{3cm} L{1cm}}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\textbf{+++RECIEVED+++}\\\\\n &  \\\\\n &  \\\\\n &  ------------------------------------------------------\\\\\n+++USER+++ & +++CUSTOMER+++\\\\\n\\end{tabular*}\n\\end{small}\n\n\n\\end{flushleft}\n\n\\end{document}','Administrator','2008-01-23','',''),('','Order Confirmation','Default Orderconfirmation template','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Orderconfirmation}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n      \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline}\n     \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2cm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{70mm} r @{\\hspace{1mm}}l R{25mm} R{25mm} r}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushright}\n\\begin{small}\n\\begin{tabular}{ @{}l  r  r}\n+++DISCOUNT+++\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTEXCL_DESC+++}} & \\textbf{+++TOTEXCL+++} \\\\\n\\hline \n+++VAT+++\n\\hline\n \\\\\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTINCL_DESC+++}} & \\textbf{+++TOTINCL+++} \\\\\n\\hline\n\\hline\n\\end{tabular}\n\\end{small}\n\\end{flushright}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\\\\n &  \\\\\n &  \\\\\n &  \\\\\n+++USER+++ &  \\\\\n\\end{tabular*}\n\\end{small}\n\n\n\\end{flushleft}\n\n\\end{document}','Administrator','2008-01-23','','');").replace("\\", "\\\\");
mysqsqlcreatelist << QString("INSERT INTO `templates` VALUES ('','sys_inventory','Default Inventory template','\\documentclass[landscape,a4paper,10pt]{report}\n\\special{landscape}\n\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=1.5cm,right=1.5cm,top=1.5cm,bottom=1.5cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0.5pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\\lhead{\\sffamily \\begin{large}+++TITLE+++\\end{large}}\n\\lfoot{\\sffamily \\begin{tiny}Seite: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}12.02.2006\\end{tiny}}\n\n\\begin{document}\n\\sffamily\n\\begin{flushleft}\n\n\\begin{scriptsize}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}p{4cm} @{}p{9.2cm} p{1.5cm} @{}p{1.5cm} @{}p{1.5cm} |p{1.5cm} |p{1.5cm} |p{3.8cm}}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\end{longtable}\n\\end{scriptsize}\n\n\\end{flushleft}\n\\end{document}','Administrator','2008-01-27','','0000-00-00'),('','sys_address','Default Address template with details','\\documentclass[a4paper,10pt]{report}\n\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=2cm,top=3cm,bottom=2cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Seite: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}12.02.2006\\end{tiny}}\n\n\\begin{document}\n\\sffamily\n\\begin{flushleft}\n\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17cm}{p{3.5cm} p{5cm} p{3.5cm} p{5cm}}\n\\multicolumn{4}{@{}l}{\\begin{large}\\textbf{+++TITLE+++}\\end{large}} \\\\ \\hline \\\\\n+++DATA+++\n\\end{tabular*}\n\\end{small}\n\n\\end{flushleft}\n\\end{document}','Administrator','2008-01-27','','0000-00-00'),('','sys_stocklist','Default Stocklist template','\\documentclass[landscape,a4paper,10pt]{report}\n\\special{landscape}\n\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=2cm,top=1cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0.5pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\\lhead{\\sffamily \\begin{large}###STOCKNAME###\\end{large}}\n\\lfoot{\\sffamily \\begin{tiny}+++PAGE+++ \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\\sffamily\n\\begin{flushleft}\n\n\n\\begin{scriptsize}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{p{4cm}|p{7cm}|p{1cm}|p{1cm}|p{1cm}|p{1cm}|p{1.5cm}|p{1.5cm}|p{5cm}}\n###TABHEAD### \\\\ \\hline\\endhead\n###TABCONTENT###\n\\end{longtable}\n\\end{scriptsize}\n\n\n\\end{flushleft}\n\\end{document}','Administrator','2008-01-29','','0000-00-00'),('','sys_ieoverview','Default Inc/Exp Template','\\documentclass[a4paper,10pt]{report}\n\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=1.5cm,right=1.5cm,top=1.5cm,bottom=1.5cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0.5pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\\lhead{\\sffamily \\begin{large}+++TITLE+++\\end{large}}\n\\lfoot{\\sffamily \\begin{tiny}+++PAGE+++ \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\\sffamily\n\\begin{flushleft}\n\\vspace{2mm}\n\\begin{small}\n\\textbf{Konto-Nr.: }+++ACCOUNTNR+++ \\\\\n\\textbf{Bank: }+++BANK+++ \\\\\n\\textbf{BLZ: }+++CLEARING+++ \\\\\n\\textbf{Währung: }+++CURRENCY+++ \\\\\n\\textbf{Saldo: }+++AMOUNT+++ +++CURRENCY+++ \\\\\n\\textbf{Einnahmen: }+++IN+++ +++CURRENCY+++ \\\\\n\\textbf{Ausgabe: }+++OUT+++ +++CURRENCY+++ \\\\\n\\end{small}\n\\vspace{2mm}\n\\begin{scriptsize}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}p{2cm} @{}p{3cm} @{}p{4cm} p{1cm} @{}p{4cm} @{}p{2cm} @{}p{1cm}}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\end{longtable}\n\\end{scriptsize}\n\n\\end{flushleft}\n\\end{document}','Administrator','2008-01-29','','0000-00-00');").replace("\\", "\\\\");
mysqsqlcreatelist << QString("INSERT INTO `templates` VALUES ('','sys_vesr','VESR default Template (A4)','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{ESR}\n\\author{procopio.ch}\n\n\\usepackage{textpos}\n\\usepackage {multirow}\n\\usepackage{helvet}\n\\usepackage[T1]{fontenc}\n\\usepackage{ocr}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=6mm,right=6mm,top=18.5cm,bottom=6mm]{geometry}\n\n\\newcommand\\topboxX{0mm} \\newcommand\\topboxY{0mm}\n\\newcommand\\topboxW{50mm} \\newcommand\\topboxH{40mm}\n\\textblockorigin{10mm}{10mm}\n\\TPGrid[1mm,1mm]\n\n\\begin{document}\n\\sffamily\n\\begin{textblock*}{\\topboxH}(0,12mm)%\n    \\parbox[t]{\\topboxW}{+++COMPANY+++}\n\\end{textblock*}\n\n\\begin{textblock*}{\\topboxH}(55mm,12mm)%\n    \\parbox[t]{\\topboxW}{+++COMPANY+++}\n\\end{textblock*}\n\n\\begin{textblock*}{10mm}(110mm,32mm)\n    \\parbox[t]{9cm}{\\ocrfamily\\fontsize{10pt}{9.5pt}\\selectfont+++VESR1+++}\n\\end{textblock*}\n\n\\begin{textblock*}{10mm}(20mm,38mm)\n    \\parbox[t]{40mm}{\\flushleft{\\small{+++TNR+++}}}\n\\end{textblock*}\n\n\\begin{textblock*}{10mm}(0,45mm)\n    \\parbox[t]{33mm}{\\flushright{\\ocrfamily+++AMOUNT+++}}\n\\end{textblock*}\n\\begin{textblock*}{10mm}(10mm,45mm)\n    \\parbox[t]{35mm}{\\flushright{\\ocrfamily+++AMOUNTCENTS+++}}\n\\end{textblock*}\n\n\\begin{textblock*}{10mm}(57mm,45mm)\n    \\parbox[t]{33mm}{\\flushright{\\ocrfamily+++AMOUNT+++}}\n\\end{textblock*}\n\\begin{textblock*}{10mm}(67mm,45mm)\n    \\parbox[t]{35mm}{\\flushright{\\ocrfamily+++AMOUNTCENTS+++}}\n\\end{textblock*}\n\n\\begin{textblock*}{10mm}(0,60mm)%\n    \\parbox[t]{\\topboxW}{+++CUSTOMER+++}\n\\end{textblock*}\n\n\\begin{textblock*}{10mm}(112mm,50mm)%\n    \\parbox[t]{\\topboxW}{+++CUSTOMER+++}\n\\end{textblock*}\n\n\\begin{textblock*}{10mm}(60mm,90mm)%\n    \\parbox[t]{14cm}{\\ocrfamily+++VESR2+++}\n\\end{textblock*}\n\n\\end{document}','Administrator','2008-03-18','','0000-00-00');").replace("\\", "\\\\");
mysqsqlcreatelist << "UNLOCK TABLES;";
mysqsqlcreatelist << "CREATE TABLE `vattable` (`ID` int(11) NOT NULL auto_increment,`col1` text NOT NULL,`col2` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << "INSERT INTO datatables (name, description, users, cols, tabtyp) VALUES ('vattable', 'VAT-Table', '"+txtnewadminuser->text()+" [11] , ', 'Tax:70#Comments:200', 'vattable');";
mysqsqlcreatelist << "CREATE TABLE `userlocks` (`ID` int(11) NOT NULL auto_increment, `table` text NOT NULL, `tabid` text NOT NULL,  `user` text NOT NULL, `timestamp` TIMESTAMP NOT NULL , PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
mysqsqlcreatelist << QString("UPDATE maincfg SET value = '%1' WHERE var = 'dbversion';").arg("1.3.98.02");

//	
	progfrm pfrm;
	pfrm.progbar->setMaximum(mysqsqlcreatelist.count());
	pfrm.txtcomments->setText(tr("Initializing database..."));
	pfrm.show();
	QApplication::processEvents();

	QSqlError sqlerror;
	QSqlDatabase createDB = QSqlDatabase::addDatabase("QMYSQL", "createDB");
	createDB.setDatabaseName("mysql");
	createDB.setHostName(txtnewhost->text());
	createDB.setUserName(txtnewuser->text());
	createDB.setPassword(txtnewpwd->text());
	createDB.setPort(txtnewport->text().toInt());
	if(createDB.open())
	{
	    	QString qstr_newdb = QString("CREATE DATABASE %1").arg(txtnewdbname->text()); //creating database
		QSqlQuery query_newdb(qstr_newdb, createDB);
		sqlerror = query_newdb.lastError();
		if(sqlerror.isValid())
			QMessageBox::critical(0,"Error...",sqlerror.text());
		else
		{
			QString qstr_privileges = QString("GRANT ALL PRIVILEGES ON %1.* TO '%2'@'%' IDENTIFIED BY '%3'").arg(txtnewdbname->text()).arg(txtnewfirstuser->text()).arg(txtnewfirstpwd->text()); //grant privileges
			QSqlQuery query_privileges(qstr_privileges, createDB);
			sqlerror = query_privileges.lastError();
			if(sqlerror.isValid())
				QMessageBox::critical(0,"Error...",sqlerror.text());
		}
	}
	else
	{
		sqlerror = createDB.lastError();
		QMessageBox::critical(0,"Error...",tr("Unable to connect to server!")+"\n\n"+sqlerror.text());
	}
	createDB.close();
	QSqlDatabase::removeDatabase("createDB"); 
    
	QSqlDatabase initDB = QSqlDatabase::addDatabase("QMYSQL", "initDB");
	//initDB.setDatabaseName("mysql");
	initDB.setHostName(txtnewhost->text());
	initDB.setUserName(txtnewuser->text());
	initDB.setPassword(txtnewpwd->text());
	initDB.setPort(txtnewport->text().toInt());
	initDB.setDatabaseName(txtnewdbname->text());
	if(!sqlerror.isValid())
	{
	    	if(initDB.open() && !sqlerror.isValid())
		{
			//Creating tables;
			int i;
			for(i=0;i<mysqsqlcreatelist.size();i++)
			{
				QApplication::processEvents();
				QSqlQuery query_newtables(mysqsqlcreatelist[i], initDB);
				sqlerror = query_newtables.lastError();
				if(sqlerror.isValid())
					QMessageBox::critical(0,"Error...",sqlerror.text());
				pfrm.progbar->setValue(i);
			}
			pfrm.close();
			initDB.close();
		}
		writeconffile(); //schreibe conffile
		QMessageBox::information(0,"Database created...",tr("Database successfully created."));
		QSqlDatabase::removeDatabase("initDB");
		this->accept();
	}
	else
	{
		QMessageBox::critical(0,"Database not created...",tr("Database can't be created.\n\nPlease check your settings."));
	}
}
//
void dbwizzardfrm::createnewsqlite()
{
	cfgfrm cfrm;
	//SQLite Scripts
QStringList sqlitecreatelist;
sqlitecreatelist << "CREATE TABLE `accounts` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`description` text NOT NULL,`accountnr` text NOT NULL,`bank` text NOT NULL,`blz` text NOT NULL,`currency` text NOT NULL,`users` text NOT NULL );";
sqlitecreatelist << "CREATE TABLE `adrtabs` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,`idcounter` integer(10) NOT NULL default '0');";
sqlitecreatelist << "CREATE TABLE `datatables` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL,`cols` text NOT NULL,`tabtyp` text NOT NULL );";
sqlitecreatelist << "CREATE TABLE `documentdrafts` (`ID` integer PRIMARY KEY AUTOINCREMENT,`doctyp` text NOT NULL,`date` text NOT NULL,`client` text NOT NULL,`comments` text NOT NULL,`amount` text NOT NULL,`discount` text NOT NULL,`docID` text NOT NULL,`salutation` text NOT NULL,`introduction` text NOT NULL );";
sqlitecreatelist << "CREATE TABLE `documentpositions` (`ID` integer PRIMARY KEY AUTOINCREMENT,`DOCID` text NOT NULL,`STOCK` text NOT NULL,`STOCK_ID` text NOT NULL,`DOC_POSITION` int(11) NOT NULL default '0',`LABEL` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` float NOT NULL default '0',`UNIT` text NOT NULL,`PRICE` float NOT NULL default '0',`VAT` float NOT NULL default '0',`TYPE` char(10) default NULL);";

sqlitecreatelist << "CREATE TABLE `documents` (`ID` integer PRIMARY KEY AUTOINCREMENT,`doctyp` text NOT NULL,`date` text NOT NULL,`client` text NOT NULL,`comments` text NOT NULL,`amount` text NOT NULL,`discount` text NOT NULL,`docID` text NOT NULL,`salutation` text NOT NULL,`introduction` text NOT NULL );";
sqlitecreatelist << "CREATE TABLE `documentcfg` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`filename` text NOT NULL,`count` text NOT NULL,`users` text NOT NULL );";

sqlitecreatelist << "INSERT INTO `documentcfg` VALUES (1,'1 offer','','0001','');";
sqlitecreatelist << "INSERT INTO `documentcfg` VALUES (2,'2 orderconf','','0001','');";
sqlitecreatelist << "INSERT INTO `documentcfg` VALUES (3,'3 deliverynote','/','0001','');";
sqlitecreatelist << "INSERT INTO `documentcfg` VALUES (4,'4 invoice','','0002','');";

sqlitecreatelist << "CREATE TABLE `inventorycfg` (`ID` integer PRIMARY KEY AUTOINCREMENT,`USERS` text NOT NULL );";
sqlitecreatelist << "INSERT INTO `inventorycfg` VALUES (1,'');";

sqlitecreatelist << "CREATE TABLE `inventories` (`ID` integer PRIMARY KEY AUTOINCREMENT,`NAME` text NOT NULL,`DATATABLE` text NOT NULL,`TABLENAME` text NOT NULL,`DATE` text NOT NULL,`USERS` text NOT NULL,`FINISHED` text NOT NULL,`COMMENTS` text );";
sqlitecreatelist << "CREATE TABLE `maincfg` (`ID` integer PRIMARY KEY AUTOINCREMENT,`var` text NOT NULL,`value` text NOT NULL );";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (1,'docfolder','');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (2,'templatefolder','');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (3,'dbversion','"+firstver+"');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (4,'company','"+txtcompany->text()+"');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (5,'companyaddress','"+txtstreetnr->text()+"');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (6,'bankname','');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (7,'bankaddress','');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (8,'bankblz','');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (9,'bankaccountnr','');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (10,'banktnr','');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (11,'docpref','');";
sqlitecreatelist << "INSERT INTO `maincfg` VALUES (12,'DoG','');";

sqlitecreatelist << "CREATE TABLE `msgcfgtab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`name` text NOT NULL,`description` text NOT NULL,`users` text NOT NULL );";
sqlitecreatelist << "INSERT INTO `msgcfgtab` VALUES (1,'gen','1 general','');";
sqlitecreatelist << "INSERT INTO `msgcfgtab` VALUES (2,'sto','2 stock','');";
sqlitecreatelist << "INSERT INTO `msgcfgtab` VALUES (3,'ord','3 order','');";
sqlitecreatelist << "INSERT INTO `msgcfgtab` VALUES (4,'iem','4 incexp','');";

sqlitecreatelist << "CREATE TABLE `ordercfg` (`ID` integer PRIMARY KEY AUTOINCREMENT,`USERS` text NOT NULL,`COUNTER` int(11) NOT NULL default '0' );";
sqlitecreatelist << "INSERT INTO `ordercfg` VALUES (1,'',5000);";

sqlitecreatelist << "CREATE TABLE `orders` (`ID` integer PRIMARY KEY AUTOINCREMENT,`STATUS` integer(11) NOT NULL default '0',`ORDERED_BY` text NOT NULL,`FOR_ORDER` int(11) NOT NULL default '0',`STOCK` text NOT NULL,`DATE1` date NOT NULL default '0000-00-00',`DATE2` date NOT NULL default '0000-00-00',`DATE3` date NOT NULL default '0000-00-00',`DEF` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` int(11) NOT NULL default '0',`SUPPLIER` text NOT NULL,`PRICE` text NOT NULL,`COMMENTS` text NOT NULL);";
sqlitecreatelist << "CREATE TABLE `procedurearchive` (`ID` integer PRIMARY KEY AUTOINCREMENT,`status` text NOT NULL,`completed` text NOT NULL,`priority` text NOT NULL,`date` date NOT NULL default '0000-00-00',`client` text NOT NULL,`contactperson` text NOT NULL,`orderid` text NOT NULL,`description` text NOT NULL,`resp_person` text NOT NULL,`complete_until` date NOT NULL default '0000-00-00',`tasks` text NOT NULL,`orders` text NOT NULL) ;";
sqlitecreatelist << "CREATE TABLE `procedurecfgtab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`users` text NOT NULL,`auftrid` text NOT NULL );";
sqlitecreatelist << "INSERT INTO `procedurecfgtab` VALUES (1,'','0');";

sqlitecreatelist << "CREATE TABLE `procedureorders` (`ID` integer PRIMARY KEY AUTOINCREMENT,`PROC_ID` text NOT NULL,`STOCK` text NOT NULL,`STOCK_ID` text NOT NULL,`STATE` char(1) NOT NULL default '0',`LABEL` text NOT NULL,`DESCRIPTION` text NOT NULL,`QUANTITY` float NOT NULL default '0',`UNIT` text NOT NULL,`PRICE` float NOT NULL default '0',`VAT` float NOT NULL default '0' );";
sqlitecreatelist << "CREATE TABLE `proceduretab` (`ID` integer PRIMARY KEY AUTOINCREMENT,`status` text NOT NULL,`completed` text NOT NULL,`priority` text NOT NULL,`date` date NOT NULL default '0000-00-00',`client` text NOT NULL,`contactperson` text NOT NULL,`orderid` text NOT NULL,`description` text NOT NULL,`resp_person` text NOT NULL,`complete_until` date NOT NULL default '0000-00-00' ) ;";
sqlitecreatelist << "CREATE TABLE `proceduretasks` (`ID` integer PRIMARY KEY AUTOINCREMENT,`PROC_ID` text,`STATE` int(11) default NULL,`TASK` text,`DATE` text ) ;";
sqlitecreatelist << "CREATE TABLE `users` (`ID` integer PRIMARY KEY AUTOINCREMENT,`username` text NOT NULL,`userpass` text NOT NULL,`fullname` text NOT NULL,`firstname` text NOT NULL,`lastname` text NOT NULL,`dob` date NOT NULL default '0000-00-00',`p_street` text NOT NULL,`p_zip` text NOT NULL,`p_location` text NOT NULL,`p_country` text NOT NULL,`b_street` text NOT NULL,`b_zip` text NOT NULL,`b_location` text NOT NULL,`b_country` text NOT NULL,`profession` text NOT NULL,`org_unit` text NOT NULL,`position` text NOT NULL,`emp_type` text NOT NULL,`p_tel` text NOT NULL,`p_fax` text NOT NULL,`p_mobile` text NOT NULL,`p_pager` text NOT NULL,`p_ip` text NOT NULL,`email1` text NOT NULL,`email2` text NOT NULL,`email3` text NOT NULL,`p_web` text NOT NULL,`b_tel` text NOT NULL,`b_teldir` text NOT NULL,`b_fax` text NOT NULL,`b_mobile` text NOT NULL,`b_pager` text NOT NULL,`b_ip` text NOT NULL,`email4` text NOT NULL,`email5` text NOT NULL,`email6` text NOT NULL,`notes` text NOT NULL,`emp_grade` text NOT NULL ) ;";
sqlitecreatelist << "INSERT INTO `users` VALUES (0,'Administrator','"+cfrm.cryptpwd(txtnewfadminpwd->text())+"','Administrator','','','0000-00-00','','','','0','','','','','','','','','','','','','','','','','','','','','','','','','','','','');";

sqlitecreatelist << "CREATE TABLE `vattable` (`ID` integer PRIMARY KEY AUTOINCREMENT,`col1` text NOT NULL,`col2` text NOT NULL);";
sqlitecreatelist << "INSERT INTO datatables (name, description, users, cols, tabtyp) VALUES ('vattable', 'VAT-Table', '"+txtnewadminuser->text()+" [11] , ', 'Tax:70#Comments:200', 'vattable');";

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

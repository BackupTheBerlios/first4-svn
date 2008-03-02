#include <QSqlQuery>
#include <QMessageBox>
//
#include "dbupdatefrm.h"
#include "vars.h"
//
QString newdbver;
//
dbupdatefrm::dbupdatefrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
int dbupdatefrm::init()
{
	this->setFixedSize ( this->width(), this->height() );

	connect ( btncancel, SIGNAL ( released() ), this, SLOT ( reject() ) );
	connect ( btnproceed, SIGNAL ( released() ), this, SLOT ( check_db_structure() ) );

	QString cfgdbver;
	newdbver = "1.4.0.1";
	QSqlQuery query ( "SELECT value FROM maincfgtab WHERE var = 'dbversion';");
	if(query.isActive())
	{
		query.next();
		cfgdbver = query.value ( 0 ).toString();
		lblcurrentversion->setText(cfgdbver);
		lblnewversion->setText(newdbver);
	}

	int retrcode = 0;
	QSqlQuery query1("SHOW TABLES LIKE '%templatestab%';");
	if(query1.size() !=1 )
	  retrcode = 1;
	
	QSqlQuery query2("SHOW TABLES LIKE '%msgtab%';");
	if(query2.size() !=1 )
	  retrcode = 1;
	
	QSqlQuery query3("SHOW COLUMNS FROM doctab WHERE field='filename';");
	if(query3.size() !=0 )
	  retrcode = 1;
	
	QSqlQuery query4("SHOW TABLES LIKE '%userlocktab%';");
	if(query4.size() !=1 )
	  retrcode = 1;

	return retrcode;
	
}
//
void dbupdatefrm::check_db_structure()
{
	    progbar->setMaximum(4);

	    QSqlQuery query1("SHOW TABLES LIKE '%templatestab%';");
	    if(query1.size() !=1 )
		update_db_structure("templates");
	    progbar->setValue(1);
	    
	    QSqlQuery query2("SHOW TABLES LIKE '%msgtab%';");
	    if(query2.size() !=1 )
	      update_db_structure("msg");
	    progbar->setValue(2);
	    
	    QSqlQuery query3("SHOW COLUMNS FROM doctab WHERE field='filename';");
	    if(query3.size() !=0 )
	      update_db_structure("filename2templateid");
	    progbar->setValue(3);

	    QSqlQuery query4("SHOW TABLES LIKE '%userlocktab%';");
	    if(query4.size() !=1 )
	      update_db_structure("userlocktab");
	    progbar->setValue(4);
	    
	QSqlQuery query5(QString("UPDATE maincfgtab SET value = '%1' WHERE var = 'dbversion';").arg(newdbver));
	QMessageBox::information( 0, "DB update..." , "Update completed." );
	this->accept();
}
//
void dbupdatefrm::update_db_structure(QString section)
{
	if(section == "templates")
			{
				QSqlQuery query1("CREATE TABLE `templatestab` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL, `data` mediumtext NOT NULL,`created_by` text NOT NULL,`created` date NOT NULL default '0000-00-00',`modificated_by` text NOT NULL, `modificated` date NOT NULL default '0000-00-00',   PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;");
				QSqlQuery query2("LOCK TABLES `templatestab` WRITE;");
				QSqlQuery query3(QString("INSERT INTO `templatestab` VALUES ('','Offer','Default Offer template','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Offer}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n  \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline\\newline}\n    \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2cm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{70mm} r @{\\hspace{1mm}}l R{25mm} R{25mm} r}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushright}\n\\begin{small}\n\\begin{tabular}{ @{}l  r  r}\n+++DISCOUNT+++\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTEXCL_DESC+++}} & \\textbf{+++TOTEXCL+++} \\\\\n\\hline \n+++VAT+++\n\\hline\n \\\\\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTINCL_DESC+++}} & \\textbf{+++TOTINCL+++} \\\\\n\\hline\n\\hline\n\\end{tabular}\n\\end{small}\n\\end{flushright}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\\\\n &  \\\\\n &  \\\\\n &  \\\\\n------------------------------------------------------ & ------------------------------------------------------ \\\\\n+++USER+++ & +++CUSTOMER+++ \\\\\n\\end{tabular*}\n\\end{small}\n\n\\end{flushleft}\n\n\\end{document}','Administrator','0000-00-00','',''),('','Invoice','Default Invoice template','\n\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Invoice}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n     \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline}\n     \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n& & \\\\\n\\begin{footnotesize}Zahlbar bis: \n+++DoG+++\\end{footnotesize} \\\\\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2mm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{70mm} r @{\\hspace{1mm}}l R{25mm} R{25mm} r}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushright}\n\\begin{small}\n\\begin{tabular}{ @{}l  r  r}\n+++DISCOUNT+++\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTEXCL_DESC+++}} & \\textbf{+++TOTEXCL+++} \\\\\n\\hline \n+++VAT+++\n\\hline\n \\\\\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTINCL_DESC+++}} & \\textbf{+++TOTINCL+++} \\\\\n\\hline\n\\hline\n\\end{tabular}\n\\end{small}\n\\end{flushright}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\\\\n &  \\\\\n &  \\\\\n+++USER+++ & \\\\\n\\end{tabular*}\n\\end{small}\n\n\n\\end{flushleft}\n\n\\end{document}','Administrator','2008-01-23','',''),('','Deliverynote','Default Deliverynote template','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Deliverynote}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n    \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline}\n     \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2cm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{11.5cm} R{3cm} L{1cm}}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\textbf{+++RECIEVED+++}\\\\\n &  \\\\\n &  \\\\\n &  ------------------------------------------------------\\\\\n+++USER+++ & +++CUSTOMER+++\\\\\n\\end{tabular*}\n\\end{small}\n\n\n\\end{flushleft}\n\n\\end{document}','Administrator','2008-01-23','',''),('','Order Confirmation','Default Orderconfirmation template','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Orderconfirmation}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n      \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline}\n     \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2cm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{70mm} r @{\\hspace{1mm}}l R{25mm} R{25mm} r}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushright}\n\\begin{small}\n\\begin{tabular}{ @{}l  r  r}\n+++DISCOUNT+++\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTEXCL_DESC+++}} & \\textbf{+++TOTEXCL+++} \\\\\n\\hline \n+++VAT+++\n\\hline\n \\\\\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTINCL_DESC+++}} & \\textbf{+++TOTINCL+++} \\\\\n\\hline\n\\hline\n\\end{tabular}\n\\end{small}\n\\end{flushright}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\\\\n &  \\\\\n &  \\\\\n &  \\\\\n+++USER+++ &  \\\\\n\\end{tabular*}\n\\end{small}\n\n\n\\end{flushleft}\n\n\\end{document}','Administrator','2008-01-23','','');").replace("\\", "\\\\"));
				QSqlQuery query4(QString("INSERT INTO `templatestab` VALUES ('','sys_inventory','Default Inventory template','\\documentclass[landscape,a4paper,10pt]{report}\n\\special{landscape}\n\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=1.5cm,right=1.5cm,top=1.5cm,bottom=1.5cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0.5pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\\lhead{\\sffamily \\begin{large}+++TITLE+++\\end{large}}\n\\lfoot{\\sffamily \\begin{tiny}Seite: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}12.02.2006\\end{tiny}}\n\n\\begin{document}\n\\sffamily\n\\begin{flushleft}\n\n\\begin{scriptsize}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}p{4cm} @{}p{9.2cm} p{1.5cm} @{}p{1.5cm} @{}p{1.5cm} |p{1.5cm} |p{1.5cm} |p{3.8cm}}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\end{longtable}\n\\end{scriptsize}\n\n\\end{flushleft}\n\\end{document}','Administrator','2008-01-27','','0000-00-00'),('','sys_address','Default Address template with details','\\documentclass[a4paper,10pt]{report}\n\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=2cm,top=3cm,bottom=2cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Seite: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}12.02.2006\\end{tiny}}\n\n\\begin{document}\n\\sffamily\n\\begin{flushleft}\n\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17cm}{p{3.5cm} p{5cm} p{3.5cm} p{5cm}}\n\\multicolumn{4}{@{}l}{\\begin{large}\\textbf{+++TITLE+++}\\end{large}} \\\\ \\hline \\\\\n+++DATA+++\n\\end{tabular*}\n\\end{small}\n\n\\end{flushleft}\n\\end{document}','Administrator','2008-01-27','','0000-00-00'),('','sys_stocklist','Default Stocklist template','\\documentclass[landscape,a4paper,10pt]{report}\n\\special{landscape}\n\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=2cm,top=1cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0.5pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\\lhead{\\sffamily \\begin{large}###STOCKNAME###\\end{large}}\n\\lfoot{\\sffamily \\begin{tiny}+++PAGE+++ \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\\sffamily\n\\begin{flushleft}\n\n\n\\begin{scriptsize}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{p{4cm}|p{7cm}|p{1cm}|p{1cm}|p{1cm}|p{1cm}|p{1.5cm}|p{1.5cm}|p{5cm}}\n###TABHEAD### \\\\ \\hline\\endhead\n###TABCONTENT###\n\\end{longtable}\n\\end{scriptsize}\n\n\n\\end{flushleft}\n\\end{document}','Administrator','2008-01-29','','0000-00-00'),('','sys_ieoverview','Default Inc/Exp Template','\\documentclass[a4paper,10pt]{report}\n\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=1.5cm,right=1.5cm,top=1.5cm,bottom=1.5cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0.5pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\\lhead{\\sffamily \\begin{large}+++TITLE+++\\end{large}}\n\\lfoot{\\sffamily \\begin{tiny}+++PAGE+++ \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\\sffamily\n\\begin{flushleft}\n\\vspace{2mm}\n\\begin{small}\n\\textbf{Konto-Nr.: }+++ACCOUNTNR+++ \\\\\n\\textbf{Bank: }+++BANK+++ \\\\\n\\textbf{BLZ: }+++CLEARING+++ \\\\\n\\textbf{Währung: }+++CURRENCY+++ \\\\\n\\textbf{Saldo: }+++AMOUNT+++ +++CURRENCY+++ \\\\\n\\textbf{Einnahmen: }+++IN+++ +++CURRENCY+++ \\\\\n\\textbf{Ausgabe: }+++OUT+++ +++CURRENCY+++ \\\\\n\\end{small}\n\\vspace{2mm}\n\\begin{scriptsize}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}p{2cm} @{}p{3cm} @{}p{4cm} p{1cm} @{}p{4cm} @{}p{2cm} @{}p{1cm}}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\end{longtable}\n\\end{scriptsize}\n\n\\end{flushleft}\n\\end{document}','Administrator','2008-01-29','','0000-00-00');").replace("\\", "\\\\"));
				QSqlQuery query5("UNLOCK TABLES;");
			}
			else if(section == "msg")
			{
				QSqlQuery query("CREATE TABLE `msgtab` (`ID` int(11) NOT NULL auto_increment, `typ` text NOT NULL, `user` text NOT NULL,  `date` date NOT NULL default '0000-00-00',`msgtext` text NOT NULL,`data1` text NOT NULL,`data2` text NOT NULL,`data3` text NOT NULL,`data4` text NOT NULL,`data5` text NOT NULL,PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;");
			}
			else if(section == "filename2templateid")
			{
				QSqlQuery query1("ALTER TABLE doctab CHANGE filename templateid TEXT;");
				QSqlQuery query2("ALTER TABLE doctab CHANGE templateid templateid INT(11) NOT NULL;");
			}
			else if(section == "userlocktab")
			{
				QSqlQuery query1("SHOW TABLE STATUS WHERE (Name LIKE 'data%' OR Name LIKE 'inv%') AND Engine = 'MyISAM';");
				while(query1.next())
				{
					QString qstr = QString("ALTER TABLE %1 ENGINE = InnoDB;").arg(query1.value(0).toString());
					QSqlQuery query2(qstr);
				}
				QSqlQuery query3("CREATE TABLE `userlocktab` (`ID` int(11) NOT NULL auto_increment, `table` text NOT NULL, `tabid` text NOT NULL,  `user` text NOT NULL, `timestamp` TIMESTAMP NOT NULL , PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;");
			}
}
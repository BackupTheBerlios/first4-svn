#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
//
#include "vars.h"
//
int uid;
QString firstver = "1.3.94-pre-beta1";
QString build = "213";
QString dbhost, dbname, dbuid, dbpwd, dbport;
QString docfolder, templatefolder;
QString username, fullname;

void vars::savegeo(QString frname, bool max, int x, int y, int width, int height)
{
	QStringList lines;
	QString filename;
	if(username != "")
		filename = QDir::homePath() +"/.first4/"+username+".first4.conf";
	else
		filename = QDir::homePath() +"/.first4/local.first4.conf";
	QFile file ( filename );
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
		bool foundfrm = FALSE;
		for(i=0;i<lines.count();i++)
		{
			if(lines[i] == "[WINDOW_POSITIONS]")
				foundsec = TRUE;
			if(foundsec && lines[i].section("=",0,0) == frname && !foundfrm)
			{
				stream << frname << QString("=%1,%2,%3,%4,%5").arg(max).arg(x).arg(y).arg(width).arg(height) << "\n";	
				foundfrm = TRUE;
			}
			else if(foundsec && lines[i].section("=",0,0) == frname && foundfrm) {	}
			else if(foundsec && lines[i].simplified() == "" && !foundfrm)
			{
				stream << frname << QString("=%1,%2,%3,%4,%5").arg(max).arg(x).arg(y).arg(width).arg(height) << "\n\n";
				foundfrm = TRUE;
			}
			else
			{
				stream << lines[i] << "\n";	
			}
		}
		if(!foundsec)
		{
			stream << "\n" << "[WINDOW_POSITIONS]" << "\n";
			stream << frname << QString("=%1,%2,%3,%4,%5").arg(max).arg(x).arg(y).arg(width).arg(height) << "\n";
			stream << "\n";
		}
		if(foundsec && !foundfrm)
		{
			stream << frname << QString("=%1,%2,%3,%4,%5").arg(max).arg(x).arg(y).arg(width).arg(height) << "\n";	
			stream << "\n";
		}
		file.close();
	}
	else
		QMessageBox::warning(0, "Window positions...", "Can't write to configuration file.");
}
//
QStringList vars::loadgeo(QString frmname)
{
    QStringList tmp;
	QString filename;
	if(username != "")
		filename = QDir::homePath() +"/.first4/"+username+".first4.conf";
	else
		filename = QDir::homePath() +"/.first4/local.first4.conf";
	QFile file ( filename );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QString line;
		QTextStream stream ( &file );
		while(stream.readLine() != "[WINDOW_POSITIONS]" && !stream.atEnd());
		do {
			line = stream.readLine();
			if(line.section("=",0,0) == frmname)
		    {
				tmp << line.section(",",0,0);
				tmp << line.section(",",1,1);
				tmp << line.section(",",2,2);
				tmp << line.section(",",3,3);
				tmp << line.section(",",4,5);
		    }
		} while (line != "");
		file.close();
	}
    return tmp;
}
//
void vars::savecolwidth(QString frmname, QString obj, QStringList colwidth)
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
		QTextStream stream(&file);
		bool foundsec = FALSE;
		bool foundobj = FALSE;
		for(i=0;i<lines.count();i++)
		{
			if(lines[i] == "[COLUMNS]")
				foundsec = TRUE;
			if(foundsec && lines[i].section("-",0,0) == frmname && lines[i].section("-", 1, 1).section("-", 0, 0) == obj && !foundobj)
			{
				stream << QString("%1-%2-%3").arg(frmname).arg(obj).arg(colwidth.join(";")) << "\n";
				foundobj = TRUE;
			}
			else if(foundsec && lines[i].section("-",0,0) == frmname && lines[i].section("-", 1, 1).section("-", 0, 0) == obj && foundobj) { }
			else if(foundsec && lines[i].simplified() == "")
			{
				stream << QString("%1-%2-%3").arg(frmname).arg(obj).arg(colwidth.join(";")) << "\n\n";
				foundobj = TRUE;
			}
			else
			{
				stream << lines[i] << "\n";	
			}
		}
		if(!foundsec)
		{
			stream << "\n\n" << "[COLUMNS]" << "\n";
			stream << QString("%1-%2-%3").arg(frmname).arg(obj).arg(colwidth.join(";")) << "\n";
			stream << "\n";
		}
		if(foundsec && ! foundobj)
		{
			stream << QString("%1-%2-%3").arg(frmname).arg(obj).arg(colwidth.join(";")) << "\n";
			stream << "\n";
		}
		file.close();
	}
	else
		QMessageBox::warning(0, "Window positions...", "Can't write to configuration file.");
}
//
QStringList vars::loadcolwidth(QString frmname, QString obj)
{	
	QString line;
	QStringList cols;
	QFile file ( QDir::homePath() +"/.first4/"+username+".first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QTextStream stream ( &file );
		while(stream.readLine() != "[COLUMNS]" && !stream.atEnd());
		do {
			line = stream.readLine();
			if(line.section("-", 0, 0) == frmname && line.section("-", 1, 1).section("-", 0, 0) == obj)
				cols = line.section("-", 2, 2).split(";");
		} while (line != "");
		file.close();
	}
    return cols;
}
//
QString vars::get_tool(QString toolname)
{
	QString tool = "";
	QFile file ( QDir::homePath() +"/.first4/"+username+".first4.conf" );
	if ( file.open ( QIODevice::ReadOnly ) )
	{
		QTextStream stream ( &file );
		QString streamline;
		while(!stream.atEnd())
		{
			streamline = stream.readLine();
			if(streamline.contains(toolname+"=", Qt::CaseSensitive))
				tool = streamline.section("=", 1, 1);
		}
		file.close();
	}
	if(tool == "")
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
		QString qstr1 = QString("SELECT var, value FROM maincfgtab WHERE `var`='tool_%1_"+toolname.toLower()+"';").arg(os);
		QSqlQuery querytools(qstr1);
		if ( querytools.isActive())
		{
			querytools.next();
			tool = querytools.value(1).toString();
		}
		else
		{
			QSqlError sqlerror = querytools.lastError();
			QMessageBox::critical(0,"Error...", "Unable to read settings from database!\n\n"+sqlerror.text());
		}
	}
	return tool;
}
//
int vars::check_db_structure(QString section)
{
	int retrcode = 0;
	if(section == "templates") //beta1
	{
		QSqlQuery query("SHOW TABLES LIKE '%templatestab%';");
		if(query.size() !=1 )
			retrcode = 1;
	}
	else if(section == "msg") //beta1
	{
		QSqlQuery query("SHOW TABLES LIKE '%msgtab%';");
		if(query.size() !=1 )
			retrcode = 1;
	}
	else if(section == "filename2templateid") //beta1
	{
		QSqlQuery query("SHOW COLUMNS FROM doctab WHERE field='filename';");
		if(query.size() !=0 )
			retrcode = 1;
	}
	return retrcode;
}
//
void vars::update_db_structure(QString section)
{
	if(uid != 0)
		QMessageBox::warning( 0, "DB update needed..." , "The database must be updated.\nPlease log-in as Administrator and perform the update." );
	else
	{
		int r = QMessageBox::question ( 0, "DB update..." , "The database must be updated.\nDo you want to do it now?" , QMessageBox::Yes, QMessageBox::No );
		if ( r == QMessageBox::Yes )
		{
			if(section == "templates")
			{
				QSqlQuery query1("CREATE TABLE `templatestab` (`ID` int(11) NOT NULL auto_increment,`name` text NOT NULL,`description` text NOT NULL, `data` mediumtext NOT NULL,`created_by` text NOT NULL,`created` date NOT NULL default '0000-00-00',`modificated_by` text NOT NULL, `modificated` date NOT NULL default '0000-00-00',   PRIMARY KEY  (`ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;");
				QSqlQuery query2("LOCK TABLES `templatestab` WRITE;");
				QSqlQuery query3("INSERT INTO `templatestab` VALUES ('','Offer','Default Offer template','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Offer}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n  \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline\\newline}\n    \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2cm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{70mm} r @{\\hspace{1mm}}l R{25mm} R{25mm} r}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushright}\n\\begin{small}\n\\begin{tabular}{ @{}l  r  r}\n+++DISCOUNT+++\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTEXCL_DESC+++}} & \\textbf{+++TOTEXCL+++} \\\\\n\\hline \n+++VAT+++\n\\hline\n \\\\\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTINCL_DESC+++}} & \\textbf{+++TOTINCL+++} \\\\\n\\hline\n\\hline\n\\end{tabular}\n\\end{small}\n\\end{flushright}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\\\\n &  \\\\\n &  \\\\\n &  \\\\\n------------------------------------------------------ & ------------------------------------------------------ \\\\\n+++USER+++ & +++CUSTOMER+++ \\\\\n\\end{tabular*}\n\\end{small}\n\n\\end{flushleft}\n\n\\end{document}','Administrator','0000-00-00','',''),('','Invoice','Default Invoice template','\n\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Invoice}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n     \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline}\n     \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n& & \\\\\n\\begin{footnotesize}Zahlbar bis: \n+++DoG+++\\end{footnotesize} \\\\\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2mm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{70mm} r @{\\hspace{1mm}}l R{25mm} R{25mm} r}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushright}\n\\begin{small}\n\\begin{tabular}{ @{}l  r  r}\n+++DISCOUNT+++\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTEXCL_DESC+++}} & \\textbf{+++TOTEXCL+++} \\\\\n\\hline \n+++VAT+++\n\\hline\n \\\\\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTINCL_DESC+++}} & \\textbf{+++TOTINCL+++} \\\\\n\\hline\n\\hline\n\\end{tabular}\n\\end{small}\n\\end{flushright}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\\\\n &  \\\\\n &  \\\\\n+++USER+++ & \\\\\n\\end{tabular*}\n\\end{small}\n\n\n\\end{flushleft}\n\n\\end{document}','Administrator','2008-01-23','',''),('','Deliverynote','Default Deliverynote template','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Deliverynote}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n    \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline}\n     \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2cm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{11.5cm} R{3cm} L{1cm}}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\textbf{+++RECIEVED+++}\\\\\n &  \\\\\n &  \\\\\n &  ------------------------------------------------------\\\\\n+++USER+++ & +++CUSTOMER+++\\\\\n\\end{tabular*}\n\\end{small}\n\n\n\\end{flushleft}\n\n\\end{document}','Administrator','2008-01-23','',''),('','Order Confirmation','Default Orderconfirmation template','\\documentclass[a4paper,10pt]{report}\n\n% Title Page\n\\title{Orderconfirmation}\n\\author{procopio.ch}\n\\usepackage{multirow}\n\\usepackage{helvet}\n\\usepackage[utf8]{inputenc}\n\\usepackage[left=2cm,right=1.5cm,top=4cm,bottom=1cm,includeheadfoot]{geometry}\n\n\\usepackage{tabularx}\n\\newcolumntype{R}[1]{>{\\raggedleft\\arraybackslash}p{#1}}\n\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}\n\n\\usepackage{longtable}\n\n\\usepackage{fancyhdr}\n\\pagestyle{fancy}\n\\fancyhf{}\n\\renewcommand{\\headrulewidth}{0pt}\n\\renewcommand{\\footrulewidth}{0.5pt}\n\n\\lfoot{\\sffamily \\begin{tiny}Page: \\thepage\\end{tiny}}\n\\rfoot{\\sffamily \\begin{tiny}+++DATE+++\\end{tiny}}\n\n\\begin{document}\n\n\\sffamily\n\n\\begin{flushleft}\n\\textbf{\n      \\begin{tabular}{@{}p{9cm} l}\n         +++LOCATION+++, +++DATE+++ & \\multirow{5}{8cm}{+++RECIPIENT+++\\newline}\n     \\end{tabular}\n}\n\n\\vspace{2cm}\n\n\\begin{tabular}{@{}l c l@{}}\n\\textbf{+++DOCTYPE+++} &  \\hspace{2cm}  & \\textbf{+++DOCID+++} \\\\\n\\hline\n\\end{tabular}\n\n+++SALUTATION+++\n\n+++INTRODUCTION+++\n\n\\vspace{2cm}\n\\begin{small}\n\\setlength{\\extrarowheight}{1mm}\n\\begin{longtable}{@{}l L{70mm} r @{\\hspace{1mm}}l R{25mm} R{25mm} r}\n+++TABHEAD+++ \\\\ \\hline\\endhead\n+++TABCONTENT+++\n\\hline\n\\end{longtable}\n\\end{small}\n\\end{flushleft}\n\n\\vspace{1mm}\n\n\\begin{flushright}\n\\begin{small}\n\\begin{tabular}{ @{}l  r  r}\n+++DISCOUNT+++\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTEXCL_DESC+++}} & \\textbf{+++TOTEXCL+++} \\\\\n\\hline \n+++VAT+++\n\\hline\n \\\\\n\\multicolumn{2}{@{}l}{\\textbf{+++TOTINCL_DESC+++}} & \\textbf{+++TOTINCL+++} \\\\\n\\hline\n\\hline\n\\end{tabular}\n\\end{small}\n\\end{flushright}\n\n\\vspace{1mm}\n\n\\begin{flushleft}\n\n\\begin{footnotesize}\n\n+++COMMENTS+++\n\n\\setlength{\\extrarowheight}{1mm}\n\\begin{tabular*}{17.5cm}{l}\n\\hline\n\\textbf{+++GENERAL+++} \\\\\n+++GENERAL_INFORMATIONS+++\n\\end{tabular*}\n\\end{footnotesize}\n\n\\vspace{1cm}\n\n\n\\begin{small}\n\\begin{tabular*}{17cm}{p{8.5cm}p{9cm}}\n+++KIND_REGARDS+++ & \\\\\n &  \\\\\n &  \\\\\n &  \\\\\n+++USER+++ &  \\\\\n\\end{tabular*}\n\\end{small}\n\n\n\\end{flushleft}\n\n\\end{document}','Administrator','2008-01-23','','');");
				QSqlQuery query4("UNLOCK TABLES;");
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
			QMessageBox::information( 0, "DB update..." , "The database was successfully updated."  );
		}
	}
}

#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
//
#include "vars.h"
#include "dbupdatefrm.h"
//
int uid;
QString firstver = "1.3.95-pre-beta3";
QString build = "287";
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
void vars::lockrow(QString table, QString rowID)
{
	QSqlDatabase::database().transaction();
	QString qstr = QString("INSERT INTO userlocktab (`table`, `tabid`, `user`) VALUES ('%1', '%2', '%3');").arg(table).arg(rowID).arg(username);
	QSqlQuery query(qstr);
	QSqlDatabase::database().commit();
}
//
void vars::unlockrow(QString table, QString rowID)
{
	QSqlDatabase::database().transaction();
	QString qstr = QString("DELETE FROM userlocktab WHERE `table`='%1' AND `tabid`='%2' AND `user`='%3' LIMIT 1;").arg(table).arg(rowID).arg(username);
	QSqlQuery query(qstr);
	QSqlDatabase::database().commit();
}
//
void vars::locktable(QString table)
{
	QSqlDatabase::database().transaction();
	QString qstr = QString("INSERT INTO userlocktab (`table`, `user`) VALUES ('%1', '%2');").arg(table).arg(username);
	QSqlQuery query(qstr);
	QSqlDatabase::database().commit();
}
//
void vars::unlocktable(QString table)
{
	QSqlDatabase::database().transaction();
	QString qstr = QString("DELETE FROM userlocktab WHERE `table`='%1' AND `user`='%2' LIMIT 1;").arg(table).arg(username);
	QSqlQuery query(qstr);
	QSqlDatabase::database().commit();
}
//
QString vars::checklockstate(QString table, QString rowID)
{
	QString qstr;
	if(rowID != "")
		qstr = QString("SELECT user FROM userlocktab WHERE `table`='%1' AND `tabid`='%2';").arg(table).arg(rowID);
	else
		qstr = QString("SELECT user FROM userlocktab WHERE `table`='%1';").arg(table);
	QSqlQuery query(qstr);
	query.next();
	return query.value(0).toString();
}

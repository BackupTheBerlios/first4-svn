#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>

#include "vars.h"

QString firstver = "1.3.92-alpha2";
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

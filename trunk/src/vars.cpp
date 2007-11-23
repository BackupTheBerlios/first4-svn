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
    QFile file(QDir::homePath()+"/.first4/wingeometry.conf" );
    if(file.open(QIODevice::ReadOnly))
    {
		QTextStream stream(&file);
		while(!stream.atEnd())
		    lines << stream.readLine();
		file.close();    
    }
    
    bool found = FALSE;
    int i;
    if(file.open(QIODevice::WriteOnly))
    {
		QTextStream stream(&file);
		for(i=0;i<lines.count();i++)
		{
		    if(lines[i].section("=",0,0) == frname)
		    {
				found = TRUE;
				stream << frname << QString("=%1,%2,%3,%4,%5").arg(max).arg(x).arg(y).arg(width).arg(height) << "\n";
		    }  
		    else
			stream << lines[i] << "\n";
		}
		if(!found)
		    stream << frname << QString("=%1,%2,%3,%4,%5").arg(max).arg(x).arg(y).arg(width).arg(height) << "\n";
		file.close();    
    }
}
//
QStringList vars::loadgeo(QString frmname)
{
    QStringList tmp;
    QFile file(QDir::homePath()+"/.first4/wingeometry.conf" );
    if(file.open(QIODevice::ReadOnly) && file.exists())
    {
		QTextStream stream(&file);
		QString streamline;
		while(!stream.atEnd())
		{
		    streamline = stream.readLine();
		    if(streamline.section("=",0,0) == frmname)
		    {
				tmp << streamline.section(",",0,0);
				tmp << streamline.section(",",1,1);
				tmp << streamline.section(",",2,2);
				tmp << streamline.section(",",3,3);
				tmp << streamline.section(",",4,5);
		    }
		}
		file.close();    
    }
    return tmp;
}
//
void vars::savecolwidth(QString frmname, QString obj, QStringList colwidth)
{
    QStringList lines;
    QFile file(QDir::homePath()+"/.first4/columns.conf" );
    if(file.open(QIODevice::ReadOnly))
    {
		QTextStream stream(&file);
		while(!stream.atEnd())
		    lines << stream.readLine();
		file.close();    
    }
    
    bool found = FALSE;
    int i;
    if(file.open(QIODevice::WriteOnly))
    {
		QTextStream stream(&file);
		for(i=0;i<lines.count();i++)
		{
		    if(lines[i].section("-",0,0) == frmname && lines[i].section("-", 1, 1).section("-", 0, 0) == obj)
		    {
				found = TRUE;
				stream << QString("%1-%2-%3").arg(frmname).arg(obj).arg(colwidth.join(";")) << "\n";
		    }  
		    else
			stream << lines[i] << "\n";
		}
		if(!found)
		    stream << QString("%1-%2-%3").arg(frmname).arg(obj).arg(colwidth.join(";")) << "\n";
		file.close();    
    }
}
//
QStringList vars::loadcolwidth(QString frmname, QString obj)
{
    QString tmpstr;
    QStringList cols;
    QFile file(QDir::homePath()+"/.first4/columns.conf");
    if(file.open(QIODevice::ReadOnly))
    {
		QTextStream stream(&file);
		while(!stream.atEnd())
		{
		    tmpstr = stream.readLine();
		    if(tmpstr.section("-", 0, 0) == frmname && tmpstr.section("-", 1, 1).section("-", 0, 0) == obj)
		    	cols = tmpstr.section("-", 2, 2).split(";");
		}
		file.close();    
    }
    return cols;
}

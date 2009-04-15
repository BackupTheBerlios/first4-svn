#include <QWidget>
#include <QVariant>

#ifndef VARS_H
#define VARS_H
//

class vars
{
public:
    QStringList loadgeo( QString frmname );
    void savegeo( QString frname, bool max, int x, int y, int width, int height );
    void savecolwidth(QString frname, QString obj, QStringList colwidth);
    QStringList loadcolwidth(QString frmname, QString obj);
    QString get_tool(QString toolname);
	void lockrow(QString table, QString rowID);
	void unlockrow(QString table, QString rowID);
	void locktable(QString table);
	void unlocktable(QString table);
	QString checklockstate(QString table, QString rowID);
	QString getAttr(QString attr);
	void setAttr(QString attr, QString value);
private slots:
};
#endif

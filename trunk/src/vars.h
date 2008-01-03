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
	int check_db_structure();
	void update_db_structure();
private slots:
};
#endif

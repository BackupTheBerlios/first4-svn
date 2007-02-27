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
private slots:
};
#endif

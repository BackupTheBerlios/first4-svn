#include <QDebug>
//
#include "auth.h"
//
bool Auth::loginUser(QString username, QString passwd, QString clientid)
{
    qDebug() << "Processing Login User: " << username << passwd << clientid;
    return true;
}
//
bool Auth::logoutUser(QString username, QString clientid)
{
    qDebug() << "Processing Logout User: " << username << clientid;
    return true;
}

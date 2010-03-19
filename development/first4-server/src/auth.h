#ifndef AUTH_H
#define AUTH_H
//
#include <QString>
//
class Auth
{
public:
    bool loginUser(QString, QString, QString);
    bool logoutUser(QString, QString);
protected:

private:
};

#endif // AUTH_H

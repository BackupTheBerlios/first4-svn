#ifndef AUTH_H
#define AUTH_H
//
#include <QString>
//
class Auth
{
public:
    int loginUser(QString, QString);
    bool logoutUser(QString);
protected:

private:
};

#endif // AUTH_H

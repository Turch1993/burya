#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class database
{
public:
    bool createMainDatabase(QString path);
    bool readMainDatabase(QString path);
};

#endif // DATABASE_H

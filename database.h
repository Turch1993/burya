#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class database
{
public:
    void createDatabase(QString path);
    void readDatabase(QString path);
};

#endif // DATABASE_H

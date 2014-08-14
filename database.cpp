#include "database.h"

bool database::createMainDatabase(QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open())
    {
        qDebug()<<"Error";
        return false;
    }
    else
    {
        qDebug()<<"Base created";
        return true;
    }
    QSqlQuery *query = new QSqlQuery;
    query->exec("CREATE TABLE data (x INTEGER, y TEXT)");
    //query->exec("INSERT INTO t (x, y) VALUES (20, \'ex\')");
}

bool database::readMainDatabase(QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open())
    {
        qDebug()<<"Error";
        return false;
    }
    else
    {
        qDebug()<<"Base opened";
        return true;
    }
}

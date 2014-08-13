#include "database.h"

void database::createDatabase(QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open())
    {
        qDebug()<<"Error";
    }
    else
    {
        qDebug()<<"Base created";
    }
    QSqlQuery *query = new QSqlQuery;
    query->exec("CREATE TABLE data (x INTEGER, y TEXT)");
    //query->exec("INSERT INTO t (x, y) VALUES (20, \'ex\')");
}

void database::readDatabase(QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open())
    {
        qDebug()<<"Error";
    }
    else
    {
        qDebug()<<"Base opened";
    }
}

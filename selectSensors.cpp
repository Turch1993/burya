#include <selectSensors.h>\

void selectSensors::searchSensors()
{
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    bool isCreated = db.open();*/
    QSqlQuery *searchSensors1 = new QSqlQuery;
    QSqlQuery *searchSensors2 = new QSqlQuery;
    QSqlQuery *searchSensors3 = new QSqlQuery;
    searchSensors1->exec("SELECT Id, Channel, RegTime FROM SIGNALS");
    while (searchSensors1->next())
    {
        qDebug()<<searchSensors1->value(1).toInt();
    }
}

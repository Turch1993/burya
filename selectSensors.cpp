#include <selectSensors.h>\

void selectSensors::searchSensors()
{
    QSqlQuery *searchSensors1 = new QSqlQuery;
    QSqlQuery *searchSensors2 = new QSqlQuery;
    QSqlQuery *searchSensors3 = new QSqlQuery;
    QSqlQuery *search = new QSqlQuery;
    searchSensors1->exec("SELECT Id, Channel, RegTime, Events FROM SIGNALS");
    countEvents=0;
    while (searchSensors1->next())
    {
        if ((searchSensors1->value(3).toInt())==NULL)
        {
            //Поиск 1 сигнала
            ++countEvents;
            search->prepare("UPDATE SIGNALS SET Events = ? WHERE Id = ?");
            search->addBindValue(countEvents);
            search->addBindValue(searchSensors1->value(0).toInt());
            search->exec();
            searchSensors2->exec("SELECT Id, Channel, RegTime, Events FROM SIGNALS WHERE Events = NULL");
            while (searchSensors2->next())
            {
                //Поиск 2 сигнала
                search->prepare("UPDATE SIGNALS SET Events = ? WHERE Id = ?");
                search->addBindValue(countEvents);
                search->addBindValue(searchSensors2->value(0).toInt());
                search->exec();
                searchSensors3->exec("SELECT Id, Channel, RegTime, Events FROM SIGNALS WHERE Events = NULL");
                while (searchSensors3->next())
                {
                   //Поиск 3 сигнала
                    search->prepare("UPDATE SIGNALS SET Events = ? WHERE Id = ?");
                    search->addBindValue(countEvents);
                    search->addBindValue(searchSensors3->value(0).toInt());
                    search->exec();
                    if (search->exec("SELECT "));
                }
            }
        }
    }
}

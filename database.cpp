#include "database.h"
#include <QMessageBox>
#include <QFile>

bool database::createMainDatabase(QString pathFile, QString pathBase)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathBase);
    bool isCreated = db.open();
    QSqlQuery *query = new QSqlQuery;
    query->exec("CREATE TABLE data"
                        "(Channel                   INTEGER,"
                        "RegTime                    REAL,"
                        "MaxAmp                     INTEGER,"
                        "RiseTIme                   REAL,"
                        "FirstPeakAmp               INTEGER,"
                        "RiseTImeBeforeFirstPeak    REAL,"
                        "DurationOfSignal           REAL,"
                        "CountOscillation           INTEGER,"
                        "ASLanddB                   INTEGER,"
                        "isForm                     INTEGER)"
                );
    //query->exec("INSERT INTO t (x, y) VALUES (20, \'ex\')");
    FILE *data;
    QByteArray p (pathFile.toUtf8());
    char *ph = p.data();
    data = fopen(ph, "rb");
    qint32 id;
    int i=0;
    int pos = 0;
    qint32 channel;

    while (id!=ID_EOM)
    {
        fread(&id, sizeof(qint32), 1, data);
        pos += 4;
        //qDebug()<<id;
        /*if (id==ID_SIG)
        {
            fread(&channel, sizeof(qint32), 1, data);
            query->prepare("INSERT INTO data"
                                    " (Channel, RegTime, MaxAmp, RiseTIme,"
                                    "FirstPeakAmp, RiseTImeBeforeFirstPeak,"
                                    "DurationOfSignal, CountOscillation,"
                                    "ASLanddB, isForm)"
                                    " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
                           );
            query->addBindValue(channel);
            query->addBindValue(0);
            query->addBindValue(0);
            query->addBindValue(0);
            query->addBindValue(0);
            query->addBindValue(0);
            query->addBindValue(0);
            query->addBindValue(0);
            query->addBindValue(0);
            query->addBindValue(0);
            query->exec();
            //qDebug()<<channel;
        }*/
        query->prepare("INSERT INTO data (Channel) VALUES (?)");
        query->addBindValue(id);
        query->exec();
        pos += passBytes(id);
        if (id==ID_EOM)
        {
            qDebug()<<"YES";
            break;
        }
        fseek(data, pos, SEEK_SET);
    }
    fclose(data);

    /*if (!isCreated)
    {
        QMessageBox::critical(0, "Ошибка создания базы данных", "При создании базы данных произошла ошибка");

        qDebug()<<"Error";
        return false;
    }
    else
    {
        qDebug()<<"Base created";
        return true;
    }*/
    return true;
}

bool database::readMainDatabase(QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open())
    {
        QMessageBox::critical(0, "Ошибка открытия базы данных", "При открытии базы данных произошла ошибка");
        qDebug()<<"Error";
        return false;
    }
    else
    {
        qDebug()<<"Base opened";
        return true;
    }
}

int database::passBytes(qint32 id)
{
    switch (id)
    {
    case ID_MDF:
        return 12;
    case ID_HW:
        return 312;
    case ID_TDD:
        return 40;
    case ID_PAR:
        return 16;
    case ID_SIG:
        return 41;
    case ID_START:
        return 4;
    case ID_PAUSE:
        return 4;
    case ID_EOM:
        return -5;
    }
}

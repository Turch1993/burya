#include "database.h"
#include <QMessageBox>
#include <QFile>
#include <QProgressDialog>

bool database::createMainDatabase(QString pathFile, QString pathBase)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathBase);
    bool isCreated = db.open();
    QSqlQuery *query = new QSqlQuery;
    query->exec("PRAGMA synchronous=OFF");
    query->exec("PRAGMA temp_store=MEMORY");
    query->exec("PRAGMA count_changes=FALSE");
    query->exec("PRAGMA journal_mode=OFF");
    query->exec("CREATE TABLE SIGNALS"
                        "(Id                        INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Channel                    INTEGER,"
                        "RegTime                    REAL,"
                        "MaxAmp                     REAL,"
                        "RiseTIme                   REAL,"
                        "FirstPeakAmp               REAL,"
                        "RiseTImeBeforeFirstPeak    REAL,"
                        "DurationOfSignal           REAL,"
                        "CountOscillation           INTEGER,"
                        "ASLanddB                   REAL,"
                        "isForm                     TEXT)"
                );
    query->exec("CREATE TABLE ASL"
                        "(Id                        INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Time                       REAL,"
                        "Channel                    INTEGER,"
                        "ASL                        REAL)"
                );
    query->exec("CREATE TABLE START_PAUSE"
                        "(Id                        INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "START                      REAL,"
                        "PAUSE                      REAL)"
                );
    query->exec("CREATE TABLE EQUIPMENT"
                        "(Id                        INTEGER PRIMARY KEY AUTOINCREMENT)"

                );
    query->exec("CREATE TABLE DISTANCE"
                        "(Id                        INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Channel_1                  INTEGER,"
                        "Channel_2                  INTEGER,"
                        "Distance                   REAL)"
                );
    FILE *data;
    QByteArray p (pathFile.toUtf8());
    char *ph = p.data();
    data = fopen(ph, "rb");
    bool isForm;
    QString Form;
    qint32 id, channel, riseTime, riseTimeBeforeFirstPeak,
            durationOfSignal, countOscillation;
    float maxAmp, firstPeakAmp, ASLanddB;
    qint64 regTime;
    fseek(data, 0, SEEK_END);
    QProgressDialog *progress = new QProgressDialog("Создание базы данных...", "&Отмена", 0, ftell(data));
    fseek(data, 0, SEEK_SET);
    progress->setWindowTitle("Пожалуйста подождите");
    progress->setMinimumDuration(0);
    progress->setAutoClose(true);
    query->exec("BEGIN");
    while (id!=ID_EOM)
    {
        fread(&id, 4, 1, data);
        if (id==ID_SIG)
        {
            fread(&channel, 4, 1, data);
            fread(&regTime, 8, 1, data);
            fread(&maxAmp, 4, 1, data);
            fread(&riseTime, 4, 1, data);
            fread(&firstPeakAmp, 4, 1, data);
            fread(&riseTimeBeforeFirstPeak, 4, 1, data);
            fread(&durationOfSignal, 4, 1, data);
            fread(&countOscillation, 4, 1, data);
            fread(&ASLanddB, 4, 1, data);
            fread(&isForm, 1, 1, data);
            if (isForm)
            {
                Form="Да";
            }
            else
            {
                Form="Нет";
            }
            query->prepare("INSERT INTO SIGNALS"
                                    " (Channel, RegTime, MaxAmp, RiseTIme,"
                                    "FirstPeakAmp, RiseTImeBeforeFirstPeak,"
                                    "DurationOfSignal, CountOscillation,"
                                    "ASLanddB, isForm)"
                                    " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
                           );
            query->addBindValue(channel);
            query->addBindValue(regTime);
            query->addBindValue(maxAmp);
            query->addBindValue(riseTime);
            query->addBindValue(firstPeakAmp);
            query->addBindValue(riseTimeBeforeFirstPeak);
            query->addBindValue(durationOfSignal);
            query->addBindValue(countOscillation);
            query->addBindValue(ASLanddB);
            query->addBindValue(Form);
            query->exec();
        }
        if (id==ID_TDD)
        {
            fread(&regTime, 8, 1, data);
            for (int i=1; i<=8; i++)
            {
            fread(&ASLanddB, 4, 1, data);
            query->prepare("INSERT INTO ASL"
                                    " (Time, Channel, ASL)"
                                    " VALUES (?, ?, ?)"
                           );
            query->addBindValue(regTime);
            query->addBindValue(i);
            query->addBindValue(ASLanddB);
            query->exec();
            }
        }
        fseek(data, passBytes(id), SEEK_CUR);
        progress->setValue(ftell(data));
        if (progress->wasCanceled())
        {
            break;
        }
        qApp->processEvents();
    }
    delete progress;
    query->exec("COMMIT");
    db.close();
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
        return 304;
    case ID_TDD:
        return 0;
    case ID_PAR:
        return 16;
    case ID_SIG:
        return 0;
    case ID_START:
        return 4;
    case ID_PAUSE:
        return 4;
    case ID_EOM:
        return 0;
    }
}

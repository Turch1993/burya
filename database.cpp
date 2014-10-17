#include "database.h"

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
    query->exec("CREATE TABLE SIGNALS_TEMP"
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
                        "(Id                        INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Gain1                      REAL,"
                        "Gain2                      REAL,"
                        "FloatStep                  TEXT,"
                        "Step                       REAL,"
                        "IKP                        INTEGER,"
                        "IKD                        INTEGER,"
                        "IKK                        INTEGER,"
                        "MinF                       REAL,"
                        "MaxF                       REAL)"
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
    bool isForm, step;
    QString Form;
    qint32 id, channel, riseTime, riseTimeBeforeFirstPeak,
            durationOfSignal, countOscillation;
    float maxAmp, firstPeakAmp, ASLanddB, minF, maxF;
    qint64 regTime;
    if ((!isCreated)&&(data==NULL))
    {
        isCreated=false;
        return isCreated;
    }
    else
    {
    fseek(data, 0, SEEK_END);
    QProgressDialog *progress = new QProgressDialog("Создание базы данных...", "&Отмена", 0, ftell(data));
    fseek(data, 0, SEEK_SET);
    progress->setModal(true);
    progress->setWindowTitle("Пожалуйста подождите");
    progress->setMinimumDuration(0);
    query->exec("BEGIN");
    while (id!=ID_EOM)
    {
        fread(&id, 4, 1, data);
        progress->setValue(ftell(data));
        qApp->processEvents();
        qDebug()<<id;
        if (progress->wasCanceled())
        {
            isCreated=false;
            break;
        }
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
            query->prepare("INSERT INTO SIGNALS_TEMP"
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
        if (id==ID_HW)
        {

            fseek(data, 24, SEEK_CUR);
            for (int i=1; i<=8; i++)
            {
                fseek(data, 1, SEEK_CUR);
                fread(&step, 1, 1, data);
                if(step)
                {
                    Form="Да";
                }
                else
                {
                    Form="Нет";
                }
                fread(&maxAmp, 4, 1, data);
                fread(&firstPeakAmp, 4, 1, data);
                fread(&ASLanddB, 4, 1, data);
                fread(&channel, 4, 1, data);
                fread(&riseTime, 4, 1, data);
                fread(&riseTimeBeforeFirstPeak, 4, 1, data);
                fread(&minF, 4, 1, data);
                fread(&maxF, 4, 1, data);
                fseek(data, 1, SEEK_CUR);
                query->prepare("INSERT INTO EQUIPMENT"
                                        " (Gain1, Gain2, FloatStep, Step, IKP, IKD, IKK, MinF, MaxF)"
                                        " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)"
                               );
                query->addBindValue(firstPeakAmp);
                query->addBindValue(ASLanddB);
                query->addBindValue(Form);
                query->addBindValue(maxAmp);
                query->addBindValue(channel);
                query->addBindValue(riseTime);
                query->addBindValue(riseTimeBeforeFirstPeak);
                query->addBindValue(minF);
                query->addBindValue(maxF);
                query->exec();
            }
        }
        fseek(data, passBytes(id), SEEK_CUR);
    }
    query->exec("CREATE TABLE SIGNALS AS SELECT * FROM SIGNALS_TEMP");
    query->exec("ALTER TABLE SIGNALS ADD Events INTEGER");
    query->exec("ALTER TABLE SIGNALS ADD Cluster INTEGER");
    query->exec("COMMIT");
    fclose(data);
    return isCreated;
    }
}

bool database::readMainDatabase(QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open())
    {
        return false;
    }
    else
    {
        return true;
    }
}

int database::passBytes(qint32 id)
{
    int skip;
    switch (id)
    {
    case ID_MDF:
        skip=12;
    case ID_HW:
        skip=0;
    case ID_TDD:
        skip=0;
    case ID_PAR:
        skip=16;
    case ID_SIG:
        skip=0;
    case ID_START:
        skip=4;
    case ID_PAUSE:
        skip=4;
    case ID_EOM:
        skip=0;
    }
    return skip;
}

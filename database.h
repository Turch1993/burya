#ifndef DATABASE_H
#define DATABASE_H

#define ID_MDF     1472984537
#define ID_HW      1962783628
#define ID_TDD     372903725
#define ID_PAR     892997421
#define ID_SIG     1729264929
#define ID_START   1562804378
#define ID_PAUSE   1432028480
#define ID_EOM     678923475

#include <header.h>

class database
{
public:
    bool createMainDatabase(QString pathFile, QString pathBase);
    bool readMainDatabase(QString path);
private:
    int passBytes (qint32 id);
};

#endif // DATABASE_H

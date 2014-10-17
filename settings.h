#ifndef SETTINGS_H
#define SETTINGS_H

#include <header.h>

class settings
{
public:
    settings();
    void saveColor(bool mode, QColor background, QColor line);
    QSettings *config;
};

#endif // SETTINGS_H

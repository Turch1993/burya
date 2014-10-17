#include "settings.h"

settings::settings()
{
    config = new QSettings(QSettings::NativeFormat, QSettings::UserScope, "AE_analysis", "CMiR");
}

void settings::saveColor(bool mode, QColor background, QColor line)
{
    config->setValue("color/mode", mode);
    config->setValue("color/backgroundColor", background);
    config->setValue("color/lineColor", line);
    config->sync();
}

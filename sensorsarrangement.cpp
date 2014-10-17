#include "sensorsarrangement.h"
#include "ui_sensorsarrangement.h"

sensorsArrangement::sensorsArrangement(QWidget *parent) :
    QDialog(parent),
    ui_sensors(new Ui::sensorsArrangement)
{
    ui_sensors->setupUi(this);
}

sensorsArrangement::~sensorsArrangement()
{
    delete ui_sensors;
}

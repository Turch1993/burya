#include "sensorsarrangement.h"
#include "ui_sensorsarrangement.h"

sensorsArrangement::sensorsArrangement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sensorsArrangement)
{
    ui->setupUi(this);
}

sensorsArrangement::~sensorsArrangement()
{
    delete ui;
}

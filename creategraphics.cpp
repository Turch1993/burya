#include "creategraphics.h"
#include "ui_creategraphics.h"

createGraphics::createGraphics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createGraphics)
{
    ui->setupUi(this);
}

createGraphics::~createGraphics()
{
    delete ui;
}

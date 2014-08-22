#include "creategraphics.h"
#include "ui_creategraphics.h"

createGraphics::createGraphics(QWidget *parent) :
    QDialog(parent),
    ui_graphics(new Ui::createGraphics)
{
    ui_graphics->setupUi(this);
}

createGraphics::~createGraphics()
{
    delete ui_graphics;
}

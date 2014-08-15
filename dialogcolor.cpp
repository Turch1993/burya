#include "dialogcolor.h"
#include "ui_dialogcolor.h"
#include <QColorDialog>

DialogColor::DialogColor(QWidget *parent) :
    QDialog(parent),
    ui_color(new Ui::DialogColor)
{
    ui_color->setupUi(this);
    connect(ui_color->backgroundColor, SIGNAL(clicked()),this, SLOT(setBackgroundColor()));
    connect(ui_color->lineColor, SIGNAL(clicked()),this, SLOT(setLineColor()));
}

DialogColor::~DialogColor()
{
    delete ui_color;
}

void DialogColor::setBackgroundColor()
{
    backgroundColor = QColorDialog::getColor(Qt::white);
}

void DialogColor::setLineColor()
{
    LineColor = QColorDialog::getColor(Qt::black);
}

QColor DialogColor::getBackgroundColor()
{
    return backgroundColor;
}

QColor DialogColor::getLineColor()
{
    return LineColor;
}

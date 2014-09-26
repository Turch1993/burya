#include "plotgraphics.h"
#include "ui_plotgraphics.h"

plotgraphics::plotgraphics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plotgraphics)
{
    ui->setupUi(this);
}

plotgraphics::~plotgraphics()
{
    delete ui;
}

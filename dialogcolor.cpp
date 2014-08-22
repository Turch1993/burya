#include "dialogcolor.h"
#include "ui_dialogcolor.h"
#include <QColorDialog>
#include <QPainter>

DialogColor::DialogColor(QWidget *parent) :
    QDialog(parent),
    ui_color(new Ui::DialogColor)
{
    ui_color->setupUi(this);
    connect(ui_color->backgroundColor, SIGNAL(clicked()),this, SLOT(setBackgroundColor()));
    connect(ui_color->lineColor, SIGNAL(clicked()),this, SLOT(setLineColor()));
    backgroundColor=Qt::white;
    LineColor=Qt::black;
    ui_color->widget->xAxis->setVisible(false);
    ui_color->widget->yAxis->setVisible(false);
    ui_color->widget->axisRect()->setAutoMargins(QCP::msNone);
    ui_color->widget->axisRect()->setMargins(QMargins(0,0,0,0));
    QVector <double> x(100), y(100);
    for (int i=0; i<100; i++)
    {
        x[i]=rand()%100;
        y[i]=rand()%100;
    }
    ui_color->widget->addGraph();
    ui_color->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui_color->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
    ui_color->widget->graph(0)->setData(x,y);
    ui_color->widget->graph(0)->setPen(LineColor);
    ui_color->widget->xAxis->setRange(0, 100);
    ui_color->widget->yAxis->setRange(0, 100);
    ui_color->widget->replot();
}

DialogColor::~DialogColor()
{
    delete ui_color;
}

void DialogColor::setBackgroundColor()
{
    backgroundColor = QColorDialog::getColor(Qt::white);
    ui_color->widget->setBackground(backgroundColor);
    ui_color->widget->replot();

}

void DialogColor::setLineColor()
{
    LineColor = QColorDialog::getColor(Qt::black);
    ui_color->widget->graph(0)->setPen(LineColor);
    ui_color->widget->replot();
}

QColor DialogColor::getBackgroundColor()
{
    return backgroundColor;
}

QColor DialogColor::getLineColor()
{
    return LineColor;
}

void DialogColor::paintEvent(QEvent *event)
{
    QPainter p(this);
    p.drawLine(0,0,100,100);
}

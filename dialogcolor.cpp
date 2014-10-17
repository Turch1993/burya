#include "dialogcolor.h"
#include "ui_dialogcolor.h"

DialogColor::DialogColor(QWidget *parent) :
    QDialog(parent),
    ui_color(new Ui::DialogColor)
{
    ui_color->setupUi(this);
    connect(ui_color->backgroundColor, SIGNAL(clicked()),this, SLOT(setBackgroundColor()));
    connect(ui_color->lineColor, SIGNAL(clicked()),this, SLOT(setLineColor()));
    connect(ui_color->set, SIGNAL(clicked()),this, SLOT(dialogColorSet()));
    connect(ui_color->cancel, SIGNAL(clicked()),this,SLOT(dialogColorCancel()));
    conf = new QSettings(QSettings::NativeFormat, QSettings::UserScope, "AE_analysis", "CMiR");
    _backgroundColor = conf->value("color/backgroundColor").value<QColor>();
    _lineColor = conf->value("color/lineColor").value<QColor>();
    ui_color->widget->setBackground(_backgroundColor);
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
    ui_color->widget->graph(0)->setPen(_lineColor);
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
    _backgroundColor = QColorDialog::getColor(Qt::white);
    ui_color->widget->setBackground(_backgroundColor);
    ui_color->widget->replot();
}

void DialogColor::setLineColor()
{
    _lineColor = QColorDialog::getColor(Qt::black);
    ui_color->widget->graph(0)->setPen(_lineColor);
    ui_color->widget->replot();
}

void DialogColor::dialogColorSet()
{
    backgroundColor=_backgroundColor;
    LineColor=_lineColor;
    conf->setValue("color/backgroundColor", _backgroundColor);
    conf->setValue("color/lineColor", _lineColor);
    colorMode=1;
    conf->setValue("color/mode", colorMode);
    conf->sync();
    close();
}

void DialogColor::dialogColorCancel()
{
    emit canceledButton();
    close();
}

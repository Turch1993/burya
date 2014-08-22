#include "mainwindow.h"
#include "database.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <creategraphics.h>
#include <qmdisubwindow.h>
#include <QMessageBox>
#include <dialogcolor.h>
#include <QTableView>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openDatabase, SIGNAL(triggered()),this, SLOT(openDatabaseDialog()));
    connect(ui->createDatabase, SIGNAL(triggered()), this, SLOT(createDatabaseDialog()));
    connect(ui->exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->createSensorsPosition, SIGNAL(triggered()), this, SLOT(createSensorsPositionDialog()));
    connect(ui->readSensorsPosition, SIGNAL(triggered()), this, SLOT(readSensorsPositionDialog()));
    connect(ui->saveSensorsPositionAs, SIGNAL(triggered()), this, SLOT(saveSensorsPositionAsDialog()));
    connect(ui->readGraphicsSet, SIGNAL(triggered()), this, SLOT(readGraphicsSetDialog()));
    connect(ui->saveGraphicsSetAs, SIGNAL(triggered()), this, SLOT(saveGraphicsSetAsDialog()));
    connect(ui->readFileAttenuation, SIGNAL(triggered()), this, SLOT(readFileFunctionAttenuationDialog()));
    connect(ui->saveFileAttenuationAs, SIGNAL(triggered()), this, SLOT(saveFileFunctionAttenuationDialog()));
    connect(ui->setBlackWhiteColor, SIGNAL(triggered(bool)), this, SLOT(setBlackWhiteColorDialog(bool)));
    connect(ui->setManualColor, SIGNAL(triggered(bool)), this, SLOT(setManualColorDialog(bool)));
    connect(ui->enter_editFunctionAttenuation, SIGNAL(triggered()), this, SLOT(enterEditFunctionAttenuationDialog()));
    connect(ui->computeAmplitudeEvents, SIGNAL(triggered()), this, SLOT(computeAmplitudeEventsDialog()));
    connect(ui->correctionRandA, SIGNAL(triggered()), this, SLOT(correctionRandADialog()));
    connect(ui->location, SIGNAL(triggered()), this, SLOT(locationDialog()));
    connect(ui->filterOfEvent, SIGNAL(triggered()), this, SLOT(filterOfEventDialog()));
    connect(ui->tableOfSignals, SIGNAL(triggered()), this, SLOT(tableOfSignalsDialog()));
    connect(ui->tableOfClasters, SIGNAL(triggered()), this, SLOT(tableOfClastersDialog()));
    connect(ui->StatisticsByChannel, SIGNAL(triggered()), this, SLOT(statisticsByChannelDialog()));
    connect(ui->equipmentParameters, SIGNAL(triggered()), this, SLOT(equipmentParametersDialog()));
    connect(ui->sensorsLocation, SIGNAL(triggered()), this, SLOT(sensorsLocaitonDialog()));
    connect(ui->timeOfCommandStartPause, SIGNAL(triggered()), this, SLOT(timeOfCommandStartPauseDialog()));
    connect(ui->ASLbyChannel, SIGNAL(triggered()), this, SLOT(ASLbyChannelDialog()));
    connect(ui->find, SIGNAL(triggered()), this, SLOT(findDialog()));
    connect(ui->createGraphics, SIGNAL(triggered()), this, SLOT(createGraphicsDialog()));
    connect(ui->graphicsAnalysis, SIGNAL(triggered()), this, SLOT(graphicsAnalysisDialog()));
    connect(ui->localization, SIGNAL(triggered()), this, SLOT(localizationDialog()));
    connect(ui->zonalLocalization, SIGNAL(triggered()), this, SLOT(zonalLocalizationDialog()));
    connect(ui->copy, SIGNAL(triggered()), this, SLOT(copyDialog()));
    connect(ui->saveInFile, SIGNAL(triggered()), this, SLOT(saveInFileDialog()));
    connect(ui->filtrationOfSignals, SIGNAL(triggered()), this, SLOT(filtrationOfSignalsDialog()));
    connect(ui->deletePeriodicNoise, SIGNAL(triggered()), this, SLOT(deletePeriodicNoiseDialog()));
    connect(ui->deleteCasualNoise, SIGNAL(triggered()), this, SLOT(deleteCasualNoiseDialog()));
    connect(ui->menuAbout, SIGNAL(aboutToShow()), this, SLOT(aboutDialog()));
    ui->setDefaultColor->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDatabaseDialog()
{
    QString path = QFileDialog::getOpenFileName(0, "Открыть базу данных", "", "Файлы баз данных (*.db)");
    database *db = new database;
    bool isOpened = db->readMainDatabase(path);
    if(isOpened)
    {
    ui->menuGraphics->setEnabled(true);
    ui->menuTables->setEnabled(true);
    ui->menuTasks->setEnabled(true);
    ui->menuWindow->setEnabled(true);
    }
}

void MainWindow::createDatabaseDialog()
{
    QString pathFile = QFileDialog::getOpenFileName(0, "Создать базу данных", "База данных", "Файлы АЭ (*.cmr)");
    QString pathBase = QFileDialog::getSaveFileName(0, "Создать базу данных", "База данных", "Файлы баз данных (*.db)");
    database *db = new database;
    bool isCreated = db->createMainDatabase(pathFile, pathBase);
    if(isCreated)
    {
    ui->menuGraphics->setEnabled(true);
    ui->menuTables->setEnabled(true);
    ui->menuTasks->setEnabled(true);
    ui->menuWindow->setEnabled(true);
    }
}

void MainWindow::createSensorsPositionDialog()
{
    ui->saveSensorsPositionAs->setEnabled(true);
}

void MainWindow::readSensorsPositionDialog()
{
    ui->saveSensorsPositionAs->setEnabled(true);
}

void MainWindow::saveSensorsPositionAsDialog()
{

}

void MainWindow::readGraphicsSetDialog()
{
    ui->saveGraphicsSetAs->setEnabled(true);
}

void MainWindow::saveGraphicsSetAsDialog()
{

}

void MainWindow::readFileFunctionAttenuationDialog()
{

}

void MainWindow::saveFileFunctionAttenuationDialog()
{

}

void MainWindow::setBlackWhiteColorDialog(bool isChecked)
{
    if (isChecked)
    {
        ui->setDefaultColor->setChecked(false);
        ui->setManualColor->setChecked(false);
    }
}

void MainWindow::setManualColorDialog(bool isChecked)
{
    if (isChecked)
    {
        ui->setBlackWhiteColor->setChecked(false);
        ui->setDefaultColor->setChecked(false);
    }
    DialogColor *color = new DialogColor;
    color->show();
}

void MainWindow::enterEditFunctionAttenuationDialog()
{

}

void MainWindow::computeAmplitudeEventsDialog()
{

}

void MainWindow::correctionRandADialog()
{

}

void MainWindow::locationDialog()
{

}

void MainWindow::filterOfEventDialog()
{

}

void MainWindow::tableOfSignalsDialog()
{
    QMdiSubWindow *tableSignals = new QMdiSubWindow;
    ui->centralWidget->addSubWindow(tableSignals);
    QTableView *view = new QTableView;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM SIGNALS");
    view->setModel(model);
    tableSignals->setWidget(view);
    view->setColumnHidden(0, true);
    model->setHeaderData(0, Qt::Horizontal, "Id");
    model->setHeaderData(1, Qt::Horizontal, "Номер канала");
    model->setHeaderData(2, Qt::Horizontal, "Время начала регистрации сигнала");
    model->setHeaderData(3, Qt::Horizontal, "Максимальная амплитуда");
    model->setHeaderData(4, Qt::Horizontal, "Время нарастания");
    model->setHeaderData(5, Qt::Horizontal, "Амплитуда первого пика");
    model->setHeaderData(6, Qt::Horizontal, "Время нарастания до 1-го пика амплитуды");
    model->setHeaderData(7, Qt::Horizontal, "Длительность сигнала");
    model->setHeaderData(8, Qt::Horizontal, "Осцилляции");
    model->setHeaderData(9, Qt::Horizontal, "Порог");
    model->setHeaderData(10, Qt::Horizontal, "Есть ли форма сигнала?");
    tableSignals->show();

}

void MainWindow::tableOfClastersDialog()
{

}

void MainWindow::statisticsByChannelDialog()
{

}

void MainWindow::equipmentParametersDialog()
{

}

void MainWindow::sensorsLocaitonDialog()
{

}

void MainWindow::timeOfCommandStartPauseDialog()
{

}

void MainWindow::ASLbyChannelDialog()
{
    QMdiSubWindow *tableSignals = new QMdiSubWindow;
    ui->centralWidget->addSubWindow(tableSignals);
    QTableView *view = new QTableView;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM ASL");
    qDebug()<<model->lastError();
    view->setModel(model);
    tableSignals->setWidget(view);
    view->setColumnHidden(0, true);
    model->setHeaderData(0, Qt::Horizontal, "Id");
    model->setHeaderData(1, Qt::Horizontal, "Время измерения");
    model->setHeaderData(2, Qt::Horizontal, "Номер канала");
    model->setHeaderData(3, Qt::Horizontal, "ASL");
    tableSignals->show();
}

void MainWindow::findDialog()
{

}

void MainWindow::createGraphicsDialog()
{
    createGraphics *gp = new createGraphics;
    gp->show();
}

void MainWindow::graphicsAnalysisDialog()
{

}

void MainWindow::localizationDialog()
{

}

void MainWindow::zonalLocalizationDialog()
{

}

void MainWindow::copyDialog()
{

}

void MainWindow::saveInFileDialog()
{

}

void MainWindow::filtrationOfSignalsDialog()
{

}

void MainWindow::deletePeriodicNoiseDialog()
{

}

void MainWindow::deleteCasualNoiseDialog()
{

}

void MainWindow::aboutDialog()
{
    QMessageBox *about = new QMessageBox;
    about->about(0, "О программе", "Проверка");
}

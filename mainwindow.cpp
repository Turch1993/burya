#include "mainwindow.h"
#include "database.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include <QMessageBox>
#include <dialogcolor.h>

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
    connect(ui->setDefaultColor, SIGNAL(triggered(bool)), this, SLOT(setDefaultColorDialog(bool)));
    connect(ui->setBlackWhiteColor, SIGNAL(triggered(bool)), this, SLOT(setBlackWhiteColorDialog(bool)));
    connect(ui->setManualColor, SIGNAL(triggered(bool)), this, SLOT(setManualColorDialog(bool)));
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
    connect(ui->localizationIncrease, SIGNAL(triggered()), this, SLOT(localizationIncreaseDialog()));
    connect(ui->localizationReduce, SIGNAL(triggered()), this, SLOT(localizationReduseDialog()));
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

void MainWindow::setDefaultColorDialog(bool isChecked)
{
    if (isChecked)
    {
        ui->setBlackWhiteColor->setChecked(false);
        ui->setManualColor->setChecked(false);
    }
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

}

void MainWindow::findDialog()
{

}

void MainWindow::createGraphicsDialog()
{

}

void MainWindow::graphicsAnalysisDialog()
{

}

void MainWindow::localizationIncreaseDialog()
{

}

void MainWindow::localizationReduseDialog()
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

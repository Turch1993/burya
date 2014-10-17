#include "mainwindow.h"
#include "database.h"
#include "ui_mainwindow.h"
#include <creategraphics.h>
#include <dialogcolor.h>
#include <sensorsarrangement.h>
#include <settings.h>
#include <selectSensors.h>

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
    connect(ui->setBlackWhiteColor, SIGNAL(triggered()), this, SLOT(setBlackWhiteColorDialog()));
    connect(ui->setManualColor, SIGNAL(triggered()), this, SLOT(setManualColorDialog()));
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
    conf = new QSettings(QSettings::NativeFormat, QSettings::UserScope, "AE_analysis", "CMiR");
    getColorMode();
    if (colorMode)
    {
        ui->setManualColor->setChecked(true);
    }
    else
    {
        ui->setBlackWhiteColor->setChecked(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDatabaseDialog()
{
    QString path = QFileDialog::getOpenFileName(0, "Открыть базу данных", "", "Файлы баз данных (*.db)");
    database *db = new database;
    isDbOpened = db->readMainDatabase(path);
    if(isDbOpened)
    {
        ui->menuPreparationOfSensors->setEnabled(true);
        ui->tableOfSignals->setEnabled(true);
        ui->StatisticsByChannel->setEnabled(true);
        ui->equipmentParameters->setEnabled(true);
        ui->timeOfCommandStartPause->setEnabled(true);
        ui->ASLbyChannel->setEnabled(true);
        ui->createGraphics->setEnabled(true);

    }
    else
    {
        QMessageBox::critical(0, "Ошибка открытия базы данных", "При открытии базы данных произошла ошибка");
    }
}

void MainWindow::createDatabaseDialog()
{
    QString pathFile = QFileDialog::getOpenFileName(0, "Создать базу данных", "База данных", "Файлы АЭ (*.cmr)");
    QString pathBase = QFileDialog::getSaveFileName(0, "Создать базу данных", "База данных", "Файлы баз данных (*.db)");
    database *db = new database;
    isDbOpened = db->createMainDatabase(pathFile, pathBase);
    if(isDbOpened)
    {
        ui->computeAmplitudeEvents->setEnabled(true);
        ui->correctionRandA->setEnabled(true);
        ui->menuPreparationOfSensors->setEnabled(true);
        ui->tableOfSignals->setEnabled(true);
        ui->StatisticsByChannel->setEnabled(true);
        ui->equipmentParameters->setEnabled(true);
        ui->timeOfCommandStartPause->setEnabled(true);
        ui->ASLbyChannel->setEnabled(true);
        ui->createGraphics->setEnabled(true);
    }
    else
    {
        QMessageBox::critical(0, "Ошибка создания базы данных", "При создании базы данных произошла ошибка");
    }
}

void MainWindow::createSensorsPositionDialog()
{
    sensorsArrangement *n = new sensorsArrangement;
    n->showMaximized();
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

void MainWindow::setBlackWhiteColorDialog()
{
    ui->setManualColor->setChecked(false);
    ui->setBlackWhiteColor->setChecked(true);
    conf->setValue("color/backgroundColor", QColor(Qt::white));
    conf->setValue("color/lineColor", QColor(Qt::black));
    colorMode=0;
    conf->setValue("color/mode", colorMode);
    conf->sync();
}

void MainWindow::setManualColorDialog()
{
    ui->setBlackWhiteColor->setChecked(false);
    ui->setManualColor->setChecked(true);
    DialogColor *color = new DialogColor;
    getColorMode();
    if (!colorMode)
    {
    connect(color, SIGNAL(canceledButton()), this, SLOT(setBlackWhiteColorDialog()));
    }
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
    model->setHeaderData(1, Qt::Horizontal, "Номер\nканала");
    model->setHeaderData(2, Qt::Horizontal, "Время начала\nрегистрации сигнала, мкс");
    model->setHeaderData(3, Qt::Horizontal, "Максимальная\nамплитуда, дБ");
    model->setHeaderData(4, Qt::Horizontal, "Время\nнарастания, мкс");
    model->setHeaderData(5, Qt::Horizontal, "Амплитуда\nпервого пика, дБ");
    model->setHeaderData(6, Qt::Horizontal, "Время нарастания до 1-го\nпика амплитуды, мкс");
    model->setHeaderData(7, Qt::Horizontal, "Длительность\nсигнала, мкс");
    model->setHeaderData(8, Qt::Horizontal, "Осцилляции");
    model->setHeaderData(9, Qt::Horizontal, "Порог, дБ");
    model->setHeaderData(10, Qt::Horizontal, "Есть ли\nформа сигнала?");
    tableSignals->setWindowTitle("Таблица сигналов");
    view->resizeColumnsToContents();
    tableSignals->showMaximized();
    /*model->setHeaderData(0, Qt::Vertical, "Id");
    model->setHeaderData(1, Qt::HANDLE);
    view->setTabOrder(QWidget *paint);*/

}

void MainWindow::tableOfClastersDialog()
{

}

void MainWindow::statisticsByChannelDialog()
{
    selectSensors *sensors = new selectSensors;
    sensors->searchSensors();
    /*QMdiSubWindow *tableSignals = new QMdiSubWindow;
    ui->centralWidget->addSubWindow(tableSignals);
    QTableView *view = new QTableView;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM SIGNALS");
    view->setModel(model);
    tableSignals->setWidget(view);
    view->setColumnHidden(0, true);
    model->setHeaderData(0, Qt::Horizontal, "Id");
    model->setHeaderData(1, Qt::Horizontal, "Номер\nканала");
    model->setHeaderData(2, Qt::Horizontal, "Время начала\nрегистрации сигнала, мкс");
    model->setHeaderData(3, Qt::Horizontal, "Максимальная\nамплитуда, дБ");
    model->setHeaderData(4, Qt::Horizontal, "Время\nнарастания, мкс");
    model->setHeaderData(5, Qt::Horizontal, "Амплитуда\nпервого пика, дБ");
    model->setHeaderData(6, Qt::Horizontal, "Время нарастания до 1-го\nпика амплитуды, мкс");
    model->setHeaderData(7, Qt::Horizontal, "Длительность\nсигнала, мкс");
    model->setHeaderData(8, Qt::Horizontal, "Осцилляции");
    model->setHeaderData(9, Qt::Horizontal, "Порог, дБ");
    model->setHeaderData(10, Qt::Horizontal, "Есть ли\nформа сигнала?");
    tableSignals->setWindowTitle("Таблица сигналов");
    view->resizeColumnsToContents();
    tableSignals->showMaximized();*/
}

void MainWindow::equipmentParametersDialog()
{
    QMdiSubWindow *tableSignals = new QMdiSubWindow;
    ui->centralWidget->addSubWindow(tableSignals);
    QTableView *view = new QTableView;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM EQUIPMENT");
    view->setModel(model);
    tableSignals->setWidget(view);
    view->setColumnHidden(0, true);
    model->setHeaderData(0, Qt::Horizontal, "Id");
    model->setHeaderData(1, Qt::Horizontal, "Усиление 1, дБ, мкс");
    model->setHeaderData(2, Qt::Horizontal, "Усиление 2, дБ");
    model->setHeaderData(3, Qt::Horizontal, "Плавающий порог");
    model->setHeaderData(4, Qt::Horizontal, "Порог, дБ");
    model->setHeaderData(5, Qt::Horizontal, "ИКП, мкс");
    model->setHeaderData(6, Qt::Horizontal, "ИКД, мкс");
    model->setHeaderData(7, Qt::Horizontal, "ИКК, мкс");
    model->setHeaderData(8, Qt::Horizontal, "ФВЧ, Гц");
    model->setHeaderData(9, Qt::Horizontal, "ФНЧ, Гц");
    tableSignals->setWindowTitle("Параметры аппаратуры");
    view->resizeColumnsToContents();
    tableSignals->showMaximized();
    view->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(255, 0, 0, 0.2)}");
    view->verticalHeader()->setStyleSheet("QHeaderView::section {background-color:blue}");
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    view->selectRow(15);
}

void MainWindow::sensorsLocaitonDialog()
{

}

void MainWindow::timeOfCommandStartPauseDialog()
{
    QMdiSubWindow *tableSignals = new QMdiSubWindow;
    ui->centralWidget->addSubWindow(tableSignals);
    QTableView *view = new QTableView;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM START_PAUSE");
    view->setModel(model);
    tableSignals->setWidget(view);
    view->setColumnHidden(0, true);
    model->setHeaderData(0, Qt::Horizontal, "Id");
    model->setHeaderData(1, Qt::Horizontal, "СТАРТ, мкс");
    model->setHeaderData(2, Qt::Horizontal, "ПАУЗА, мкс");
    model->setHeaderData(3, Qt::Horizontal, "ASL, дБ");
    tableSignals->setWindowTitle("Время СТАРТА и ПАУЗЫ");
    view->resizeColumnsToContents();
    tableSignals->showMaximized();
}

void MainWindow::ASLbyChannelDialog()
{
    QMdiSubWindow *tableSignals = new QMdiSubWindow;
    ui->centralWidget->addSubWindow(tableSignals);
    QTableView *view = new QTableView;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM ASL");
    view->setModel(model);
    tableSignals->setWidget(view);
    view->setColumnHidden(0, true);
    model->setHeaderData(0, Qt::Horizontal, "Id");
    model->setHeaderData(1, Qt::Horizontal, "Время измерения, мкс");
    model->setHeaderData(2, Qt::Horizontal, "Номер канала");
    model->setHeaderData(3, Qt::Horizontal, "ASL, дБ");
    tableSignals->setWindowTitle("ASL по каналам");
    view->resizeColumnsToContents();
    tableSignals->showMaximized();
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

void MainWindow::getColorMode()
{
    colorMode=conf->value("color/mode").toBool();
}

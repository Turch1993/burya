#include "mainwindow.h"
#include "database.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openDatabase, SIGNAL(triggered()),this, SLOT(openDatabaseDialog()));
    connect(ui->createDatabase, SIGNAL(triggered()), this, SLOT(createDatabaseDialog()));
    connect(ui->exit, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDatabaseDialog()
{
    QString path = QFileDialog::getOpenFileName(0, "Открыть базу данных", "", "Файлы баз данных (*.db)");
    database *db = new database;
    db->readDatabase(path);
}

void MainWindow::createDatabaseDialog()
{
    QString path = QFileDialog::getSaveFileName(0, "Создать базу данных", "База данных", "Файлы баз данных (*.db)");
    database *db = new database;
    db->createDatabase(path);
}

void MainWindow::createSensorsPositionDialog()
{

}

void MainWindow::readSensorsPositionDialog()
{

}

void MainWindow::saveSensorsPositionAsDialog()
{

}

void MainWindow::readGraphicsSetDialog()
{

}

void MainWindow::saveGraphicsSetAsDialog()
{

}

void MainWindow::setDefaultColorDialog()
{

}

void MainWindow::setBlackWhiteColorDialog()
{

}

void MainWindow::setManualColorDialog()
{

}

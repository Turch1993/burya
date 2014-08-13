#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void openDatabaseDialog();
    void createDatabaseDialog();
    void createSensorsPositionDialog();
    void readSensorsPositionDialog();
    void saveSensorsPositionAsDialog();
    void readGraphicsSetDialog();
    void saveGraphicsSetAsDialog();
    void setDefaultColorDialog();
    void setBlackWhiteColorDialog();
    void setManualColorDialog();
};

#endif // MAINWINDOW_H

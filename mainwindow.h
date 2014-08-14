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
    void correctionRandADialog();
    void locationDialog();
    void filterOfEventDialog();
    void tableOfSignalsDialog();
    void tableOfClastersDialog();
    void statisticsByChannelDialog();
    void equipmentParametersDialog();
    void sensorsLocaitonDialog();
    void timeOfCommandStartPauseDialog();
    void ASLbyChannelDialog();
    void findDialog();
    void createGraphicsDialog();
    void graphicsAnalysisDialog();
    void localizationIncreaseDialog();
    void localizationReduseDialog();
    void zonalLocalizationDialog();
    void copyDialog();
    void saveInFileDialog();
    void filtrationOfSignalsDialog();
    void deletePeriodicNoiseDialog();
    void deleteCasualNoiseDialog();
    void aboutDialog();
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <header.h>

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
    QSettings *conf;
    void getColorMode();
private slots:
    void openDatabaseDialog();
    void createDatabaseDialog();
    void createSensorsPositionDialog();
    void readSensorsPositionDialog();
    void saveSensorsPositionAsDialog();
    void readGraphicsSetDialog();
    void saveGraphicsSetAsDialog();
    void readFileFunctionAttenuationDialog();
    void saveFileFunctionAttenuationDialog();
    void setBlackWhiteColorDialog();
    void setManualColorDialog();
    void enterEditFunctionAttenuationDialog();
    void computeAmplitudeEventsDialog();
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
    void localizationDialog();
    void zonalLocalizationDialog();
    void copyDialog();
    void saveInFileDialog();
    void filtrationOfSignalsDialog();
    void deletePeriodicNoiseDialog();
    void deleteCasualNoiseDialog();
    void aboutDialog();
};

#endif // MAINWINDOW_H

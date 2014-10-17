#ifndef DIALOGCOLOR_H
#define DIALOGCOLOR_H

#include <header.h>

namespace Ui {
class DialogColor;
}

class DialogColor : public QDialog
{
    Q_OBJECT

public:
    explicit DialogColor(QWidget *parent = 0);
    ~DialogColor();    
signals:
    void canceledButton();

private:
    QSettings *conf;
    QVector <double> x, y;
    Ui::DialogColor *ui_color;
    QColor _lineColor;
    QColor _backgroundColor;
private slots:
    void setBackgroundColor();
    void setLineColor();
    void dialogColorSet();
    void dialogColorCancel();
};

#endif // DIALOGCOLOR_H

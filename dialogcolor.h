#ifndef DIALOGCOLOR_H
#define DIALOGCOLOR_H

#include <QDialog>
#include <QColor>

namespace Ui {
class DialogColor;
}

class DialogColor : public QDialog
{
    Q_OBJECT

public:
    QColor getBackgroundColor();
    QColor getLineColor();
    explicit DialogColor(QWidget *parent = 0);
    ~DialogColor();

private:
    QColor backgroundColor;
    QColor LineColor;
    Ui::DialogColor *ui_color;
private slots:
    void setBackgroundColor();
    void setLineColor();
};

#endif // DIALOGCOLOR_H

#ifndef SENSORSARRANGEMENT_H
#define SENSORSARRANGEMENT_H

#include <QDialog>

namespace Ui {
class sensorsArrangement;
}

class sensorsArrangement : public QDialog
{
    Q_OBJECT

public:
    explicit sensorsArrangement(QWidget *parent = 0);
    ~sensorsArrangement();

private:
    Ui::sensorsArrangement *ui;
};

#endif // SENSORSARRANGEMENT_H

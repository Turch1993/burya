#ifndef SENSORSARRANGEMENT_H
#define SENSORSARRANGEMENT_H

#include <header.h>

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
    Ui::sensorsArrangement *ui_sensors;
};

#endif // SENSORSARRANGEMENT_H

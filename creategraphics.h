#ifndef CREATEGRAPHICS_H
#define CREATEGRAPHICS_H

#include <header.h>

namespace Ui {
class createGraphics;
}

class createGraphics : public QDialog
{
    Q_OBJECT

public:
    explicit createGraphics(QWidget *parent = 0);
    ~createGraphics();

private:
    Ui::createGraphics *ui_graphics;
};

#endif // CREATEGRAPHICS_H

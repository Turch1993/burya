#ifndef PLOTGRAPHICS_H
#define PLOTGRAPHICS_H

#include <QWidget>

namespace Ui {
class plotgraphics;
}

class plotgraphics : public QWidget
{
    Q_OBJECT

public:
    explicit plotgraphics(QWidget *parent = 0);
    ~plotgraphics();

private:
    Ui::plotgraphics *ui;
};

#endif // PLOTGRAPHICS_H

#ifndef SCALEPARAMETERS_H
#define SCALEPARAMETERS_H

#include <QWidget>

namespace Ui {
class ScaleParameters;
}

class ScaleParameters : public QWidget
{
    Q_OBJECT

public:
    explicit ScaleParameters(QWidget *parent = nullptr);
    ~ScaleParameters();

private:
    Ui::ScaleParameters *ui;
signals:
    void applied(double cx, double cy, double kx, double ky);
private slots:
    void on_scale_pushButton_clicked();
};

#endif // SCALEPARAMETERS_H

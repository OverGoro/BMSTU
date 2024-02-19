#ifndef ROTATEPARAMETERS_H
#define ROTATEPARAMETERS_H

#include <QWidget>

namespace Ui {
class RotateParameters;
}

class RotateParameters : public QWidget
{
    Q_OBJECT

public:
    explicit RotateParameters(QWidget *parent = nullptr);
    ~RotateParameters();

private:
    Ui::RotateParameters *ui;
signals:
    void applied(double cx, double cy, double angle);
private slots:
    void on_rotate_pushButton_clicked();
};

#endif // ROTATEPARAMETERS_H

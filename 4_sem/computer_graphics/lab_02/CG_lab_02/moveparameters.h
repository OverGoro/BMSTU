#ifndef MOVEPARAMETERS_H
#define MOVEPARAMETERS_H

#include <QWidget>

namespace Ui {
class moveParameters;
}

class moveParameters : public QWidget
{
    Q_OBJECT

public:
    explicit moveParameters(QWidget *parent = nullptr);
    ~moveParameters();

private:
    Ui::moveParameters *ui;
signals:
    void applied(double dx, double dy);
private slots:
    void on_move_pushButton_clicked();
};

#endif // MOVEPARAMETERS_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "historywidget.h"
#include "moveparameters.h"
#include "rotateparameters.h"
#include "scaleparameters.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    HistoryWidget *historyWidget;
    moveParameters *moveParametersWidget;
    RotateParameters *rotateParametersWidget;
    ScaleParameters *scaleParametersWidget;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double getCountWidth() const;
    void setCountWidth(double newCountWidth);

    double getCountHeight() const;
    void setCountHeight(double newCountHeight);

private slots:
    void move(double dx, double dy);
    void rotate(double cx, double cy, double a);
    void scale(double cx, double cy, double kx, double ky);
    void redraw();

    void on_moveMode_pushButton_toggled(bool checked);

    void on_rotateMode_pushButton_toggled(bool checked);

    void on_scaleMode_pushButton_toggled(bool checked);

    void on_backward_action_triggered();

    void on_forward_action_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

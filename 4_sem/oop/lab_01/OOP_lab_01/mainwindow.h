#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "manager.h"

#include <QMainWindow>
#include <QLocale>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    manager_params_t manager_params;
    Ui::MainWindow *ui;
private slots:
    void manage_read();
    void manage_save();
    void manage_move();
    void manage_rotate();
    void manage_scale();
    void manage_drawGL();
    void handle_rc(int rc);
protected:
    void closeEvent(QCloseEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

};
#endif // MAINWINDOW_H

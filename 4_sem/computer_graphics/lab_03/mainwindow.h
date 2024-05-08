#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum line_type_t
{
    LIB,
    BRES_FLOAT,
    BRES_INT,
    BRES_LEDDER,
    CDA,
    VU
};

struct line_t
{
    QPoint p1, p2;
    QColor color;
    line_type_t type;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    std::vector<line_t> lines;
    QColor line_color;
private:
    void manageDraw();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void add_line(QPoint p1, QPoint p2, QColor color);

    void on_draw_pushButton_clicked();

    void on_lib_radioButton_toggled(bool checked);

    void on_bres_float_radioButton_toggled(bool checked);

    void on_bres_int_radioButton_toggled(bool checked);

    void on_cda_radioButton_toggled(bool checked);

    void on_bres_ledder_radioButton_toggled(bool checked);

    void on_vu_radioButton_toggled(bool checked);

    void on_scpectre_pushButton_clicked();

    void on_analyze_pushButton_clicked();

    void on_background_color_pushButton_clicked();

    void on_line_color_pushButton_clicked();

    void on_clear_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

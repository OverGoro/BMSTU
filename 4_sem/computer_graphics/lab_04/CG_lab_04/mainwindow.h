#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum circle_type_t
{
    CANONIC_CIRCLE,
    PARAMETRIC_CIRCLE,
    BRESENHEM_CIRCLE,
    MID_POINT_CIRCLE,
    LIB_CIRCLE
};

enum ellipse_type_t
{
    CANONIC_ELLIPSE,
    PARAMETRIC_ELLIPSE,
    BRESENHEM_ELLIPSE,
    MID_POINT_ELLIPSE,
    LIB_ELLIPSE
};

struct circle_t
{
    QPoint p_center;
    double r;
    QColor color;
    circle_type_t type;
};

struct ellipse_t
{
    QPoint p_center;
    double a,b;
    QColor color;
    ellipse_type_t type;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    std::vector<circle_t> circles;
    std::vector<ellipse_t> ellipses;
    QColor line_color;
private:
    void manageDraw();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void add_circle(QPoint p_center, double r, QColor color);
    void add_ellipse(QPoint p_center, double a, double b, QColor color);

    void on_lib_radioButton_toggled(bool checked);

    void on_analyze_pushButton_clicked();

    void on_background_color_pushButton_clicked();

    void on_clear_pushButton_clicked();

    void on_draw_circle_pushButton_clicked();

    void on_line_color_pushButton_clicked();

    void on_draw_ellipse_pushButton_clicked();

    void on_circle_scpectre_pushButton_clicked();

    void on_ellipse_spectre_pushButton_clicked();

    void on_bresenhem_radioButton_clicked(bool checked);

    void on_parametric_radioButton_clicked(bool checked);

    void on_mid_point_radioButton_clicked(bool checked);

    void on_canonic_radioButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

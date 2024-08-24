#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "painterwidget.h"
#include "figuremodel.h"
#include <QMainWindow>
#include <QAbstractTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addPoint_pushButton_clicked();

    void on_clear_pushButton_clicked();

    void draw_figure_borders();
    // void draw_seed_point();
    // void fill_figures();
    // void fill_figures_delay();

    void painter_widget_clicked(QMouseEvent *event);

    // void on_closeFigure_pushButton_clicked();

    // void on_fill_pushButton_clicked();

    // void on_fillDelay_pushButton_clicked();

    void draw_clipper();

    void on_pushButton_clicked();

    void draw_clipped();

    // void show_fill_results();

    void on_background_color_pushButton_clicked();

    void on_line_color_pushButton_clicked();

    void on_fillColor_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    std::vector<Figure> figures;
    FigureModel *figures_model;
    bool clipper_mode, clipper_point_mode;
    int delay_max_lines;
    drawResults fill_result;
    QColor backgroundColor, lineColor, clipperColor, clippedColor;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

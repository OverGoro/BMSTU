#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QColorDialog>

void MainWindow::manageDraw()
{
    for (auto & circle : circles)
    {
        if (circle.type == LIB_CIRCLE)
            ui->painter_widget->drawCircleLib(circle.p_center.x(), circle.p_center.y(), circle.r, circle.color);
        else if (circle.type == BRESENHEM_CIRCLE)
            ui->painter_widget->drawCircleBresenhem(circle.p_center.x(), circle.p_center.y(), circle.r, circle.color);
        else if (circle.type == MID_POINT_CIRCLE)
            ui->painter_widget->drawCircleMidPoint(circle.p_center.x(), circle.p_center.y(), circle.r, circle.color);
        else if (circle.type == CANONIC_CIRCLE)
            ui->painter_widget->drawCircleCanonical(circle.p_center.x(), circle.p_center.y(), circle.r, circle.color);
        else if (circle.type == PARAMETRIC_CIRCLE)
            ui->painter_widget->drawCircleParametric(circle.p_center.x(), circle.p_center.y(), circle.r, circle.color);
    }

    for (auto & ellipse : ellipses)
    {
        if (ellipse.type == LIB_ELLIPSE)
            ui->painter_widget->drawEllipseLib(ellipse.p_center.x(), ellipse.p_center.y(), ellipse.a, ellipse.b, ellipse.color);
        else if (ellipse.type == BRESENHEM_ELLIPSE)
            ui->painter_widget->drawEllipseBresenhem(ellipse.p_center.x(), ellipse.p_center.y(), ellipse.a, ellipse.b, ellipse.color);
        else if (ellipse.type == MID_POINT_ELLIPSE)
            ui->painter_widget->drawEllipseMidPoint(ellipse.p_center.x(), ellipse.p_center.y(), ellipse.a, ellipse.b, ellipse.color);
        else if (ellipse.type == CANONIC_ELLIPSE)
            ui->painter_widget->drawEllipseCanonical(ellipse.p_center.x(), ellipse.p_center.y(), ellipse.a, ellipse.b, ellipse.color);
        else if (ellipse.type == PARAMETRIC_ELLIPSE)
            ui->painter_widget->drawEllipseParametric(ellipse.p_center.x(), ellipse.p_center.y(), ellipse.a, ellipse.b, ellipse.color);
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->x_center_lineEdit->setValidator(new QIntValidator);
    ui->y_center_lineEdit->setValidator(new QIntValidator);
    ui->r_lineEdit->setValidator(new QIntValidator);
    ui->a_lineEdit->setValidator(new QIntValidator);
    ui->b_lineEdit->setValidator(new QIntValidator);

    ui->circle_spectre_min_r_lineEdit->setValidator(new QIntValidator);
    ui->circle_spectre_max_r_lineEdit->setValidator(new QIntValidator);
    ui->circle_spectre_num_lineEdit->setValidator(new QIntValidator);

    ui->ellipse_spectre_min_a_lineEdit->setValidator(new QIntValidator);
    ui->ellipse_spectre_max_a_lineEdit->setValidator(new QIntValidator);
    ui->ellipse_spectre_min_b_lineEdit->setValidator(new QIntValidator);
    ui->ellipse_spectre_max_b_lineEdit->setValidator(new QIntValidator);
    ui->ellipse_spectre_num_lineEdit->setValidator(new QIntValidator);

    line_color = Qt::black;

    connect(ui->painter_widget, &PainterWidget::paintSignal, this, &MainWindow::manageDraw);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_circle(QPoint p_center, double r, QColor color)
{
    if (ui->bresenhem_radioButton->isChecked())
        circles.push_back({p_center, r, color, BRESENHEM_CIRCLE});
    else if (ui->mid_point_radioButton->isChecked())
        circles.push_back({p_center, r, color, MID_POINT_CIRCLE});
    else if (ui->canonic_radioButton->isChecked())
        circles.push_back({p_center, r, color, CANONIC_CIRCLE});
    else if (ui->parametric_radioButton->isChecked())
        circles.push_back({p_center, r, color, PARAMETRIC_CIRCLE});
    else if (ui->lib_radioButton->isChecked())
        circles.push_back({p_center, r, color, LIB_CIRCLE});
}

void MainWindow::add_ellipse(QPoint p_center, double a, double b, QColor color)
{
    if (ui->bresenhem_radioButton->isChecked())
        ellipses.push_back({p_center, a, b, color, BRESENHEM_ELLIPSE});
    else if (ui->mid_point_radioButton->isChecked())
        ellipses.push_back({p_center, a, b, color, MID_POINT_ELLIPSE});
    else if (ui->canonic_radioButton->isChecked())
        ellipses.push_back({p_center, a, b, color, CANONIC_ELLIPSE});
    else if (ui->parametric_radioButton->isChecked())
        ellipses.push_back({p_center, a, b, color, PARAMETRIC_ELLIPSE});
    else if (ui->lib_radioButton->isChecked())
        ellipses.push_back({p_center, a, b, color, LIB_ELLIPSE});
}


void MainWindow::on_draw_circle_pushButton_clicked()
{
    add_circle(QPoint(ui->x_center_lineEdit->text().toInt(), ui->y_center_lineEdit->text().toInt()),
                ui->r_lineEdit->text().toInt(),
                line_color);
    ui->painter_widget->repaint();
}

void MainWindow::on_draw_ellipse_pushButton_clicked()
{
    add_ellipse(QPoint(ui->x_center_lineEdit->text().toInt(), ui->y_center_lineEdit->text().toInt()),
                ui->a_lineEdit->text().toInt(),
                ui->b_lineEdit->text().toInt(),
                line_color);
    ui->painter_widget->repaint();
}

void MainWindow::on_circle_scpectre_pushButton_clicked()
{
    int x1 = ui->painter_widget->width() / 2, y1 = ui->painter_widget->height() / 2;
    double min_r = ui->circle_spectre_min_r_lineEdit->text().toDouble();
    double max_r = ui->circle_spectre_max_r_lineEdit->text().toDouble();

    if (max_r < min_r)
    {
        std::swap(min_r, max_r);
    }

    double step_r = (max_r - min_r) / ui->circle_spectre_num_lineEdit->text().toDouble();

    if (step_r > 0)
    {
        for (double i = min_r; i <= max_r; i += step_r)
        {
            add_circle(QPoint(x1,y1), i, line_color);
        }
    }

    ui->painter_widget->repaint();
}

void MainWindow::on_ellipse_spectre_pushButton_clicked()
{
    int x1 = ui->painter_widget->width() / 2, y1 = ui->painter_widget->height() / 2;
    double min_a = ui->ellipse_spectre_min_a_lineEdit->text().toDouble();
    double max_a = ui->ellipse_spectre_max_a_lineEdit->text().toDouble();

    double min_b = ui->ellipse_spectre_min_b_lineEdit->text().toDouble();
    double max_b = ui->ellipse_spectre_max_b_lineEdit->text().toDouble();

    if (max_b < min_b)
        std::swap(min_b, max_b);

    if (max_a < min_a)
        std::swap(max_a, min_a);

    double step_b = (max_b - min_b) / ui->ellipse_spectre_num_lineEdit->text().toDouble();
    double step_a = (max_a - min_a) / ui->ellipse_spectre_num_lineEdit->text().toDouble();

    if (step_a > 0 && step_b > 0)
    {
        for (double ai = min_a, bi = min_b; ai <= max_a && bi <= max_b; ai += step_a, bi+= step_b)
        {
            add_ellipse(QPoint(x1,y1), ai, bi, line_color);
        }
    }

    ui->painter_widget->repaint();
}

void MainWindow::on_analyze_pushButton_clicked()
{
    int x1 = 0, y1 = 0;
    int R = ui->analyze_r_lineEdit->text().toInt();
    int a = ui->analyze_a_lineEdit->text().toInt();
    int b = ui->analyze_b_lineEdit->text().toInt();

    std::vector<double> circle_time_measures(5);
    std::vector<double> ellipse_time_measures(5);
    std::vector<QString> method_names = {"Встроенный метод",
                                         "Брезенхема",
                                         "Серединной точки",
                                         "Каноническое уравнение",
                                         "Параметрическое уравнение"};
    size_t measures_num = 25;

    for (size_t i = 0; i < measures_num; i++)
    {
        circle_time_measures[0] += ui->painter_widget->drawCircleLib(x1,y1,R).time / measures_num;
        circle_time_measures[1] += ui->painter_widget->drawCircleBresenhem(x1,y1,R).time / measures_num;
        circle_time_measures[2] += ui->painter_widget->drawCircleMidPoint(x1,y1,R).time / measures_num;
        circle_time_measures[3] += ui->painter_widget->drawCircleCanonical(x1,y1,R).time / measures_num;
        circle_time_measures[4] += ui->painter_widget->drawCircleParametric(x1,y1,R).time / measures_num;

        ellipse_time_measures[0] += ui->painter_widget->drawEllipseLib(x1,y1,a,b).time / measures_num;
        ellipse_time_measures[1] += ui->painter_widget->drawEllipseBresenhem(x1,y1,a,b).time / measures_num;
        ellipse_time_measures[2] += ui->painter_widget->drawEllipseMidPoint(x1,y1,a,b).time / measures_num;
        ellipse_time_measures[3] += ui->painter_widget->drawEllipseCanonical(x1,y1,a,b).time / measures_num;
        ellipse_time_measures[4] += ui->painter_widget->drawEllipseParametric(x1,y1,a,b).time / measures_num;
    }


    ui->time_plotter_widget->setBars(circle_time_measures, "Время окружностей", method_names);
    ui->time_plotter_widget->repaint();

    ui->ledder_plotter_widget->setBars(ellipse_time_measures, "Время эллипсов", method_names);
    ui->ledder_plotter_widget->repaint();
}

void MainWindow::on_lib_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->bresenhem_radioButton->setChecked(false);
        ui->mid_point_radioButton->setChecked(false);
        ui->canonic_radioButton->setChecked(false);
        ui->parametric_radioButton->setChecked(false);
    }
}

void MainWindow::on_bresenhem_radioButton_clicked(bool checked)
{
    if (checked)
    {
        ui->lib_radioButton->setChecked(false);
        ui->mid_point_radioButton->setChecked(false);
        ui->canonic_radioButton->setChecked(false);
        ui->parametric_radioButton->setChecked(false);
    }
}

void MainWindow::on_mid_point_radioButton_clicked(bool checked)
{
    if (checked)
    {
        ui->bresenhem_radioButton->setChecked(false);
        ui->lib_radioButton->setChecked(false);
        ui->canonic_radioButton->setChecked(false);
        ui->parametric_radioButton->setChecked(false);
    }
}


void MainWindow::on_canonic_radioButton_clicked(bool checked)
{
    if (checked)
    {
        ui->lib_radioButton->setChecked(false);
        ui->bresenhem_radioButton->setChecked(false);
        ui->mid_point_radioButton->setChecked(false);
        ui->parametric_radioButton->setChecked(false);
    }
}

void MainWindow::on_parametric_radioButton_clicked(bool checked)
{
    if (checked)
    {
        ui->lib_radioButton->setChecked(false);
        ui->bresenhem_radioButton->setChecked(false);
        ui->mid_point_radioButton->setChecked(false);
        ui->canonic_radioButton->setChecked(false);
    }
}



void MainWindow::on_background_color_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет");
    if (color.isValid())
    {
        ui->painter_widget->setBackground_color(color);
        ui->painter_widget->repaint();
    }
}


void MainWindow::on_line_color_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет");
    if (color.isValid())
    {
        line_color = color;
        ui->painter_widget->repaint();
    }
}


void MainWindow::on_clear_pushButton_clicked()
{
    circles.clear();
    ellipses.clear();
    ui->painter_widget->repaint();
}

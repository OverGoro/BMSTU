#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QColorDialog>

void MainWindow::manageDraw()
{
    for (auto & line : lines)
    {
        if (line.type == LIB)
            ui->painter_widget->drawLineLib(line.p1.x(), line.p1.y(), line.p2.x(), line.p2.y(), line.color);
        else if (line.type == BRES_FLOAT)
            ui->painter_widget->drawLineBresFloat(line.p1.x(), line.p1.y(), line.p2.x(), line.p2.y(), line.color);
        else if (line.type == BRES_INT)
            ui->painter_widget->drawLineBresInt(line.p1.x(), line.p1.y(), line.p2.x(), line.p2.y(), line.color);
        else if (line.type == BRES_LEDDER)
            ui->painter_widget->drawLineBresLedder(line.p1.x(), line.p1.y(), line.p2.x(), line.p2.y(), line.color);
        else if (line.type == CDA)
            ui->painter_widget->drawLineCDA(line.p1.x(), line.p1.y(), line.p2.x(), line.p2.y(), line.color);
        else if (line.type == VU)
            ui->painter_widget->drawLineVu(line.p1.x(), line.p1.y(), line.p2.x(), line.p2.y(), line.color);
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x1_lineEdit->setValidator(new QIntValidator);
    ui->y1_lineEdit->setValidator(new QIntValidator);
    ui->x2_lineEdit->setValidator(new QIntValidator);
    ui->y2_lineEdit->setValidator(new QIntValidator);
    ui->len_lineEdit->setValidator(new QIntValidator);
    ui->min_angle_lineEdit->setValidator(new QIntValidator);
    ui->max_angle_lineEdit->setValidator(new QIntValidator);
    ui->step_lineEdit->setValidator(new QIntValidator);
    ui->spectre_len_lineEdit->setValidator(new QIntValidator);

    line_color = Qt::black;

    connect(ui->painter_widget, &PainterWidget::paintSignal, this, &MainWindow::manageDraw);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_line(QPoint p1, QPoint p2, QColor color)
{
    if (ui->lib_radioButton->isChecked())
        lines.push_back({p1, p2, color, LIB});

    else if (ui->bres_float_radioButton->isChecked())
        lines.push_back({p1, p2, color, BRES_FLOAT});

    else if (ui->bres_int_radioButton->isChecked())
        lines.push_back({p1, p2, color, BRES_INT});

    else if (ui->bres_ledder_radioButton->isChecked())
        lines.push_back({p1, p2, color, BRES_LEDDER});

    else if (ui->cda_radioButton->isChecked())
        lines.push_back({p1, p2, color, CDA});

    else if (ui->vu_radioButton->isChecked())
        lines.push_back({p1, p2, color, VU});
}



void MainWindow::on_draw_pushButton_clicked()
{
    int x1 = ui->x1_lineEdit->text().toInt();
    int y1 = ui->y1_lineEdit->text().toInt();
    int x2 = ui->x2_lineEdit->text().toInt();
    int y2 = ui->y2_lineEdit->text().toInt();

    add_line(QPoint(x1, y1), QPoint(x2, y2), line_color);

    ui->painter_widget->repaint();
}

void MainWindow::on_scpectre_pushButton_clicked()
{
    int x1 = 290, y1 = 290;
    int R = ui->spectre_len_lineEdit->text().toInt();

    int min_angle = ui->min_angle_lineEdit->text().toInt();
    int max_angle = ui->max_angle_lineEdit->text().toInt();
    int step_angle = ui->step_lineEdit->text().toInt();

    if (step_angle > 0 && max_angle > min_angle)
    {
        for (int i = min_angle; i < max_angle; i += step_angle)
        {
            int x2 = x1 + R * qCos(qDegreesToRadians(i));
            int y2 = y1 + R * qSin(qDegreesToRadians(i));
            add_line(QPoint(x1, y1), QPoint(x2, y2), line_color);
        }
    }

    ui->painter_widget->repaint();
}

void MainWindow::on_analyze_pushButton_clicked()
{
    int x1 = 0, y1 = 0;
    int R = ui->len_lineEdit->text().toInt();

    std::vector<double> time_measures(6);
    std::vector<std::vector<QPointF>> steps_measures(6);
    std::vector<QString> method_names = {"Встроенный метод",
                                         "Брезенхема с действительными данными",
                                         "Брезенхема с целочисленными данными",
                                         "Брезенхема с устранением ступенчатости",
                                         "ЦДА",
                                         "Алгоритм Ву"};
    size_t measures_num = 25;

    for (int a = 0; a <= 360; a += 1)
    {
        int x2 = x1 + R * qCos(qDegreesToRadians(a));
        int y2 = y1 + R * qSin(qDegreesToRadians(a));

        steps_measures[0].push_back(QPointF(a, ui->painter_widget->drawLineLib(x1,y1,x2,y2).steps_num));
        steps_measures[1].push_back(QPointF(a, ui->painter_widget->drawLineBresFloat(x1,y1,x2,y2).steps_num));
        steps_measures[2].push_back(QPointF(a, ui->painter_widget->drawLineBresInt(x1,y1,x2,y2).steps_num));
        steps_measures[3].push_back(QPointF(a, ui->painter_widget->drawLineBresLedder(x1,y1,x2,y2).steps_num));
        steps_measures[4].push_back(QPointF(a, ui->painter_widget->drawLineCDA(x1,y1,x2,y2).steps_num));
        steps_measures[5].push_back(QPointF(a, ui->painter_widget->drawLineVu(x1,y1,x2,y2).steps_num));

        for (size_t i = 0; i < measures_num; i++)
        {
            time_measures[0] += ui->painter_widget->drawLineLib(x1,y1,x2,y2).time / measures_num;
            time_measures[1] += ui->painter_widget->drawLineBresFloat(x1,y1,x2,y2).time / measures_num;
            time_measures[2] += ui->painter_widget->drawLineBresInt(x1,y1,x2,y2).time / measures_num;
            time_measures[3] += ui->painter_widget->drawLineBresLedder(x1,y1,x2,y2).time / measures_num;
            time_measures[4] += ui->painter_widget->drawLineCDA(x1,y1,x2,y2).time / measures_num;
            time_measures[5] += ui->painter_widget->drawLineVu(x1,y1,x2,y2).time / measures_num;
        }
    }


    ui->time_plotter_widget->setBars(time_measures, "Время", method_names);
    ui->time_plotter_widget->repaint();

    ui->ledder_plotter_widget->setLines(steps_measures, "Ступеньки", method_names);
    ui->ledder_plotter_widget->repaint();
}

void MainWindow::on_lib_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->bres_float_radioButton->setChecked(false);
        ui->bres_int_radioButton->setChecked(false);
        ui->bres_ledder_radioButton->setChecked(false);
        ui->cda_radioButton->setChecked(false);
        ui->vu_radioButton->setChecked(false);
    }
}


void MainWindow::on_bres_float_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->lib_radioButton->setChecked(false);
        ui->bres_int_radioButton->setChecked(false);
        ui->bres_ledder_radioButton->setChecked(false);
        ui->cda_radioButton->setChecked(false);
        ui->vu_radioButton->setChecked(false);
    }
}


void MainWindow::on_bres_int_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->lib_radioButton->setChecked(false);
        ui->bres_float_radioButton->setChecked(false);
        ui->bres_ledder_radioButton->setChecked(false);
        ui->cda_radioButton->setChecked(false);
        ui->vu_radioButton->setChecked(false);
    }
}

void MainWindow::on_bres_ledder_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->lib_radioButton->setChecked(false);
        ui->bres_float_radioButton->setChecked(false);
        ui->bres_int_radioButton->setChecked(false);
        ui->cda_radioButton->setChecked(false);
        ui->vu_radioButton->setChecked(false);
    }
}

void MainWindow::on_cda_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->lib_radioButton->setChecked(false);
        ui->bres_int_radioButton->setChecked(false);
        ui->bres_float_radioButton->setChecked(false);
        ui->bres_ledder_radioButton->setChecked(false);
        ui->vu_radioButton->setChecked(false);
    }
}

void MainWindow::on_vu_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->lib_radioButton->setChecked(false);
        ui->bres_int_radioButton->setChecked(false);
        ui->bres_float_radioButton->setChecked(false);
        ui->bres_ledder_radioButton->setChecked(false);
        ui->cda_radioButton->setChecked(false);
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
    lines.clear();

    ui->painter_widget->repaint();
}


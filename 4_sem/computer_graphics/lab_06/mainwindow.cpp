#include "mainwindow.h"
#include "painterexceptions.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QMessageBox>
#include <thread>
#include <QColorDialog>

using namespace std::chrono_literals;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x_center_lineEdit->setValidator(new QIntValidator());
    ui->y_center_lineEdit->setValidator(new QIntValidator());
    figures_model = new FigureModel();
    ui->tableView->setModel(figures_model);
    fill_mode = false;
    delay_fill_mode = false;
    is_ended_fill = false;
    lineColor = Qt::black;
    fillColor = Qt::gray;
    backgroundColor = Qt::white;
    connect(ui->painter_widget, &PainterWidget::paintSignal, this, &MainWindow::draw_figure_borders);
    connect(ui->painter_widget, &PainterWidget::paintSignal, this, &MainWindow::fill_figures);
    connect(ui->painter_widget, &PainterWidget::paintSignal, this, &MainWindow::fill_figures_delay);
    connect(ui->painter_widget, &PainterWidget::paintSignal, this, &MainWindow::draw_seed_point);
    connect(ui->painter_widget, &PainterWidget::paintEndedSignal, this, &MainWindow::show_fill_results);
    connect(ui->painter_widget, &PainterWidget::mouseClicked, this, &MainWindow::painter_widget_clicked);
    connect(ui->painter_widget, &PainterWidget::mouseMoved, this, &MainWindow::painter_widget_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPoint_pushButton_clicked()
{
    fill_mode = false;
    delay_fill_mode = false;
    this->figures_model->addPoint(QPoint(ui->x_center_lineEdit->text().toInt(),
                                         ui->y_center_lineEdit->text().toInt()));
    ui->painter_widget->repaint();
}


void MainWindow::on_closeFigure_pushButton_clicked()
{
    try
    {
        this->figures_model->closeFigure();
    }
    catch (BaseException e)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",e.what());
        messageBox.setFixedSize(500,200);
    }
    catch (std::exception e)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",e.what());
        messageBox.setFixedSize(500,200);
    }
    ui->painter_widget->repaint();
}


void MainWindow::on_clear_pushButton_clicked()
{
    figures_model->clear();
    ui->painter_widget->repaint();
}

void MainWindow::draw_figure_borders()
{
    ui->painter_widget->drawClosedFiguresBorders(figures_model->getClosedFigures(), lineColor);
    ui->painter_widget->drawOpenedFiguresBorders(figures_model->getOpenedFigures(), lineColor);
}

void MainWindow::draw_seed_point()
{
    ui->painter_widget->drawCircle(ui->x_seed_lineEdit->text().toInt(),
                                   ui->y_seed_lineEdit->text().toInt(),
                                   1,
                                   Qt::red);
}

void MainWindow::fill_figures()
{
    if (fill_mode)
    {
        auto tmp_figures = figures_model->getClosedFigures();
        QPoint seed = QPoint(ui->x_seed_lineEdit->text().toInt(), ui->y_seed_lineEdit->text().toInt());
        fill_result = ui->painter_widget->fillFiguresWithSeed(seed, lineColor, fillColor);
    }
}

void MainWindow::fill_figures_delay()
{
    if (delay_fill_mode)
    {
        auto tmp_figures = figures_model->getClosedFigures();
        QPoint seed = QPoint(ui->x_seed_lineEdit->text().toInt(), ui->y_seed_lineEdit->text().toInt());
        ui->painter_widget->fillFiguresWithSeed(seed, delay_max_lines, lineColor, fillColor);
    }
}

void MainWindow::painter_widget_clicked(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        fill_mode = false;
        delay_fill_mode = false;
        figures_model->addPoint(event->pos());
        ui->painter_widget->repaint();
    }
    else if (event->button() == Qt::MiddleButton)
    {
        fill_mode = false;
        delay_fill_mode = false;
        ui->x_seed_lineEdit->setText(QString::number(event->pos().x()));
        ui->y_seed_lineEdit->setText(QString::number(event->pos().y()));
        ui->painter_widget->repaint();
    }
    if (event->button() == Qt::NoButton)
    {
        fill_mode = false;
        delay_fill_mode = false;
        figures_model->addPoint(event->pos());
        ui->painter_widget->repaint();
    }
}

void MainWindow::on_fill_pushButton_clicked()
{
    try
    {
        fill_mode = true;
        delay_fill_mode = false;
        is_ended_fill = false;
        ui->painter_widget->repaint();
    }
    catch (BaseException e)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",e.what());
        messageBox.setFixedSize(500,200);
    }

}


void MainWindow::on_fillDelay_pushButton_clicked()
{
    try
    {
        fill_mode = false;
        delay_fill_mode = false;
        ui->painter_widget->repaint();

        fill_mode = false;
        delay_fill_mode = true;
        is_ended_fill = false;
        auto tmp_figures = figures_model->getClosedFigures();
        QPoint seed = QPoint(ui->x_seed_lineEdit->text().toInt(), ui->y_seed_lineEdit->text().toInt());
        ui->painter_widget->drawClosedFiguresBorders(tmp_figures, lineColor);

        int max_lines = ui->painter_widget->fillFiguresWithSeed(seed, lineColor, fillColor).drawed_lines;
        for (delay_max_lines = 0; delay_max_lines <= max_lines + 1; delay_max_lines++)
        {
            ui->painter_widget->repaint();
        }
        delay_fill_mode = false;
    }
    catch (BaseException e)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",e.what());
        messageBox.setFixedSize(500,200);
    }
}


void MainWindow::on_pushButton_clicked()
{
    figures_model->pop();
    ui->painter_widget->repaint();
}

void MainWindow::show_fill_results()
{
    if (fill_mode)
    {
        QMessageBox time_message;
        time_message.information(this, "Время заливки", QString::number(fill_result.time) + " мс");
        fill_mode = false;
    }
}


void MainWindow::on_background_color_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
    if (color.isValid())
    {
        ui->painter_widget->setBackgroundColor(color);
        this->backgroundColor = color;
        ui->painter_widget->repaint();
    }
}


void MainWindow::on_line_color_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет линий");
    if (color.isValid())
    {
        this->lineColor = color;
        ui->painter_widget->repaint();
    }
}


void MainWindow::on_fillColor_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет заливки");
    if (color.isValid())
    {
        this->fillColor = color;
        ui->painter_widget->repaint();
    }
}

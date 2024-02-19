#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tableitemdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    points.clear();
    ui->setupUi(this);

    QDoubleValidator *qdv = new QDoubleValidator(-9999999, 9999999,8, this);
    qdv->setNotation(QDoubleValidator::StandardNotation);
    ui->x_lineEdit->setValidator(qdv);
    ui->y_lineEdit->setValidator(qdv);

    addingMode = false;
    connect(ui->points_tableView, &PointsTableView::signalModelDataChanged, this, &MainWindow::loadDataFromTable);

    updateTable();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearResult()
{
    ui->res_x1_lineEdit->clear();
    ui->res_x2_lineEdit->clear();
    ui->res_x3_lineEdit->clear();
    ui->res_y1_lineEdit->clear();
    ui->res_y2_lineEdit->clear();
    ui->res_y3_lineEdit->clear();
    ui->res_angle_lineEdit->clear();
    ui->angle_point_x_lineEdit->clear();
    ui->angle_point_y_lineEdit->clear();
    ui->painter_widget->clear();
    update();
}

void MainWindow::addPoint()
{
    addingMode = true;
    QPointF enteredPoint = QPointF(0,0);

    if (!ui->x_lineEdit->text().isEmpty())
        enteredPoint.setX(ui->x_lineEdit->text().replace(",",".").toDouble());
    if (!ui->y_lineEdit->text().isEmpty())
        enteredPoint.setY(ui->y_lineEdit->text().replace(",",".").toDouble());
    points.push_back(enteredPoint);
    updateTable();
    addingMode = false;
}

void MainWindow::handle_error(int rc)
{
    if (rc == OK)
        ui->status_label->setText("ОК");
    if (rc == ERR_INCORRECT_TRIANGLE)
        ui->status_label->setText("Треугольник не найден");
    if (rc == ERR_PARALLEL_LINES)
        ui->status_label->setText("Линии параллельны");
    if (rc == ERR_SAME_POINT)
        ui->status_label->setText("Точки совпадают");
}

void MainWindow::updateTable()
{
    ui->points_tableView->setData(points);
}

void MainWindow::loadDataFromTable()
{
    if (!addingMode)
        ui->points_tableView->getData(points);
}


void MainWindow::on_calculate_pushButton_pressed()
{
    clearResult();

    QVector<Triangle> triangles = formTriangleVector(points);
    QPointF point_1, point_2, point_3;
    QPointF point, pointBisec, pointHeight;;
    double angle = 0;
    bool isTriangleFound = false;
    for (Triangle t : triangles)
    {
        double curAngle;
        QPointF curPoint, curPointBisec, curPointHeight;;
        int rc = t.getMaxBHAngle(curAngle, curPoint, curPointBisec, curPointHeight);
        handle_error(rc);
        if (!rc && (curAngle > angle || isTriangleFound == false))
        {
            isTriangleFound = true;
            angle = curAngle;
            point_1 = t.points[0];
            point_2 = t.points[1];
            point_3 = t.points[2];
            point = curPoint;
            pointBisec = curPointBisec;
            pointHeight = curPointHeight;
        }
    }
    if (isTriangleFound)
    {
        handle_error(OK);
        ui->res_x1_lineEdit->setText(QString::number(point_1.x(), 'g', 8));
        ui->res_x2_lineEdit->setText(QString::number(point_2.x(), 'g', 8));
        ui->res_x3_lineEdit->setText(QString::number(point_3.x(), 'g', 8));
        ui->res_y1_lineEdit->setText(QString::number(point_1.y(), 'g', 8));
        ui->res_y2_lineEdit->setText(QString::number(point_2.y(), 'g', 8));
        ui->res_y3_lineEdit->setText(QString::number(point_3.y(), 'g', 8));
        ui->angle_point_x_lineEdit->setText(QString::number(point.x(), 'g', 8));
        ui->angle_point_y_lineEdit->setText(QString::number(point.y(), 'g', 8));
        ui->res_angle_lineEdit->setText(QString::number(angle) + "°");
        ui->painter_widget->clear();
        ui->painter_widget->addPoints({point_1, point_2, point_3, pointBisec, pointHeight});
        ui->painter_widget->addClosedLines({point_1, point_2, point_3});
        ui->painter_widget->addLines({{point, pointBisec}, {point, pointHeight}});
        qreal len_1 = abs(QVector2D(pointHeight - point_1).length());
        qreal len_2 = abs(QVector2D(pointHeight - point_2).length());
        qreal len_3 = abs(QVector2D(pointHeight - point_3).length());
        if (point_1 != point && point_2 != point)
        {
            if (len_1 < len_2)
                ui->painter_widget->addPointLines({{point_1, pointHeight}});
            else
                ui->painter_widget->addPointLines({{point_2, pointHeight}});
        }
        else if (point_2 != point && point_3 != point)
        {
            if (len_2 < len_3)
                ui->painter_widget->addPointLines({{point_2, pointHeight}});
            else
                ui->painter_widget->addPointLines({{point_3, pointHeight}});
        }
        else if (point_3 != point && point_1 != point)
        {
            if (len_3 < len_1)
                ui->painter_widget->addPointLines({{point_3, pointHeight}});
            else
                ui->painter_widget->addPointLines({{point_1, pointHeight}});
        }
    }
    if(triangles.size() == 0)
    {
        handle_error(ERR_INCORRECT_TRIANGLE);
    }
    update();
}

void MainWindow::on_add_pushButton_pressed()
{
    addPoint();
}


void MainWindow::on_clear_pushButton_pressed()
{
    ui->points_tableView->slotClear();
    clearResult();
}


void MainWindow::on_aboutProgramAction_triggered()
{
    this->taskWidget.show();
}

void MainWindow::on_save_scale_checkBox_toggled(bool checked)
{
    this->ui->painter_widget->setSaveScale(checked);
    update();
}


void MainWindow::on_exit_pushButton_clicked()
{
    exit(OK);
}


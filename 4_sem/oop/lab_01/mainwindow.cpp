#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::manage_read()
{
    char *file_name = ui->read_file_lineEdit->text().toUtf8().data();
    manager_params.filename = file_name;
    int rc = manage(manager_params, COMMAND_READ);
    handle_rc(rc);
    update();
}

void MainWindow::manage_save()
{
    char *file_name = ui->save_file_lineEdit->text().toUtf8().data();
    manager_params.filename = file_name;
    int rc = manage(manager_params, COMMAND_SAVE);
    handle_rc(rc);
    update();
}

void MainWindow::manage_move()
{

    double dx = ui->move_x_lineEdit->text().replace(",", ".").toDouble();
    double dy = ui->move_y_lineEdit->text().replace(",", ".").toDouble();
    double dz = ui->move_z_lineEdit->text().replace(",", ".").toDouble();
    manager_params.move_params = move_coefficients_create(dx ,dy, dz);
    int rc = manage(manager_params, COMMAND_MOVE);
    handle_rc(rc);
    update();
}

void MainWindow::manage_rotate()
{
    double x = ui->center_x_lineEdit->text().replace(",", ".").toDouble();
    double y = ui->center_y_lineEdit->text().replace(",", ".").toDouble();
    double z = ui->center_z_lineEdit->text().replace(",", ".").toDouble();

    double x_angle = qDegreesToRadians(ui->rotate_x_lineEdit->text().replace(",", ".").toDouble());
    double y_angle = qDegreesToRadians(ui->rotate_y_lineEdit->text().replace(",", ".").toDouble());
    double z_angle = qDegreesToRadians(ui->rotate_z_lineEdit->text().replace(",", ".").toDouble());

    point_t center = point_init(x, y, z);
    rotate_coefficients_t rotation = rotate_coefficients_init(x_angle, y_angle, z_angle);

    manager_params.center = center;
    manager_params.rotation_angle = rotation;

    int rc = manage(manager_params, COMMAND_ROTATE);
    handle_rc(rc);
    update();
}

void MainWindow::manage_scale()
{
    double x = ui->center_x_lineEdit->text().replace(",", ".").toDouble();
    double y = ui->center_y_lineEdit->text().replace(",", ".").toDouble();
    double z = ui->center_z_lineEdit->text().replace(",", ".").toDouble();

    double kx = ui->scale_x_lineEdit->text().replace(",", ".").toDouble();
    double ky = ui->scale_y_lineEdit->text().replace(",", ".").toDouble();
    double kz = ui->scale_z_lineEdit->text().replace(",", ".").toDouble();

    point_t center = point_init(x, y, z);
    scale_coefficients_t scale = scale_coefficients_init(kx, ky, kz);

    manager_params.center = center;
    manager_params.scale_params = scale;

    int rc = manage(manager_params, COMMAND_SCALE);
    handle_rc(rc);
    update();
}

void MainWindow::manage_draw()
{
    double r_width = 2, r_height = 2;
    size_t c_width = ui->widget->width(), c_height = ui->widget->height();
    QPen lines_pen = QPen(QColor(1,0,0));
    canvas_set_count_size(manager_params.canvas, r_width, r_height);
    canvas_set_screen_size(manager_params.canvas, c_width, c_height);
    canvas_set_lines_pen(manager_params.canvas, lines_pen);
    canvas_set_painter(manager_params.canvas, ui->widget->painter);
    int rc = manage(manager_params, COMMAND_DRAW);
    handle_rc(rc);
}


void MainWindow::handle_rc(int rc)
{
    switch (rc)
    {
    case OK:
        break;
    case ERR_FILE:
        ui->rc_label->setText("Не удалось открыть файл");
    break;
    case ERR_FILE_ACCESS:
        ui->rc_label->setText("Нет доступа к файлу");
    break;
    case ERR_FILE_NOT_EXIST:
        ui->rc_label->setText("Файл не существует");
    break;
    case ERR_IO:
        ui->rc_label->setText("Ошибка ввода/вывода");
    break;
    case ERR_RANGE:
        ui->rc_label->setText("Ошибка диапазона данных");
    break;
    case ERR_MEM:
        ui->rc_label->setText("Ошибка работы с динамической памятью");
    break;
    case ERR_UNKNOWN_COMMAND:
        ui->rc_label->setText("Ошибка: неизвестная команда");
    break;
    case ERR_NULL_PTR:
        ui->rc_label->setText("Ошибка: передан нулевой указатель");
    break;
    default:
        ui->rc_label->setText("Неизвестная ошибка");
    break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    manage(manager_params, COMMAND_EXIT);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->center_x_lineEdit->setValidator(new QDoubleValidator);
    ui->center_y_lineEdit->setValidator(new QDoubleValidator);
    ui->center_z_lineEdit->setValidator(new QDoubleValidator);

    ui->move_x_lineEdit->setValidator(new QDoubleValidator);
    ui->move_y_lineEdit->setValidator(new QDoubleValidator);
    ui->move_z_lineEdit->setValidator(new QDoubleValidator);

    ui->scale_x_lineEdit->setValidator(new QDoubleValidator);
    ui->scale_y_lineEdit->setValidator(new QDoubleValidator);
    ui->scale_z_lineEdit->setValidator(new QDoubleValidator);

    ui->rotate_x_lineEdit->setValidator(new QDoubleValidator);
    ui->rotate_y_lineEdit->setValidator(new QDoubleValidator);
    ui->rotate_z_lineEdit->setValidator(new QDoubleValidator);


    connect(ui->widget, &PainterWidget::paint_signal, this, &MainWindow::manage_draw);

    connect(ui->read_file_pushButton, &QPushButton::clicked, this, &MainWindow::manage_read);
    connect(ui->save_file_pushButton, &QPushButton::clicked, this, &MainWindow::manage_save);

    connect(ui->move_pushButton, &QPushButton::clicked, this, &MainWindow::manage_move);
    connect(ui->rotate_pushButton, &QPushButton::clicked, this, &MainWindow::manage_rotate);
    connect(ui->scale_pushButton, &QPushButton::clicked, this, &MainWindow::manage_scale);

}

MainWindow::~MainWindow()
{
    delete ui;
}


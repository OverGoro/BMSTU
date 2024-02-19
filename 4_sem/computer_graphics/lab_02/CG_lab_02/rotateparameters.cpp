#include "rotateparameters.h"
#include "ui_rotateparameters.h"
#include "QDoubleValidator"
RotateParameters::RotateParameters(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RotateParameters)
{
    ui->setupUi(this);
    ui->angle_lineEdit->setValidator(new QDoubleValidator());
    ui->centerX_lineEdit->setValidator(new QDoubleValidator());
    ui->centerY_lineEdit->setValidator(new QDoubleValidator());
}

RotateParameters::~RotateParameters()
{
    delete ui;
}

void RotateParameters::on_rotate_pushButton_clicked()
{
    double cx = ui->centerX_lineEdit->text().replace(",", ".").toDouble();
    double cy = ui->centerY_lineEdit->text().replace(",", ".").toDouble();
    double a = ui->angle_lineEdit->text().replace(",", ".").toDouble();
    emit applied(cx, cy, a);
}


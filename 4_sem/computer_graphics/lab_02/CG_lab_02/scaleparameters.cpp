#include "scaleparameters.h"
#include "ui_scaleparameters.h"
#include <QIntValidator>
#include <QDoubleValidator>
ScaleParameters::ScaleParameters(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScaleParameters)
{
    ui->setupUi(this);
    ui->centerX_lineEdit->setValidator(new QIntValidator());
    ui->centerY_lineEdit->setValidator(new QIntValidator());
    ui->kx_lineEdit->setValidator(new QDoubleValidator());
    ui->ky_lineEdit->setValidator(new QDoubleValidator());
}

ScaleParameters::~ScaleParameters()
{
    delete ui;
}

void ScaleParameters::on_scale_pushButton_clicked()
{
    double kx, ky;

    if (ui->kx_lineEdit->text().isEmpty())
        kx = 1;
    else
        kx = ui->kx_lineEdit->text().replace(",", ".").toDouble();

    if (ui->ky_lineEdit->text().isEmpty())
        ky = 1;
    else
        ky = ui->ky_lineEdit->text().replace(",", ".").toDouble();

    double cx = ui->centerX_lineEdit->text().replace(",", ".").toDouble();
    double cy = ui->centerY_lineEdit->text().replace(",", ".").toDouble();

    emit applied(cx, cy, kx, ky);
}


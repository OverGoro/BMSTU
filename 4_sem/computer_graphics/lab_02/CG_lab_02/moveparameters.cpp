#include "moveparameters.h"
#include "ui_moveparameters.h"
#include <QIntValidator>
moveParameters::moveParameters(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::moveParameters)
{
    ui->setupUi(this);
    ui->dx_lineEdit->setValidator(new QIntValidator);
    ui->dy_lineEdit->setValidator(new QIntValidator);
}

moveParameters::~moveParameters()
{
    delete ui;
}

void moveParameters::on_move_pushButton_clicked()
{
    double dx = ui->dx_lineEdit->text().replace(",", ".").toDouble();
    double dy = ui->dy_lineEdit->text().replace(",", ".").toDouble();
    emit applied(dx, dy);
}


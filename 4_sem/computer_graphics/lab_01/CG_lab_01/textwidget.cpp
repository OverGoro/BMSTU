#include "textwidget.h"
#include "ui_textwidget.h"

textWidget::textWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::textWidget)
{
    ui->setupUi(this);
}

textWidget::~textWidget()
{
    delete ui;
}

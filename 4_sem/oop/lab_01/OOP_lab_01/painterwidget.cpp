#include "painterwidget.h"

PainterWidget::PainterWidget(QWidget *parrent)
    :QWidget(parrent)
{
}

PainterWidget::PainterWidget(const PainterWidget &pw)
{

}

void PainterWidget::paintEvent(QPaintEvent *event)
{
    painter = new QPainter(this);
    emit paint_signal();
    painter->end();

}

void PainterWidget::resizeEvent(QResizeEvent *event)
{
    emit resize_signal();
}

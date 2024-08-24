#include "painterwidget.h"
#include <QStack>
#include <QMatrix4x4>

const QColor &PainterWidget::getBackgroundColor() const
{
    return background_color;
}

void PainterWidget::setBackgroundColor(const QColor &newBackground_color)
{
    background_color = newBackground_color;
}

void PainterWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mouseRightButtonPressed = true;
    }
    emit mouseClicked(event);
}

void PainterWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mouseRightButtonPressed = false;
    }
}

void PainterWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseRightButtonPressed)
    {
        emit(mouseMoved(event));
    }
}

PainterWidget::PainterWidget(QWidget *parrent)
    :QWidget(parrent)
{
    background_color = Qt::white;
}

PainterWidget::PainterWidget(const PainterWidget &pw)
{
    background_color = Qt::white;
}

void PainterWidget::paintEvent(QPaintEvent *event)
{
    this->buffer = QImage(width(), height(), QImage::Format_ARGB32);
    this->painter = new QPainter(&this->buffer);

    // Отрисовка в буффер
    painter->fillRect(rect(), background_color);
    emit paintSignal();
    painter->end();

    // Перенос изображения из буфера
    this->painter = new QPainter(this);
    this->painter->drawImage(0,0, buffer);
    this->painter->end();

    this->painter = nullptr;
    emit paintEndedSignal();
}

void PainterWidget::resizeEvent(QResizeEvent *event)
{
    emit resizeSignal();
}

drawResults::drawResults()
{
    this->drawed_lines = 0;
    this->time = 0;
}

#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPointF>
#include <QVector>
#include <QVector3D>
#include <QMatrix3x3>

class PainterWidget : public QWidget
{
    Q_OBJECT
public:
    QPainter *painter;        // Объект отрисовщика
public:
    PainterWidget(QWidget *parrent = 0);
    PainterWidget(const PainterWidget &pw);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:
    void paint_signal();
    void resize_signal();
};

#endif // PAINTERWIDGET_H


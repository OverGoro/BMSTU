#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPointF>
#include <QVector>
#include <QVector3D>
#include <QMatrix3x3>

struct drawLineResults
{
    double time;
};

class PainterWidget : public QWidget
{
    Q_OBJECT
public:
    QPainter *painter;        // Объект отрисовщика
    QColor background_color;
public:
    PainterWidget(QWidget *parrent = 0);
    PainterWidget(const PainterWidget &pw);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    const QColor &getBackground_color() const;
    void setBackground_color(const QColor &newBackground_color);

public slots:
    drawLineResults drawCircleBresenhem(int x_0, int y_0, int r, QColor color = Qt::black);
    drawLineResults drawCircleMidPoint(int x_0, int y_0, int r, QColor color = Qt::black);
    drawLineResults drawCircleCanonical(int x_0, int y_0, int r, QColor color = Qt::black);
    drawLineResults drawCircleParametric(int x_0, int y_0, int r, QColor color = Qt::black);
    drawLineResults drawCircleLib(int x_0, int y_0, int r, QColor color = Qt::black);

    drawLineResults drawEllipseBresenhem(int x_0, int y_0, int a, int b, QColor color = Qt::black);
    drawLineResults drawEllipseMidPoint(int x_0, int y_0, int a, int b, QColor color = Qt::black);
    drawLineResults drawEllipseCanonical(int x_0, int y_0, int a, int b, QColor color = Qt::black);
    drawLineResults drawEllipseParametric(int x_0, int y_0, int a, int b, QColor color = Qt::black);
    drawLineResults drawEllipseLib(int x_0, int y_0, int a, int b, QColor color = Qt::black);

signals:
    void paintSignal();
    void resizeSignal();

};

#endif // PAINTERWIDGET_H

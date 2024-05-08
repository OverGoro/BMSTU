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
    size_t steps_num;
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
    drawLineResults drawLineLib(int x1, int y1, int x2, int y2, QColor color = Qt::black);
    drawLineResults drawLineCDA(int x1, int y1, int x2, int y2, QColor color = Qt::black);
    drawLineResults drawLineBresInt(int x1, int y1, int x2, int y2, QColor color = Qt::black);
    drawLineResults drawLineBresFloat(int x1, int y1, int x2, int y2, QColor color = Qt::black);
    drawLineResults drawLineBresLedder(int x1, int y1, int x2, int y2, QColor color = Qt::black);
    drawLineResults drawLineVu(int x1, int y1, int x2, int y2, QColor color = Qt::black);

signals:
    void paintSignal();
    void resizeSignal();

};

#endif // PAINTERWIDGET_H

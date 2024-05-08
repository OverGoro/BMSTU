#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include "primitives.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPointF>
#include <QVector>
#include <QVector3D>
#include <QMatrix3x3>
#define TMP_COLOR QColor(255,0,255)

struct drawResults
{
    double time;
};

class PainterWidget : public QWidget
{
    Q_OBJECT
public:
    QPainter *painter;        // Объект отрисовщика
    QColor background_color;
    QColor lines_color;
    QColor fill_color;
private:
    QImage buffer; // Буффера для отрисоки виджета
public:
    PainterWidget(QWidget *parrent = 0);
    PainterWidget(const PainterWidget &pw);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    const QColor &getBackgroundColor() const;
    void setBackgroundColor(const QColor &newBackground_color);
    virtual void mousePressEvent(QMouseEvent *event) override;
public slots:
    void roundSide(Line l);
    void roundSide(QPoint p1, QPoint p2);
    void roundFigure(const std::vector<Figure> &figures);
    drawResults drawLine(int x_1, int y_1, int x_2, int y_2, QColor color = Qt::black);
    drawResults drawLine(QPoint p_1, QPoint p_2, QColor = Qt::black);
    drawResults drawOpenedFiguresBorders(const std::vector<Figure> &figures, QColor color = Qt::black);
    drawResults drawClosedFiguresBorders(const std::vector<Figure> &figures, QColor color = Qt::black);
    drawResults fillFiguresListAndFlag(const std::vector<Figure> &figures, QColor border_color = Qt::black, QColor fill_color = Qt::black);
    drawResults fillFiguresListAndFlag(const std::vector<Figure> &figures, int start_y, int end_y,
                                       QColor border_color = Qt::black, QColor fill_color = Qt::black);

signals:
    void paintSignal();
    void resizeSignal();
    void paintEndedSignal();
    void mouseClicked(QMouseEvent *event);

};

#endif // PAINTERWIDGET_H

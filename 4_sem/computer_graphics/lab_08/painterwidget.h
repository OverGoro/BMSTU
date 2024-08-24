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

class drawResults
{
public:
    drawResults();
    double time;
    int drawed_lines;
    bool mouseRightButtonPressed;
};

class PainterWidget : public QWidget
{
    Q_OBJECT
public:
    QPainter *painter;        // Объект отрисовщика
    QColor background_color;
private:
    QImage buffer; // Буффера для отрисоки виджета
    bool mouseRightButtonPressed;
public:
    PainterWidget(QWidget *parrent = 0);
    PainterWidget(const PainterWidget &pw);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    const QColor &getBackgroundColor() const;
    void setBackgroundColor(const QColor &newBackground_color);
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
public slots:
    void drawCircle(int x, int y, int rad = 1, QColor color = Qt::black);
    void roundSide(Line l);
    void roundSide(QPoint p1, QPoint p2);
    void roundFigure(const std::vector<Figure> &figures);
    drawResults drawLine(int x1, int y1, int x2, int y2, QColor color);
    drawResults drawLine(int x1, int y1, int x2, int y2, Line l, QColor color);
    drawResults drawLine(QPoint p_1, QPoint p_2, QColor = Qt::black);
    drawResults drawOpenedFiguresBorders(const std::vector<Figure> &figures, QColor color = Qt::black);
    drawResults drawClosedFiguresBorders(const std::vector<Figure> &figures, QColor color = Qt::black);
    drawResults drawClipper(int x1, int y1, int x2, int y2, QColor color = Qt::black);
    drawResults drawClippedLine(Figure &clipper, Line l,  QColor color = Qt::black);

    // drawResults fillFiguresWithSeed(QPoint seed,
    //                                 QColor border_color = Qt::black,
    //                                 QColor fill_color = Qt::gray);
    // drawResults fillFiguresWithSeed(QPoint seed,
    //                                 int max_lines,
    //                                 QColor border_color = Qt::black,
    //                                 QColor fill_color = Qt::gray);

signals:
    void paintSignal();
    void resizeSignal();
    void paintEndedSignal();
    void mouseClicked(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);

};

#endif // PAINTERWIDGET_H

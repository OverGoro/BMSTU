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

signals:
    void paintSignal();
    void resizeSignal();
    void paintEndedSignal();
    void mouseClicked(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);

};

#endif // PAINTERWIDGET_H

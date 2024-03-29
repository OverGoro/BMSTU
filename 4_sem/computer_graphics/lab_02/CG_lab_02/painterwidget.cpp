#include "painterwidget.h"

void PainterWidget::paintEvent(QPaintEvent *event)
{
   emit sign
}

void PainterWidget::resizeEvent(QResizeEvent *event)
{

}

void PainterWidget::movePoint(QPointF &point)
{
    point.setX(moveMatrix(2,0) + point.x());
    point.setY(moveMatrix(2,1) + point.y());
}

void PainterWidget::scalePoint(QPointF &point)
{
    point.setX((point.x() - scaleCenter.x()) * scaleMatrix(0,0) + scaleCenter.x());
    point.setY((point.y() - scaleCenter.y()) * scaleMatrix(1,1) + scaleCenter.y());
}

void PainterWidget::rotatePoint(QPointF &point)
{
    double x = rotationCenter.x() +
                (point.x() - rotationCenter.x()) * rotationMatrix(0,0) +
                (point.y() - rotationCenter.y()) * rotationMatrix(1,0);
    double y = rotationCenter.y() +
                (point.x() - rotationCenter.x()) * rotationMatrix(0,1) +
                (point.y() - rotationCenter.y()) * rotationMatrix(1,1);
    point.setX(x);
    point.setY(y);
}

QVector2D PainterWidget::getCountVector(const QVector2D &screen_vector)
{
    int min_size = qMin(height(), width());
    return  QVector2D(screen_vector.x() / min_size * countWidth,
                      screen_vector.y() / min_size * countHeight);
}

QPointF PainterWidget::getCountPoint(const QPointF &screen_point)
{
    int min_size = qMin(height(), width());
    return QPointF(screen_point.x() / min_size * countWidth - countWidth / 2.0,
                   screen_point.y() / min_size * countHeight - countHeight / 2.0);
}

QPointF PainterWidget::getScreenPoint(const QPointF &point, int screen_min_size)
{
    double x = (point.x() + countWidth / 2) / countWidth * screen_min_size;
    double y = height() - (point.y() + countHeight / 2) / countHeight * screen_min_size;
    return QPointF(x,y);
}

void PainterWidget::applyToAll(void (PainterWidget::*f)(QPointF &))
{
    for (auto &cl : closedLines)
    {
        for(auto &p : cl)
            (this->*f)(p);
    }
    for (auto &l : lines)
    {
        (this->*f)(l.first);
        (this->*f)(l.second);
    }
    for (auto &pl : polylines)
    {
        for(auto &p : pl)
            (this->*f)(p);
    }
}

void PainterWidget::setMoveMatrix(double dx, double dy)
{
    moveMatrix.setToIdentity();
    moveMatrix(2,0) = dx;
    moveMatrix(2,1) = dy;
}

void PainterWidget::setMoveMatrixPx(double dx, double dy)
{    
    int min_size = qMin(height(), width());
    dx = dx * countWidth / min_size;
    dy = dy * countHeight / min_size;
    setMoveMatrix(dx, dy);
}


void PainterWidget::setScaleMatrix(double cx, double cy, double kx, double ky)
{
    setCenterPoint(getScreenPoint({cx, cy}, qMin(this->width(), this->height())));
    scaleMatrix.setToIdentity();
    scaleMatrix(0,0) = kx;
    scaleMatrix(1,1) = ky;
    scaleCenter = QPointF(cx, cy);
}

void PainterWidget::setScaleMatrixPx(double cx, double cy, double kx, double ky)
{
    setCenterPoint({cx, cy});
    int min_size = qMin(height(), width());
    cx = cx * countWidth / min_size;
    cy = cy * countHeight / min_size;
    setScaleMatrix(cx, cy, kx, ky);
}

void PainterWidget::setRotationMatrix(double cx, double cy, double angle)
{
    setCenterPoint(getScreenPoint({cx, cy}, qMin(this->width(), this->height())));
    rotationMatrix.setToIdentity();
    angle = qDegreesToRadians(angle);
    rotationMatrix(0, 0) = qCos(angle);
    rotationMatrix(0, 1) = -qSin(angle);
    rotationMatrix(1, 0) = qSin(angle);
    rotationMatrix(1, 1) = qCos(angle);
    rotationCenter = QPointF(cx, cy);

}

void PainterWidget::setRotationMatrixPx(double cx, double cy, double angle)
{
    setCenterPoint({cx, cy});
    int min_size = qMin(height(), width());
    cx = cx * countWidth / min_size;
    cy = cy * countHeight / min_size;
    setRotationMatrix(cx,cy, angle);
}

void PainterWidget::moveAll()
{
    applyToAll(&PainterWidget::movePoint);
}

void PainterWidget::scaleAll()
{
    applyToAll(&PainterWidget::scalePoint);
}

void PainterWidget::rotateAll()
{
    applyToAll(&PainterWidget::rotatePoint);
}

void PainterWidget::addClosedLines(const QVector<QPointF> &points)
{
    this->closedLines.push_back(points);
}

void PainterWidget::addLines(const QVector<QPair<QPointF, QPointF> > &lines)
{
    this->lines.append(lines);
}

void PainterWidget::addPolyline(const QVector<QPointF> &points)
{
    this->polylines.push_back(points);
}

void PainterWidget::addByFunc(double f(double), double start_x, double end_x, size_t points_num)
{
    // Иневрсия интервала функции, если конец меньше начала
    if (end_x < start_x)
    {
        double tmp = start_x;
        start_x = end_x;
        end_x = tmp;
    }
    // Шаг расчета функции
    double step = (end_x - start_x) / points_num;

    // Точки ломаной
    QVector<QPointF> points;

    // Текущее значение Х
    double x = start_x;

    // Добавление точек
    while (x <= end_x)
    {
        double y = f(x);
        if (!std::isnan(y))
            points.push_back(QPointF(x,f(x)));
        x += step;
    }

    // Если получено хотя бы 2 точки, то добавить ломаную в отрисовку
    if (points.size() > 1)
        addPolyline(points);
}

void PainterWidget::clear()
{
    this->lines.clear();
    this->closedLines.clear();
    this->polylines.clear();
}

void PainterWidget::drawClosedLines()
{
    double min_size = qMin(width(), height()); // Минимальный размер окна
    for (const auto &cl : closedLines)
    {
        if (cl.size() > 1)
        {
            qsizetype i = 0;
            do
            {
                QPointF p1 = getScreenPoint(cl[i], min_size);
                QPointF p2 = getScreenPoint(cl[(i + 1) % cl.size()], min_size);
                this->painter->drawLine(p1, p2);
                i++;
            } while (i < cl.size());
        }
    }
}

void PainterWidget::drawLines()
{
    double min_size = qMin(width(), height()); // Минимальный размер окна
    for (const auto &l : lines)
    {
        QPointF p1 = getScreenPoint(l.first, min_size);
        QPointF p2 = getScreenPoint(l.second, min_size);
        painter->drawLine(p1, p2);
    }
}

void PainterWidget::drawPolylines()
{
    int min_size = qMin(width(), height()); // Минимальный размер окна
    for (const auto &pl : polylines)
    {
        for (qsizetype i = 1; i < pl.size(); i++)
        {
            QPointF p1 = getScreenPoint(pl[i-1], min_size);
            QPointF p2 = getScreenPoint(pl[i], min_size);
            this->painter->drawLine(p1, p2);
        }
    }
}

void PainterWidget::drawPoint(const QPointF &p)
{
    painter->drawPoint(p);
}

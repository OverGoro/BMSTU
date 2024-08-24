#include "painterwidget.h"
#include "painterexceptions.h"
#include <chrono>
#include <QStack>
#include <exception>
#include <algorithm>
#include <QMatrix4x4>>

drawResults PainterWidget::drawLine(int x1, int y1, int x2, int y2, QColor color, bool flag)
{
    if (flag && painter)
    {
        auto pen = QPen(color);
        pen.setWidth(2);
        painter->setPen(pen);
    }
    else if (painter)
    {
        auto pen = QPen(color);
        pen.setWidth(1);
        painter->setPen(pen);
    }

    if (x1 != x2 || y1 != y2)
    {
        int len_x = abs(x2 - x1);
        int len_y = abs(y2 - y1);

        if (len_x > len_y)
        {
            if (x1 > x2)
            {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }
            double dy = y2 - y1;
            double m = dy / len_x;
            double y = y1;
            for (int x = x1; x < x2; x++)
            {
                if (painter)
                    painter->drawPoint(x, std::round(y));
                y += m;
            }
        }
        else
        {
            if (y1 > y2)
            {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }
            double dx = x2 - x1;
            double n = dx / len_y;
            double x = x1;
            for (int y = y1; y < y2; y++)
            {
                if (painter)
                    painter->drawPoint(std::round(x), y);
                x += n;
            }
        }
    }
    else
    {
        if (painter)
            painter->drawPoint(x1, y1);
    }
    if (painter)
        painter->drawPoint(x2, y2);
    return drawResults();
    return drawResults();
}

drawResults PainterWidget::drawLine(int xs, int ys, int xe, int ye, Line l, QColor color)
{
    if (painter)
        painter->setPen(color);

    int x1 = l.x_1;
    int x2 = l.x_2;
    int y1 = l.y_1;
    int y2 = l.y_2;

    if (x1 != x2 || y1 != y2)
    {
        int len_x = abs(x2 - x1);
        int len_y = abs(y2 - y1);

        if (len_x > len_y)
        {
            if (x1 > x2)
            {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }
            double dy = y2 - y1;
            double m = dy / len_x;
            double y = y1;
            for (int x = x1; x <= x2; x++)
            {
                if (painter && x <= std::max(xs, xe) && x >= std::min(xs, xe)
                    && round(y) >= std::min(ys, ye) && std::round(y) <= std::max(ys, ye))
                    painter->drawPoint(x, std::round(y));
                y += m;
            }
        }
        else
        {
            if (y1 > y2)
            {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }
            double dx = x2 - x1;
            double n = dx / len_y;
            double x = x1;
            for (int y = y1; y <= y2; y++)
            {
                if (painter && round(x) <= std::max(xe, xs) && round(x) >= std::min(xs, xe)
                    && y >= std::min(ys, ye) && y <= std::max(ys, ye))
                    painter->drawPoint(round(x), y);
                x += n;
            }
        }
    }
    else
    {
        if (painter && x1 >= std::min(xs, xe) && x1 <= std::max(xs, xe)
            && y1 >= std::min(ys, ye) && y1 <= std::max(ys, ye))
            painter->drawPoint(x1, y1);
    }

    return drawResults();
}

drawResults PainterWidget::drawLine(QPoint p_1, QPoint p_2, QColor color)
{
    return drawLine(p_1.x(), p_1.y(), p_2.x(), p_2.y(), color);
}

drawResults PainterWidget::drawOpenedFiguresBorders(const std::vector<Figure> &figures, QColor border_color)
{
    drawResults res;
    painter->setPen(border_color);
    for (auto f : figures)
    {
        if (f.points.size() >= 1)
        {
            for (int i = 1; i < f.points.size(); i++)
            {
                res.time += drawLine(f.points[i - 1], f.points[i], border_color).time;
            }
            if (f.points.size() == 1)
            {
                if (painter)
                    painter->drawPoint(f.points[0]);
            }
        }
    }
    return res;
}

drawResults PainterWidget::drawClosedFiguresBorders(const std::vector<Figure> &figures, QColor border_color)
{
    drawResults res;
    if (painter)
        painter->setPen(border_color);
    for (auto f : figures)
    {
        if (f.points.size() >= 1)
        {
            for (int i = 1; i < f.points.size(); i++)
            {
                res.time += drawLine(f.points[i - 1], f.points[i], border_color).time;
            }
            drawLine(f.points[0], f.points[f.points.size() - 1], border_color);
        }
    }
    return res;
}

drawResults PainterWidget::drawClipper(int x1, int y1, int x2, int y2, QColor color)
{
    drawResults res;
    if (painter)
    {
        painter->setPen(color);
        painter->drawRect(x1,y1, x2 - x1, y2 - y1);
    }
    return res;
}


double scalar_mult(const QVector2D &v1, const QVector2D &v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}
QVector2D get_vector(const QPoint &p1, const QPoint &p2)
{
    return QVector2D(p2.x() - p1.x(), p2.y() - p1.y());
}
double get_vector_mult(const QVector2D &v1, const QVector2D &v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}

bool check_convexity_polygon(Figure &clipper) {
    if (clipper.points.size() < 3)
        return false;

    int n = clipper.points.size();
    int sign = 0;

    for (int i = 0; i < n; i++) {
        QVector2D v1 = get_vector(clipper.points[i], clipper.points[(i + 1) % n]);
        QVector2D v2 = get_vector(clipper.points[(i + 1) % n], clipper.points[(i + 2) % n]);
        int cross_product = get_vector_mult(v1, v2);

        if (cross_product != 0) {
            if (sign == 0) {
                sign = (cross_product > 0) ? 1 : -1;
            } else if ((cross_product > 0 && sign < 0) || (cross_product < 0 && sign > 0)) {
                return false;
            }
        }
    }

    // if (sign < 0) {
    //     std::reverse(clipper.points.begin(), clipper.points.end());
    // }

    return true;
}

int sign(double value)
{
    if (value > 0) return 1;
    if (value < 0) return -1;
    return 0;
}

int visibility(const QPoint &point, const QPoint &begin, const QPoint &end)
{
    double tmp1 = (point.x() - begin.x()) * (end.y() - begin.y());
    double tmp2 = (point.y() - begin.y()) * (end.x() - begin.x());
    double res = tmp1 - tmp2;

    if (-1e-7 < res && res < 1e-7)
    {
        res = 0;
    }

    return sign(res);
}

bool check_lines_crossing(const QPoint &begin1, const QPoint &end1, const QPoint &begin2, const QPoint &end2)
{
    int vis1 = visibility(begin1, begin2, end2);
    int vis2 = visibility(end1, begin2, end2);

    return (vis1 < 0 && vis2 > 0) || (vis1 > 0 && vis2 < 0);
}

QPoint get_cross_point(const QPoint &b1, const QPoint &e1, const QPoint &b2, const QPoint &e2)
{
    float A1 = e1.y() - b1.y();
    float B1 = b1.x() - e1.x();
    float C1 = A1 * b1.x() + B1 * b1.y();

    float A2 = e2.y() - b2.y();
    float B2 = b2.x() - e2.x();
    float C2 = A2 * b2.x() + B2 * b2.y();

    float determinant = A1 * B2 - A2 * B1;

    if (fabs(determinant) < 1e-10) {
        return QPoint(); // Линии параллельны и не пересекаются
    } else {
        float x = (B2 * C1 - B1 * C2) / determinant;
        float y = (A1 * C2 - A2 * C1) / determinant;
        return QPoint(static_cast<int>(x), static_cast<int>(y));
    }
}

drawResults PainterWidget::drawClippedFigure(Figure &polygon, Figure &clipper, QColor color)
{
    if (!check_convexity_polygon(clipper))
        return drawResults();

    std::vector<QPoint> outputList = polygon.getPoints();
    QPoint cp1 = clipper.points.back();

    for (const auto &cp2 : clipper.points) {
        std::vector<QPoint> inputList = outputList;
        outputList.clear();

        if (inputList.empty())
            break;

        QPoint s = inputList.back();

        for (const auto &e : inputList) {
            if (visibility(e, cp1, cp2) >= 0) {  // Внутри или на границе
                if (visibility(s, cp1, cp2) < 0) {  // Снаружи
                    outputList.push_back(get_cross_point(s, e, cp1, cp2));
                }
                outputList.push_back(e);
            } else if (visibility(s, cp1, cp2) >= 0) {  // Снаружи
                outputList.push_back(get_cross_point(s, e, cp1, cp2));
            }
            s = e;
        }

        cp1 = cp2;
    }

    for (size_t i = 0; i < outputList.size(); i++)
    {
        drawLine(outputList[i].x(), outputList[i].y(),
                 outputList[(i + 1) % outputList.size()].x(), outputList[(i + 1) % outputList.size()].y(),color, true);
    }

    return drawResults();
}

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
void PainterWidget::drawCircle(int x, int y, int rad, QColor color)
{
    if (painter)
    {
        painter->setPen(color);
        painter->setBrush(color);
        painter->drawEllipse(x - rad / 2, y - rad / 2,rad, rad);
    }
}

void PainterWidget::roundSide(Line l)
{
    roundSide({l.x_1, l.y_1}, {l.x_2, l.y_2});
}

void PainterWidget::roundSide(QPoint p1, QPoint p2)
{
    if (p1.y() == p2.y())
        return;
    Line l1(p1,p2);

    int y = l1.y_1;

    int y_max = l1.y_2;

    while (y < y_max)
    {
        int tmp_x = l1.x(y);
        if (buffer.pixelColor(tmp_x + 1, y) != TMP_COLOR)
        {
            tmp_x++;
        }
        else
        {
            tmp_x += 2;
        }
        buffer.setPixelColor(tmp_x, y, TMP_COLOR);
        y++;
    }
}

void PainterWidget::roundFigure(const std::vector<Figure> &figures)
{
    for (auto f : figures)
    {
        auto lines = f.getLines();
        for (auto l : lines)
        {
            roundSide(l);
        }
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

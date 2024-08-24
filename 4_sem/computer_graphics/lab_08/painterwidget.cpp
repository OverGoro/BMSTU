#include "painterwidget.h"
#include "painterexceptions.h"
#include <chrono>
#include <QStack>
#include <exception>
#include <algorithm>
drawResults PainterWidget::drawLine(int x1, int y1, int x2, int y2, QColor color)
{
    if (painter)
        painter->setPen(color);

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

bool check_convexity_polygon(Figure &clipper)
{
    if (clipper.points.size() < 3)
        throw FewToCloseExcpetion();
    auto v1 = get_vector(clipper.points[0], clipper.points[1]);
    auto v2 = get_vector(clipper.points[1], clipper.points[2]);
    int sign = 0;
    if (get_vector_mult(v1, v2) > 0)
        sign = 1;
    else
        sign = -1;

    for (auto i = 0; i < clipper.points.size(); i++)
    {
        auto vecti = get_vector(clipper.points[i-2], clipper.points[i-1]);
        auto vectj = get_vector(clipper.points[i-1], clipper.points[i]);\
        if (sign * get_vector_mult(vecti, vectj) < 0)
            return false;
    }
    if (sign < 0)
    {
        reverse(clipper.points.begin(), clipper.points.end());
    }
    return true;
}

QVector2D get_normal(const QPoint &p1, const QPoint &p2, const QPoint &p3)
{
    auto v = get_vector(p1,p2);
    QVector2D normal;
    if (v.y())
        normal = {1, - v.x() / v.y()};
    else
        normal = {0, 1};
    if (scalar_mult(get_vector(p2, p3), normal) < 0)
    {
        normal.setX(-normal.x());
        normal.setY(-normal.y());
    }
    return normal;
}
drawResults PainterWidget::drawClippedLine(Figure &clipper, Line l, QColor color)
{
    drawResults res;
    if (clipper.points.size() < 3)
        return res;
    double t_beg = 0.0;
    double t_end = 1.0;

    auto p1 = l.getFirstPoint();
    auto p2 = l.getSecondPoint();

    QVector2D d(p2.x() - p1.x(), p2.y() - p1.y());

    for (int i = 0; i < clipper.points.size(); i++)
    {
        auto current = clipper.points[i];
        auto next = clipper.points[(i + 1) % clipper.points.size()];

        QVector2D edge = get_vector(current, next);
        QVector2D normal = get_normal(current, next, clipper.points[(i + 2) % clipper.points.size()]);

        QVector2D w(p1.x() - current.x(), p1.y() - current.y());
        double d_scalar = scalar_mult(d, normal);
        double w_scalar = scalar_mult(w, normal);

        if (d_scalar == 0)
        {
            if (w_scalar < 0)
                return res; // Линия за пределами окна отсечения
            else
                continue; // Линия параллельна и внутри окна отсечения
        }

        double t = -w_scalar / d_scalar;

        if (d_scalar > 0)
        {
            if (t > 1)
                return res; // Линия за пределами окна отсечения
            t_beg = std::max(t_beg, t);
        }
        else
        {
            if (t < 0)
                return res; // Линия за пределами окна отсечения
            t_end = std::min(t_end, t);
        }

        if (t_beg > t_end)
            return res; // Линия за пределами окна отсечения
    }

    if (t_beg <= t_end)
    {
        QPoint pr1(round(p1.x() + d.x() * t_beg), round(p1.y() + d.y() * t_beg));
        QPoint pr2(round(p1.x() + d.x() * t_end), round(p1.y() + d.y() * t_end));
        if (painter)
        {
            drawLine(pr1.x(), pr1.y(), pr2.x(), pr2.y(), l, color);
        }
    }
    return res;
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

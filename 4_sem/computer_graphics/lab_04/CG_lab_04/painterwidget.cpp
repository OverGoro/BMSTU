#include "painterwidget.h"

const QColor &PainterWidget::getBackground_color() const
{
    return background_color;
}

void PainterWidget::setBackground_color(const QColor &newBackground_color)
{
    background_color = newBackground_color;
}

drawLineResults PainterWidget::drawCircleBresenhem(int x_0, int y_0, int r, QColor color)
{
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();
    r = (int)r;
    int cur_x = 0, cur_y = r;
    int rr = r * r;

    int end_x = ceil(r / sqrt(2));
    int end_y = ceil(r / sqrt(2));

    int delta = (cur_x + 1) * (cur_x + 1) + (cur_y - 1) * (cur_y - 1) - rr;

    if (painter)
    {
        painter->setPen(color);
        painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
        painter->drawPoint(x_0 - cur_x, y_0 - cur_y);

        painter->drawPoint(x_0 + cur_y, y_0 + cur_x);
        painter->drawPoint(x_0 - cur_y, y_0 + cur_x);
        painter->drawPoint(x_0 + cur_y, y_0 - cur_x);
        painter->drawPoint(x_0 - cur_y, y_0 - cur_x);
    }

    while (cur_x <= end_x && cur_y >= end_y)
    {
        if (delta > 0)
        {
            int delta_2 = abs((cur_x + 1) * (cur_x + 1)  + (cur_y - 1) * (cur_y - 1) - rr) -
                             abs(cur_x * cur_x + (cur_y - 1) * (cur_y - 1) - rr);
            if (delta_2 > 0)
            {
                --cur_y;
                delta += - 2 * cur_y + 1;
            }
            else
            {
                ++cur_x;
                --cur_y;
                delta += 2 * cur_x - 2 * cur_y + 2;
            }
        }
        else if (delta < 0)
        {
            int delta_1 = abs((cur_x + 1) * (cur_x + 1) + cur_y * cur_y - rr) -
                             abs((cur_x + 1) * (cur_x + 1) + (cur_y - 1) * (cur_y - 1) - rr);
            if (delta_1 >= 0)
            {
                ++cur_x;
                --cur_y;
                delta += 2 * cur_x - 2 * cur_y + 2;
            }
            else
            {
                ++cur_x;
                delta += 2 * cur_x + 1;
            }
        }
        else
        {
            ++cur_x;
            --cur_y;
            delta += 2 * cur_x - 2 * cur_y + 2;

        }
        if (painter)
        {
            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);

            painter->drawPoint(x_0 + cur_y, y_0 + cur_x);
            painter->drawPoint(x_0 - cur_y, y_0 + cur_x);
            painter->drawPoint(x_0 + cur_y, y_0 - cur_x);
            painter->drawPoint(x_0 - cur_y, y_0 - cur_x);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawCircleMidPoint(int x_0, int y_0, int r, QColor color)
{
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();

    double cur_x = 0, cur_y = r;
    int rr = r * r;
    int rr2 = rr * 2;

    double f = 5.0 / 4.0 * rr - rr * r;
    double dx = rr2 * cur_x;
    double dy = rr2 * cur_y;

    if (painter)
    {
        painter->setPen(color);
        painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
        painter->drawPoint(x_0 - cur_x, y_0 - cur_y);

        painter->drawPoint(x_0 + cur_y, y_0 + cur_x);
        painter->drawPoint(x_0 - cur_y, y_0 + cur_x);
        painter->drawPoint(x_0 + cur_y, y_0 - cur_x);
        painter->drawPoint(x_0 - cur_y, y_0 - cur_x);
    }
    while (dx < dy)
    {
        ++cur_x;
        dx += rr2;
        if (f < 0)
            f += dx + rr;
        else
        {
            dy -= rr2;
            --cur_y;
            f += dx - dy + rr;
        }
        if (painter)
        {
            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);

            painter->drawPoint(x_0 + cur_y, y_0 + cur_x);
            painter->drawPoint(x_0 - cur_y, y_0 + cur_x);
            painter->drawPoint(x_0 + cur_y, y_0 - cur_x);
            painter->drawPoint(x_0 - cur_y, y_0 - cur_x);
        }
    }
//    f = rr * ((cur_x + 0.5) * (cur_x + 0.5) + (cur_y - 1) * (cur_y -1)) - rr * rr;
//    while (cur_y >= 0)
//    {
//        --cur_y;
//        dy -= 2 * rr;
//        if (f > 0)
//            f += -dy + rr;
//        else
//        {
//            ++cur_x;
//            dx += 2 * rr;
//            f += dx - dy + rr;
//        }
//        if (painter)
//        {
//            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
//            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
//            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
//            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);
//        }
//    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawCircleCanonical(int x_0, int y_0, int r, QColor color)
{
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();

    int cur_x = 0;
    int cur_y = r;
    int rr = r * r;
    double end_x = round(r / sqrt(2));

    double cur_square = rr;

    if (painter)
    {
        painter->setPen(color);
        painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
        painter->drawPoint(x_0 - cur_x, y_0 - cur_y);

        painter->drawPoint(x_0 + cur_y, y_0 + cur_x);
        painter->drawPoint(x_0 - cur_y, y_0 + cur_x);
        painter->drawPoint(x_0 + cur_y, y_0 - cur_x);
        painter->drawPoint(x_0 - cur_y, y_0 - cur_x);
    }

    for (cur_x = 0; cur_x <= end_x; ++cur_x)
    {
        cur_y = round(sqrt(cur_square));
        cur_square += - 2 * cur_x - 1;
        if (painter)
        {
            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);

            painter->drawPoint(x_0 + cur_y, y_0 + cur_x);
            painter->drawPoint(x_0 - cur_y, y_0 + cur_x);
            painter->drawPoint(x_0 + cur_y, y_0 - cur_x);
            painter->drawPoint(x_0 - cur_y, y_0 - cur_x);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawCircleParametric(int x_0, int y_0, int r, QColor color)
{
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();

    int cur_x = 0;
    int cur_y = r;

    if (painter)
    {
        painter->setPen(color);
        painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
        painter->drawPoint(x_0 - cur_x, y_0 - cur_y);

        painter->drawPoint(x_0 + cur_y, y_0 + cur_x);
        painter->drawPoint(x_0 - cur_y, y_0 + cur_x);
        painter->drawPoint(x_0 + cur_y, y_0 - cur_x);
        painter->drawPoint(x_0 - cur_y, y_0 - cur_x);
    }

    double step = 1 / (double)r;
    double end_alpha = M_PI / 4 + step;

    for (double alpha = 0; alpha < end_alpha; alpha += step)
    {
        cur_x = round(r * cos(alpha));
        cur_y = round(r * sin(alpha));
        if (painter)
        {
            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);

            painter->drawPoint(x_0 + cur_y, y_0 + cur_x);
            painter->drawPoint(x_0 - cur_y, y_0 + cur_x);
            painter->drawPoint(x_0 + cur_y, y_0 - cur_x);
            painter->drawPoint(x_0 - cur_y, y_0 - cur_x);
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawCircleLib(int x_0, int y_0, int r, QColor color)
{
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();
    if (painter)
    {
        painter->setPen(color);
        painter->drawEllipse(x_0 - r, y_0 - r, 2 * r, 2 * r);
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawEllipseBresenhem(int x_0, int y_0, int a, int b, QColor color)
{
#define EPS 1e-3
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();

    int aa = a * a;
    int bb = b * b;

    int cur_x = 0;
    int cur_y = b;

    if (painter)
    {
        painter->setPen(color);
        painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
    }
    double k = 1 - bb / ((double)aa);

    // Квадрат расстояния от центра эллипса до диагонального пикселя
    int rrd = (cur_x + 1) * (cur_x + 1) + (cur_y - 1) * (cur_y - 1);

    // Квадрат расстояния от центра эллипса до точки на эллипсе с x = cur_x + 1
    double rre = bb + k;

    double delta = rrd - rre;

    if (a != 0 && b != 0)
    {
        while (cur_x <= a && cur_y >= 0)
        {
            if (delta > 0)
            {
                int delta_2 = abs((cur_x + 1) * (cur_x + 1)  + (cur_y - 1) * (cur_y - 1) - rre) -
                                 abs(cur_x * cur_x + (cur_y - 1) * (cur_y - 1) - rre);
                if (delta_2 > 0)
                {
                    --cur_y;
                    rrd = (cur_x + 1) * (cur_x + 1) + (cur_y - 1) * (cur_y - 1);
                    delta = rrd - rre;
                }
                else
                {
                    ++cur_x;
                    --cur_y;
                    rre = bb + k * cur_x * cur_x;
                    rrd = (cur_x + 1) * (cur_x + 1) + (cur_y - 1) * (cur_y - 1);
                    delta = rrd - rre;
                }
            }
            else if (delta < 0)
            {
                int delta_1 = abs((cur_x + 1) * (cur_x + 1) + cur_y * cur_y - rre) -
                                 abs((cur_x + 1) * (cur_x + 1) + (cur_y - 1) * (cur_y - 1) - rre);
                if (delta_1 >= 0)
                {
                    ++cur_x;
                    --cur_y;
                    rre = bb + k * cur_x * cur_x;
                    rrd = (cur_x + 1) * (cur_x + 1) + (cur_y - 1) * (cur_y - 1);
                    delta = rrd - rre;
                }
                else
                {
                    ++cur_x;
                    rre = bb + k * cur_x * cur_x;
                    rrd = (cur_x + 1) * (cur_x + 1) + (cur_y - 1) * (cur_y - 1);
                    delta = rrd - rre;
                }
            }
            else
            {
                ++cur_x;
                --cur_y;
                rre = bb + k * cur_x * cur_x;
                rrd = (cur_x + 1) * (cur_x + 1) + (cur_y - 1) * (cur_y - 1);
                delta = rrd - rre;
            }
            if (painter)
            {
                painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
                painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
                painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
                painter->drawPoint(x_0 - cur_x, y_0 - cur_y);
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
#undef EPS
}

drawLineResults PainterWidget::drawEllipseMidPoint(int x_0, int y_0, int a, int b, QColor color)
{
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();

    int cur_x = 0, cur_y = b;
    double aa = a * a;
    double bb = b * b;
    double aa2 = aa * 2;
    double bb2 = bb * 2;

    double f = bb + 0.25 * aa - aa * b;
    double dx = 0;
    double dy = 2 * aa * cur_y;

    if (painter)
    {
        painter->setPen(color);
        painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
    }
    // Первый интервал
    while (dx < dy)
    {
        ++cur_x;
        dx += bb2;
        // Горизонтальный шаг
        if (f < 0)
            f += dx + bb;
        // Диагональный шаг
        else
        {
            dy -= aa2;
            --cur_y;
            f += dx - dy + bb;
        }
        if (painter)
        {
            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);
        }
    }
    f = bb * (cur_x + 0.5) * (cur_x + 0.5) + aa * (cur_y - 1) * (cur_y - 1) - aa * bb;

    // Второй интервал
    while (cur_y >= 0)
    {
        --cur_y;
        dy -= aa2;
        // Вертикальный шаг
        if (f > 0)
            f += -dy + aa;
        // Диагональный шаг
        else
        {
            ++cur_x;
            dx += bb2;
            f += dx - dy + aa;
        }
        if (painter)
        {
            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawEllipseCanonical(int x_0, int y_0, int a, int b, QColor color)
{
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();

    int cur_x = 0, cur_y = b;

    int aa = a * a;
    int bb = b * b;
    double aabb = aa / (double)bb;
    double bbaa = bb / (double)aa;

    double end_x = aa / sqrt(aa + bb);
    double end_y = sqrt(bb - bbaa * end_x * end_x);

    if (painter)
    {
        painter->setPen(color);
        painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
        painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
    }   
    while (cur_x <= end_x)
    {
        ++cur_x;
        cur_y = round(sqrt(bb - bbaa * cur_x * cur_x));
        if (painter)
        {
            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);
        }
    }

    cur_y = end_y;
    while (cur_y > 0)
    {
        --cur_y;
        cur_x = round(sqrt(aa - aabb * cur_y * cur_y));
        if (painter)
        {
            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawEllipseParametric(int x_0, int y_0, int a, int b, QColor color)
{
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();

    int cur_x = 0, cur_y = b;

    if (painter)
    {
        painter->setPen(color);
        painter->drawPoint(0, b);
        painter->drawPoint(0, -b);
        painter->drawPoint(a, 0);
        painter->drawPoint(-a, 0);
    }
    double step = 1 / (double)qMax(a, b);
    double end_alpha = M_PI / 2 + step;
    for (double alpha = 0; alpha < end_alpha; alpha += step)
    {
        cur_x = round(a * cos(alpha));
        cur_y = round(b * sin(alpha));
        if (painter)
        {
            painter->drawPoint(x_0 + cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 + cur_y);
            painter->drawPoint(x_0 + cur_x, y_0 - cur_y);
            painter->drawPoint(x_0 - cur_x, y_0 - cur_y);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawEllipseLib(int x_0, int y_0, int a, int b, QColor color)
{
    drawLineResults result = {.time = 0};
    auto start = std::chrono::steady_clock::now();

    if (painter)
    {
        painter->setPen(color);
        painter->drawEllipse(x_0 - a, y_0 - b, a * 2, b * 2);
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
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
    this->painter = new QPainter(this);
    painter->fillRect(rect(), background_color);
    emit paintSignal();
    painter->end();
    this->painter = nullptr;
}

void PainterWidget::resizeEvent(QResizeEvent *event)
{
    emit resizeSignal();
}

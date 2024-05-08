#include "painterwidget.h"

const QColor &PainterWidget::getBackground_color() const
{
    return background_color;
}

void PainterWidget::setBackground_color(const QColor &newBackground_color)
{
    background_color = newBackground_color;
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

drawLineResults PainterWidget::drawLineLib(int x1, int y1, int x2, int y2, QColor color)
{
    if (painter)
        painter->setPen(color);
    drawLineResults result = {0,0};

    auto start = std::chrono::steady_clock::now();

    if (painter != NULL)
        painter->drawLine(x1, y1, x2, y2);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();
    result.steps_num = qMin(qAbs(x2 - x1), qAbs(y2 - y1));

    return result;
}

drawLineResults PainterWidget::drawLineCDA(int x1, int y1, int x2, int y2, QColor color)
{
    if (painter)
        painter->setPen(color);
    drawLineResults result = {0,0};

    double steps_num = 0;
    auto start = std::chrono::steady_clock::now();


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
                steps_num += m;
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
                steps_num += n;
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
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();
    result.steps_num = qAbs(steps_num);
    return result;
}

drawLineResults PainterWidget::drawLineBresFloat(int x1, int y1, int x2, int y2, QColor color)
{
    if (painter)
        painter->setPen(color);

    drawLineResults result = {0,0};
    auto start = std::chrono::steady_clock::now();

    double dx = (double)qAbs(x2 - x1);
    double dy = (double)qAbs(y2 - y1);

    double err = 0;


    if (dx >= dy)
    {
        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        double m = abs(y2 - y1) / dx;
        int y = y1;
        int sy = y2 > y1 ? 1 : -1;
        for (int x = x1; x < x2; ++x)
        {
            if (err >= 0.5)
            {
                err -= 1;
                y += sy;
                result.steps_num++;
            }
            if(painter)
                painter->drawPoint(x, y);
            err += m;
        }
    }
    else
    {
        if (y1 > y2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        double n = abs(x2 - x1) / dy;
        int x = x1;
        int sx = x2 > x1 ? 1 : -1;
        for (int y = y1; y < y2; ++y)
        {
            if (err >= 0.5)
            {
                err -= 1;
                x += sx;
                result.steps_num++;
            }
            if(painter)
                painter->drawPoint(x, y);
            err += n;
        }
    }
    if (painter)
        painter->drawPoint(x2, y2);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawLineBresInt(int x1, int y1, int x2, int y2, QColor color)
{
    if (painter)
        painter->setPen(color);

    drawLineResults result = {0,0};
    auto start = std::chrono::steady_clock::now();

    int len_x = qAbs(x2 - x1);
    int len_y = qAbs(y2 - y1);



    if (len_x >= len_y)
    {
        int err = 2 * len_y - len_x;
        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        int dx = x2 - x1;
        int dy = y2 - y1;

        int m = std::abs(2 * dy);
        int de = 2 * dx;

        int y = y1;
        int sy = y2 > y1 ? 1 : -1;
        for (int x = x1; x < x2; ++x)
        {
            if(painter)
                painter->drawPoint(x, y);
            if (err > 0)
            {
                err -= de;
                y += sy;
                result.steps_num++;
            }
            err += m;
        }
    }
    else
    {
        int err = 2 * len_x - len_y;
        if (y1 > y2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        int dx = x2 - x1;
        int dy = y2 - y1;

        int n = std::abs(2 * dx);
        int de = 2 * dy;

        int x = x1;
        int sx = x2 > x1 ? 1 : -1;
        for (int y = y1; y < y2; ++y)
        {
            if(painter)
                painter->drawPoint(x, y);
            if (err > 0)
            {
                err -= de;
                x += sx;
                result.steps_num++;
            }
            err += n;
        }
    }
    if (painter)
        painter->drawPoint(x2, y2);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawLineBresLedder(int x1, int y1, int x2, int y2, QColor color)
{
    drawLineResults result = {0,0};
    auto start = std::chrono::steady_clock::now();
    double len_x = abs(x2 - x1);
    double len_y = abs(y2 - y1);

    const int I = 256;

    if (len_x > len_y)
    {
        double m = (I * len_y) / len_x; // Тангенс на кол-во цветов
        double w = I - m;
        double e = 0.5;
        color.setAlphaF(1 - m / I);
        if (painter)
        {
            painter->setPen(color);
            painter->drawPoint(x1, y1);
        }

        int y = y1;
        int sy = y2 > y1 ? 1 : -1;
        int sx = x2 > x1 ? 1 : -1;
        for (int x = x1; x != x2; x += sx)
        {
            if (e < w)
            {
                e += m;
            }
            else
            {
                e -= w;
                y += sy;
                result.steps_num++;
            }
            color.setAlphaF(1 - e / I);
            if (painter)
            {
                painter->setPen(color);
                painter->drawPoint(x, y);
            }
        }
    }
    else
    {
        double n = (I * len_x) / len_y;
        double w = I - n;
        double e = 0.5;
        color.setAlphaF(qAbs(1 - n / I));
        if (painter)
        {
            painter->setPen(color);
            painter->drawPoint(x1, y1);
        }
        int x = x1;
        int sx = x2 > x1 ? 1 : -1;
        int sy = y2 > y1 ? 1 : -1;
        for (int y = y1; y != y2; y += sy)
        {
            if (e < w)
            {
                e += n;
            }
            else
            {
                e -= w;
                x += sx;
                result.steps_num++;
            }
            color.setAlphaF(qAbs((1 - e / I)));
            if (painter)
            {
                painter->setPen(color);
                painter->drawPoint(x, y);
            }
        }
    }
    if (painter)
        painter->drawPoint(x2, y2);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}

drawLineResults PainterWidget::drawLineVu(int x1, int y1, int x2, int y2, QColor color)
{
    drawLineResults result = {.steps_num = 0,
                              .time = 0};
    auto start = std::chrono::steady_clock::now();

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) > abs(dy))
    {
        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
    }
    if (abs(dy) >= abs(dx))
    {
        if (y1 > y2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
    }

//    qDebug() << "Алгоритм Ву";
    // Построение линии
    if (abs(dy) >= abs(dx))
    {
        double gradient = (x2 - x1) / (double)(y2 - y1);
        double x = x1;
        for (int y = y1; y <= y2; ++y)
        {
            float alpha = std::fabs(x - (int)x);

            color.setAlphaF(alpha);
            if (painter)
            {
                painter->setPen(color);
                painter->drawPoint(x + 1, y);
            }

            color.setAlphaF(1.0 - alpha);
            if (painter)
            {
                painter->setPen(color);
                painter->drawPoint(x, y);
            }
            if ((int)(x + gradient) != (int)(x))
                result.steps_num++;
            x += gradient;
        }
    }
    else
    {
        double gradient = (y2 - y1) / (double)(x2 - x1);
        double y = y1 + gradient;
        for (int x = x1; x <= x2; ++x)
        {
            float alpha = std::fabs(y - (int)y);

            color.setAlphaF(alpha);
            if (painter)
            {
                painter->setPen(color);
                painter->drawPoint(x, y + 1);
            }

            color.setAlphaF(1.0 - alpha);
            if (painter)
            {
                painter->setPen(color);
                painter->drawPoint(x, y);
            }
            if ((int)(y + gradient) != (int)(y))
                result.steps_num++;
            y += gradient;
        }
    }
    if (painter)
        painter->drawPoint(x2, y2);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    result.time = duration.count();

    return result;
}


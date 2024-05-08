#include "painterwidget.h"
#include <chrono>
drawResults PainterWidget::drawLine(int x_1, int y_1, int x_2, int y_2, QColor color)
{
    if (painter)
        painter->setPen(color);
    drawResults res;
    auto start = std::chrono::high_resolution_clock::now();
    if (painter)
    {
        painter->drawPoint(x_1, y_1);
        painter->drawPoint(x_2, y_2);
        painter->drawLine(x_1, y_1, x_2, y_2);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Преобразуем продолжительность в секунды типа double
    res.time = duration.count();
    return res;
}

drawResults PainterWidget::drawLine(QPoint p_1, QPoint p_2, QColor color)
{
    return drawLine(p_1.x(), p_1.y(), p_2.x(), p_2.y(), color);
}

drawResults PainterWidget::drawOpenedFiguresBorders(const std::vector<Figure> &figures, QColor border_color)
{
    drawResults res = {0};
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
    drawResults res = {0};
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

drawResults PainterWidget::fillFiguresListAndFlag(const std::vector<Figure> &figures, QColor border_color, QColor fill_color)
{
    drawResults res = {0};
    auto start = std::chrono::high_resolution_clock::now();
    int start_x = Figure::getMinX(figures);
    int start_y = Figure::getMinY(figures);
    int end_x = Figure::getMaxX(figures);
    int end_y = Figure::getMaxY(figures);

    roundFigure(figures);

    for (int y = start_y; y < end_y; y++)
    {
        bool flag = false;
        for (int x = start_x; x <= end_x + 1; x++)
        {
            if (buffer.pixelColor(x,y) == TMP_COLOR)
            {
                flag = !flag;
            }
            if (flag)
            {
                buffer.setPixelColor(x,y, fill_color);
            }
            else
            {
                buffer.setPixelColor(x,y, background_color);
            }
        }
    }


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    drawClosedFiguresBorders(figures, border_color);
    // Преобразуем продолжительность в секунды типа double
    res.time = duration.count();
    return res;
}

drawResults PainterWidget::fillFiguresListAndFlag(const std::vector<Figure> &figures, int start_y, int end_y,
                                                  QColor border_color, QColor fill_color)
{
    drawResults res = {0};
    auto start = std::chrono::high_resolution_clock::now();

    int start_x = Figure::getMinX(figures);
    int end_x = Figure::getMaxX(figures);

    roundFigure(figures);
    for (int y = start_y; y < end_y; y++)
    {
        bool flag = false;
        for (int x = start_x; x <= end_x + 1; x++)
        {
            if (buffer.pixelColor(x,y) == TMP_COLOR)
            {
                flag = !flag;
            }
            if (flag)
            {
                buffer.setPixelColor(x,y, fill_color);
            }
            else
            {
                buffer.setPixelColor(x,y, background_color);
            }
        }
    }


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (end_y == Figure::getMaxY(figures))
        drawClosedFiguresBorders(figures, border_color);
    // Преобразуем продолжительность в секунды типа double
    res.time = duration.count();
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
    emit mouseClicked(event);
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

#include "painterwidget.h"
#include <chrono>
#include <QStack>
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

drawResults PainterWidget::fillFiguresWithSeed(QPoint seed,
                                               QColor border_color, QColor fill_color)
{
    drawResults res;
    auto start = std::chrono::high_resolution_clock::now();

    QStack<QPoint> points;
    points.push(seed);
    while (!points.empty())
    {
        res.drawed_lines++;
        QPoint p = points.pop();
        if (p.x() >= 0 && p.x() < buffer.width() && p.y() >= 0 && p.y() < buffer.height())
            buffer.setPixelColor(p, fill_color);
        // Сохранение х затравки
        int tmp_x = p.x();
        // Заполнение интервала спправа от затравки
        p.setX(p.x() + 1);
        while (p.x() < buffer.width() && buffer.pixelColor(p) != border_color)
        {
            buffer.setPixelColor(p, fill_color);
            p.setX(p.x() + 1);
        }
        // Сохранение крайнего справа пикселя
        int right_x = p.x() - 1;
        // Восстановление координат затравки
        p.setX(tmp_x);
        // Заполнение интервала слева
        p.setX(p.x() - 1);
        while (p.x() >= 0 && buffer.pixelColor(p) != border_color)
        {
            buffer.setPixelColor(p, fill_color);
            p.setX(p.x() - 1);
        }
        // Сохранение крайнего левого пиксела
        int left_x = p.x() + 1;
        // Сохранение строки текущей затравки
        int seed_y = p.y();
        // Проверка, что строка выше не является ни границей многоугольника,
        // ни уже полностью закрашенной. Если это не так, то найти затравку, начиная с левого края
        // подынтревала сканирующей строки
        p.setX(left_x);
        p.setY(seed_y - 1);
        while (p.x() < right_x && p.y() > 0)
        {
            bool flag = false;
            while (p.x() < right_x &&
                   buffer.pixelColor(p) != border_color &&
                   buffer.pixelColor(p) != fill_color)
            {
                if (!flag)
                    flag = true;
                p.setX(p.x() + 1);
            }
            if (flag)
            {
                if (p.x() == right_x && buffer.pixelColor(p) != border_color && buffer.pixelColor(p) != fill_color)
                {
                    points.push_back(p);
                }
                else
                {
                    points.push_back(QPoint(p.x() - 1, p.y()));
                }
                flag = false;
            }
            // Продолжение проверки, если интервал был прерван
            int input_x = p.x();
            while (p.x() < right_x &&
                   (buffer.pixelColor(p) == border_color ||
                    buffer.pixelColor(p) == fill_color))
            {
                p.setX(p.x() + 1);
            }
            // Проверка, что координата пиксела точно увеличена
            if (p.x() == input_x)
                p.setX(p.x() + 1);

        }
        // Проверка, что строка ниже не является ни границей многоугольника, ни уже заполненной областью
        p.setX(left_x);
        p.setY(seed_y + 1);
        while (p.x() < right_x && p.y() < buffer.height())
        {
            bool flag = false;
            while (buffer.pixelColor(p) != border_color &&
                   buffer.pixelColor(p) != fill_color &&
                   p.x() < right_x)
            {
                if (!flag)
                    flag = true;
                p.setX(p.x() + 1);
            }
            if (flag)
            {
                if (p.x() == right_x && buffer.pixelColor(p) != border_color && buffer.pixelColor(p) != fill_color)
                {
                    points.push_back(p);
                }
                else
                {
                    points.push_back(QPoint(p.x() - 1, p.y()));
                }
                flag = false;
            }
            // Продолжение проверки, если интервал был прерван
            int input_x = p.x();
            while (p.x() < right_x &&
                   (buffer.pixelColor(p) == border_color ||
                    buffer.pixelColor(p) == fill_color))
            {
                p.setX(p.x() + 1);
            }
            // Проверка, что координата пиксела точно увеличена
            if (p.x() == input_x)
                p.setX(p.x() + 1);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // if (end_y == Figure::getMaxY(figures))
    //     drawClosedFiguresBorders(figures, border_color);
    // // Преобразуем продолжительность в секунды типа double
    res.time = duration.count();
    return res;
}

drawResults PainterWidget::fillFiguresWithSeed(QPoint seed, int max_lines, QColor border_color, QColor fill_color)
{
    drawResults res;
    auto start = std::chrono::high_resolution_clock::now();

    QStack<QPoint> points;
    points.push(seed);
    while (!points.empty() && res.drawed_lines < max_lines)
    {
        res.drawed_lines++;
        QPoint p = points.pop();
        if (p.x() >= 0 && p.x() < buffer.width() && p.y() >= 0 && p.y() < buffer.height())
            buffer.setPixelColor(p, fill_color);
        // Сохранение х затравки
        int tmp_x = p.x();
        // Заполнение интервала спправа от затравки
        p.setX(p.x() + 1);
        while (p.x() < buffer.width() && buffer.pixelColor(p) != border_color)
        {
            buffer.setPixelColor(p, fill_color);
            p.setX(p.x() + 1);
        }
        // Сохранение крайнего справа пикселя
        int right_x = p.x() - 1;
        // Восстановление координат затравки
        p.setX(tmp_x);
        // Заполнение интервала слева
        p.setX(p.x() - 1);
        while (p.x() >= 0 && buffer.pixelColor(p) != border_color)
        {
            buffer.setPixelColor(p, fill_color);
            p.setX(p.x() - 1);
        }
        // Сохранение крайнего левого пиксела
        int left_x = p.x() + 1;
        // Сохранение строки текущей затравки
        int seed_y = p.y();
        // Проверка, что строка выше не является ни границей многоугольника,
        // ни уже полностью закрашенной. Если это не так, то найти затравку, начиная с левого края
        // подынтревала сканирующей строки
        p.setX(left_x);
        p.setY(seed_y - 1);
        while (p.x() < right_x && p.y() > 0)
        {
            bool flag = false;
            while (p.x() < right_x &&
                   buffer.pixelColor(p) != border_color &&
                   buffer.pixelColor(p) != fill_color)
            {
                if (!flag)
                    flag = true;
                p.setX(p.x() + 1);
            }
            if (flag)
            {
                if (p.x() == right_x && buffer.pixelColor(p) != border_color && buffer.pixelColor(p) != fill_color)
                {
                    points.push_back(p);
                }
                else
                {
                    points.push_back(QPoint(p.x() - 1, p.y()));
                }
                flag = false;
            }
            // Продолжение проверки, если интервал был прерван
            int input_x = p.x();
            while (p.x() < right_x &&
                   (buffer.pixelColor(p) == border_color ||
                    buffer.pixelColor(p) == fill_color))
            {
                p.setX(p.x() + 1);
            }
            // Проверка, что координата пиксела точно увеличена
            if (p.x() == input_x)
                p.setX(p.x() + 1);

        }
        // Проверка, что строка ниже не является ни границей многоугольника, ни уже заполненной областью
        p.setX(left_x);
        p.setY(seed_y + 1);
        while (p.x() < right_x && p.y() < buffer.height())
        {
            bool flag = false;
            while (buffer.pixelColor(p) != border_color &&
                   buffer.pixelColor(p) != fill_color &&
                   p.x() < right_x)
            {
                if (!flag)
                    flag = true;
                p.setX(p.x() + 1);
            }
            if (flag)
            {
                if (p.x() == right_x && buffer.pixelColor(p) != border_color && buffer.pixelColor(p) != fill_color)
                {
                    points.push_back(p);
                }
                else
                {
                    points.push_back(QPoint(p.x() - 1, p.y()));
                }
                flag = false;
            }
            // Продолжение проверки, если интервал был прерван
            int input_x = p.x();
            while (p.x() < right_x &&
                   (buffer.pixelColor(p) == border_color ||
                    buffer.pixelColor(p) == fill_color))
            {
                p.setX(p.x() + 1);
            }
            // Проверка, что координата пиксела точно увеличена
            if (p.x() == input_x)
                p.setX(p.x() + 1);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // if (end_y == Figure::getMaxY(figures))
    //     drawClosedFiguresBorders(figures, border_color);
    // // Преобразуем продолжительность в секунды типа double
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

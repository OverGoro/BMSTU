#include "painterwidget.h"
#include <chrono>
#include <QStack>
#include <exception>
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

drawResults PainterWidget::drawClippedLine(int x_c1, int y_c1, int x_c2, int y_c2, Line l, QColor color)
{
    drawResults res;
    int x_left = qMin(x_c1, x_c2);
    int x_right = qMax(x_c1, x_c2);
    int y_bottom = qMin(y_c1, y_c2);
    int y_top = qMax(y_c1, y_c2);
    int code_1 = 0, code_2 = 0;

    long double x1 = l.getFirstPoint().x();
    long double y1 = l.getFirstPoint().y();
    long double x2 = l.getSecondPoint().x();
    long double y2 = l.getSecondPoint().y();

    // Инициализация кодов
    if (x1 < x_left) code_1 |= 0b1000;
    if (x1 > x_right) code_1 |= 0b0100;
    if (y1 < y_bottom) code_1 |= 0b0010;
    if (y1 > y_top) code_1 |= 0b0001;

    if (x2 < x_left) code_2 |= 0b1000;
    if (x2 > x_right) code_2 |= 0b0100;
    if (y2 < y_bottom) code_2 |= 0b0010;
    if (y2 > y_top) code_2 |= 0b0001;

    int flag = 0;
    QPoint p_1 = l.getFirstPoint();
    QPoint p_2 = l.getSecondPoint();
    QPointF pr_1 = p_1;
    QPointF pr_2 = p_2;
    QPoint tmp_p;
    long double m = INFINITY;
    int number  = 0; // Номер рассматриваемого конца отрезка
    long double x,y;

    // Проверка полной видимости отрезка
    if (code_1 == 0 && code_2 == 0)
    {
        goto end;
    }
    // Отрезок не является полностью видимым
    // Проверка случая тривиальной невидимости
    if ((code_1 & code_2) != 0)
    {
        flag = -1;
        goto end;
    }
    // Отрезок может быть частично видимым
    // Проверка попадания первой точки внуть окна
    // Проверка попадания первой точки в область видимости
    if (code_1 == 0)
    {
        pr_1 = p_1;
        tmp_p = p_2;
        number = 2;
        goto left_intersection;
    }
    // Проверка попадания второй точки в область видимости
    if (code_2 == 0)
    {
        pr_1 = p_2;
        tmp_p = p_1;
        number = 2;
        goto left_intersection;
    }
    number = 0;
// Внутри окна нет концов отрезка
first_step:
    if (number != 0)
    {
        if (number == 1) pr_1 = tmp_p;
        else if (number == 2) pr_2 = tmp_p;
    }
    number++;
    if (number > 2) goto end;
    if (number == 1) tmp_p = p_1;
    else if (number == 2) tmp_p = p_2;
// Проверка пересечения с левым краем
left_intersection:
    // Проверка вертикальности отрезка
    if (x2 - x1 == 0) goto top_intersection;
    m = (y2 - y1) / (x2 - x1);
    if (x_left < tmp_p.x()) goto right_intersection;
    y = m * (x_left - tmp_p.x()) + tmp_p.y();
    if (y > y_top) goto right_intersection;
    if (y < y_bottom) goto right_intersection;
    // Обнаружено корректное персечение
    tmp_p.setY(y);
    tmp_p.setX(x_left);
    goto first_step;
// Проверка пересечения с правым краем
right_intersection:
    if (x_right > tmp_p.x()) goto top_intersection;
    y = m * (x_right - tmp_p.x()) + tmp_p.y();
    if (y > y_top) goto top_intersection;
    if (y < y_bottom) goto top_intersection;
    // Обнаружено корректное персечение
    tmp_p.setY(y);
    tmp_p.setX(x_right);
    goto first_step;
// Проверка пересечения с верхним краем
top_intersection:
    // Проверка горизонтальности отрезка
    if (m == 0) goto first_step;
    if (y_top > tmp_p.y()) goto bottom_intersection;
    x = (1 / m) * (y_top - tmp_p.y()) + tmp_p.x();
    if (x < x_left) goto bottom_intersection;
    if (x > x_right) goto bottom_intersection;
    // Обнаружено корректное пересечение
    tmp_p.setX(x);
    tmp_p.setY(y_top);
    goto first_step;
// Проверка пересечения с нижним краем
bottom_intersection:
    // Проверка пересечения с нижним краем
    if (y_bottom < tmp_p.y()) throw std::exception();
    x = (1 / m) * (y_bottom - tmp_p.y()) + tmp_p.x();
    if (x < x_left) goto invisible;
    if (x > x_right) goto invisible;
    // Обнаружено корректное пересечение
    tmp_p.setX(x);
    tmp_p.setY(y_bottom);
    goto first_step;
invisible:
    flag= -1;
end:
    if (flag == 0 && painter)
    {
        drawLine(pr_1.x(), pr_1.y(), pr_2.x(), pr_2.y(), l, color);
        // drawLine(pr_1.x(), pr_1.y(), pr_2.x(), pr_2.y(), color);
    }

    return res;
}

int get_code(int x_left, int x_right, int y_bottom, int y_top, QPoint p)
{
    int code = 0;
    if (p.x() < x_left)
        code |= 1;
    else if (p.x() > x_right)
        code |= 2;
    if (p.y() < y_bottom)
        code |= 4;
    else if (p.y() > y_top)
        code |= 8;
    return code;
}
// drawResults PainterWidget::drawClippedLine(int x_c1, int y_c1, int x_c2, int y_c2, Line l, QColor color)
// {
//     int x_left = qMin(x_c1, x_c2);
//     int x_right = qMax(x_c1, x_c2);
//     int y_bottom = qMin(y_c1, y_c2);
//     int y_top = qMax(y_c1, y_c2);

//     int code1 = get_code(x_left, x_right, y_bottom, y_top, l.getFirstPoint());
//     int code2 = get_code(x_left, x_right, y_bottom, y_top, l.getSecondPoint());

//     auto p1 = l.getFirstPoint(), p2 = l.getSecondPoint();
//     int x1 = p1.x(), x2 = p2.x();
//     int y1 = p1.y(), y2 = p2.y();
//     int pr = 1;

//     while (true) {
//         if (code1 == 0 && code2 == 0)
//         {
//             drawLine(p1.x(), p1.y(), p2.x(), p2.y(), l, color);
//             return drawResults();
//         }

//         if (code1 & code2)
//         {
//             pr = -1;
//             return drawResults();
//         }

//         int code_out; // Код точки вне области
//         if (code1 != 0)
//         {
//             code_out = code1;
//         }
//         else
//         {
//             code_out = code2;
//         }

//         double x, y;
//         if (code_out & 1)
//         { // Левее отсекателя
//             x = x_left;
//             y = y1 + (y2 - y1) * (x_left - x1) / (x2 - x1);
//         } else if (code_out & 2) { // Правее отсекателя
//             x = x_right;
//             y = y1 + (y2 - y1) * (x_right - x1) / (x2 - x1);
//         } else if (code_out & 4) { // Ниже отсекателя
//             y = y_bottom;
//             x = x1 + (x2 - x1) * (y_bottom - y1) / (y2 - y1);
//         } else if (code_out & 8) { // Выше отсекателя
//             y = y_top;
//             x = x1 + (x2 - x1) * (y_top - y1) / (y2 - y1);
//         }

//         if (code_out == code1) {
//             p1 = QPoint(x,y);
//             x1 = p1.x();
//             y1 = p1.y();
//             code1 = get_code(x_left, x_right, y_bottom, y_top, QPoint(x1, y1));
//         } else {
//             p2 = QPoint(x,y);
//             x2 = p2.x();
//             y2 = p2.y();
//             code2 = get_code(x_left, x_right, y_bottom, y_top, QPoint(x2, y2));
//         }
//     }

//     return drawResults();
// }



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

#ifndef CANVAS_H
#define CANVAS_H

#include <QPainter>

#include "figure.h"

typedef struct
{
    QPainter &painter;
    QPen lines_pen;
    size_t canvas_width, canvas_height;
    double count_width, count_height;
} canvas_t;


/**
 * @brief canvas_draw_line Отрисовка линии на холсте
 *
 * @param canvas_parameters [in]    Параметры отрисовщика
 * @param point_1[in]               Первая точка
 * @param point_2[in                Вторая точка
 *
 * @return Код ошибки
 */
int canvas_draw_line(const canvas_t &canvas_parameters, const point_t &point_1,const point_t &point_2);

/**
 * @brief canvas_draw_points_array Отрисовка массив точек
 *
 * @param canvas_parameters[in] Параметры отрисовщика
 * @param points[in]      Точки
 * @param link[in]       Связь
 *
 * @return Код ошибки
 */
int canvas_draw_points_array(const canvas_t &canvas_parameters, const point_t *points, const link_t &link);

int canvas_draw_points(const canvas_t &canvas_parameters,
                       const points_array_t &points_array,
                       const links_array_t &links_array);

/**
 * @brief canvas_draw_figure Отрисовка фигуры на холсте
 *
 * @param canvas_parameters[in] Параметры отрисовщика
 * @param figure[in]            Фигура
 *
 * @return Код ошибки
 */
int canvas_draw_figure(const canvas_t &canvas_parameters, const figure_t &figure);

#endif // CANVAS_H

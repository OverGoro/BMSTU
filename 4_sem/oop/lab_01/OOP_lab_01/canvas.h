#ifndef CANVAS_H
#define CANVAS_H

#include <QPainter>

#include "figure.h"

typedef struct
{
    size_t width;
    size_t height;
} screen_size_t;

typedef struct
{
    double width;
    double height;
} count_size_t;

typedef struct
{
    QPainter *painter;
    QPen lines_pen;
    screen_size_t screen_size;
    count_size_t count_size;
} canvas_t;

canvas_t canvas_init_empty();

void canvas_set_painter(canvas_t &canvas, QPainter *painter);

void canvas_set_lines_pen(canvas_t &canvas, QPen &lines_pen);

void canvas_set_screen_size(canvas_t &canvas, size_t width, size_t height);

void canvas_set_count_size(canvas_t &canvas, double width, double height);


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
 * @brief canvas_draw_3d_line Отрисовка 3D линии на холсте
 *
 * @param canvas_parameters [in]    Параметры отрисовщика
 * @param point_1[in]               Первая точка
 * @param point_2[in                Вторая точка
 *
 * @return Код ошибки
 */
int canvas_draw_3d_line(const canvas_t &canvas_parameters, const point_t &point_1, const point_t &point_2);

/**
 * @brief canvas_draw_points_array Отрисовка массив точек
 *
 * @param canvas_parameters[in] Параметры отрисовщика
 * @param points[in]      Точки
 * @param link[in]       Связь
 *
 * @return Код ошибки
 */
int canvas_draw_linked_points(const canvas_t &canvas_parameters, const point_t *points, const link_t &link);

int canvas_draw_linked_points_array(const canvas_t &canvas_parameters,
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

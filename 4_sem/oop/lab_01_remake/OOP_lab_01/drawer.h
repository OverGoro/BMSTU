#ifndef DRAWER_H
#define DRAWER_H

#include <QOpenGLFunctions>
#include <QtOpenGLWidgets>

#include "point.h"
#include "figure.h"
#include "color.h"

typedef struct
{
    color_t lines_color;    // Цвет линий
} drawer_params_t;

/**
 * @brief drawer_params_set_lines_color Установка цвета линий для отрисовщика
 *
 * @param drawer_params[out]    Параметры отрисовщика
 * @param color[in]             Цвет
 */
void drawer_params_set_lines_color(drawer_params_t &drawer_params, const color_t &color);

/**
 * @brief drawer_draw_line Отрисовка отрезка
 *
 * @param color[in]     Цвет отрезка
 * @param point_1[in]   Первая точка отрезка
 * @param point_2[in]   Вторая точка отрезка
 *
 * @return Код ошибки
 */
int drawer_draw_line(const color_t &color, const point_t &point_1, const point_t &point_2);

/**
 * @brief drawer_draw_points_array Отрсиовка массива точек

 * @param drawer_params[in] Параметры отрисовщика
 * @param points_array[in]  Массив точек
 * @param links_array[in]   Массив связей между точками
 *
 * @return Код ошибки
 */
int drawer_draw_points_array(const drawer_params_t &drawer_params,
                             const points_array_t &points_array,
                             const links_array_t &links_array);

/**
 * @brief drawer_draw_points_array Отрисовка фигуры
 *
 * @param drawer_params[in] Параметры отрисовщика
 * @param figure[in]        Фигура
 *
 * @return Код ошибки
 */
int drawer_draw_figure(const drawer_params_t &drawer_params, const figure_t &figure);

#endif // DRAWER_H

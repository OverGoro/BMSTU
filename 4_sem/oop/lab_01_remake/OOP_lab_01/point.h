#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <math.h>

#include "rotate_coefficients.h"
#include "error.h"
#include "move_coefficients.h"
#include "scale_coefficients.h"

typedef struct
{
    double x;
    double y;
    double z;
} point_t;

point_t point_init(double x, double y, double z);

/**
 * @brief point_read Чтение параметров точки из файлового потока
 *
 * @param file[in, out]     Файловый поток
 * @param point[in, out]    Точка
 *
 * @return Код ошибки
 */
int point_read(FILE *file, point_t &point);

/**
 * @brief point_move Сдвиг точки
 *
 * @param point[in, out]    Точка
 * @param move[in]          Параметры сдивга
 *
 * @return Код ошибки
 */
int point_move(point_t &point, const move_coefficients_t &move);

/**
 * @brief point_rotate Поворот точки относительно заданного центра
 *
 * @param point[in, out]    Точка
 * @param center[in]        Центр поворота
 * @param angle[in]         Угол поворота
 *
 * @return Код ошибки
 */
int point_rotate(point_t &point, const point_t &center, const rotate_coefficients_t &angle);

/**
 * @brief point_scale Масштабирование точки относительно заданного центра
 *
 * @param point[in, out]    Точка
 * @param center[in]        Центр масштабирования
 * @param scale[in]         Коэффициенты масштабирования
 *
 * @return Код ошибки
 */
int point_scale(point_t &point, const point_t &center, const scale_coefficients_t &scale);

/**
 * @brief point_print Вывод точки в файловый поток
 *
 * @param file[in, out]     Файловый поток
 * @param point[in]         Точка
 *
 * @return Код ошибки
 */
int point_print(FILE *f, const point_t &point);

#endif // POINT_H

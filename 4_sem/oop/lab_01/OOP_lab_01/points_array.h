#ifndef POINTS_ARRAY_H
#define POINTS_ARRAY_H
#include "point.h"

typedef struct
{
    point_t *array;     // Массив точек
    size_t array_size;  // Размер массива точек
} points_array_t;

/**
 * @brief points_array_init_empty Инициализация пустого массива точек
 * @return Массив точек
 */
points_array_t points_array_init_empty();

/**
 * @brief points_array_allocate Выделение памяти под массив точек
 *
 * @param points_array[in,out]  Массив точек
 * @param size[in]              Количество точек
 *
 * @return Код ошибки
 */
int points_array_allocate(points_array_t &points_array, size_t array_size);

/**
 * @brief points_array_free Освобождение памяти из под массива точек
 *
 * @param points_array [in, out] Массив точек
 */
void points_array_clear(points_array_t &points_array);


/**
 * @brief points_array_read_file Чтение фигуры из текстового файла
 *
 * @param points_array[in,out]  Массив точек
 * @param f[in,out]             Файловый поток
 *
 * @return Код ошибки
 */
int points_array_read(points_array_t &points_array, FILE *f);

/**
 * @brief points_array_print Вывод фигуры в файловый поток
 *
 * @param file[in, out]     Файловый поток
 * @param points_array[in]  Массив точек
 *
 * @return Код ошибки
 */
int points_array_print(FILE *f, const points_array_t &points_array);

/**
 * @brief points_array_move Сдвиг массива точек
 * @param points_array[in, out] Массив точек
 * @param move[in]              Параметры сдвига
 *
 * @return Код ошибки
 */
int points_array_move(points_array_t &points_array, const move_coefficients_t &move);

/**
 * @brief points_array_rotate Поворот точек относительно заданного центра
 *
 * @param points_array[in, out] Массив точек
 * @param center[in]    Центр поворота
 * @param angle[in]     Угол поворота
 *
 * @return Код ошибки
 */
int points_array_rotate(points_array_t &points_array, const point_t &center, const rotate_coefficients_t &angle);

/**
 * @brief points_array_scale    Масштабирование точек относительно заданного центра
 *
 * @param points_array[in, out] Массив точек
 * @param center[in]    Центр масштабирования
 * @param scale[in]     Параметры масштабирования
 *
 * @return Код ошибки
 */
int points_array_scale(points_array_t &points_array, const point_t &center, const scale_coefficients_t &scale);


#endif // POINTS_ARRAY_H

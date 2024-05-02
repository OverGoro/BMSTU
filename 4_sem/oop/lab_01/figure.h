#ifndef FIGURE_H
#define FIGURE_H

#include <unistd.h>

#include "points_array.h"
#include "elements_link_array.h"

// Массив точек
typedef struct
{
    points_array_t points_array;    // Массив точек
    links_array_t links_array;      // Массив связей
} figure_t;

figure_t figure_init_empty();

/**
 * @brief figure_allocate Выделение памяти под фигуру
 *
 * @param figure[in,out]    Фигура
 * @param array_size[in]    Количество точек
 * @param links_size[in]    Количество связей
 *
 * @return Код ошибки
 */
int figure_allocate(figure_t &figure, size_t array_size, size_t links_size);

/**
 * @brief figure_free Освобождение памяти из под фигуры
 *
 * @param figure [in, out] Фигура
 */
void figure_clear(figure_t &figure);


/**
 * @brief figure_read Чтение фигуры из файлового потока
 *
 * @param figure[out] Фигура
 * @param f[in,out] Файловый поток
 *
 * @return Код ошибки
 */
int figure_read(figure_t &figure, FILE *f);

/**
 * @brief figure_read_file Чтение фигуры из текстового файла
 *
 * @param figure[in,out]    Фигура
 * @param filename[in]      Имя файла
 *
 * @return Код ошибки
 */
int figure_read_file(figure_t &figure, const char *filename);

/**
 * @brief figure_read_file Запись фигуры в текстовый файл
 *
 * @param figure[in,out]  Фигура
 * @param filename[in]    Имя файла
 *
 * @return Код ошибки
 */
int figure_save_file(const figure_t &figure, const char *filename);

/**
 * @brief figure_move Сдвиг фигуры
 *
 * @param figure[in, out]   Фигура
 * @param move[in]          Параметры сдвига
 *
 * @return Код ошибки
 */
int figure_move(figure_t &figure, const move_coefficients_t &move);

/**
 * @brief figure_rotate Поворот точек относительно заданного центра
 *
 * @param figure[in, out]   Фигура
 * @param center[in]        Центр поворота
 * @param angle[in]         Угол поворота
 *
 * @return Код ошибки
 */
int figure_rotate(figure_t &figure, const point_t &center, const rotate_coefficients_t &angle);

/**
 * @brief figure_scale    Масштабирование точек относительно заданного центра
 *
 * @param figure[in, out]   Фигура
 * @param center[in]        Центр масштабирования
 * @param scale[in]         Параметры масштабирования
 *
 * @return Код ошибки
 */
int figure_scale(figure_t &figure, const point_t &center, const scale_coefficients_t &scale);

/**
 * @brief figure_print Вывод фигуры в файловый поток
 *
 * @param file[in, out]     Файловый поток
 * @param figure[in]        Фигура
 *
 * @return Код ошибки
 */
int figure_print(FILE *file, const figure_t &figure);

#endif // FIGURE_H

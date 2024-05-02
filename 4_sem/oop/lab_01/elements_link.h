#ifndef ELEMENTS_LINK_H
#define ELEMENTS_LINK_H

#include <stddef.h>
#include <stdio.h>

#include "error.h"

// Связь между 2 элементами массива
typedef struct
{
   size_t i_1; // Индекс первого элемента
   size_t i_2; // Индекс второго элемента
} link_t;

/**
 * @brief link_read Чтение связи между элементами массива из файлового потока
 *
 * @param link[out]         Связь между элементами
 * @param file[in, out]     Файловый поток
 *
 * @return Код ошибки
 */
int link_read(link_t &link, FILE *file);

/**
 * @brief link_print Вывод связи в файловый поток
 * @param file[in, out] Файловый поток
 * @param link[in]      Связь
 *
 * @return Код ошибки
 */
int link_print(FILE *file, const link_t &link);

/**
 * @brief link_validate Проверка
 *
 * @param link[in]              Связь
 * @param target_array_size[in] Размер целевого массива
 *
 * @return Код ошибки
 */
int link_validate(const link_t &link, size_t target_array_size);

#endif // ELEMENTS_LINK_H

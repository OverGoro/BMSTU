#ifndef ELEMENTS_LINK_ARRAY_H
#define ELEMENTS_LINK_ARRAY_H
#include "elements_link.h"
#include <stdlib.h>

typedef struct
{
    link_t *array;
    size_t array_size;
} links_array_t;

links_array_t links_array_create_empty();

/**
 * @brief links_array_allocate Выделение памяти под массив связей
 *
 * @param links_array[in,out]  Массив связей
 * @param size[in]             Количество связей
 *
 * @return Код ошибки
 */
int links_array_allocate(links_array_t &links_array, size_t array_size);

/**
 * @brief links_array_free Освобождение памяти из под массива связей
 *
 * @param links_array [in, out] Массив связей
 */
void links_array_free(links_array_t &links_array);

/**
 * @brief links_array_read_file Чтение массива связей из файлового потока
 *
 * @param links_array[in,out]   Массив связей
 * @param f[in,out]             Файловый поток
 *
 * @return Код ошибки
 */
int links_array_read(links_array_t &links_array, FILE *f);

/**
 * @brief links_array_print Вывод массива связей в файловый поток
 *
 * @param file[in, out]    Файловый поток
 * @param links_array[in]  Массив связей
 *
 * @return Код ошибки
 */
int links_array_print(FILE *file, const links_array_t &links_array);

int links_validate(const link_t *links, size_t links_size, size_t target_array_size);

/**
 * @brief links_array_validate Проверка корректности индексов связей для целевого массива
 *
 * @param links_array       [in] Массив связей
 * @param target_array_size [in] Размер целевого массива
 *
 * @return Код ошибки
 */
int links_array_validate(const links_array_t &links_array, size_t target_array_size);

#endif // ELEMENTS_LINK_ARRAY_H

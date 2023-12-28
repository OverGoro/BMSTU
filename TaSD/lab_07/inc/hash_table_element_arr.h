#ifndef HASH_TABLE_ELEMENT_ARR_H__
#define HASH_TABLE_ELEMENT_ARR_H__

#include "hash_table_element.h"

// Массив элементов хеш-таблицы
typedef struct
{
    element_t *values; // Элементы
    size_t n; // Кол-во элементов
} element_arr_t;

int element_arr_add(element_arr_t *arr, char *name, char *manual);

void element_arr_free_content(element_arr_t *arr);

int element_arr_read(FILE *f, element_arr_t *arr);

size_t element_arr_get_size(element_arr_t *arr);

#endif


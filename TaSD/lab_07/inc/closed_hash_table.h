#ifndef CLOSED_HASH_TABLE_H__
#define CLOSED_HASH_TABLE_H__

#include "error.h"
#include "hash_func.h"
#include "hash_table_element.h"
#include <bits/types/struct_tm.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(a,b) ((a > b) ? a : b)



// Hash талица с внутренним хешированием
typedef struct closed_hash_table
{
    element_t *values;
    size_t m;
} closed_hash_table_t;



void cht_free_content(closed_hash_table_t *cht);

/**
* @brief Реструктурирует хэш таблицу с внутренним хешированием
*
* @param cht[in] Хэш таблица
* @param new_m[in] Новая размерность
*
* @return Код ошикби
*/
int cht_restruct(closed_hash_table_t *cht, size_t new_m);

size_t cht_get_max_collision(closed_hash_table_t *cht);
double cht_get_average_collision(closed_hash_table_t *cht);

/**
* @brief Добавление элемента в хэш таблицу с внутренним хешированием
*
* @param name[in] Слово
* @param manual[in] Описание 
* @param max_collision[in] Коллизия 
*
* @return Код ошикби
*/
int cht_insert(closed_hash_table_t *hash_table, char *name, char *manual, double max_collision);

void cht_print(FILE *f, closed_hash_table_t *cht);

const char *cht_get_manual(closed_hash_table_t *cht, char *name);

int cht_read_from_file(closed_hash_table_t *cht, const char *file_name);

size_t cht_get_size(closed_hash_table_t *cht);

#endif // !HASH_TABLE_H__


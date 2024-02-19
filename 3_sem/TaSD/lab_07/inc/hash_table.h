#ifndef HASH_TABLE_H__
#define HASH_TABLE_H__

#include "error.h"
#include "hash_table_element_arr.h"
#include "hash_func.h"
#include <bits/types/struct_tm.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(a,b) ((a > b) ? a : b)



// Hash талица
typedef struct hash_table
{
    element_arr_t *values; // Массив массивов элементов
    size_t m;              // Размерность массива
} hash_table_t;

/**
* @brief Хэш функция деления
*
* @param s[in] Строка
* @param m[in] Размерность массива
*
* @return Результат хэш функции
*/
size_t hash_func(char *s, size_t m);

void ht_free_content(hash_table_t *ht);

/**
* @brief Реструктурирует хэш таблицу
*
* @param ht[in] Хэш таблица
* @param new_m[in] Новая размерность
*
* @return Код ошикби
*/
int ht_restruct(hash_table_t *ht, size_t new_m);

size_t ht_get_max_collision(hash_table_t *ht);
double ht_get_average_collision(hash_table_t *ht);

/**
* @brief Добавление элемента в хэш таблицу
*
* @param name[in] Слово
* @param manual[in] Описание 
* @param max_collision[in] Максимальная коллизия
*
* @return Код ошикби
*/
int ht_insert(hash_table_t *hash_table, char *name, char *manual, double max_collision);

void ht_print(FILE *f, hash_table_t *ht);

const char *ht_get_manual(hash_table_t *ht, char *name);

int ht_read_from_file(hash_table_t *ht, const char *file_name);

/**
* @brief Вычисление занимаемой памяти в байтах
*
* @param ht[in] Хеш-таблица
*
* @return Размер
*/
size_t ht_get_size(hash_table_t *ht);

#endif // !HASH_TABLE_H__


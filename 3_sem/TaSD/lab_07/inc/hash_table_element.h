#define _GNU_SOURCE
#ifndef HASH_TABLE_ELEMENT_T__
#define HASH_TABLE_ELEMENT_T__

#include "error.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Элмент хэш таблицы
typedef struct element
{
    char *name;   // Слово
    char *manual; // Описание
} element_t;

/**
* @brief Очистка содержимого элемента хэш таблицы
*
* @param e[in, out] Элемент
*/
void element_free_content(element_t *e);

int element_set_content(element_t *e, char *name, char *manual);

int element_read(FILE *f, element_t *e);

size_t element_get_size(element_t *e);

#endif // !HASH_TABLE_ELEMENT_T__

#define _GNU_SOURCE
#include "associative_array.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int num;
    const char *key;
} element_t;

struct assoc_array_type
{
    element_t *elements; // Массив с элементами
    size_t n; // Количество элементов в массиве
};

/**
* @brief Освобождает содержимое элемента массива
*
* @param e[in, out] Элемента массива
*/
static void element_free_content(element_t *e)
{
    free((void *)e->key);
    e->key = NULL;
}

/**
* @brief Поиск индкса элемента в ассоциативном массиве по ключу
*
* @param arr[in] Массив
* @param key[in] Ключ
* @param i[out] Индекс найденного элемента
*
* @return ASSOC_ARRAY_OK, если элемента найден
* ASSOC_ARRAY_NOT_FOUND, если не найден
*/
static assoc_array_error_t assoc_array_find_element(const assoc_array_t arr, const char *key, size_t *i)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;
    element_t *pcur = NULL;

    size_t find_i;

    for (size_t cur_i = 0; cur_i < arr->n && pcur == NULL; cur_i++)
    {
        if (strcmp(key, arr->elements[cur_i].key) == 0)
        {
            pcur = &arr->elements[cur_i];
            find_i = cur_i;
        }
    }
    if (pcur != NULL)
    {
        *i = find_i;
        return ASSOC_ARRAY_OK;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = calloc(1, sizeof(struct assoc_array_type));
    return arr;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    int *p_num = NULL;
    
    assoc_array_error_t rc = assoc_array_find(arr, key, &p_num);

    if (rc == ASSOC_ARRAY_OK)
        rc = ASSOC_ARRAY_KEY_EXISTS;
    else
    {
        rc = ASSOC_ARRAY_OK;
        element_t *tmp = NULL;
        char *tmp_key = strdup(key);
        if (tmp_key == NULL)
            rc = ASSOC_ARRAY_MEM;

        if (rc == ASSOC_ARRAY_OK && arr->elements != NULL)
            tmp = realloc(arr->elements, sizeof(element_t) * (arr->n + 1));
        else if (rc == ASSOC_ARRAY_OK)
            tmp = calloc(1, sizeof(element_t));

        if (rc == ASSOC_ARRAY_OK && tmp == NULL)
        {
            free(tmp_key);
            rc = ASSOC_ARRAY_MEM;
        }
        if (rc == ASSOC_ARRAY_OK)
        {
            arr->elements = tmp;
            arr->n++;
            arr->elements[arr->n - 1].num = num;
            arr->elements[arr->n - 1].key = tmp_key;
            rc = ASSOC_ARRAY_OK;
        }
    }
    return rc;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || key == NULL || num == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    size_t find_i;
    int rc = assoc_array_find_element(arr, key, &find_i);
    if (!rc)
        *num = &arr->elements[find_i].num;
    else
    {
        *num = NULL;
        rc = ASSOC_ARRAY_NOT_FOUND;
    }
    return rc;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;


    size_t i_find;
    int rc = assoc_array_find_element(arr, key, &i_find);
    if (rc == ASSOC_ARRAY_OK)
    {
        element_free_content(&arr->elements[i_find]);
        for (size_t i = i_find; i < arr->n - 1; i++)
            arr->elements[i] = arr->elements[i + 1];
        element_t *tmp = NULL;
        tmp = realloc(arr->elements, sizeof(element_t) * (arr->n - 1));
        if (tmp != NULL || arr->n == 1)
            arr->elements = tmp;
        else
            rc = ASSOC_ARRAY_MEM;
    }
    if (rc == ASSOC_ARRAY_OK)
        arr->n--;

    return rc;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    for (size_t i = 0; i < arr->n; i++)
        element_free_content(&arr->elements[i]);
    free(arr->elements);
    arr->elements = NULL;
    arr->n = 0;
    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->n; i++)
        action(arr->elements[i].key, &arr->elements[i].num, param);

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->elements == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    element_t *pfind = NULL;
    for (size_t i = 0; i < arr->n; i++)
    {
        if (pfind == NULL || strcmp(arr->elements[i].key, pfind->key) < 0)
            pfind = &arr->elements[i];
    }
    *num = &pfind->num;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->elements == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    element_t *pfind = NULL;
    for (size_t i = 0; i < arr->n; i++)
    {
        if (pfind == NULL || strcmp(arr->elements[i].key, pfind->key) > 0)
            pfind = &arr->elements[i];
    }
    *num = &pfind->num;
    return ASSOC_ARRAY_OK;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    assoc_array_clear(*arr);
    free(*arr);
    *arr = NULL;
}


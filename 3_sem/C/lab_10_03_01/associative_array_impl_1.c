#include "associative_array.h"
#include "node.h"
#include <stdlib.h>
#include <string.h>


struct assoc_array_type
{
    node_t head;
};


/**
* @brief Поиск узла в ассоциативном массиве на списке по ключу
*
* @param arr[in] Массив
* @param key[in] Ключ
*
* @return Указатель на найденный узел
* Если узел не найден или arr = NULL, то NULL
*/
node_t assoc_array_find_node(const assoc_array_t arr, const char *key)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
        return NULL;
    node_t pcur = arr->head;
    while (pcur != NULL && strcmp(pcur->key, key) != 0)
    {
        pcur = pcur->next;
    }
    return pcur;
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

    int *p_item = NULL;
    
    assoc_array_error_t rc = assoc_array_find(arr, key, &p_item);

    if (rc == ASSOC_ARRAY_OK)
        rc = ASSOC_ARRAY_KEY_EXISTS;
    else
    {
        node_t n = assoc_node_create(num, key);
        if (n == NULL)
            rc = ASSOC_ARRAY_MEM;
        else if (arr->head == NULL)
        {
            arr->head = n;
            rc = ASSOC_ARRAY_OK;
        }
        else
        {
            node_t pcur = arr->head;
            while (pcur->next != NULL)
                pcur = pcur->next;
            pcur->next = n;
            rc = ASSOC_ARRAY_OK;
        }
    }
    return rc;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || key == NULL || num == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;
    node_t pfind = assoc_array_find_node(arr, key);

    int rc = ASSOC_ARRAY_OK;
    if (pfind != NULL)
        *num = &pfind->item;
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

    node_t pprev = NULL;
    node_t pcur = arr->head;
    while (pcur != NULL && strcmp(pcur->key, key) != 0)
    {
        pprev = pcur;
        pcur = pcur->next;
    }

    if (pcur == NULL)
        return ASSOC_ARRAY_NOT_FOUND;
    if (pprev != NULL)
        pprev->next = pcur->next;
    else
        arr->head = pcur->next;

    assoc_node_free(&pcur);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t pcur = arr->head;
    while (pcur != NULL)
    {
        node_t pnext = pcur->next;
        assoc_node_free(&pcur);
        pcur = pnext;
    }
    arr->head = NULL;
    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    for (node_t pcur = arr->head; pcur != NULL; pcur = pcur->next)
    {
        action(pcur->key, &(pcur->item), param);
    }
    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->head == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t pfind = NULL;
    for (node_t pcur = arr->head; pcur != NULL; pcur = pcur->next)
    {
        if (pfind == NULL || strcmp(pcur->key, pfind->key) < 0)
            pfind = pcur;
    }
    *num = &pfind->item;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->head == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t pfind = NULL;
    for (node_t pcur = arr->head; pcur != NULL; pcur = pcur->next)
    {
        if (pfind == NULL || strcmp(pcur->key, pfind->key) > 0)
            pfind = pcur;
    }
    *num = &pfind->item;
    return ASSOC_ARRAY_OK;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || *arr == NULL)
        return;
    assoc_array_clear(*arr);
    free(*arr);
    *arr = NULL;
}



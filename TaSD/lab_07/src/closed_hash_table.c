#include "../inc/closed_hash_table.h"
#include <stdbool.h>
#include <stdio.h>

static bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

static size_t next_prime(int current_prime) {
    int next_number = current_prime + 1;
    while (1) {
        if (is_prime(next_number)) {
            return next_number;
        }
        next_number++;
    }
}

size_t cht_get_max_collision(closed_hash_table_t *cht)
{
    double res = 0;
    for (size_t i = 0; i < cht->m; i++)
    {
        if (cht->values[i].name != NULL)
            res = MAX(res, i - hash_func(cht->values[i].name, cht->m));
    }
    return res;
}

double cht_get_average_collision(closed_hash_table_t *cht)
{
    double res = 0;
    for (size_t i = 0; i < cht->m; i++)
    {
        if (cht->values[i].name != NULL)
            res +=  (double)(i - hash_func(cht->values[i].name, cht->m)) / (double)cht->m;
    }
    return res;
}

/**
* @brief Добавление элемента в хеш-таблицу с внутренним хешированием
*
* @param cht[in, out] Хеш-таблица
* @param index[in] Индекс элемента
* @param name[in] Слово
* @param manual[in] Описание
*
* @return Код ошибки
*/
static int cht_element_arr_add(closed_hash_table_t *cht, size_t index, char *name, char *manual)
{
    while (index < cht->m && cht->values[index].name != NULL) 
        index++;        

    if (index < cht->m)
    {
        // Запись элемента
        return element_set_content(&cht->values[index], name, manual);
    }
    
    // Таблица заполнена
    return ERR_FULL;
}



closed_hash_table_t *cht_create(void)
{
    closed_hash_table_t *cht = malloc(sizeof(closed_hash_table_t));
    if (cht != NULL)
    {
        cht->values = NULL;
        cht->m = 0;
    }
    return cht;
}

void cht_free_content(closed_hash_table_t *cht)
{
    for (size_t i = 0; i < cht->m; i++)
        element_free_content(&cht->values[i]);
    free(cht->values);
    cht->values = NULL;
    cht->m = 0;
}

int cht_restruct(closed_hash_table_t *cht, size_t new_m)
{
    if (new_m == 0)
        return ERR_RANGE;

    closed_hash_table_t tmp_cht = {0, new_m};
    tmp_cht.values = calloc(new_m, sizeof(element_t));
    if (tmp_cht.values == NULL)
        return ERR_MEM;

    int rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && i < cht->m; i++)
    {
        if (cht->values[i].name != NULL)
        {
            size_t index = hash_func(cht->values[i].name, new_m);
            rc = cht_element_arr_add(&tmp_cht,
                                 index,
                                 cht->values[i].name,
                                 cht->values[i].manual);
        }
    }

    if (rc == ERR_OK)
    {
        cht_free_content(cht);
        cht->values = tmp_cht.values;
        cht->m = new_m;
    }
    else 
        cht_free_content(&tmp_cht);
    return rc;
}


int cht_insert(closed_hash_table_t *cht, char *name, char *manual, double max_collision)
{
    if (cht == NULL || name == NULL || manual == NULL)
        return ERR_RANGE;
    int rc = ERR_OK;

    if (cht->m == 0)
        rc = cht_restruct(cht, 1);

    size_t index = hash_func(name, cht->m);

    rc = cht_element_arr_add(cht, index, name, manual);
    while (rc == ERR_FULL)
    {
        size_t delta_m = cht->m;
        while (rc == ERR_FULL)
        {
            rc = cht_restruct(cht, next_prime(delta_m));
            delta_m = next_prime(delta_m);
        }

        size_t index = hash_func(name, cht->m);
        if (!rc) rc = cht_element_arr_add(cht, index, name, manual);
    }
    size_t delta_m = cht->m;
    while (rc == ERR_FULL || cht_get_average_collision(cht) >= max_collision)
    {
        rc = cht_restruct(cht, delta_m);
        delta_m = next_prime(delta_m);
    }


    return rc;
}

void cht_print(FILE *f, closed_hash_table_t *cht)
{
    if (cht->m == 0)
    {
        fprintf(f, "Пустая таблица\n");
        return;
    }
    for (size_t i = 0; i < cht->m; i++)
    {
        if (cht->values[i].name != NULL)
            fprintf(f, "\"%lu: %s\" ", hash_func(cht->values[i].name, cht->m), cht->values[i].name);
        else 
            fprintf(f, "-");
        fprintf(f, "\n");
    }
    fprintf(f, "Среднее количесво сравнения для поиска: %lf\n", cht_get_average_collision(cht));
}

const char *cht_get_manual(closed_hash_table_t *cht, char *name)
{
    if (!name)
        return NULL;
    const char *manual = NULL;
    size_t index = hash_func(name, cht->m);
    for (size_t i = index; manual == NULL && i < cht->m; i++)
    {
        if (strcmp(name, cht->values[i].name) == 0)
        {
            manual = cht->values[i].manual;
        }
    }
    return manual;
}   

int cht_read_from_file(closed_hash_table_t *cht, const char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return ERR_FILE;
    cht_free_content(cht);
    int rc = ERR_OK;
    while (!rc) 
    {
        element_t e;
        rc = element_read(f, &e);
        if (!rc) rc = cht_insert(cht, e.name, e.manual, 4);
    }
    if (rc && feof(f))
        rc = ERR_OK;
    fclose(f);
    return rc;
}

size_t cht_get_size(closed_hash_table_t *cht)   
{
    size_t s = sizeof(closed_hash_table_t);
    for (size_t i = 0; i < cht->m; i++)
    {
        s += sizeof(element_t *) + element_get_size(&cht->values[i]);
    }
    return s;
}


#include "../inc/hash_table.h"
#include <stdio.h>

hash_table_t *ht_create(void)
{
    hash_table_t *ht = malloc(sizeof(hash_table_t));
    if (ht != NULL)
    {
        ht->m = 0;
        ht->values = NULL;
    }
    return ht;
}

void ht_free_content(hash_table_t *ht)
{
    for (size_t i = 0; i < ht->m; i++)
    {
        element_arr_free_content(&ht->values[i]);
    }
    free(ht->values);
    ht->values = NULL;
    ht->m = 0;
}

int ht_restruct(hash_table_t *ht, size_t new_m)
{
    if (new_m == 0)
        return ERR_RANGE;

    element_arr_t *tmp = calloc(new_m, sizeof(element_arr_t));
    if (tmp == NULL)
        return ERR_MEM;

    int rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && i < ht->m; i++)
    {
        for (size_t j = 0; rc == ERR_OK && j < ht->values[i].n; j++)
        {
            size_t index = hash_func(ht->values[i].values[j].name, new_m);
            rc = element_arr_add(&tmp[index],
                                 ht->values[i].values[j].name,
                                 ht->values[i].values[j].manual);
        }
    }

    if (rc == ERR_OK)
    {
        ht_free_content(ht);
        ht->values = tmp;
        ht->m = new_m;
    }
    else {
        free(tmp);
    }
    return rc;
}

size_t ht_get_max_collision(hash_table_t *ht)
{
    size_t max_c = 0;
    for (size_t i = 0; i < ht->m; i++)
    {
        max_c = MAX(max_c, ht->values[i].n);
    }
    return max_c;
}

double ht_get_average_collision(hash_table_t *ht)
{
    double res = 0;
    for (size_t i = 0; i < ht->m; i++)
    {
        res += ((double)ht->values[i].n) / 2.0 / ht->m;
    }
    return res;
}

int ht_insert(hash_table_t *hash_table, char *name, char *manual, double max_collision)
{
    if (hash_table == NULL || name == NULL || manual == NULL)
        return ERR_RANGE;
    int rc = ERR_OK;

    if (hash_table->m == 0)
        rc = ht_restruct(hash_table, 1);

    size_t index = hash_func(name, hash_table->m);

    rc = element_arr_add(&hash_table->values[index], name, manual);
    while (!rc && ht_get_average_collision(hash_table) >= max_collision)
    {
        rc = ht_restruct(hash_table, hash_table->m + 1);
    }

    return rc;
}

void ht_print(FILE *f, hash_table_t *ht)
{
    if (ht->m == 0)
    {
        fprintf(f, "Пустая таблица\n");
        return;
    }
    for (size_t i = 0; i < ht->m; i++)
    {
        if (ht->values[i].n > 0)
            fprintf(f, "%lu: ", hash_func(ht->values[i].values[0].name, ht->m));
        for (size_t j = 0; j < ht->values[i].n; j++)
        {
            fprintf(f, "\"%s\" ", ht->values[i].values[j].name);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "Среднее количесво сравнения для поиска: %lf\n", ht_get_average_collision(ht));
}

const char *ht_get_manual(hash_table_t *ht, char *name)
{
    const char *manual = NULL;
    size_t index = hash_func(name, ht->m);
    for (size_t i = 0; !manual && i < ht->values[index].n; i++)
    {
        if (strcmp(name, ht->values[index].values[i].name) == 0)
            manual = ht->values[index].values[i].manual;
    }
    return manual;
}   

int ht_read_from_file(hash_table_t *ht, const char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return ERR_FILE;
    ht_free_content(ht);
    int rc = ERR_OK;
    while (!rc) 
    {
        element_t e;
        rc = element_read(f, &e);
        if (!rc) rc = ht_insert(ht, e.name, e.manual, 3);
    }
    if (rc && feof(f))
        rc = ERR_OK;
    fclose(f);
    return rc;
}

size_t ht_get_size(hash_table_t *ht)
{
    size_t s = sizeof(hash_table_t) + sizeof(element_arr_t *) * ht->m;
    for (size_t i = 0; i < ht->m; i++)
        s += element_arr_get_size(&ht->values[i]);
    return s;
}


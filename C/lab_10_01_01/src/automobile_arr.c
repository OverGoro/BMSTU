#include "automobile_arr.h"
#include "automobile.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

int a_arr_count(FILE *f, size_t *n)
{
    size_t tmp_n = 0;
    int rc = ERR_OK;
    automobile_t a = { NULL, 0, 0 };
    while (rc == ERR_OK)
    {
        rc = automobile_read(f, &a);
        if (!rc)
            tmp_n++;
    }
    automobile_free_content(&a);
    if (!feof(f))
        rc = ERR_IO;
    else
    {
        rc = ERR_OK;
        *n = tmp_n;
    }
    return rc;
}

int a_arr_read(FILE *f, automobile_t **a_arr, size_t *n)
{
    int rc = a_arr_count(f, n);
    if (rc)
        return rc;  
    *a_arr = calloc(*n, sizeof(automobile_t));
    if (*a_arr == NULL)
        return ERR_MEM;
    fseek(f, 0, SEEK_SET);
    for (size_t i = 0; i < *n; i++)
        automobile_read(f, &(*a_arr)[i]);
    return rc;
}

void a_arr_free(automobile_t **a_arr, size_t *n)
{
    for (size_t i = 0; i < *n; i++)
    {
        automobile_free_content(&(*a_arr)[i]);
    }
    free(*a_arr);
    *a_arr = NULL;
    *n = 0;
}


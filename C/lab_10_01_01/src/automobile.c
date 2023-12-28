#include "automobile.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int automobile_vin_cmp(const void *a_l, const void *a_r)
{
    automobile_t *aal = (automobile_t *)a_l;
    automobile_t *aar = (automobile_t *)a_r;
    int rc = strcmp(aal->vin, aar->vin);
    return rc;
}

int automobile_mileage_cmp(const void *a_l, const void *a_r)
{
    automobile_t *aal = (automobile_t *)a_l;
    automobile_t *aar = (automobile_t *)a_r;
    int rc = 0;
    if (aal->mileage < aar->mileage)
        rc = -1;
    else if (aal->mileage > aar->mileage)
        rc = 1;
    return rc;
}

int automobile_price_cmp(const void *a_l, const void *a_r)
{
    automobile_t *aal = (automobile_t *)a_l;
    automobile_t *aar = (automobile_t *)a_r;
    int rc = 0;
    if (aal->price < aar->price)
        rc = -1;
    else if (aal->price > aar->price)
        rc = 1;
    return rc;
}

int automobile_cmp(const void *a_l, const void *a_r)
{
    int rc = automobile_vin_cmp(a_l, a_r);
    if (rc == 0)
        rc = automobile_mileage_cmp(a_l, a_r);
    if (rc == 0)
        rc = automobile_price_cmp(a_l, a_r);
    return rc;
}

void automobile_free_content(automobile_t *a)
{
    if (a != NULL)
    {
        free(a->vin);
        a->vin = NULL;
    }
}

automobile_t *automobile_create(void)
{
    automobile_t *a = calloc(1, sizeof(automobile_t));
    return a;
}

int automobile_init_content(automobile_t *a, char *vin, size_t mileage, size_t price)
{
    char *tmp_vin = strdup(vin);
    if (tmp_vin)
    {
        automobile_free_content(a);
        a->vin = tmp_vin;
        a->mileage = mileage;
        a->price = price;
        return ERR_OK;
    }
    free(tmp_vin);
    return ERR_MEM;
}

int automobile_read(FILE *f, automobile_t *a)
{
    char *vin = NULL;
    int mileage;
    int price;
    int rc = ERR_OK;
    int len;
    size_t read = 0;

    // Чтение VIN
    if ((len = getline(&vin, &read, f)) == -1 || len <= 1)
    {
        rc = ERR_IO;
    }
    else
    {
        vin[--len] = '\0';
        if (len == 0)
            rc = ERR_RANGE;
    }

    // Чтение пробега
    if (rc == ERR_OK)
    {
        if (fscanf(f, "%d\n", &mileage) == 1)
        {
            if (mileage < 0)
                rc = ERR_RANGE;
        }
        else
            rc = ERR_IO;
    }

    // Чтение стоимости
    if (rc == ERR_OK)
    {
        if (fscanf(f, "%d\n", &price) == 1)
        {
            if (price < 0)
                rc = ERR_RANGE;
        }
        else
            rc = ERR_IO;
    }
    if (!rc)
        rc = automobile_init_content(a, vin, mileage, price);

    free(vin);
    return rc;
}

void automobile_print(FILE *f, const void *p)
{
    automobile_t *a = (automobile_t *)p;
    fprintf(f, "%s\n%lu\n%lu\n", a->vin, a->mileage, a->price);
}


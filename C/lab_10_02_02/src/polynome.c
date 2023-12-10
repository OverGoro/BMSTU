#include "polynome.h"
#include <stdio.h>

int polynome_input(FILE *f, node_t **polynome)
{
    list_free(polynome);
    int k = 0;
    int n = 0;
    
    if (fscanf(f, "%d", &n) != 1)
        return ERR_IO;
    else if (n <= 0)
        return ERR_RANGE;

    int rc = ERR_OK;

    for (int i = 0 ; rc == ERR_OK && i < n; i++)
    {
        if (fscanf(f, "%d", &k) == 1)
        {
            node_t *tmp_node = node_create(k);
            *polynome = list_add_tail(*polynome, tmp_node);
        }
        else
            rc = ERR_IO;
    }

    return rc;
}

void polynome_free(node_t **polynome)
{
    list_free(polynome);
}

void polynome_print(FILE *f, node_t *polynome)
{
    node_t *pcur = polynome;
    while (pcur != NULL)
    {
        fprintf(f, "%d ", pcur->data);
        pcur = pcur->next;
    }
    fprintf(f, "L\n");
}

int polynome_count(node_t *polynome, int x, int *r)
{
    int res = 0;
    node_t *pcur = polynome;

    if (pcur == NULL)
        return ERR_EMPTY_ARR;

    res = pcur->data;
    pcur = pcur->next;
    while (pcur != NULL)
    {
        res = res * x + pcur->data;
        pcur = pcur->next;
    }

    *r = res;
    return ERR_OK;
}

node_t *polynome_get_derivative(node_t *polynome)
{
    node_t *res = NULL;
    node_t *pcur = polynome;
    int cur_pow = 0;
    while (pcur->next != NULL)
    {
        cur_pow++;
        pcur = pcur->next;
    }

    // Если полином - просто число
    if (cur_pow == 0)
    {
        node_t *n = node_create(0);
        res = list_add_tail(res, n);
    }
    else 
    {
        for (pcur = polynome; pcur->next != NULL; pcur = pcur->next)
        {
            node_t *n = node_create(pcur->data * cur_pow);
            res = list_add_tail(res, n);
            cur_pow--;
        }
    }
    return res;
}

node_t *polynome_summ(const node_t *polynome_1, const node_t *polynome_2)
{
    node_t *res = NULL;
    const node_t *pcur_1 = polynome_1, *pcur_2 = polynome_2;

    int pow_1 = -1;
    for (const node_t *pcur = polynome_1;  pcur != NULL; pcur = pcur->next)
        pow_1++;

    int pow_2 = -1;
    for (const node_t *pcur = polynome_2;  pcur != NULL; pcur = pcur->next)
        pow_2++;

    while (pcur_1 != NULL || pcur_2 != NULL)
    {
        if (pow_1 == pow_2)
        {
            node_t *n = node_create(pcur_1->data + pcur_2->data);
            res = list_add_tail(res, n);
            pcur_1 = pcur_1->next;
            pcur_2 = pcur_2->next;
            pow_1--;
            pow_2--;
        }
        else if (pow_1 > pow_2)
        {
            node_t *n = node_create(pcur_1->data);
            res = list_add_tail(res, n);
            pcur_1 = pcur_1->next;
            pow_1--;
        }
        else
        {
            node_t *n = node_create(pcur_2->data);
            res = list_add_tail(res, n);
            pcur_2 = pcur_2->next;
            pow_2--;
        }
    }
    return res;
}

void polynome_devide(node_t **polynome, node_t **polynome_even, node_t **polynome_odd)
{
    if (*polynome == NULL)
    {
        *polynome_even = NULL;
        *polynome_odd = NULL;
        return;
    }
    int max_pow = 0;
    for (node_t *pcur = (*polynome)->next;  pcur != NULL; pcur = pcur->next)
        max_pow++;
    
    node_t *pcur = *polynome;
    while (pcur != NULL)
    {
        node_t *pnext = pcur->next;
        pcur->next = 0;
        if (max_pow % 2 == 0)
            *polynome_even = list_add_tail(*polynome_even, pcur);
        else 
            *polynome_odd = list_add_tail(*polynome_odd, pcur);
        max_pow--;
        pcur = pnext;
    }
    *polynome = NULL;
}


#include "student_keys.h"


int ka_cmp_marks(const void *p_l, const void *p_r)
{
    double res = ((student_key_t *)p_l)->average_mark - ((student_key_t *)p_r)->average_mark;
    if (res < 0)
        return -1;
    else if (res == 0)
        return 0;
    else
        return 1;
}
int ka_create(student_key_t **ka_beg, student_key_t **ka_end, const student_t *arr_beg, const student_t *arr_end)
{
    if (*ka_beg == NULL)
    {
        *ka_beg = malloc(sizeof(student_key_t) * (arr_end - arr_beg));
        if (*ka_beg == NULL)
            return ERR_MEMORY;
    }
    else
    {
        student_key_t *ptemp = NULL;
        ptemp = malloc(sizeof(student_key_t) * (arr_end - arr_beg));
        if (ptemp == NULL)
            return ERR_MEMORY;
        free(*ka_beg);
        *ka_beg = ptemp;
    }
    *ka_end = *ka_beg + (arr_end - arr_beg);
    const student_t *arr_cur = arr_beg;
    for (student_key_t *pcur = *ka_beg; pcur < *ka_end; pcur++)
    {
        pcur->n = arr_cur->n;
        pcur->average_mark = arr_cur->average_mark;
        arr_cur++;
    }
    return ERR_OK;
}

void ka_print(FILE *f, const student_key_t *arr_beg, const student_key_t *arr_end, bool is_table)
{
    if (is_table)
    {
        fprintf(f, "  n | Оценка\n");
        for (const student_key_t *pcur = arr_beg; pcur < arr_end; pcur++)
        {
            fprintf(f, "%*lu | ",4, pcur->n);
            fprintf(f, "%*lf\n", 4, pcur->average_mark);
        }
    }
}

int ka_print_table(FILE *f, 
                   const student_t *arr_beg,
                   const student_key_t *key_beg, const student_key_t *key_end)
{
    if (key_beg == key_end)
    {
        fprintf(f, "\033[92mПустая таблица\033[0m\n");
        return ERR_OK;
    }
    printf(TABLE_TITLE);
    for (const student_key_t *pcur = key_beg; pcur < key_end; pcur++)
    {
        student_print(f, &arr_beg[pcur->n], true);
    }
    return ERR_OK;
}


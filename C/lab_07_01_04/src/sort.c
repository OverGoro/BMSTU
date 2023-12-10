#include "sort.h"

// Компораторы
int cmp_int(const void *l, const void *r)
{
    return *(int *)l - *(int *)r;
}

// Сортировка
void swap(void *l, void *r, size_t e_size)
{
    char tmp;
    char *pl = l;
    char *pr = r;
    for (size_t i = 0; i < e_size; i++)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
        pl++;
        pr++;
    }
}

/*void mysort(void *pdata, size_t n, size_t e_size, cmp_t cmp)
{
    if (n < 2)
        return;
    char *pbeg = pdata;
    char *pend = pbeg + n * e_size;
    char *last_swap = pend;
    char *ptop = pend;
    while (ptop > pbeg)
    {
        last_swap = pbeg;
        for (char *pcur = pbeg + e_size; pcur < ptop; pcur += e_size)
        {
            if (cmp(pcur - e_size, pcur) > 0)
            {
                swap(pcur - e_size, pcur, e_size);
                last_swap = pcur;
            }
        }
        ptop = last_swap;
    }
}*/

void mysort(void *pdata, size_t n, size_t e_size, cmp_t cmp)
{
    if (n < 2)
        return;
    char *pbeg = pdata;
    char *pend = pbeg + n * e_size;
    char *pcur = pbeg;
    char *pmin = pcur;
    while (pcur < pend)
    {
        pmin = pcur;
        for (char *pi = pcur + e_size; pi < pend; pi += e_size)
        {
            if (cmp(pi, pmin) < 0)
            {
                pmin = pi;
            }
        }
        swap(pcur, pmin, e_size);
        pcur += e_size;
    }
}

double get_average(const int *pbeg, const int *pend)
{
    // Подсчет среднего арифметического массива
    double average_value = 0;         // Среднее значение элементов в массиве
    size_t n_src = (pend - pbeg); // Количество элмеентов в массив

    // Определение среднего арифметического массива
    for (const int *pcur = pbeg; pcur < pend; pcur++)
    {
        average_value += *pcur;
    }
    average_value /= n_src;
    return average_value;
}

size_t count_greater(const int *pbeg, const int *pend, double val)
{
    size_t n_stb = 0;
    for (const int *pcur = pbeg; pcur < pend; pcur++)
    {
        if ((double)*pcur > val)
            n_stb++;
    }
    return n_stb;
}


int fill_greater(const int *pb_src, const int *pe_src, int *pb_dst, double val)
{
    const int *pcur_src = pb_src;
    int *pcur_dst = pb_dst;

    while (pcur_src < pe_src)
    {
        if (*pcur_src > val)
        {
            *pcur_dst = *pcur_src;
            pcur_src++;
            pcur_dst++;
        }
        else
            pcur_src++;
    }
    if (pcur_dst == pb_dst)
        return ERR_EMPTY_ARR;
    return ERR_OK;
}

// Фильтрация
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src >= pe_src)
        return ERR_RANGE;
    // Подсчет среднего арифметического массива
    double average_value = 0; // Среднее значение элементов в массиве
    size_t n_stb = 0;         // Количество подхоядщих элементов в массиве

    // Определение среднего арифметического массива
    average_value = get_average(pb_src, pe_src);

    // Определение количества подходящих элементов
    n_stb = count_greater(pb_src, pe_src, average_value);

    // Если подходящих элементов нет - вернуть код ошибки
    if (!n_stb)
        return ERR_EMPTY_ARR;

    // Запись подходящих элементов в новый массив
    *pb_dst = (int *)malloc(sizeof(int) * n_stb);
    if (pb_dst == NULL)
        return ERR_MEMORY;
    *pe_dst = *pb_dst + n_stb;
    
    int rc = fill_greater(pb_src, pe_src, *pb_dst, average_value);

    return rc;
}

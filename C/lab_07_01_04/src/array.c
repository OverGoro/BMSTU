#include "array.h"

size_t arr_cnt_in_file(FILE *f, size_t *pn)
{
    *pn = 0;
    int cur_el = 0;
    // Подсчет элементов в массиве
    while (fscanf(f, "%d", &cur_el) == 1)
    {
        (*pn)++;
    }
    // Считывание последнего \n
    fgetc(f);

    // Если не конец файла, то файл имеет неправильный формат
    if (!feof(f))
        return ERR_IO;
    return ERR_OK;
}

int arr_read(FILE *f, int *pbeg, int *pend)
{
    for (int *pcur = pbeg; pcur < pend; pcur++)
    {
        if (fscanf(f, "%d", pcur) != 1)
            return ERR_IO;
    }
    return ERR_OK;
}

int arr_create(FILE *f, int **pbeg, int **pend)
{
    // Подсчет количества элементов в файле
    size_t n;

    fseek(f, 0, SEEK_SET);
    int rc = arr_cnt_in_file(f, &n);
    if (rc != ERR_OK)
        return rc;

    // Выделение памяти под массив
    if (n == 0)
        return ERR_IO;
    
    *pbeg = malloc(sizeof(int) * n);
    if (*pbeg == NULL)
        return ERR_MEMORY;
    *pend = *pbeg + n;
    
    // Установка указателя на начало файла
    fseek(f, 0, SEEK_SET);

    // Заполнение массива
    rc = arr_read(f, *pbeg, *pend);

    return rc;
}

int arr_print(FILE *f, const int *pbeg, const int *pend)
{
    for (const int *pcur = pbeg; pcur < pend; pcur++)
    {
        fprintf(f, "%d ", *pcur);
    }
    fprintf(f, "\n");
    return ERR_OK;
}

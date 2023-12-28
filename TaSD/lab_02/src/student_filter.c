#include "student_filter.h"

size_t sa_count_filtered(const student_t *arr_beg, const student_t *arr_end, const student_t *prototype, cmp_t *cmp_arr, size_t cmp_n)
{
    size_t temp_n = 0;
    for (const student_t *pcur = arr_beg; pcur < arr_end; pcur++)
    {
        int rc = ERR_OK;
        for (size_t i = 0; i < cmp_n; i++)
        {
            if ((rc = cmp_arr[i](pcur, prototype)) != 0)
                break;
        }
        if (rc == ERR_OK)
            temp_n++;
    }
    return temp_n;
}

int sa_create_filtered(const student_t *arr_beg, const student_t *arr_end,
                         student_t **dst_beg, student_t **dst_end,
                         const student_t *prototype, size_t n_stb,
                         cmp_t *cmp_arr, size_t cmp_n)
{
    // Выделение памяти под новый массив
    if (*dst_beg == NULL)
    {
        *dst_beg = (student_t *)malloc(sizeof(student_t) * n_stb);
        if (*dst_beg == NULL)
            return ERR_MEMORY;
    }
    else
    {
        student_t *ptemp = realloc(*dst_beg, sizeof(student_t) * n_stb);
        if (ptemp == NULL)
            return ERR_MEMORY;
        *dst_beg = ptemp;
    }

    *dst_end = *dst_beg + n_stb;

    // Заполнение фильтрованного массива
    student_t *res_cur = *dst_beg;
    for (const student_t *pcur = arr_beg; pcur < arr_end; pcur++)
    {
        bool suitable = true;
        for (size_t i = 0; i < cmp_n; i++)
        {
            if (cmp_arr[i](pcur, prototype) != 0)
                suitable = false;
        } 
        if (suitable)
        {
            *res_cur = *pcur;
            res_cur++;
        }
    }
    return ERR_OK;

}

int sa_filter(const student_t *prototype,
               const student_t *arr_beg, const student_t *arr_end,
               student_t **res_beg, student_t **res_end,
               cmp_t *cmp_arr, size_t cmp_n)
{
    // Проверка корректности исходного массива
    if (arr_beg >= arr_end)
        return ERR_RANGE;

    // Определение размера фильтрованного массива
    size_t n_stb = sa_count_filtered(arr_beg, arr_end, prototype, cmp_arr, cmp_n);
    
    // Фильтрованный массив оказался пустым
    if (!n_stb)
        return ERR_EMPTY_ARR;
    int rc = sa_create_filtered(arr_beg, arr_end, res_beg, res_end, prototype, n_stb, cmp_arr, cmp_n);
    return rc;
}


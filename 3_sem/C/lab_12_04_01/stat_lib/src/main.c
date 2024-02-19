#include "array.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
        return ERR_ARGS_NUM;
    if (argc == 4 && strcmp(argv[3], "f") != 0)
        return ERR_ARGS_VALUE;

    char *in_file = argv[1];  // Входной файл
    char *out_file = argv[2]; // Выходной файл

    int *arr = NULL;    // Массив целых чисел
    int *arr_end = arr; // Конец массива целых чисел
    size_t arr_n = 0;
    
    int *arr_sort_beg = arr; // Начало массива для сортировки
    int *arr_sort_end = arr_end; // Конец массива для сортировки 

    int rc = ERR_OK;

    FILE *f_in = fopen(in_file, "r");
    if (f_in == NULL)
        rc = ERR_FILE;

    FILE *f_out = fopen(out_file, "w");
    if (f_out == NULL)
        rc = ERR_FILE;

    // Чтение массива
    if (!rc) rc = arr_cnt_in_file(f_in, &arr_n);
    if (!rc && arr_n == 0) rc = ERR_IO;
    if (!rc)
    {
        arr = malloc(sizeof(int) * arr_n);
        if (!arr) rc = ERR_MEMORY;
        else arr_end = arr + arr_n;
    }
    if (!rc)
    { 
        fseek(f_in, 0, SEEK_SET);
        rc = arr_read(f_in, arr, arr_end);
    }
    

    // 3-й аргумент уже проверялся при проверке аргументов и равен "f"
    if (!rc)
    {
        size_t n = 0;
        if (argc == 4)
        {
            arr_sort_beg = NULL;
            arr_sort_end = arr_sort_beg;
            double average = get_average(arr, arr_end);
            n = count_greater(arr, arr_end, average);
            arr_sort_beg = malloc(sizeof(int) * n);
            if (arr_sort_beg == NULL)
                rc = ERR_MEMORY;
            if (!rc)
            {
                rc = key(arr, arr_end, arr_sort_beg, arr_sort_end);
                arr_sort_end = arr_sort_beg + n;
            }
        }
        else
        {
            arr_sort_beg = arr;
            arr_sort_end = arr_end;
            n = arr_end - arr;
        }
        if (!rc)
        {
            mysort(arr_sort_beg, n, sizeof(arr_sort_beg[0]), cmp_int);
            rc = arr_print(f_out, arr_sort_beg, arr_sort_end);
        }
    }

    if (f_in != NULL && f_in != stdin)
        fclose(f_in);
    if (f_out != NULL && f_out != stdout)
        fclose(f_out);
    if (arr != NULL)
        free(arr);
    if (arr_sort_beg != arr && arr_sort_beg != NULL)
        free(arr_sort_beg);
    return rc;
}

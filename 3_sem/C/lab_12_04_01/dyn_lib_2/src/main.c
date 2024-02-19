#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*cmp_t)(const void *l, const void *r);
typedef size_t (*fn_count_greater)(const int *, const int *, double );
typedef double (*fn_get_average)(const int *, const int *);

typedef int (*fn_key_t)(const int *, const int *, int *);
typedef void (*fn_my_sort_t)(void *, size_t, size_t, cmp_t);
typedef int (*fn_arr_print_t)(FILE *, const int *, const int *);
typedef size_t (*fn_arr_cnt_in_file)(FILE *f, size_t *pn);
typedef int (*fn_arr_read)(FILE *f, int *pbeg, int *pend);

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
        return ERR_ARGS_NUM;
    if (argc == 4 && strcmp(argv[3], "f") != 0)
        return ERR_ARGS_VALUE;

    int rc = ERR_OK;

    char *in_file = argv[1];  // Входной файл
    char *out_file = argv[2]; // Выходной файл

    int *arr = NULL;    // Массив целых чисел
    int *arr_end = arr; // Конец массива целых чисел
    size_t arr_n = 0;   // Количество элементов в массиве

    
    int *arr_sort_beg = arr; // Начало массива для сортировки
    int *arr_sort_end = arr_end; // Конец массива для сортировки 
    
    void *sortlib = NULL, *arrlib = NULL; // Динамические библиотеки
    FILE *f_in = NULL, *f_out = NULL;

    f_in = fopen(in_file, "r");
    if (f_in == NULL)
    {
        rc = ERR_FILE;
        goto out;
    }

    f_out = fopen(out_file, "w");
    if (f_out == NULL)
    {
        rc = ERR_FILE;
        goto out;
    }

   
    sortlib = dlopen("./out/libsort.so", RTLD_NOW);
    if (!sortlib)
    {
        rc = ERR_LIB;
        goto out;
    }

    arrlib  = dlopen("./out/libarray.so", RTLD_NOW);
    if (!arrlib)
    {
        rc = ERR_LIB;
        goto out;
    }

    fn_arr_print_t arr_print = (fn_arr_print_t) dlsym(arrlib, "arr_print");

    fn_get_average get_average = (fn_get_average) dlsym(sortlib, "get_average");
    fn_count_greater count_greater = (fn_count_greater) dlsym(sortlib, "count_greater");
    fn_arr_cnt_in_file arr_cnt_in_file = (fn_arr_cnt_in_file) dlsym(arrlib, "arr_cnt_in_file");
    fn_arr_read arr_read = (fn_arr_read) dlsym(arrlib, "arr_read");

    fn_key_t key = (fn_key_t) dlsym(sortlib, "key");
    fn_my_sort_t mysort = (fn_my_sort_t) dlsym(sortlib, "mysort");
    cmp_t cmp_int = (cmp_t) dlsym(sortlib, "cmp_int");


    // Чтение массива
    if ((rc = arr_cnt_in_file(f_in, &arr_n))) goto out;
    if (arr_n == 0)
    {
        rc = ERR_IO;
        goto out;
    }
    arr = malloc(sizeof(int) * arr_n);
    if (!arr) rc = ERR_MEMORY;
    else arr_end = arr + arr_n;
    if (rc) goto out;
    fseek(f_in, 0, SEEK_SET);
    if((rc = arr_read(f_in, arr, arr_end))) goto out;
    


    size_t n = 0;
    if (argc == 4)
    {
        arr_sort_beg = NULL;
        arr_sort_end = arr_sort_beg;
        double average = get_average(arr, arr_end);
        n = count_greater(arr, arr_end, average);
        arr_sort_beg = malloc(sizeof(int) * n);
        if (arr_sort_beg == NULL)
        {
            rc = ERR_MEMORY;
            goto out;
        }
        rc = key(arr, arr_end, arr_sort_beg);
        arr_sort_end = arr_sort_beg + n;
    }
    else
    {
        arr_sort_beg = arr;
        arr_sort_end = arr_end;
        n = arr_end - arr;
    }
    mysort(arr_sort_beg, n, sizeof(arr_sort_beg[0]), cmp_int);
    rc = arr_print(f_out, arr_sort_beg, arr_sort_end);

out:
    if (sortlib)
        dlclose(sortlib);
    if (arrlib)
        dlclose(arrlib);
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

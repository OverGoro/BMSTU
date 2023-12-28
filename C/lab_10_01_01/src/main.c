#include "automobile_arr.h"
#include "automobile.h"
#include "list.h"
#include "error.h"
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>
// Файл содержит объявления по продаже автомобилей

// Комманды:
// p file_name [f_out]- вывести содержимое файла
// p-unique file_name [f_out] - вывести с удаленными дубликатами
// p-max file_name [f_out] - вывести самое самое дорогое предложение
// p-min file_name [f_out] - вывести самое дешевое предложение
// ps-vin file_name [f_out] - отсортировать по VIN и вывести
// ps-mileage file_name [f_out] - отсортировать по пробегу и вывести
// ps-price  file_name [f_out] - отсортровать по цене и вывести
// pr-vin file_name [f_out] - отсортировать по VIN и вывести в обратном порядке
// pr-mileage file_name [f_out] - отсортировать по пробегу и вывести в обратном порядке
// pr-price  file_name [f_out] - отсортровать по цене и вывести в обратном порядке 
int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
        return ERR_ARGS_NUM;

    int rc = ERR_OK;

    char *cmnd = argv[1];

    FILE *f_in = fopen(argv[2], "r");
    if (f_in == NULL)
        rc = ERR_FILE;

    FILE *f_out = stdout;
    if (rc == ERR_OK && argc == 4)
    {
        f_out = fopen(argv[3], "w");
        if (f_out == NULL)
            rc = ERR_FILE;
    }
    automobile_t *arr = NULL;
    size_t n = 0;
    node_t *head = NULL;

    if (rc == ERR_OK)
        rc = a_arr_read(f_in, &arr, &n);
    if (rc == ERR_OK)
        rc = list_form_by_arr(&head, arr, n);

    if (rc == ERR_OK && strcmp(cmnd, "p") == 0)
    {
        list_print(f_out, head, automobile_print);
    }
    else if (rc == ERR_OK && strcmp(cmnd, "p-unique") == 0)
    {
        remove_duplicates(&head, automobile_cmp);
        list_print(f_out, head, automobile_print);
    }
    else if (rc == ERR_OK && strcmp(cmnd, "p-max") == 0)
    {
        remove_duplicates(&head, automobile_cmp);
        head = sort(head, automobile_price_cmp);
        automobile_t *a = (automobile_t *)pop_back(&head);
        automobile_print(f_out, a);
    }
    else if (rc == ERR_OK && strcmp(cmnd, "p-min") == 0)
    {
        remove_duplicates(&head, automobile_cmp);
        head = sort(head, automobile_price_cmp);
        automobile_t *a = (automobile_t *)pop_front(&head);
        automobile_print(f_out, a);
    }
    else if (rc == ERR_OK && strcmp(cmnd, "ps-vin") == 0)
    {
        remove_duplicates(&head, automobile_cmp);
        head = sort(head, automobile_vin_cmp);
        list_print(f_out, head, automobile_print);
    }
    else if (rc == ERR_OK && strcmp(cmnd, "ps-mileage") == 0)
    {
        head = sort(head, automobile_mileage_cmp);
        list_print(f_out, head, automobile_print);
    }
    else if (rc == ERR_OK && strcmp(cmnd, "ps-price") == 0)
    {
        head = sort(head, automobile_price_cmp);
        list_print(f_out, head, automobile_print);
    }
    else if (rc == ERR_OK && strcmp(cmnd, "pr-vin") == 0)
    {
        head = sort(head, automobile_vin_cmp);
        head = reverse(head);
        list_print(f_out, head, automobile_print);
    }
    else if (rc == ERR_OK && strcmp(cmnd, "pr-mileage") == 0)
    {
        head = sort(head, automobile_mileage_cmp);
        head = reverse(head);
        list_print(f_out, head, automobile_print);
    }
    else if (rc == ERR_OK && strcmp(cmnd, "pr-price") == 0)
    {
        head = sort(head, automobile_price_cmp);
        head = reverse(head);
        list_print(f_out, head, automobile_print);
    }
    else if (rc == ERR_OK)
        rc = ERR_ARGS_VALUE;
    if (f_in != NULL)
        fclose(f_in);
    if (f_out != NULL && f_out != stdout)
        fclose(f_out);
    list_free(&head);
    a_arr_free(&arr, &n);
    return rc;
}

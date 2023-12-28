#include "check_cmp.h"
#include <string.h>

int cmp_film_t_arr(film_t *arr_1, film_t *arr_2, size_t n_1, size_t n_2)
{
    if (n_1 != n_2)
         return 1;
    for (size_t i = 0; i < n_1; i++)
    {
        if (strcmp(arr_1[i].title, arr_2[i].title) != 0)
            return 1;
        if (strcmp(arr_1[i].name, arr_2[i].name) != 0)
            return 1;
        if (arr_1->year != arr_2->year)
            return 1;
    }
    return 0;
}


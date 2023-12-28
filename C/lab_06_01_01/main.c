#include <stdio.h>

#include "error.h"
#include "film.h"
#include "film_array.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *f_r = NULL, *f_w = NULL;
    int rc = ERR_OK;

    int search_year = 0;

    if (argc < 3 || argc > 4)
    {
        return ERR_ARGS_NUM;
    }

    // Проверка параметров 
    if (strcmp(argv[2], FIELD_TYPE_TITLE) == 0)
        rc = ERR_OK;
    else if (strcmp(argv[2], FIELD_TYPE_NAME) == 0)
        rc = ERR_OK;
    else if (strcmp(argv[2], FIELD_TYPE_YEAR) == 0)
    {
        rc = ERR_OK;
        if (argc == 4)
        {
            char *end_ptr = NULL;
            search_year = strtol(argv[3], &end_ptr, 10);
            if (*end_ptr != '\0' || search_year <= 0)
                return ERR_ARGS_VALUE;
        }
    }
    else
        return ERR_ARGS_VALUE;

    f_r = fopen(argv[1], "r");
    if (f_r == NULL)
    {
        return ERR_FILE; 
    }
    
    film_t film_array[MAX_N];
    size_t n = 0;
    
    if (strcmp(argv[2], FIELD_TYPE_TITLE) == 0)        
        rc = fa_sorted_read(f_r, film_array, &n, MAX_N, film_cmp_by_title);
    else if (strcmp(argv[2], FIELD_TYPE_NAME) == 0)
        rc = fa_sorted_read(f_r, film_array, &n, MAX_N, film_cmp_by_name);
    else if (strcmp(argv[2], FIELD_TYPE_YEAR) == 0)
        rc = fa_sorted_read(f_r, film_array, &n, MAX_N, film_cmp_by_year);


    if (n == 0 && rc == ERR_OK)
        rc = ERR_EMPTY_ARR;

    if (argc == 3 && rc == ERR_OK)
    {    
        f_w = stdout;
        rc = fa_print(f_w, film_array, n);
    }
    else if (argc == 4 && rc == ERR_OK)
    {
        f_w = stdout;
        film_t *found_film = NULL;
        film_t prototype;

        // Поиск по названию
        if (strcmp(argv[2], FIELD_TYPE_TITLE) == 0)
        {
            strncpy(prototype.title, argv[3], TITLE_LEN);
            found_film = fa_bin_search(film_array, n, &prototype, film_cmp_by_title);
        }
        // Поиск по фамилии автора
        else if (strcmp(argv[2], FIELD_TYPE_NAME) == 0)
        {
            strncpy(prototype.name, argv[3], NAME_LEN);
            found_film = fa_bin_search(film_array, n, &prototype, film_cmp_by_name);
        }
        // Поиск по году выпуска
        else if (strcmp(argv[2], FIELD_TYPE_YEAR) == 0)
        {
            prototype.year = search_year;
            found_film = fa_bin_search(film_array, n, &prototype, film_cmp_by_year);
        }

        if (found_film != NULL)
            film_print(f_w, found_film);
        else if (rc == ERR_OK)
            fprintf(f_w, "Not found\n");
    }

    if (f_r != NULL)
        fclose(f_r);
    if (f_w != NULL && f_w != stdout)
        fclose(f_w);

    return rc;
}


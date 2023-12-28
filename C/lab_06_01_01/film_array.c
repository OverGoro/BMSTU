#include "film_array.h"

// Функции ввода 
int fa_sorted_read(FILE *f, film_t *film_array, size_t *pn, size_t max_n, comporator_t cmp)
{
    film_t film;
    int rc = ERR_OK;
    size_t i = 0;

    while (rc == ERR_OK)
    {
        rc = film_read(f, &film);
        if (rc == ERR_OK)
        {
            if (i < max_n) 
            {
                size_t pos = 0;
                pos = fa_find_place(film_array, i, &film, cmp);
                fa_paste(film_array, &i, &film, pos);
            }    
            else
            {
                return ERR_OVERFLOW;
            }
        }
    }
    *pn = i;
    char tmp[2];
    fgets(tmp, sizeof(tmp), f);
    if (feof(f) != 0)
        rc = ERR_OK;

    return rc;
}

// Функции вставки
void fa_paste(film_t *film_array, size_t *n, film_t *film, size_t pos)
{
    assert(pos <= *n);
    film_t *replaced_film = &film_array[pos];
    for (film_t *cur_film = film_array + *n; cur_film > replaced_film; cur_film--)
    {
        *cur_film = *(cur_film - 1);
    }
    *replaced_film = *film;
    (*n)++;
}

size_t fa_find_place(film_t *film_array, size_t n, const film_t *film, comporator_t cmp)
{
    size_t pos = 0;
    while (pos < n && cmp(film, &film_array[pos]) >= 0)
        pos++;
    return pos;
}

// Функции вывода

int fa_print(FILE *f, film_t *film_array, size_t n)
{
    film_t *end_film = film_array + n;
    int rc = ERR_OK;
    for (film_t *film = film_array; film < end_film; film++)
    {
        rc = film_print(f, film);
        if (rc != ERR_OK)
            return rc;
    }
    return rc;
}

// Функции поиска
film_t *fa_bin_search(film_t *film_array, size_t n, film_t *prototype, comporator_t cmp)
{
    film_t *found_film = NULL;
    int left_i = 0, right_i = n - 1;
    int average_i = 0;
    while (right_i > left_i)
    {
        average_i = left_i + (right_i - left_i) / 2;
        if (cmp(&film_array[average_i], prototype) >= 0)
            right_i = average_i;
        else
            left_i = average_i + 1;
    }
    if (left_i == right_i && cmp(&film_array[right_i], prototype) == 0)
        found_film = film_array + right_i;
    return found_film;
}

#include "film_array.h"

film_t *fa_allocate(size_t n)
{
    film_t *ptmp = calloc(n, sizeof(film_t));
    return ptmp;
}

void fa_free(film_t **film_array, size_t n)
{
    if (*film_array != NULL)
    {
        for (size_t i = 0; i < n; i++)
            film_free_content(&(*film_array)[i]);
        free(*film_array);
        *film_array = NULL;
    }
}

int fa_count(FILE *f, size_t *n)
{
    film_t item = { NULL, NULL, 0 };
    size_t i = 0;
    int rc = ERR_OK;
    while (rc == ERR_OK)
    {
        rc = film_read(f, &item);
        if (rc == ERR_OK)
        {
            i++;
            film_free_content(&item);
        }
    }
    *n = i;
    char tmp[2];
    fgets(tmp, sizeof(tmp), f);
    if (rc != ERR_RANGE && feof(f) != 0)
        rc = ERR_OK;
    return rc;
}

int fa_sorted_create(FILE *f, film_t **pfilms, size_t *n_films, comporator_t cmp)
{
    film_t *ptmp = *pfilms;
    size_t n;
    int rc;
    *pfilms = NULL;
    *n_films = 0;
    rc = fa_count(f, &n);
    if (rc == ERR_OK && n == 0)
    {
        return ERR_RANGE;
    }
    if (rc == ERR_OK)
    {
        ptmp = fa_allocate(n);
        if (ptmp != NULL)
        {
            fseek(f, SEEK_SET, 0);
            rc = fa_sorted_read(f, ptmp, n_films, n, cmp);
            if (rc == ERR_OK)
            {
                *pfilms = ptmp;
                *n_films = n;
            }
        }
        else 
        {
            rc = ERR_MEM;
        }
    }
    if (rc)
        fa_free(&ptmp, n);
    return rc;
}

// Функции ввода 
int fa_sorted_read(FILE *f, film_t *film_array, size_t *pn, size_t max_n, comporator_t cmp)
{
    film_t film = { NULL, NULL, 0 };
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
                film.name = NULL;
                film.title = NULL;
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
    for (size_t i = *n; i > pos; i--)
    {
        film_array[i] = film_array[i - 1];
    }
    film_array[pos] = *film;
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

#include "film.h"

void film_free_content(film_t *pfilm)
{
    if (pfilm != NULL)
    {
        if (pfilm->title != NULL)
            free(pfilm->title);
        if (pfilm->name != NULL)
            free(pfilm->name);
        pfilm->title = NULL;
        pfilm->name = NULL;
    }
}

int film_init_content(film_t *pfilm, char *title, char *name, int year)
{
    char *tmp_title = strdup(title);
    char *tmp_name = strdup(name);
    if (tmp_title && tmp_name)
    {
        film_free_content(pfilm);
        pfilm->title = tmp_title;
        pfilm->name = tmp_name;
        pfilm->year = year;
        return ERR_OK;
    }
    free(tmp_name);
    free(tmp_title);
    return ERR_MEM;
}

int film_cmp_by_title(const film_t *l, const film_t *r)
{
    int rc = strcmp(l->title, r->title);
    if (rc > 0)
        return 1;
    else if (rc == 0)
        return 0;
    else
        return -1;
}

int film_cmp_by_name(const film_t *l, const film_t *r)
{
    int rc = strcmp(l->name, r->name);
    if (rc > 0)
        return 1;
    else if (rc == 0)
        return 0;
    else
        return -1;
}

int film_cmp_by_year(const film_t *l, const film_t *r)
{
    if (l->year > r->year)
        return 1;
    else if (l->year == r->year)
        return 0;
    else
        return -1;
}

int film_read(FILE *f, film_t *pf)
{
    char *title = NULL; // Название фильма
    char *name = NULL;  // Имя автора
    int year; // Год выпуска
    size_t read = 0;
    int len = 0;
    int rc = ERR_OK;

    if ((len = getline(&title, &read, f)) == -1 || len <= 1)
    {
        rc = ERR_IO;
    }
    else
    {
        title[--len] = '\0';
        if (len == 0)
            rc = ERR_RANGE;
    }

    if (rc == ERR_OK && ((len = getline(&name, &read, f)) == -1 || len <= 1))
    {
        rc = ERR_IO;
    }
    else if (rc == ERR_OK && len)
    {
        name[--len] = '\0';
        if (len == 0)
            rc = ERR_RANGE;
    }

    if (rc == ERR_OK)
    {
        if (fscanf(f, "%d\n", &year) == 1)
        {
            if (year > 0)
            {
                rc = film_init_content(pf, title, name, year);
            }
            else
                rc = ERR_RANGE;
        }
        else
            rc = ERR_IO;
    }

    free(title);
    free(name);

    return rc;
}

int film_print(FILE *f, film_t *pf)
{
    fprintf(f, "%s\n%s\n%d\n", pf->title, pf->name, pf->year);
    return ERR_OK;
}


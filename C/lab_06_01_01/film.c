#include "film.h"

int film_cmp_by_title(const film_t *l, const film_t *r)
{
    film_t *film_1 = (film_t *)l;
    film_t *film_2 = (film_t *)r;
    int rc = strcmp(film_1->title, film_2->title);
    if (rc > 0)
        return 1;
    else if (rc == 0)
        return 0;
    else
        return -1;
}

int film_cmp_by_name(const film_t *l, const film_t *r)
{
    film_t *film_1 = (film_t *)l;
    film_t *film_2 = (film_t *)r;
    int rc = strcmp(film_1->name, film_2->name);
    if (rc > 0)
        return 1;
    else if (rc == 0)
        return 0;
    else
        return -1;
}

int film_cmp_by_year(const film_t *l, const film_t *r)
{
    film_t *film_1 = (film_t *)l;
    film_t *film_2 = (film_t *)r;
    if (film_1->year > film_2->year)
        return 1;
    else if (film_1->year == film_2->year)
        return 0;
    else
        return -1;
}


int film_read(FILE *f, film_t *pf)
{
    char buf_title[TITLE_LEN + 2]; // Буфер для предварительного чтения и проверки названия
    size_t buf_title_len;

    char buf_name[NAME_LEN + 2]; // Буфер для предварительного чтения и проверки фамилии
    size_t buf_name_len;

    char tmp[2]; // для чтение символа перехода на новую строку
    int year; // Год выпуска
    
    // Чтение названия фильма
    if (fgets(buf_title, sizeof(buf_title), f) == NULL)
        return ERR_IO;
   
    buf_title_len = strlen(buf_title);
    if (buf_title[buf_title_len - 1] == '\n')
    {
        buf_title[buf_title_len - 1] = '\0';
        buf_title_len--;
    }
    if (!buf_title_len || buf_title_len > TITLE_LEN)
    {
        return ERR_RANGE;
    }

    // Чтение автора фильма
    if (fgets(buf_name, sizeof(buf_name), f) == NULL)
        return ERR_IO;
   
    buf_name_len = strlen(buf_name);
    if (buf_name[buf_name_len - 1] == '\n')
    {
        buf_name[buf_name_len - 1] = '\0';
        buf_name_len--;
    }
    if (!buf_name_len || buf_name_len > NAME_LEN)
    {
        return ERR_RANGE;
    }


    // Чтение года выпуска фильма
    if (fscanf(f, "%d", &year) != 1)
        return ERR_IO;

    if (year <= 0)
        return ERR_RANGE;

    // Чтение \n после fscan
    fgets(tmp, sizeof(tmp), f);

    // Копирование в структуру
    strcpy(pf->title, buf_title);
    strcpy(pf->name, buf_name);
    pf->year = year;

    return ERR_OK;
}

int film_print(FILE *f, film_t *pf)
{
    fprintf(f, "%s\n%s\n%d\n", pf->title, pf->name, pf->year);
    return ERR_OK;
}


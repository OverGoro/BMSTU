#include "student_array.h"
#include "student.h"

int sa_input(FILE *f, student_t **arr_beg, student_t **arr_end, prompt_t prompt)
{
    // Определение количества структур в файле
    size_t temp_n = 0;
    student_t s;
    
    while (student_input(f, &s, prompt) == ERR_OK)
    {
        temp_n++;
    }
    
    if (!feof(f))
        return ERR_IO;
    if (!temp_n)
        return ERR_EMPTY_ARR;
    
    // Выделение памяти под массив структур
    if (*arr_beg != NULL)
        free(*arr_beg);

    *arr_beg = (student_t *)malloc(sizeof(student_t) * temp_n);
    if (*arr_beg == NULL)
        return ERR_MEMORY;
    *arr_end = *arr_beg + temp_n;

    // Ввод структур в массив
    fseek(f, SEEK_SET, 0);
    size_t cur_n = 0;
    for (student_t *pcur = *arr_beg; pcur < *arr_end; pcur++)
    {
        student_input(f, pcur, prompt);
        pcur->n = cur_n;
        cur_n++;
    }
    return ERR_OK;
}

int sa_append(student_t **arr_beg, student_t **arr_end, student_t *s)
{
    size_t new_size = sizeof(student_t) * (*arr_end - *arr_beg + 1);
    student_t *pbuf = NULL;
   
    if (*arr_beg != NULL)
        pbuf = realloc(*arr_beg, new_size);
    else
        pbuf = malloc(new_size);

    if (pbuf == NULL)
        return ERR_MEMORY;
    *arr_beg = pbuf;
    *arr_end = pbuf + new_size / sizeof(student_t);
    s->n = new_size / sizeof(student_t) - 1;
    *(*arr_end - 1) = *s;
    return ERR_OK;
}

int sa_keyboard_append(student_t **arr_beg, student_t **arr_end)
{
    student_t s;
    int rc =  student_input(stdin, &s, normal_prompt);

    if (rc != ERR_OK)
        return rc;
    sa_append(arr_beg, arr_end, &s);
    return ERR_OK;
}

int sa_delete(student_t **arr_beg, student_t **arr_end, size_t i)
{
    // Ошибка если исходный массив не инициализирован
    if (*arr_beg == NULL)
        return ERR_EMPTY_ARR;
    // Ошибка если массив пуст
    if (*arr_beg == *arr_end)
        return ERR_EMPTY_ARR;

    // Количество элементов в исходном массиве
    size_t n = *arr_end - *arr_beg;
    if (i >= n)
        return ERR_RANGE;

    // Если количество элементов = 1, то приравнять указатели конца и начала
    if (n == 1)
    {
        *arr_end = *arr_beg;
        return ERR_OK;
    }

    student_t last_student = *(*arr_end - 1); // Последний элемент в исходном массива


    // Выделение памяти под измененный массив
    student_t *ptemp_beg = realloc(*arr_beg, sizeof(student_t) * (*arr_end - *arr_beg));
    if (ptemp_beg == NULL)
        return ERR_MEMORY;

    // Указатель на конец нового массива
    student_t *ptemp_end = ptemp_beg + (n - 1);

    // Сдвиг элементов влево
    size_t cur_n = i;
    for (student_t *pcur = ptemp_beg + i; pcur < ptemp_end; pcur++)
    {
        if (pcur < ptemp_end)
            *pcur = *(pcur + 1);
        else
            *pcur = last_student;

        pcur->n = cur_n;
        cur_n++;
    }
    
    // Запись в исходный массив
    *arr_beg = ptemp_beg;
    *arr_end = ptemp_end;
    return ERR_OK;

}

void sa_output(FILE *f, const student_t *arr_beg, const student_t *arr_end, bool is_table)
{
    if (is_table)
    {
        char *s = TABLE_TITLE;
        printf("%s", s);
    }
    for (const student_t *pcur = arr_beg; pcur < arr_end; pcur++)
        student_print(f, pcur, is_table);
    fprintf(f, "\n");
}

int sa_copy(const student_t *arr_beg, const student_t *arr_end,
            student_t **tmp_beg, student_t **tmp_end)
{
    student_t *pbuf = NULL;
    size_t new_size = arr_end - arr_beg;

    if (*tmp_beg != NULL)
        pbuf = realloc(*tmp_beg, new_size * sizeof(student_t));
    else
        pbuf = malloc(new_size * sizeof(student_t));
    
    if (pbuf == NULL)
        return ERR_MEMORY;

    *tmp_beg = pbuf;
    *tmp_end = pbuf + new_size;

    const student_t *pcur_a =  arr_beg;
    for (student_t *pcur = *tmp_beg; pcur < *tmp_end; pcur++)
    {
        *pcur = *pcur_a;
        pcur_a++;
    }

    return ERR_OK;
}


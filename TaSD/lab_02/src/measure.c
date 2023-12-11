#include "measure.h"
#include "error.h"
#include "student_array.h"
#include "student_keys.h"
#include "student_sort.h"
#include <stdio.h>

int generate_random_marks_arr(student_t **arr_beg, student_t **arr_end, size_t n)
{
    // Выделение памяти под массив структур
    if (*arr_beg != NULL)
        free(*arr_beg);

    *arr_beg = (student_t *)calloc(sizeof(student_t), n);
    if (*arr_beg == NULL)
        return ERR_MEMORY;
    *arr_end = *arr_beg + n;

    for (student_t *pcur = *arr_beg; pcur < *arr_end; pcur++)
    {
        pcur->average_mark = (double)(rand() % 400 + 100) / 100;
    }
    return ERR_OK;
}

int take_measure(const student_t *arr_beg, const student_t *arr_end,
                 measure_t *qsort_table_res, measure_t *bsort_table_res,
                 measure_t *qsort_key_res, measure_t *bsort_key_res)
{
    student_t *tmp_beg = NULL, *tmp_end = NULL;
    student_key_t *k_tmp_beg = NULL, *k_tmp_end = NULL;
    int rc;
    struct timeval start, end;

    qsort_table_res->n = arr_end - arr_beg;
    qsort_table_res->time = 0;
    qsort_table_res->memory = 0;

    bsort_table_res->n = arr_end - arr_beg;
    bsort_table_res->time = 0;
    bsort_table_res->memory = 0;

    qsort_key_res->n = arr_end - arr_beg;
    qsort_key_res->time = 0;
    qsort_key_res->memory = 0;

    bsort_key_res->n = arr_end - arr_beg;
    bsort_key_res->time = 0;
    bsort_key_res->memory = 0;
    
    for (size_t i = 0; i < 10; i++)
    {
        rc = sa_copy(arr_beg, arr_end, &tmp_beg, &tmp_end);
        if (rc != ERR_OK)
            return rc;
        
        rc = ka_create(&k_tmp_beg, &k_tmp_end, arr_beg, arr_end);
        if (rc != ERR_OK)
        {
            free(tmp_beg);
            return rc;
        }
        gettimeofday(&start, NULL);
        sa_quicksort(tmp_beg, tmp_end - tmp_beg, sizeof(student_t), cmp_mark);
        gettimeofday(&end, NULL);

        double start_double = (double)start.tv_sec + (double)start.tv_usec / 1000000;
        double end_double = (double)end.tv_sec + (double)end.tv_usec / 1000000;
        
        qsort_table_res->n = (tmp_end - tmp_beg);
        qsort_table_res->memory = sizeof(student_t) * (tmp_end - tmp_beg);
        qsort_table_res->time += (end_double - start_double) / 10;

        rc = sa_copy(arr_beg, arr_end, &tmp_beg, &tmp_end);
        if (rc != ERR_OK)
            return rc;

        rc = ka_create(&k_tmp_beg, &k_tmp_end, arr_beg, arr_end);
        if (rc != ERR_OK)
        {
            free(tmp_beg);
            return rc;
        }
        gettimeofday(&start, NULL);
        sa_bubble_sort(tmp_beg, tmp_end - tmp_beg, sizeof(student_t), cmp_mark);
        gettimeofday(&end, NULL);

        start_double = (double)start.tv_sec + (double)start.tv_usec / 1000000;
        end_double = (double)end.tv_sec + (double)end.tv_usec / 1000000;
        
        bsort_table_res->n = (tmp_end - tmp_beg);
        bsort_table_res->memory = sizeof(student_t) * (tmp_end - tmp_beg);
        bsort_table_res->time += (end_double - start_double) / 10;

        rc = sa_copy(arr_beg, arr_end, &tmp_beg, &tmp_end);
        if (rc != ERR_OK)
            return rc;
        rc = ka_create(&k_tmp_beg, &k_tmp_end, arr_beg, arr_end);
        if (rc != ERR_OK)
        {
            free(tmp_beg);
            return rc;
        }
        gettimeofday(&start, NULL);
        sa_bubble_sort(k_tmp_beg, k_tmp_end - k_tmp_beg, sizeof(student_key_t), ka_cmp_marks);
        gettimeofday(&end, NULL); 

        start_double = (double)start.tv_sec + (double)start.tv_usec / 1000000;
        end_double = (double)end.tv_sec + (double)end.tv_usec / 1000000;
        
        bsort_key_res->n = (tmp_end - tmp_beg);
        bsort_key_res->memory = (sizeof(student_t) + sizeof(student_key_t)) * (tmp_end - tmp_beg);
        bsort_key_res->time += (end_double - start_double) / 10;


        rc = sa_copy(arr_beg, arr_end, &tmp_beg, &tmp_end);
        if (rc != ERR_OK)
            return rc;
        rc = ka_create(&k_tmp_beg, &k_tmp_end, arr_beg, arr_end);
        if (rc != ERR_OK)
        {
            free(tmp_beg);
            return rc;
        }
        gettimeofday(&start, NULL);
        sa_quicksort(k_tmp_beg, k_tmp_end - k_tmp_beg, sizeof(student_key_t), ka_cmp_marks);
        gettimeofday(&end, NULL); 

        start_double = (double)start.tv_sec + (double)start.tv_usec / 1000000;
        end_double = (double)end.tv_sec + (double)end.tv_usec / 1000000;
        
        qsort_key_res->n = (tmp_end - tmp_beg);
        qsort_key_res->memory = (sizeof(student_t) + sizeof(student_key_t)) * (tmp_end - tmp_beg);
        qsort_key_res->time += (end_double - start_double) / 10;
    }

    if (tmp_beg != NULL)
        free(tmp_beg);
    if (k_tmp_beg != NULL)
        free(k_tmp_beg);

    return ERR_OK;
}

int conduct_experiment(size_t start_n, size_t end_n, size_t step_n)
{
    (void)start_n;
    (void)end_n;
    (void)step_n;
    FILE *q_t_f = fopen("quick_table.txt", "w");
    FILE *b_t_f = fopen("bubble_table.txt", "w");
    FILE *q_k_f = fopen("quick_key.txt", "w");
    FILE *b_k_f = fopen("bubble_key.txt", "w");

    size_t n = 42;
    student_t *arr_beg = NULL, *arr_end = NULL;
    int rc = generate_random_marks_arr(&arr_beg, &arr_end, n);
    if (rc)
        return rc;
    measure_t q_t, b_t, q_k, b_k;
    rc = take_measure(arr_beg, arr_end, &q_t, &b_t, &q_k, &b_k);
    if (rc)
        return rc;
    printf(" sort: n time(s) memory(bytes)\n");
    printf("qsort  table: ");
    print_measure(stdout,  &q_t);
    printf("bubble table: ");
    print_measure(stdout,  &b_t);
    printf("qsort keys: ");
    print_measure(stdout,  &q_k);
    printf("bubble keys: ");
    print_measure(stdout,  &b_k);
    
    for (size_t i = start_n; i <= end_n; i += step_n)
    {
        printf("Замер :%lu\n", i);
        srand(0);
        student_t *arr_beg = NULL, *arr_end = NULL;
        int rc = generate_random_marks_arr(&arr_beg, &arr_end, i);
        if (rc)
            return rc;
        measure_t q_t, b_t, q_k, b_k;
        rc = take_measure(arr_beg, arr_end, &q_t, &b_t, &q_k, &b_k);
        if (rc)
            return rc;
        print_measure(q_t_f,  &q_t);
        print_measure(b_t_f,  &b_t);
        print_measure(q_k_f,  &q_k);
        print_measure(b_k_f,  &b_k);
    }
    if (q_t_f != NULL)
        fclose(q_t_f);
    if (b_t_f != NULL)
        fclose(b_t_f);
    if (q_k_f != NULL)
        fclose(q_k_f);
    if (b_k_f != NULL)
        fclose(b_k_f);
    return ERR_OK;
}

void print_measure(FILE *f, measure_t *m)
{
    fprintf(f, "%lu %lf %lu\n", m->n, m->time, m->memory);
}


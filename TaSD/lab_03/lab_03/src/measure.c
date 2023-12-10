#include "measure.h"
// #include "vec_io.h"
// #include "sparse_matrix_io.h"
// #include "matrix_io.h"
#include <stdio.h>

#define START_N 500
#define DELTA_N 5
#define START_PERCENT 0
#define DELTA_PERCENT 1
#define END_PERCENT 50
#define TESTS_NUM 10

int measure_get(size_t m, size_t n, size_t fill_percent, measure_t *measure)
{
    struct timeval start, end;

    int **nor_vec_1 = NULL, **nor_mat_1 = NULL, **nor_mat_r = NULL;
    size_t nor_n = 0, nor_m = 0;

    vector_t vec_r = {NULL, NULL, 0, 0};
    sparse_t mat_1 = {0, 0, 0, NULL, NULL, NULL};
    vector_t vec_1 = {NULL, NULL, 0, 0};

    int rc = vector_generate(&nor_vec_1, &vec_1, m, fill_percent);
    if (!rc)
        rc = matrix_generate(&nor_mat_1, &mat_1, m, n, fill_percent);

    measure->normal_size = sizeof(nor_vec_1) + sizeof(int) * m;
    measure->normal_size += sizeof(nor_mat_1) + sizeof(int) * m * n;

    measure->sparse_size = sizeof(vec_1) + sizeof(mat_1);
    measure->sparse_size += sizeof(size_t) * vec_1.el_num;
    measure->sparse_size += sizeof(int) * vec_1.el_num;
    measure->sparse_size += sizeof(ssize_t) * mat_1.m;
    measure->sparse_size += sizeof(size_t) * mat_1.el_num;
    measure->sparse_size += sizeof(int) * mat_1.el_num;

    if (!rc)
    {
        // Замер умножения разреженных матриц
        gettimeofday(&start, NULL);
        rc = sm_multiply(&vec_1, &mat_1, &vec_r);
        gettimeofday(&end, NULL);

        double start_double = (double)start.tv_sec + (double)start.tv_usec / 1000000;
        double end_double = (double)end.tv_sec + (double)end.tv_usec / 1000000; 
        measure->sparse_time = end_double - start_double;
    }
    if (!rc)
    {
        // Замер умножения обычных матриц
        gettimeofday(&start, NULL);
        rc = matrix_multiply(nor_vec_1, 1, m, 
                        nor_mat_1, n, m, 
                        &nor_mat_r, &nor_n, &nor_m);
        gettimeofday(&end, NULL);

        double start_double = (double)start.tv_sec + (double)start.tv_usec / 1000000;
        double end_double = (double)end.tv_sec + (double)end.tv_usec / 1000000;

        measure->normal_time = end_double - start_double;
    }

    measure->fill_percent = fill_percent;

    sm_free_content(&mat_1);

    v_free_content(&vec_1);
    v_free_content(&vec_r);

    matrix_free(nor_vec_1);
    matrix_free(nor_mat_1);
    matrix_free(nor_mat_r);

    return rc;
}

void measure_print(FILE *f, measure_t *measure)
{
    fprintf(f, "Sparse: %lu x %lu | %lf %lu%% | %lu Bytes | rse: %lf%%\n", measure->m, measure->n, measure->sparse_time, measure->fill_percent, measure->sparse_size, measure->sparse_rse);
    fprintf(f, "Normal: %lu x %lu | %lf %lu%% | %lu Bytes | rse: %lf%%\n", measure->m, measure->n, measure->normal_time, measure->fill_percent, measure->normal_size, measure->normal_rse);
}

void measure_graph_print(FILE *f_sparse, FILE *f_normal, measure_t *measure)
{
    fprintf(f_sparse, "%lu %lf %lu\n", measure->fill_percent, measure->sparse_time, measure->sparse_size);
    fprintf(f_normal, "%lu %lf %lu\n", measure->fill_percent, measure->normal_time, measure->normal_size);
}

int make_measure(FILE *f_out, FILE *f_normal, FILE *f_sparse)
{
    size_t i = START_N;
    for (size_t fill_percent = START_PERCENT; fill_percent <= END_PERCENT; fill_percent += DELTA_PERCENT)
    {
        measure_t av_m = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL}; // Результат замера
        av_m.m = i;
        av_m.n = i;

        // Выделение памяти под результаты замеров
        av_m.sparse_measures = (double *)malloc(sizeof(double));
        if (av_m.sparse_measures == NULL)
            return ERR_MEM;

        av_m.normal_measures = (double *)malloc(sizeof(double));
        if (av_m.normal_measures == NULL)
        {
            free(av_m.sparse_measures);
            return ERR_MEM;
        }

        av_m.normal_rse = 100;
        av_m.sparse_rse = 100;

        while (av_m.sparse_rse > 5 || av_m.normal_rse > 5)
        {
            // Увеличение количества замеров
            av_m.sparse_repeats += TESTS_NUM;
            av_m.normal_repeats += TESTS_NUM;

            // Выделение новой памяти для замеров
            double *pbuf_measure = realloc(av_m.sparse_measures, (av_m.sparse_repeats + 1) * sizeof(double));
            if (pbuf_measure == NULL)
            {
                free(av_m.sparse_measures);
                free(av_m.normal_measures);
                return ERR_MEM;
            }
            else 
            {
                av_m.sparse_measures = pbuf_measure;
            }

            pbuf_measure = realloc(av_m.normal_measures, (av_m.normal_repeats + 1) * sizeof(double) + 1);
            if (pbuf_measure == NULL)
            {
                free(av_m.sparse_measures);
                free(av_m.normal_measures);
                return ERR_MEM;
            }
            else 
            {
                av_m.normal_measures = pbuf_measure;
            }

            // Проведение замеров
            for (size_t j = 0; j < TESTS_NUM; j++)
            {
                int rc = measure_get(i, i, fill_percent, &av_m);
                if (rc)
                    return rc;
                av_m.normal_measures[av_m.sparse_repeats - TESTS_NUM + j] = av_m.normal_time;
                av_m.sparse_measures[av_m.normal_repeats - TESTS_NUM + j] = av_m.sparse_time;
            }
            av_m.sparse_rse = get_rce(av_m.sparse_measures, av_m.sparse_repeats);
            av_m.normal_rse = get_rce(av_m.normal_measures, av_m.normal_repeats);
        }
        // После достижения нужного rse происходит запись результата
        av_m.sparse_time = get_average_time(av_m.sparse_measures, av_m.sparse_measures + av_m.sparse_repeats);
        av_m.normal_time = get_average_time(av_m.normal_measures, av_m.normal_measures + av_m.normal_repeats);
        measure_print(f_out, &av_m);
        measure_graph_print(f_sparse, f_normal, &av_m);
        free(av_m.sparse_measures);
        free(av_m.normal_measures);
    }
    return ERR_OK;
}

double get_average_time(const double *pbeg, const double *pend)
{
    double average = 0;
    size_t n = pend - pbeg;
    for (const double *pcur = pbeg; pcur < pend; pcur++)
        average += *pcur / n;
    return average;
}
double get_rce(const double *arr, size_t n)
{
    double average = 0;
    for (size_t i = 0; i < n; i++)
        average += arr[i] / n;
    
    double s = 0;
    for (size_t i = 0; i < n; i++)
    {
        s += (arr[i] - average) * (arr[i] - average);
    }
    s /= (n - 1);
    s = sqrt(s);

    double std_err = s / sqrt(n);
    double rse = std_err / average * 100;
    return rse;
}


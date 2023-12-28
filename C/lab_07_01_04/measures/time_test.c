#include "time_test.h"

void set_sorted_el(int *prev_e, int *cur_e)
{
    *cur_e = *prev_e + 1;
}
void set_reversed_el(int *prev_e, int *cur_e)
{
    *cur_e = *prev_e - 1;
}
void set_random_el(int *cur_e, int *temp)
{
    (void)temp;
    *cur_e = rand();
}
void set_equal_el(int *prev_e, int *cur_e)
{
    *cur_e = *prev_e;
}

int measure_get(const void *pdata, size_t n, size_t e_size, cmp_t cmp, measure_t *measure)
{
    struct timeval start, end;
    int *pres = malloc(e_size * n);

    if (pres == NULL)
        return ERR_MEMORY;

    // Замер mysort
    memcpy(pres, pdata, e_size * n);

    gettimeofday(&start, NULL);
    mysort(pres, n, e_size, cmp);
    gettimeofday(&end, NULL);

    double start_double = (double)start.tv_sec + (double)start.tv_usec / 1000000;
    double end_double = (double)end.tv_sec + (double)end.tv_usec / 1000000;
    
    measure->mysort_time = end_double - start_double;

    // Замер qsort
    memcpy(pres, pdata, e_size * n);

    gettimeofday(&start, NULL);
    qsort(pres, n, e_size, cmp);
    gettimeofday(&end, NULL);

    start_double = (double)start.tv_sec + (double)start.tv_usec / 1000000;
    end_double = (double)end.tv_sec + (double)end.tv_usec / 1000000;

    measure->qsort_time = end_double - start_double;

    if (pres != NULL)
        free(pres);

    return ERR_OK;
}

void measure_print(FILE *f_m, FILE *f_q, const measure_t *measure, size_t n)
{
    fprintf(f_m, "%lu %lf\n", n, measure->mysort_time);
    fprintf(f_q, "%lu %lf\n", n, measure->qsort_time);
}

int fill_arr(int **pbeg, int **pend, size_t n, set_el_t set_el)
{
    if (n == 0)
        return ERR_EMPTY_ARR;
    *pbeg = (int *)malloc(n * sizeof(int));

    if (pbeg == NULL)
        return ERR_MEMORY;

    *pend = *pbeg + n;
    **pbeg = 0;
    for (int *pcur = *pbeg + 1; pcur < *pend; pcur++)
    {
        set_el(pcur - 1, pcur);
    }
    return ERR_OK;
}

int fill_arr_random(int **pbeg, int **pend, size_t n)
{
    srand(0);
    if (n == 0)
        return ERR_EMPTY_ARR;
    *pbeg = (int *)malloc(n * sizeof(int));

    if (pbeg == NULL)
        return ERR_MEMORY;

    *pend = *pbeg + n;
    for (int *pcur = *pbeg; pcur < *pend; pcur++)
    {
        *pcur = rand();
    }
    return ERR_OK;
}

int make_measure(const char *in_file_name, const char *out_file_name, set_el_t set_el_func)
{
    FILE *f_out_q = fopen(in_file_name, "w");
    if (f_out_q == NULL)
        return ERR_FILE;

    FILE *f_out_m = fopen(out_file_name, "w");
    if (f_out_m == NULL)
    {
        fclose(f_out_q);
        return ERR_FILE;
    }
        
    for (size_t i = START_N; i < END_N; i += DELTA_N)
    {
        // Создание массива для сортировки
        int *pbeg, *pend;
        fill_arr(&pbeg, &pend, i, set_el_func);

        measure_t m; // Результат замера
        
        measure_t av_m; // Средний результат

        // Выделение памяти под результаты замеров
        double *mysort_measures = (double *)malloc(sizeof(double));
        if (mysort_measures == NULL)
            return ERR_MEMORY;

        double *qsort_measures = (double *)malloc(sizeof(double));
        if (qsort_measures == NULL)
            return ERR_MEMORY;

        double rse_mysort = 100; // Ошибка среднего для mysort
        double rse_qsort = 100;  // Ошибка среднего для qsort

        size_t measures_n = 0;   // Количество замеров

     
        while (rse_mysort > 5 || rse_qsort > 5)
        {
            // Увеличение количества замеров
            measures_n += TESTS_NUM;

            // Выделение новой памяти для замеров
            double *pbuf_mysort = realloc(mysort_measures, (measures_n + 1) * sizeof(double));
            if (pbuf_mysort == NULL)
            {
                free(mysort_measures);
                free(qsort_measures);
                free(pbeg);
                return ERR_MEMORY;
            }
            else 
            {
                mysort_measures = pbuf_mysort;
            }

            double *pbuf_qsort = realloc(qsort_measures, (measures_n + 1) * sizeof(double) + 1);
            if (pbuf_qsort == NULL)
            {
                free(mysort_measures);
                free(qsort_measures);
                free(pbeg);
                return ERR_MEMORY;
            }
            else 
            {
                qsort_measures = pbuf_qsort;
            }


            // Проведение замеров
            for (size_t j = 0; j < TESTS_NUM; j++)
            {
                measure_get(pbeg, pend - pbeg, sizeof(int), cmp_int, &m);
                qsort_measures[measures_n - TESTS_NUM + j] = m.qsort_time;
                mysort_measures[measures_n - TESTS_NUM + j] = m.mysort_time;
            }
            rse_mysort = get_rce(mysort_measures, measures_n);
            rse_qsort = get_rce(qsort_measures, measures_n);
        }
        av_m.qsort_repeats = measures_n;
        av_m.mysort_repeats = measures_n;
        
        // После достижения нужного rse происходит запись результата
        av_m.mysort_time = get_average_time(mysort_measures, mysort_measures + measures_n);
        av_m.qsort_time = get_average_time(qsort_measures, qsort_measures + measures_n);
        measure_print(f_out_m, f_out_q, &av_m, i);
        printf("%lu: rse mysort: %lf, rse qsort: %lf, repeats: %lu\n", i, rse_mysort, rse_qsort, av_m.qsort_repeats);
        free(mysort_measures);
        free(qsort_measures);
        free(pbeg);
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


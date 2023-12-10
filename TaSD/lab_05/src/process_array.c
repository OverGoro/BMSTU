#include "process_array.h"
#include "process_limits.h"
#include "queue_array.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

double randfrom_arr(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

process_array_t *process_array_init(void)
{
    process_array_t *p = calloc(1, sizeof(process_array_t));
    if (p != NULL)
    {
        p->q_1 = queue_array_create();
        p->q_2 = queue_array_create();
    }
    return p;
}

int process_array_add_type_1(process_array_t *process, double *interval_add)
{
    object_t *o = calloc(1, sizeof(object_t));
    if (o == NULL)
        return ERR_MEM;
    o->adding_time = randfrom_arr(Q1_MIN_ADD_TIME, Q1_MAX_ADD_TIME);
    o->processing_time = randfrom_arr(Q1_MIN_PROC_TIME, Q1_MAX_PROC_TIME);
    (*interval_add) += o->adding_time;

    int rc = ERR_OK;
    if (!rc)
    {
        rc = queue_array_push(process->q_1, o);
        free(o);
    }
    if (!rc)
    {
        process->added_num_1++;
        process->used_addresses_1 = addres_list_plus(process->used_addresses_1, &process->q_1->arr[process->q_1->tail]);
    }
    if (rc)
    {
        free(o);
    }
    return rc;
}

int process_array_add_type_2(process_array_t *process, double *interval_add)
{
    object_t *o = calloc(1, sizeof(object_t));
    if (o == NULL)
        return ERR_MEM;
    o->adding_time = randfrom_arr(Q2_MIN_ADD_TIME, Q2_MAX_ADD_TIME);
    o->processing_time = randfrom_arr(Q2_MIN_PROC_TIME, Q2_MAX_PROC_TIME);
    (*interval_add) += o->adding_time;

    int rc = ERR_OK;
    if (!rc)
    {
        rc = queue_array_push(process->q_2, o);
    }
    if (!rc)
    {
        process->added_num_2++;
        process->used_addresses_2 = addres_list_plus(process->used_addresses_2, &process->q_2->arr[process->q_2->tail]);
    }
    if (rc)
    {
        free(o);
    }
    return rc;
}

int process_array_add_random(process_array_t *process, double *interval_add)
{
    int num = 1 + rand() % 2;
    int rc = ERR_OK;
    if (num == 1)
        rc = process_array_add_type_1(process, interval_add);
    else
        rc = process_array_add_type_2(process, interval_add);
    return rc;
}

int process_array_request_1(process_array_t *pr, double *next_process_time)
{
    object_t o;
    int rc = queue_array_pop(pr->q_1, &o);
    if (!rc)
    {
        (*next_process_time) += o.processing_time;
        pr->processed_num_1++;
        pr->processed_time_1 += o.processing_time;
        pr->summ_process_time += o.processing_time;
    }
    return rc;
}

int process_array_request_2(process_array_t *pr, double *next_process_time)
{
    object_t o;
    int rc = queue_array_pop(pr->q_2, &o);
    if (!rc)
    {
        (*next_process_time) += o.processing_time;
        pr->processed_num_2++;
        pr->processed_time_2 += o.processing_time;
        pr->summ_process_time += o.processing_time;
    }
    return rc;
}

int process_array_request(process_array_t *pr, double *next_process_time, double next_add_time)
{
    int rc = ERR_OK;
    if (queue_array_is_empty(pr->q_1) && queue_array_is_empty(pr->q_2))
    {
        pr->break_time += next_add_time - *next_process_time;
        *next_process_time = next_add_time;
    }
    else if (pr->last_processed_type == 1)
    {
        if (!queue_array_is_empty(pr->q_1))
            rc = process_array_request_1(pr, next_process_time);
        else if (!queue_array_is_empty(pr->q_2))
        {
            rc = process_array_request_2(pr, next_process_time);
            pr->last_processed_type = 2;
        }
    }
    else if (pr->last_processed_type == 2)
    {
        if (!queue_array_is_empty(pr->q_2))
            rc = process_array_request_2(pr, next_process_time);
        else if (!queue_array_is_empty(pr->q_1))
        {
            rc = process_array_request_1(pr, next_process_time);
            pr->last_processed_type = 1;
        }
    }
    else if (pr->last_processed_type == 0)
    {
        if (!queue_array_is_empty(pr->q_1) && !queue_array_is_empty(pr->q_2))
        {
            double pt_1 = pr->q_1->arr[pr->q_1->head].processing_time;
            double pt_2 = pr->q_1->arr[pr->q_1->head].processing_time;
            if (pt_1 <= pt_2)
            {
                rc = process_array_request_1(pr, next_process_time);
                pr->last_processed_type = 1;
            }
            else 
            {
                rc = process_array_request_2(pr, next_process_time);
                pr->last_processed_type = 2;
            }
        }
        else if (!queue_array_is_empty(pr->q_1))
        {
            rc = process_array_request_1(pr, next_process_time);
            pr->last_processed_type = 1;
        }
        else if (!queue_array_is_empty(pr->q_2))
        {
            rc = process_array_request_2(pr, next_process_time);
            pr->last_processed_type = 2;
        }
    }
    return rc;
}

static void get_mode(double end_add_time_1, double end_add_time_2, double end_process_time, 
              bool *add_1_mode, bool *add_2_mode, bool *process_mode)
{
    double closest_time = fmin(end_add_time_1, fmin(end_add_time_2, end_process_time));
    *add_1_mode = end_add_time_1 == closest_time ? true : false;
    *add_2_mode = end_add_time_2 == closest_time ? true : false;
    *process_mode = end_process_time == closest_time ? true : false;
}

static void process_get_expected(process_array_t *pr)
{
    if (Q1_AV_ADD_TIME > Q1_AV_PROC_TIME)
        pr->expected_time = Q1_AV_ADD_TIME * pr->processed_num_1;
    else 
        pr->expected_time = Q1_AV_PROC_TIME * pr->processed_num_1;
}

int process_array_simulate(process_array_t *pr)
{
    srand(time(NULL));
    double end_add_time_1 = 0; // Время окончания добавления тек. эл. в 1 очередь
    double end_add_time_2 = 0; // Время окончания добавления тек. эл. в 2 очередь
    double end_process_time = 0; // Время окончания обработки тек. эл.
    
    bool add_1_mode, add_2_mode, process_mode;
    size_t print_num = 100; // Интервал вывода
    int rc = ERR_OK;
    while (rc == ERR_OK && pr->processed_num_1 < 1000)
    {
        get_mode(end_add_time_1, end_add_time_2, end_process_time, 
                 &add_1_mode, &add_2_mode, &process_mode);

        if (add_1_mode) process_array_add_type_1(pr, &end_add_time_1);
        if (add_2_mode) process_array_add_type_2(pr, &end_add_time_2);

        double closest_add_time = fmin(end_add_time_1, end_add_time_2);
        if (process_mode) process_array_request(pr, &end_process_time, closest_add_time);
        if (pr->processed_num_1 == print_num)
        {
            pr->elapsed_time = end_process_time; 
            process_get_expected(pr);
            print_num += 100;
            process_array_info(stdout, pr, object_print);
        }
    }
    return rc;
}

void process_array_info(FILE *f, process_array_t *pr, void printer(FILE *f, const void *item))
{
    fprintf(f, "\033[35mСОСТОЯНИЕ ОБРАБОТКИ\033[0m\n");
    fprintf(f, "\033[93mqueue type 1:\033[0m\n");
    queue_array_print(f, pr->q_1, printer);
    fprintf(f, "\033[93mqueue type 2:\033[0m\n");
    queue_array_print(f, pr->q_2, printer);
    fprintf(f, "\033[93mКол-во обработанных заявок 1 типа:\033[0m %lu\n", pr->processed_num_1);
    fprintf(f, "\033[93mКол-во обработанных заявок 2 типа:\033[0m %lu\n", pr->processed_num_2);
    fprintf(f, "\033[93mВремя обработки заявок 1 типа:\033[0m %lf\n", pr->processed_time_1);
    fprintf(f, "\033[93mВремя обработки заявок 2 типа:\033[0m %lf\n", pr->processed_time_2);
    fprintf(f, "\033[93mВремя простоя:\033[0m %lf\n", pr->break_time);
    fprintf(f, "\033[93mВремя работы аппарата:\033[0m %lf\n", pr->summ_process_time);
    fprintf(f, "\033[93mППРОШЕДШЕЕ ВРЕМЯ:\033[0m %lf, отклонение: %lf%%\n", 
            pr->elapsed_time, 
            (pr->summ_process_time / pr->expected_time - 1) * 100);
    fprintf(f, "\033[93mОжидаемое ПРОШЕДШЕЕ ВРЕМЯ: \033[0m %lf\n", pr->expected_time);
    fprintf(f, "\033[93mТип последней обработанной заявки:\033[0m %d\n", pr->last_processed_type);

    address_list_print(f, pr->used_addresses_1);
    if (address_list_check_frag(pr->used_addresses_1, sizeof(object_t)))
        printf("\033[35mФрагментация была\n\033[0m");
    else
        printf("\033[35mФрагментации не было\n\033[0m");
    address_list_print(f, pr->used_addresses_2);
    if (address_list_check_frag(pr->used_addresses_2, sizeof(object_t)))
        printf("\033[35mФрагментация была\n\033[0m");
    else
        printf("\033[35mФрагментации не было\n\033[0m");
}


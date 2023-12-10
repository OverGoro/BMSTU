#include "../inc/process.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

process_t *process_init(void)
{
    process_t *p = calloc(1, sizeof(process_t));
    return p;
}

int process_add_type_1(process_t *process, double *interval_add)
{
    object_t *o = calloc(1, sizeof(object_t));
    if (o == NULL)
        return ERR_MEM;
    o->adding_time = randfrom(Q1_MIN_ADD_TIME, Q1_MAX_ADD_TIME);
    o->processing_time = randfrom(Q1_MIN_PROC_TIME, Q1_MAX_PROC_TIME);
    (*interval_add) += o->adding_time;

    queue_list_node_t *n = queue_list_node_create(o);
    int rc = ERR_OK;
    if (n == NULL)
        rc = ERR_MEM;
    if (!rc)
    {
        process->q_1 = queue_list_push(process->q_1, n);
        process->added_num_1++;
        process->used_addresses_1 = addres_list_plus(process->used_addresses_1, (void *)n);
    }
    if (rc)
    {
        free(o);
        free(n);
    }
    return rc;
}

int process_add_type_2(process_t *process, double *interval_add)
{
    object_t *o = calloc(1, sizeof(object_t));
    if (o == NULL)
        return ERR_MEM;
    o->adding_time = randfrom(Q2_MIN_ADD_TIME, Q2_MAX_ADD_TIME);
    o->processing_time = randfrom(Q2_MIN_PROC_TIME, Q2_MAX_PROC_TIME);
    (*interval_add) += o->adding_time;
    
    queue_list_node_t *n = queue_list_node_create(o);
    int rc = ERR_OK;
    if (n == NULL)
        rc = ERR_MEM;
    if (!rc)
    {
        process->q_2 = queue_list_push(process->q_2, n);
        process->added_num_2++;
        process->used_addresses_2 = addres_list_plus(process->used_addresses_2, (void *)n);
    }
    if (rc)
    {
        free(o);
        free(n);
    }
    return rc;
}

void process_request_1(process_t *pr, double *next_process_time)
{
    object_t *o = queue_list_pop(&(pr->q_1));
    (*next_process_time) += o->processing_time;
    pr->processed_num_1++;
    pr->processed_time_1 += o->processing_time;
    pr->summ_process_time += o->processing_time;
    free(o);
}

void process_request_2(process_t *pr, double *next_process_time)
{
    object_t *o = queue_list_pop(&(pr->q_2));
    (*next_process_time) += o->processing_time;
    pr->processed_num_2++;
    pr->processed_time_2 += o->processing_time;
    pr->summ_process_time += o->processing_time;
    free(o);
}

void process_request(process_t *pr, double *next_process_time, double closest_add_time)
{
    if (pr->q_1 == NULL && pr->q_2 == NULL)
    {
        pr->break_time += closest_add_time - *next_process_time;
        *next_process_time = closest_add_time;
    }
    else if (pr->last_processed_type == 1)
    {
        if (pr->q_1 != NULL)
            process_request_1(pr, next_process_time);
        else if (pr->q_2 != NULL)
        {
            process_request_2(pr, next_process_time);
            pr->last_processed_type = 2;
        }
    }
    else if (pr->last_processed_type == 2)
    {
        if (pr->q_2 != NULL)
            process_request_2(pr, next_process_time);
        else if (pr->q_1 != NULL)
        {
            process_request_1(pr, next_process_time);
            pr->last_processed_type = 1;
        }
    }
    else if (pr->last_processed_type == 0)
    {
        if (pr->q_1 != NULL && pr->q_2 != NULL)
        {
            if (((object_t *)pr->q_1->data)->processing_time <= ((object_t *)pr->q_2->data)->processing_time)
            {
                process_request_1(pr, next_process_time);
                pr->last_processed_type = 1;
            }
            else 
            {
                process_request_2(pr, next_process_time);
                pr->last_processed_type = 2;
            }
        }
        else if (pr->q_1 != NULL)
        {
            process_request_1(pr, next_process_time);
            pr->last_processed_type = 1;
        }
        else if (pr->q_2 != NULL)
        {
            process_request_2(pr, next_process_time);
            pr->last_processed_type = 2;
        }
    }
}

static void get_mode(double end_add_time_1, double end_add_time_2, double end_process_time, 
              bool *add_1_mode, bool *add_2_mode, bool *process_mode)
{
    double closest_time = fmin(end_add_time_1, fmin(end_add_time_2, end_process_time));
    *add_1_mode = end_add_time_1 == closest_time ? true : false;
    *add_2_mode = end_add_time_2 == closest_time ? true : false;
    *process_mode = end_process_time == closest_time ? true : false;
}

static void process_get_expected(process_t *pr)
{
    if (Q1_AV_ADD_TIME > Q1_AV_PROC_TIME)
        pr->expected_time = Q1_AV_ADD_TIME * pr->processed_num_1;
    else 
        pr->expected_time = Q1_AV_PROC_TIME * pr->processed_num_1;
}

int process_simulate(process_t *pr)
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

        if (add_1_mode) process_add_type_1(pr, &end_add_time_1);
        if (add_2_mode) process_add_type_2(pr, &end_add_time_2);

        double closest_add_time = fmin(end_add_time_1, end_add_time_2);
        if (process_mode) process_request(pr, &end_process_time, closest_add_time);
        if (pr->processed_num_1 == print_num)
        {
            pr->elapsed_time = end_process_time;
            process_get_expected(pr);
            print_num += 100;
            process_info(stdout, pr, object_print);
        }
    }
    return rc;
}

void process_info(FILE *f, process_t *pr, void printer(FILE *f, const void *item))
{
    fprintf(f, "\033[35mСОСТОЯНИЕ ОБРАБОТКИ\033[0m\n");
    fprintf(f, "\033[93mqueue type 1:\033[0m\n");
    queue_list_print(f, pr->q_1, printer);
    fprintf(f, "\033[93mqueue type 2:\033[0m\n");
    queue_list_print(f, pr->q_2, printer);
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
    if (address_list_check_frag(pr->used_addresses_1, sizeof(queue_list_node_t)))
        printf("\033[35mФрагментация была\n\033[0m");
    else
        printf("\033[35mФрагментации не было\n\033[0m");
    address_list_print(f, pr->used_addresses_2);
    if (address_list_check_frag(pr->used_addresses_2, sizeof(queue_list_node_t)))
        printf("\033[35mФрагментация была\n\033[0m");
    else
        printf("\033[35mФрагментации не было\n\033[0m");
}


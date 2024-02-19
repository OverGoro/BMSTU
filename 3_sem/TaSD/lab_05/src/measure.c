#include "measure.h"
#include "object.h"
#include <stdlib.h>

#define START_N 100
#define END_N 1500

// Функция для замера времени
double get_time(void) 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

// Функция для замера памяти
size_t get_list_memory_usage(queue_list_node_t *queue) 
{
    size_t used_memory = 0;
    used_memory += sizeof(*queue);
    size_t n = 0;
    queue_list_node_t *pcur = queue;
    while (pcur != NULL)
    {
        n++;
        pcur = pcur->next;
    }
    used_memory += (n + 1) * sizeof(queue_list_node_t);
    return used_memory;
}
size_t get_static_memory_usage(queue_array_t *queue)
{
    size_t used_memory = 0;
    used_memory += sizeof(*queue);
    return used_memory;
}


// Функция работы с стеком
// Заполнение стека
void process_push_static(queue_array_t *queue, size_t size) 
{
    for (size_t i = 0; i < size; i++)
    {
        object_t item = {0,0};
        queue_array_push(queue, &item);
    }
}

void process_push_list(queue_list_node_t **queue, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        object_t *item = calloc(1, i);
        queue_list_node_t *n = queue_list_node_create(item);
        *queue = queue_list_push(*queue, n);
    }
}
// Чтение стека
void process_pop_static(queue_array_t *queue, size_t size) 
{
    object_t el;
    for (size_t i = 0; i < size; i++)
        queue_array_pop(queue, &el);
}
void process_pop_list(queue_list_node_t **queue, size_t size)
{
    for (size_t i = 0; i < size; i++)
        queue_list_pop(queue);
}


int measure(void) 
{
    FILE* time_file_push = fopen("measures/push_time_results.txt", "w");
    FILE* memory_file_push = fopen("measures/push_memory_results.txt", "w");
    FILE* time_file_pop = fopen("measures/pop_time_results.txt", "w");

    if (time_file_push == NULL || memory_file_push == NULL || time_file_pop == NULL) 
    {
        fclose(time_file_push);
        fclose(time_file_pop);
        fclose(memory_file_push);
        return ERR_FILE;
    }

    // Замер
    for (int i = START_N; i <= END_N; i += 100) 
    {
        printf("measuring %d elemnts\n", i);
        queue_array_t *s_queue = queue_array_create();
        queue_list_node_t *l_queue = NULL;


        double mean_time_push_static = 0;
        double mean_time_push_list = 0;
        double mean_time_pop_static = 0;
        double mean_time_pop_list = 0;
        size_t mean_memory_push_static = 0;
        size_t mean_memory_push_list = 0;
        size_t num_measurements = 1000;

        for (size_t j = 0; j < num_measurements; j++) 
        {
            // Замер push на массиве
            double start_time_push_static = get_time();
            process_push_static(s_queue, i);
            double end_time_push_static = get_time();

            double elapsed_time_push_static = end_time_push_static - start_time_push_static;
            mean_memory_push_static = get_static_memory_usage(s_queue);

            // Замер push на списке
            double start_time_push_list = get_time();
            process_push_list(&l_queue, i);
            double end_time_push_list = get_time();

            double elapsed_time_push_list = end_time_push_list - start_time_push_list;
            mean_memory_push_list = get_list_memory_usage(l_queue);

            // Замер pop на массиве
            double start_time_pop_static = get_time();
            process_pop_static(s_queue, i);
            double end_time_pop_static = get_time();

            double elapsed_time_pop_static = end_time_pop_static - start_time_pop_static;

            // Замер pop на списке
            double start_time_pop_list = get_time();
            process_pop_list(&l_queue, i);
            double end_time_pop_list = get_time();

            double elapsed_time_pop_list = end_time_pop_list - start_time_pop_list;


            // Вычисляем среднее значение и RSE
            mean_time_push_static += elapsed_time_push_static / num_measurements;
            mean_time_push_list += elapsed_time_push_list / num_measurements;
            mean_time_pop_static += elapsed_time_pop_static / num_measurements;
            mean_time_pop_list += elapsed_time_pop_list / num_measurements;

        }
        // Запись результатов в файлы
        fprintf(time_file_push, "%d %lf %lf\n", i, mean_time_push_list, mean_time_push_static);
        fprintf(memory_file_push, "%d %lu %lu\n", i, mean_memory_push_list, mean_memory_push_static);
        fprintf(time_file_pop, "%d %lf %lf\n", i, mean_time_pop_list, mean_time_pop_static);

        // Освобождение памяти
        queue_array_destroy(s_queue);
        queue_list_free(&l_queue);
    }

    // Закрытие файлов
    fclose(time_file_push);
    fclose(memory_file_push);
    fclose(time_file_pop);

    system("gnuplot graph.gpi");

    return ERR_OK;
}

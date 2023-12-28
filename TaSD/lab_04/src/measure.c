#include "measure.h"

#define START_N 500
#define END_N 10000

// Функция для замера времени
double get_time(void) 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

// Функция для замера памяти
size_t get_list_memory_usage(list_stack_t *stack) 
{
    size_t used_memory = 0;
    used_memory += sizeof(*stack);
    used_memory += (stack->top->node_num + 1) * sizeof(list_stack_node_t);
    return used_memory;
}
size_t get_static_memory_usage(static_stack_t *stack)
{
    size_t used_memory = 0;
    used_memory += sizeof(*stack);
    return used_memory;
}


// Функция работы с стеком
// Заполнение стека
void process_push_static(static_stack_t *stack, size_t size) 
{
    for (size_t i = 0; i < size; i++)
        ss_push(stack, NULL);
}

void process_push_list(list_stack_t *stack, size_t size)
{
    for (size_t i = 0; i < size; i++)
        ls_push(stack, NULL);
}
// Чтение стека
void process_pop_static(static_stack_t *stack, size_t size) 
{
    void *el;
    for (size_t i = 0; i < size; i++)
        ss_pop(stack, &el);
}
void process_pop_list(list_stack_t *stack, size_t size)
{
    void *el;
    for (size_t i = 0; i < size; i++)
        ls_pop(stack, &el);
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
    for (int i = START_N; i <= END_N; i += 500) 
    {
        printf("measuring %d elemnts\n", i);
        static_stack_t s_stack;
        list_stack_t l_stack;

        ss_init_stack(&s_stack);
        ls_init_stack(&l_stack, i);

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
            process_push_static(&s_stack, i);
            double end_time_push_static = get_time();

            double elapsed_time_push_static = end_time_push_static - start_time_push_static;
            mean_memory_push_static = get_static_memory_usage(&s_stack);

            // Замер push на списке
            double start_time_push_list = get_time();
            process_push_list(&l_stack, i);
            double end_time_push_list = get_time();

            double elapsed_time_push_list = end_time_push_list - start_time_push_list;
            mean_memory_push_list = get_list_memory_usage(&l_stack);

            // Замер pop на массиве
            double start_time_pop_static = get_time();
            process_pop_static(&s_stack, i);
            double end_time_pop_static = get_time();

            double elapsed_time_pop_static = end_time_pop_static - start_time_pop_static;

            // Замер pop на списке
            double start_time_pop_list = get_time();
            process_pop_list(&l_stack, i);
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
        ls_free(&l_stack);
        ss_clear(&s_stack);
    }

    // Закрытие файлов
    fclose(time_file_push);
    fclose(memory_file_push);
    fclose(time_file_pop);

    return ERR_OK;
}

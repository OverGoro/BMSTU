#ifndef PROCESS_ARRAY_H__
#define PROCESS_ARRAY_H__

#include "object.h"
#include "queue_array.h"
#include "address_list.h"
#include "process_limits.h"

// Симуляция очереди - статического массива
typedef struct
{
    queue_array_t *q_1;       // Очередь заявок 1 типа
    queue_array_t *q_2;       // Очередь заявок 2 типа
    size_t added_num_1;       // Количество добавленных заявок 1 типа
    size_t added_num_2;       // Количество добавленных заявок 2 типа
    size_t processed_num_1;   // Количество обработанных заявок 1 типа
    size_t processed_num_2;   // Количество обработанных заявок 2 типа
    double processed_time_1;  // Время обработки заявок 1 типа
    double processed_time_2;  // Время обработки заявок 2 типа
    double break_time;        // Время простоя
    double summ_process_time; // Время работы обрабатывающего аппарата без простоя
    double elapsed_time;      // Время, прошедшее с момента поступления первого элемента
    double expected_time;     // Расчетное время работы аппарата
    int last_processed_type;  // Тип последней обработанной заявки
    address_node_t *used_addresses_1; // Использованные адреса 1 очереди
    address_node_t *used_addresses_2; // Использованные адреса 2 очереди
} process_array_t;

/**
* @brief Создание нового процесса
*
* @return Адрес процесса
*/
process_array_t *process_array_init(void);

int process_array_simulate(process_array_t *pr);

void process_array_info(FILE *f, process_array_t *pr, void printer(FILE *f, const void *item));

#endif // !PROCESS_H__

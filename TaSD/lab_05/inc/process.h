#ifndef PROCESS_LIST_H__
#define PROCESS_LIST_H__

#include "address_list.h"
#include "object.h"
#include "queue_list.h"
#include "process_limits.h"

// Симулияция очереди - списка
typedef struct
{
    queue_list_node_t *q_1;   // Очередь заявок 1 типа
    queue_list_node_t *q_2;   // Очередь заявок 2 типа
    size_t added_num_1;       // Количество добавленных заявок 1 типа
    size_t added_num_2;       // Количество добавленных заявок 2 типа
    size_t processed_num_1;   // Количество обработанных заявок 1 типа
    size_t processed_num_2;   // Количество обработанных заявок 2 типа
    double processed_time_1;  // Время обработки заявок 1 типа
    double processed_time_2;  // Время обработки заявок 2 типа
    double break_time;        // Время простоя
    double summ_process_time; // Время работы обрабатывающего аппарата без простоя
    double elapsed_time;      // Время, прошедшее с момента поступленяи первого элемнта
    double expected_time;     // Расчетное время работы аппарата
    int last_processed_type;  // Тип последней обработанной заявки
    address_node_t *used_addresses_1; // Использованные адреса 1 очереди
    address_node_t *used_addresses_2; // Использованные адреса 2 очереди
} process_t;

/**
* @brief Создание нового процесса
*
* @return Адрес процесса
*/
process_t *process_init(void);

int process_simulate(process_t *pr);


void process_info(FILE *f, process_t *pr, void printer(FILE *f, const void *item));

#endif // !PROCESS_H__

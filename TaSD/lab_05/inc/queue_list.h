#ifndef QUEUE_LIST_H__
#define QUEUE_LIST_H__

#include <stdio.h>
#include "error.h"
#include "queue_list_node.h"
#include <stdio.h>

/**
* @brief Добавление узла в конец очереди
*
* @param head[in] Голова очереди
* @param pqueue_list_node[in] Узел
*
* @return Новая голова очереди
*/
queue_list_node_t *queue_list_push(queue_list_node_t *head, queue_list_node_t *pqueue_list_node);

/**
* @brief Вывод очереди в файловый поток 
*
* @param f[in, out] Файловый поток
* @param head[in] Голова очереди
* @param printer[in] Функция вывода элемента
*/
void queue_list_print(FILE *f, queue_list_node_t *head, void printer(FILE *f, const void *data));

/**
* @brief Получение данных и удаление головы очереди
*
* Очередь должен быть не пустой
*
* @param head[in, out] Голова очереди
*
* @return Данные
*/
void* queue_list_pop(queue_list_node_t **head);


/**
* @brief Освобождение памяти под очередь
*
* @param head[in] голова очереди
*/
void queue_list_free(queue_list_node_t **head);

#endif // !queue_list_H__


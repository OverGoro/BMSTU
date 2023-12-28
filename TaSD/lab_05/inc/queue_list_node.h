#ifndef QUEUE_LIST_NODE_H__
#define QUEUE_LIST_NODE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct queue_list_node queue_list_node_t;

// Узел очереди - списка
struct queue_list_node
{
    void *data; // Данные
    queue_list_node_t *next; // Следующий узел
};

/**
* @brief Инициализация узала
*
* @param data[in] Значение узла
*
* @return Указатель на выделенную под узнл память
*/
queue_list_node_t *queue_list_node_create(void *data);


/**
* @brief Освобождение выделенной под узел памяти
*
* @param queue_list_node[in] Узел
*/
void queue_list_node_free(queue_list_node_t *queue_list_node);


/**
* @brief Вывод узла в файловый поток
*
* @param f[in] Файловый поток
* @param pqueue_list_node[in] Узел
* @param printer[in] Функция вывода содержимого узла
*/
void queue_list_node_print(FILE *f, const queue_list_node_t *node, void (*printer)(FILE *f, const void *));

#endif // !QUEUE_LIST_NODE_H__


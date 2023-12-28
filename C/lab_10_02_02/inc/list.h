#ifndef LIST_H__
#define LIST_H__

#include <stdio.h>
#include "error.h"
#include "node.h"

/**
* @brief Добавление узла в конец списка
*
* @param head[in] Голова списка
* @param pnode[in] Узел
*
* @return Новая голова списка
*/
node_t *list_add_tail(node_t *head, node_t *pnode);

/**
* @brief Вывод списка в файловый поток 
*
* @param f[in, out] Файловый поток
* @param head[in] Голова списка
*/
void list_print(FILE *f, node_t *head);

/**
* @brief Получение данных и удаление головы списка
*
* Список должен быть не пустой
*
* @param head[in, out] Голова списка
*
* @return Данные
*/
int pop_front(node_t **head);

/**
* @brief Получение данных и удаление конца списка
*
* Список должен быть не пустой
*
* @param head[in, out] Голова списка
*
* @return Данные
*/
int pop_back(node_t **head);


/**
* @brief Освобождение памяти под список
*
* @param head[in] голова списка
*/
void list_free(node_t **head);

#endif // !LIST_H__

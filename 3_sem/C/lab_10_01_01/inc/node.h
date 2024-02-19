#ifndef NODE_H__
#define NODE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

/**
* @brief Инициализация узала
*
* @param data[in] Значение узла
*
* @return Указатель на выделенную под узнл память
*/
node_t *node_create(void *data);


/**
* @brief Освобождение выделенной под узел памяти
*
* @param node[in] Узел
*/
void node_free(node_t *node);


/**
* @brief Вывод узла в файловый поток
*
* @param f[in] Файловый поток
* @param pnode[in] Узел
* @param printer(FILE *, const void *)[in] Функция вывода элементов
*   FILE * - файловый поток для вывода
*   const void * - Объект для вывода
*/
void node_print(FILE *f, const node_t *pnode, void (*printer)(FILE *, const void *));

#endif // !NODE_H__

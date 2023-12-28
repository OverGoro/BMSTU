#ifndef NODE_H__
#define NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node address_node_t;

struct node
{
    void *adr;    // Адрес
    size_t used;  // Количество использований
    address_node_t *next; // Следующий узел
};

int address_node_cmp(const void *p1, const void *p2);

/**
* @brief Инициализация узала
*
* @param data[in] Значение узла
*
* @return Указатель на выделенную под узнл память
*/
address_node_t *node_create(void *data);


/**
* @brief Освобождение выделенной под узел памяти
*
* @param node[in] Узел
*/
void address_node_free(address_node_t *node);


/**
* @brief Вывод узла в файловый поток
*
* @param f[in] Файловый поток
* @param pnode[in] Узел
*/
void address_node_print(FILE *f, const void *pnode);

#endif // !NODE_H__

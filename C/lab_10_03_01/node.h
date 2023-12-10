#ifndef NODE_H__
#define NODE_H__
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
struct node_type
{
    int item;
    const char *key;
    struct node_type *next;
};

typedef struct node_type *node_t;

/**
* @brief Создание узла ассоциативного массива на списке
*
* @param item[in] Значение
* @param key[in] Ключ
*
* @return Указатель на узел
*/
node_t assoc_node_create(int item, const char *key);

/**
* @brief Очищает содержимое узла
*
* @param n[in, out] Узел
*/
void assoc_node_free_content(node_t *n);
/**
* @brief Удаление узла
*
* @param node[in, out] Узел
*/
void assoc_node_free(node_t *n);

#endif // !node_T__

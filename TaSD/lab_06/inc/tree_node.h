#ifndef TREE_NODE_H__
#define TREE_NODE_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "error.h"

// Узел дерева
typedef struct tree_type
{
    char *name;  // Имя файла
    time_t date; // Дата изменения
    struct tree_type *left;  // Левый потомок
    struct tree_type *right; // Правый потомок
} tree_t;


/**
* @brief Сравненеие узлов дерева по имени файла
*
* @param l[in] Певрый узел
* @param r[in] Второй узел
*
* @return Результат сравнения 
*/
int tree_node_cmp_name(void *l, void *r);

/**
* @brief Сравненеие узлов дерева по дате изменения 
*
* @param l[in] Певрый узел
* @param r[in] Второй узел
*
* @return Результат сравнения 
*/
int tree_node_cmp_date(void *l, void *r);

/**
* @brief Создание узла дерева
*
* @param date[in] Дата последнего изменения
* @param name[in] Имя файла
*
* @return Указатель на область памяти или NULL
*/
tree_t *tree_node_create(time_t date, char *name);

/**
* @brief Создание копии узла дерева
*
* @param node[in] Узел
*
* @return Копия узла
*/
tree_t *tree_node_copy(const tree_t *node);

/**
* @brief Уничтожение узла дерева
*
* @param tree[in, out] Узел дерева
*/
void tree_node_destroy(tree_t **tree);

/**
* @brief Очищаяет содержимое узла дерева
*
* @param tree[in, out] Узел дерева
*/
void tree_node_clear(tree_t *tree);

/**
* @brief Вывод потомков узла по имени и дате в файл формата DOT
*
* @param node[in] Узел
* @param f[in, out] Файловый поток
*/
void tree_node_print_children(tree_t *node, void *file_arg);
void tree_node_print_simple(tree_t *node, void *file_arg);

/**
* @brief Вывод потомков узла по имени в файл формата DOT
*
* @param node[in] Узел
* @param f[in, out] Файловый поток
*/
void tree_node_print_children_name(tree_t *node, void *file_arg);

/**
* @brief Вывод потомков узла по дате в файл формата DOT
*
* @param node[in] Узел
* @param f[in, out] Файловый поток
*/
void tree_node_print_children_date(tree_t *node, void *file_arg);

/**
* @brief Ввод полей узла из потока ввода
*
* @param f_in[in, out] Поток ввода
* @param f_out[in, out] Поток вывода
* @param node[in, out] Узел дерева
*
* @return Код ошибки
*/
int tree_node_read(FILE *f_in, FILE *f_out, tree_t *node);

#endif // !TREE_NODE_H__

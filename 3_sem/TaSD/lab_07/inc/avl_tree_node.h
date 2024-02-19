#ifndef AVL_TREE_NODE_H__
#define AVL_TREE_NODE_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "error.h"

// Узел дерева
typedef struct avl_tree_type
{
    char *name;  // Слово
    char *manual; // Описание
    struct avl_tree_type *left;  // Левый потомок
    struct avl_tree_type *right; // Правый потомок
    int height; // Высота узла
} avl_tree_t;


/**
* @brief Сравненеие узлов дерева по имени файла
*
* @param l[in] Певрый узел
* @param r[in] Второй узел
*
* @return Результат сравнения 
*/
int avl_tree_node_cmp_name(void *l, void *r);

/**
* @brief Сравненеие узлов дерева по дате изменения 
*
* @param l[in] Певрый узел
* @param r[in] Второй узел
*
* @return Результат сравнения 
*/
int avl_tree_node_cmp_manual(void *l, void *r);

/**
* @brief Создание узла дерева
*
* @param name[in] Слово
* @param manual[in] Описание
*
* @return Указатель на область памяти или NULL
*/
avl_tree_t *avl_tree_node_create(char *name, char *manual);

/**
* @brief Создание копии узла дерева
*
* @param node[in] Узел
*
* @return Копия узла
*/
avl_tree_t *avl_tree_node_copy(const avl_tree_t *node);

/**
* @brief Уничтожение узла дерева
*
* @param avl_tree[in, out] Узел дерева
*/
void avl_tree_node_destroy(avl_tree_t **avl_tree);

/**
* @brief Очищаяет содержимое узла дерева
*
* @param avl_tree[in, out] Узел дерева
*/
void avl_tree_node_clear(avl_tree_t *avl_tree);

/**
* @brief Вывод потомков узла по имени и дате в файл формата DOT
*
* @param node[in] Узел
* @param f[in, out] Файловый поток
*/
void avl_tree_node_print_children(avl_tree_t *node, void *file_arg);

void avl_tree_node_print_simple(avl_tree_t *node, void *file_arg);

/**
* @brief Вывод потомков узла по имени в файл формата DOT
*
* @param node[in] Узел
* @param f[in, out] Файловый поток
*/
void avl_tree_node_print_children_name(avl_tree_t *node, void *file_arg);

/**
* @brief Вывод потомков узла по дате в файл формата DOT
*
* @param node[in] Узел
* @param f[in, out] Файловый поток
*/
void avl_tree_node_print_children_manual(avl_tree_t *node, void *file_arg);

/**
* @brief Ввод полей узла из потока ввода
*
* @param f_in[in, out] Поток ввода
* @param f_out[in, out] Поток вывода
* @param node[in, out] Узел дерева
*
* @return Код ошибки
*/
int avl_tree_node_read(FILE *f_in, FILE *f_out, avl_tree_t *node);

#endif // !avl_tree_NODE_H__

#ifndef graph_NODE_H__
#define graph_NODE_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "error.h"

// Узел графа
typedef struct graph_type
{
    size_t id;                       // Идентификатор
    struct graph_type **connections; // Связанные узлы
    int *weights;                    // Стоимости связей
    size_t n;                        // Количество связей
    bool visited;                    // Посещен
} graph_t;

/**
* @brief Создание узла графа
*
* @param id[in] Идентификатор
*
* @return Указатель на область памяти или NULL
*/
graph_t *graph_node_create(size_t id);

/**
* @brief Уничтожение узла графа
*
* @param graph[in, out] Узел графа
*/
void graph_node_destroy(graph_t **graph);

/**
* @brief Очищаяет содержимое узла дерева
*
* @param graph[in, out] Узел дерева
*/
void graph_node_clear(graph_t *graph);

/**
* @brief Вывод информации об узле в формате DOT
*
* @param f[in, out] Файловый поток
* @param node[in] Узел
*/
void graph_node_print(FILE *f, graph_t *node);

/**
* @brief Ввод полей узла из потока ввода
*
* @param f_in[in, out] Поток ввода
* @param f_out[in, out] Поток вывода
* @param node[in, out] Узел дерева
*
* @return Код ошибки
*/
int graph_node_read(FILE *f_in, FILE *f_out, graph_t *node);

/**
* @brief Добавление связи
*
* @param node[in, out] Узел
* @param connected_node[in] Связанный узел
* @param weight[in] Вес связи
*
* @return Код ошибки
*/
int graph_node_add_connction(graph_t *node, graph_t *connected_node, int weight);

#endif // !graph_NODE_H__

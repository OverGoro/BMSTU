#ifndef GRAPH_H__
#define GRAPH_H__

#include "graph_node.h"

/**
* @brief Добавляет узел в граф
*
* @param graph_nodes Массив узлов
* @param n Количество узлов
* @param node Узел
*
* @return Код ошибки
*/
int graph_add(graph_t ***graph_nodes, size_t *n, graph_t *node);

/**
* @brief Уничтожает граф
*
* @param graph_nodes Массив узлов
* @param n количество узлов
*/
void graph_destroy(graph_t ***graph_nodes, size_t *n);

void graph_set_visit(graph_t **graph, size_t n, bool visit);

graph_t *graph_arr_get_by_id(graph_t **graph, size_t n, size_t id);

/**
* @brief Создает граф по вводу из файлового потока
*
* @param f_in[in, out] Входной файловый поток
* @param graph_nodes[out] Массив прочитанных узлов
* @param n[out] Количество прочитанных узлов
*
* @return Код ошибки
*/
int graph_read(FILE *f_in, graph_t ***graph_nodes, size_t *n);

/**
* @brief Получает доступные узлы
*
* @param graph_nodes Массив узлов
* @param n Количество узлов в массиве
* @param max_weight Максимальный путь
*
* @return Код ошибки
*/
int graph_get_avialable(graph_t *start_node, graph_t ***available_nodes, size_t *n, int max_weight);

int graph_draw(const char *file_name, graph_t **graph_nodes, size_t n);

int graph_print(FILE *f, graph_t **graph_nodes, size_t n);

#endif // !GRAPH_H__

#include "../inc/graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int graph_add(graph_t ***graph_nodes, size_t *n, graph_t *node)
{
    int rc = ERR_OK;
    graph_t **tmp = NULL;
    if (*graph_nodes == NULL)
        tmp = malloc(sizeof(graph_t *));
    else 
        tmp = realloc(*graph_nodes, sizeof(graph_t *) * (*n + 1));
    if (tmp == NULL)
        rc = ERR_MEM;
    if (!rc)
    {
        *graph_nodes = tmp;
        (*n)++;
        (*graph_nodes)[*n - 1] = node;
    }
    return rc;
}

void graph_destroy(graph_t ***graph_nodes, size_t *n)
{
    for (size_t i = 0; i < *n; i++)
        graph_node_destroy((&((*graph_nodes)[i])));
    free(*graph_nodes);
    *n = 0;
}

void graph_set_visit(graph_t **graph, size_t n, bool visit)
{
    for (size_t i = 0; i < n; i++)
    {
        graph[i]->visited = visit;
    }
}

graph_t *graph_arr_get_by_id(graph_t **graph, size_t n, size_t id)
{
    for (size_t i = 0; i < n;i++)
        if (graph[i]->id == id) return graph[i];
    return NULL;
}

int graph_add_connection(graph_t **graph_nodes, size_t n, size_t id_1, size_t id_2, int weight)
{
    graph_t *n_1 = graph_arr_get_by_id(graph_nodes, n, id_1);
    graph_t *n_2 = graph_arr_get_by_id(graph_nodes, n, id_2);
    if (n_1 == NULL || n_2 == NULL)
        return ERR_RANGE;
    return graph_node_add_connction(n_1, n_2, weight);
}

int graph_read(FILE *f_in, graph_t ***graph_nodes, size_t *n)
{
    int rc = ERR_OK;
    size_t tmp_n = 0;

    if (fscanf(f_in, "%lu", &tmp_n) != 1)
        rc = ERR_IO;

    graph_t **tmp = malloc(sizeof(graph_t *) * tmp_n);
    if (tmp == NULL)
        rc = ERR_IO;
    for (size_t i = 0; i < tmp_n; i++)
    {
        tmp[i] = graph_node_create(i);
    }
    size_t id_1, id_2;
    int weight;

    while (rc == ERR_OK && fscanf(f_in, "%lu%lu%d", &id_1, &id_2, &weight) == 3)
    {
        rc = graph_add_connection(tmp, tmp_n, id_1, id_2, weight);
        if (!rc) rc = graph_add_connection(tmp, tmp_n, id_2, id_1, weight);
    }
    if (rc == ERR_IO && feof(f_in))
        rc = ERR_OK;
    if (!rc)
    {
        *graph_nodes = tmp;
        *n = tmp_n;
    }
    else 
    {
        graph_destroy(&tmp, &tmp_n);
    }
    return rc;
}

int graph_get_avialable(graph_t *start_node, graph_t ***available_nodes, size_t *n, int max_weight)
{
    start_node->visited = true;
    int rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && i < start_node->n; i++)
    {
        if (start_node->weights[i] <= max_weight && start_node->connections[i]->visited == false)
        {
            rc = graph_add(available_nodes, n, start_node->connections[i]);
            if (!rc) rc = graph_get_avialable(start_node->connections[i], available_nodes, n, max_weight - start_node->weights[i]);
        }
    }
    return rc;
}

int graph_draw(const char *file_name, graph_t **graph_nodes, size_t n)
{
    FILE *f = fopen(file_name, "w");
    if (f == NULL)
        return ERR_FILE;

    fprintf(f, "digraph tree {\n");
    for (size_t i = 0; i < n; i++)
        graph_node_print(f, graph_nodes[i]);
    fprintf(f, "}");

    fclose(f);
    size_t command_len = strlen(file_name) * 2 + 29;
    char *command = malloc(command_len);
    if (command == NULL)
        return ERR_MEM;
    else
        command[0] = 0;

    command = strcat(command, "dot -T png -O ");
    if (command == NULL)
        return ERR_MEM;
    command = strcat(command, file_name);
    if (command == NULL)
        return ERR_MEM;
    command = strcat(command, " && open ");
    if (command == NULL)
        return ERR_MEM;
    command = strcat(command, file_name);
    if (command == NULL)
        return ERR_MEM;
    command = strcat(command, ".png");
    system(command);
    free(command);

    return ERR_OK;
}

int graph_print(FILE *f, graph_t **graph_nodes, size_t n)
{
    for (size_t i = 0; i < n; i++)
        fprintf(f, "%lu ", graph_nodes[i]->id);
    fprintf(f, "\n");
    return ERR_OK;
}


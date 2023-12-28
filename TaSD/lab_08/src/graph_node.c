#include <stdlib.h>
#define _GNU_SOURCE
#include "../inc/graph_node.h"

graph_t *graph_node_create(size_t id)
{
    graph_t *node = malloc(sizeof(graph_t));
    int rc = ERR_OK;
    if (node != NULL)
    {
        node->id = id;
        node->connections = NULL;
        node->weights = NULL;
        node->n = 0;
    }
    if (rc)
        graph_node_destroy(&node);
    return node;
}

void graph_node_clear(graph_t *graph)
{
    if (graph != NULL)
    {
        free(graph->connections);
        free(graph->weights);
        graph->connections = NULL;
        graph->weights = NULL;
        graph->n = 0;
    }
}


void graph_node_destroy(graph_t **graph)
{
    if (graph != NULL)
    {
        graph_node_clear(*graph);
        free(*graph);
        *graph = NULL;
    }
}

int graph_node_read(FILE *f_in, FILE *f_out, graph_t *node)
{
    if (node == NULL)
        return ERR_EMPTY_NODE;

    int rc = ERR_OK;

    // Чтение name
    if(f_out != NULL) fprintf(f_out, "Введите id: ");
    if (fscanf(f_in, "%lu", &node->id) != 1)
        rc = ERR_IO;
    
    return rc;
}

int graph_node_add_connction(graph_t *node, graph_t *connected_node, int weight)
{
    if (node == NULL || connected_node == NULL)
        return ERR_EMPTY_NODE;
    int rc = ERR_OK;
    if (node->connections == NULL)
    {
        node->connections = malloc(sizeof(void *));
        if (node->connections == NULL)
            rc = ERR_MEM;
    }
    else 
    {
        void *tmp = realloc(node->connections, sizeof(void *) * (node->n + 1));
        if (tmp == NULL)
            rc = ERR_MEM;
        else
            node->connections = tmp;
    }

    if (rc == ERR_OK && node->weights == NULL)
    {
        node->weights = malloc(sizeof(int));
        if (node->weights == NULL)
            rc = ERR_MEM;
    }
    else if (rc == ERR_OK)
    {
        int *tmp = realloc(node->weights, sizeof(int) * (node->n + 1));
        if (tmp == NULL)
            rc = ERR_MEM;
        else
            node->weights = tmp;
    }
    if (!rc)
    {
        node->n++;
        node->connections[node->n - 1] = connected_node;
        node->weights[node->n - 1] = weight;
    }
    return rc;
}


void graph_node_print(FILE *f, graph_t *node)
{
    for (size_t i = 0; i < node->n; i++)
    {
        fprintf(f, "%lu -> %lu[label=%d];\n", node->id, node->connections[i]->id, node->weights[i]);
    }
}



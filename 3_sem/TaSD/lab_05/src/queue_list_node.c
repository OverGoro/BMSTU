#include "../inc/queue_list_node.h"

queue_list_node_t *queue_list_node_create(void *data)
{
    queue_list_node_t *ptmp;
    ptmp = malloc(sizeof(queue_list_node_t));
    if (ptmp == NULL)
        return NULL;

    ptmp->data = data;
    ptmp->next = NULL;
    return ptmp;
}

void queue_list_node_free(queue_list_node_t *pqueue_list_node)
{
    free(pqueue_list_node);
}

void queue_list_node_print(FILE *f, const queue_list_node_t *node, void (*printer)(FILE *f, const void *))
{
    printer(f, node->data);
}


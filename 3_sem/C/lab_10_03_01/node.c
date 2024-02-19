#include "node.h"

node_t assoc_node_create(int item, const char *key)
{
    node_t n = calloc(1, sizeof(struct node_type));
    if (n != NULL)
    {
        n->item = item;
        char *tmp = strdup(key);
        if (tmp != NULL)
            n->key = tmp;
        else
            assoc_node_free(&n);
    }
    return n;
}

void assoc_node_free_content(node_t *n)
{
    free((void *)(*n)->key);
    (*n)->key = NULL;
}

void assoc_node_free(node_t *n)
{
    assoc_node_free_content(n);
    free(*n);
    *n = NULL;
}

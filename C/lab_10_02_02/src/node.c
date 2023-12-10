#include "node.h"

node_t *node_create(int data)
{
    node_t *ptmp;
    ptmp = malloc(sizeof(node_t));
    if (ptmp == NULL)
        return NULL;

    ptmp->data = data;
    ptmp->next = NULL;
    return ptmp;
}

void node_free(node_t *pnode)
{
    free(pnode);
}

void node_print(FILE *f, const node_t *pnode)
{
    fprintf(f, "%d ", pnode->data);
}

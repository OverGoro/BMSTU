#include "address_node.h"

int address_node_cmp(const void *p1, const void *p2)
{
    if (((address_node_t *)p1)->adr > ((address_node_t *)p2)->adr)
        return 1;
    else if (((address_node_t *)p1)->adr == ((address_node_t *)p2)->adr)
        return 0;
    else
        return -1;
}
address_node_t *node_create(void *data)
{
    address_node_t *ptmp;
    ptmp = malloc(sizeof(address_node_t));
    if (ptmp == NULL)
        return NULL;

    ptmp->adr = data;
    ptmp->used = 1;
    ptmp->next = NULL;
    return ptmp;
}

void address_node_free(address_node_t *pnode)
{
    free(pnode);
}

void address_node_print(FILE *f, const void *pnode)
{
    address_node_t *n = (address_node_t *)pnode;
    if (n->used > 1)
        fprintf(f, "\033[93m%p %lu\033[0m\n", n->adr, n->used);
    else
        fprintf(f, "\033[0m%p %lu\033[0m\n", n->adr, n->used);
}

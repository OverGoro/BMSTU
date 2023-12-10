#include "check_cmp.h"

int cmp_list(node_t *head_1, node_t *head_2)
{
    node_t *pcur_1 = head_1;
    node_t *pcur_2 = head_2;
    int rc = 0;
    while (rc == 0 && pcur_1 != NULL && pcur_2 != NULL)
    {
        if (pcur_1->data != pcur_2->data)
            rc = 1;
        pcur_1 = pcur_1->next;
        pcur_2 = pcur_2->next;
    }
    if (pcur_1 != pcur_2)
        rc = 1;
    return rc;
}

int cmp_addr(const void *l, const void *r)
{
    if (l < r)
        return -1;
    else if (l == r)
        return 0;
    else 
        return 1;
}


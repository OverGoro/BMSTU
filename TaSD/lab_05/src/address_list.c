#include "address_list.h"
#include "address_node.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

address_node_t *address_list_find_node(address_node_t *head, void *adr)
{
    address_node_t *pcur = head;
    while (pcur != NULL && pcur->adr != adr)
        pcur = pcur->next;
    return pcur;
}

address_node_t *addres_list_plus(address_node_t *head, void *adr)
{
    address_node_t *pn = address_list_find_node(head, adr);
    if (pn == NULL)
    {
        pn = node_create(adr);
        head = address_list_add_tail(head, pn);
    }
    else 
    {
        pn->used++;
    }
    return head;
}

address_node_t *address_list_add_tail(address_node_t *head, address_node_t *pnode)
{
    if (head == NULL)
        return pnode;
    address_node_t *pcur = head;
    while (pcur->next != NULL)
        pcur = pcur->next;
    pcur->next = pnode;
    return head;
}

bool address_list_check_frag(address_node_t *head, long element_size)
{
    bool frag = false;
    while (head != NULL && head->next != NULL && !frag)
    {
        if ((char *)head->next->adr - (char *)head->adr != element_size)
            frag = true;
        else
            head = head->next;
    }
    return frag;
}


void address_list_print(FILE *f, address_node_t *head)
{
    address_node_t *pcur = head;
    size_t n = 0;
    while (pcur != NULL)
    {
        n++;
        pcur = pcur->next;
    }
    fprintf(f, "\033[33m Количество различных адресов: %lu\033[0m\n",n);
    pcur = head;
    size_t i = 0;
    while (pcur != NULL && i < 25)
    {
        address_node_print(f, pcur);
        pcur = pcur->next;
        i++;
    }
    if (i == 25 && pcur->next != NULL)
        fprintf(f, "...\n");
}

void front_back_split(address_node_t* head, address_node_t** back)
{
    if (head == NULL || head->next == NULL)
        *back = NULL;
    else 
    {
        address_node_t* slow = head;
        address_node_t* fast = head->next;

        while (fast != NULL) 
        {
            fast = fast->next;
            if (fast != NULL) 
            {
                fast = fast->next;
                slow = slow->next;
            }
        }

        *back = slow->next;
        slow->next = NULL;
    }
}

address_node_t* sorted_merge(address_node_t** head_a, address_node_t** head_b, int (*comparator)(const void*, const void*))
{
    if (*head_a == NULL)
    {
        return *head_b;
    }
    else if (*head_b == NULL)
    {
        return *head_a;
    }

    address_node_t* result = NULL;

    if (comparator((*head_a)->adr, (*head_b)->adr) <= 0)
    {
        result = *head_a;
        result->next = sorted_merge(&(*head_a)->next, head_b, comparator);
    }
    else
    {
        result = *head_b;
        result->next = sorted_merge(head_a, &(*head_b)->next, comparator);
    }

    return result;
}

void address_sort(address_node_t** head, int (*comparator)(const void*, const void*)) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    address_node_t* a;

    front_back_split(*head, &a);

    address_sort(&a, comparator);
    address_sort(head, comparator);

    *head = sorted_merge(&a, head, comparator);
}

void *pop_front(address_node_t **head)
{
    assert(*head);
    void *data = (*head)->adr;
    address_node_t *next = (*head)->next;
    address_node_free(*head);
    *head = next;
    return data;
}

void *pop_back(address_node_t **head)
{
    assert(*head);
    address_node_t *pprev = NULL;
    address_node_t *pcur = *head;
    while (pcur->next != NULL)
    {
        pprev = pcur;
        pcur = pcur->next;
    }
    void *data = pcur->adr;
    address_node_free(pcur);
    if (pprev == NULL)
        *head = NULL;
    else
        pprev->next = NULL;
    return data;
}

void address_list_free(address_node_t **head)
{
    address_node_t *pcur = *head;
    address_node_t *pnext;
    if (pcur != NULL)
        pnext = pcur->next;
    else
        pnext = NULL;
    while (pcur != NULL)
    {
        pnext = pcur->next;
        address_node_free(pcur);
        pcur = pnext;
    }
    *head = NULL;
}


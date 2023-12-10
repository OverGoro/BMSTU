#include "list.h"
#include "node.h"
#include <assert.h>
#include <stdio.h>

node_t *list_add_tail(node_t *head, node_t *pnode)
{
    if (head == NULL)
        return pnode;
    node_t *pcur = head;
    while (pcur->next != NULL)
        pcur = pcur->next;
    pcur->next = pnode;
    return head;
}

void list_print(FILE *f, node_t *head)
{
    node_t *pcur = head;
    while (pcur != NULL)
    {
        node_print(f, pcur);
        pcur = pcur->next;
    }
}


int pop_front(node_t **head)
{
    assert(*head);
    int data = (*head)->data;
    node_t *next = (*head)->next;
    node_free(*head);
    *head = next;
    return data;
}

int pop_back(node_t **head)
{
    assert(*head);
    node_t *pprev = NULL;
    node_t *pcur = *head;
    while (pcur->next != NULL)
    {
        pprev = pcur;
        pcur = pcur->next;
    }
    int data = pcur->data;
    node_free(pcur);
    if (pprev == NULL)
        *head = NULL;
    else
        pprev->next = NULL;
    return data;
}

void list_free(node_t **head)
{
    node_t *pcur = *head;
    node_t *pnext;
    if (pcur != NULL)
        pnext = pcur->next;
    else
        pnext = NULL;
    while (pcur != NULL)
    {
        pnext = pcur->next;
        node_free(pcur);
        pcur = pnext;
    }
    *head = NULL;
}


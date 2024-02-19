#include "../inc/queue_list.h"
#include <stdio.h>
#include <assert.h>

queue_list_node_t *queue_list_push(queue_list_node_t *head, queue_list_node_t *pqueue_list_node)
{
    if (head == NULL)
        return pqueue_list_node;
    queue_list_node_t *pcur = head;
    while (pcur->next != NULL)
        pcur = pcur->next;
    pcur->next = pqueue_list_node;
    return head;
}

void queue_list_print(FILE *f, queue_list_node_t *head, void printer(FILE *f, const void *data))
{
    queue_list_node_t *pcur = head;
    while (pcur != NULL)
    {
        queue_list_node_print(f, pcur, printer);
        pcur = pcur->next;
    }
}

void *queue_list_pop(queue_list_node_t **head)
{
    assert(*head);
    void *data = (*head)->data;
    queue_list_node_t *next = (*head)->next;
    queue_list_node_free(*head);
    *head = next;
    return data;
}

void queue_list_free(queue_list_node_t **head)
{
    queue_list_node_t *pcur = *head;
    queue_list_node_t *pnext;
    if (pcur != NULL)
        pnext = pcur->next;
    else
        pnext = NULL;
    while (pcur != NULL)
    {
        pnext = pcur->next;
        queue_list_node_free(pcur);
        pcur = pnext;
    }
    *head = NULL;
}


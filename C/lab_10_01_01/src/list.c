#include "list.h"
#include "automobile.h"
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

int list_form_by_arr(node_t **head, automobile_t *arr, size_t n)
{
    list_free(head);
    if (n > 0)
    {
        for (size_t i = 0; i < n; i++)
        {
            node_t *pnode = node_create(&arr[i]);
            if (pnode == NULL)
            {
                list_free(head);
                *head = NULL;
            }
            *head = list_add_tail(*head, pnode);
        }
    }
    return ERR_OK;
}
void list_print(FILE *f, node_t *head, void (*printer)(FILE *, const void *))
{
    node_t *pcur = head;
    while (pcur != NULL)
    {
        node_print(f, pcur, printer);
        pcur = pcur->next;
    }
}

void remove_node(node_t **head, node_t *node)
{
    if (*head == NULL)
        return;
    node_t *pprev = NULL;
    node_t *pcur = *head;
    node_t *pnext = (*head)->next;
    while (pcur != NULL && pcur != node)
    {
        pprev = pcur;
        pcur = pcur->next;
    }
    pnext = pcur->next;
    if (pcur != NULL)
    {
        node_free(pcur);
        if (pprev != NULL)
            pprev->next = pnext;
        else
            *head = pnext;
    }
}

void remove_duplicates(node_t **head, int (*comporator)(const void *, const void *))
{
    node_t *pcur = *head;
    while (pcur != NULL)
    {
        node_t *pnext = pcur->next;
        while (pnext != NULL)
        {
            node_t *ptmp = pnext;
            pnext = pnext->next;
            if (comporator(pcur->data, ptmp->data) == 0)
            {
                remove_node(head, ptmp);
            }
        }
        pcur = pcur->next;
    }
}

node_t *reverse(node_t *head)
{
    // Если список пуст
    if (head == NULL)
        return NULL;
    node_t *pprev = NULL; // Предыдущий элемент
    node_t *pcur = head;  // Текущий элемент
    node_t *pnext = head->next; // Следующий элемент
    while (pcur != NULL)
    {
        pnext = pcur->next; 
        // Перестановка местами предыдущего и следющего
        pcur->next = pprev;
        // Текущий стал предыдущим
        pprev = pcur;
        // Следующий стал текущим
        pcur = pnext;
    }
    return pprev;
}

void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL || head->next == NULL)
        *back = NULL;
    else 
    {
        node_t *slow = head;
        node_t *fast = head->next;

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

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    // Список а пуст => записать в res список b
    if (*head_a == NULL)
    {
        node_t *res = *head_b;
        *head_b = NULL;
        return res;
    }
    // Список b пуст => записать в res список a
    else if (*head_b == NULL)
    {
        node_t *res = *head_a;
        *head_a = NULL;
        return res;
    }

    node_t *result = NULL;
    node_t *pr = NULL;

    // Пока хоть один список не пуст
    while (*head_a != NULL || *head_b != NULL)
    {
        if (*head_a != NULL && (*head_b == NULL || comparator((*head_a)->data, (*head_b)->data) <= 0))
        {
            if (result == NULL)
            {
                result = *head_a;
                pr = result;
            }
            else
            {
                pr->next = *head_a;
                pr = pr->next;
            }
            *head_a = (*head_a)->next;
        }
        else if (*head_b != NULL)
        {
            if (result == NULL)
            {
                result = *head_b;
                pr = result;
            }
            else
            {
                pr->next = *head_b;
                pr = pr->next;
            }
            *head_b = (*head_b)->next;
        }
    }

    return result;
}

node_t *sort(node_t *head, int (*comparator)(const void*, const void*)) {
    if (head == NULL || head->next == NULL) 
        return head;

    node_t *a;

    front_back_split(head, &a);

    a = sort(a, comparator);
    head = sort(head, comparator);

    head = sorted_merge(&a, &head, comparator);
    return head;
}

void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;
    void *data = (*head)->data;
    remove_node(head, *head);
    return data;
}

void *pop_back(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;
    node_t *pcur = *head;
    while (pcur->next != NULL)
    {
        pcur = pcur->next;
    }
    void *data = pcur->data;
    remove_node(head, pcur);
    return data;
}

void list_free(node_t **head)
{
    node_t *pcur = *head;
    node_t *pnext;
    if (pcur != NULL)
        pnext = pcur->next;
    while (pcur != NULL)
    {
        pnext = pcur->next;
        node_free(pcur);
        pcur = pnext;
    }
    *head = NULL;
}


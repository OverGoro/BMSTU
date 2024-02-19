#include "queue_array.h"


queue_array_t *queue_array_create(void)
{
    queue_array_t *q = malloc(sizeof(queue_array_t));
    if (q)
    {
        q->head = -1;
        q->tail = -1;
    }
    return q;
}

bool queue_array_is_empty(const queue_array_t *q)    
{
    return (q->tail < 0);
}
bool queue_array_is_full(const queue_array_t *q) 
{
    assert(q);
    return (q->tail + 1 == q->head) || (q->head == 0 && q->tail == QUEUE_ARRAY_EL_NUM - 1);
}
int queue_array_push(queue_array_t *q, object_t *item)
{
    assert(q);
    if (queue_array_is_full(q))
    {
        return ERR_RANGE;
    }
    if (queue_array_is_empty(q))
    {
        q->head = q->tail = 0;
    }
    else 
    {
        if (q->tail == QUEUE_ARRAY_EL_NUM - 1)
            q->tail = 0;
        else
            q->tail += 1;
    }
    q->arr[q->tail] = *item;
    return ERR_OK;
}
int queue_array_pop(queue_array_t *q, object_t *item)
{
    assert(q);
    if (queue_array_is_empty(q))
    {
        return ERR_EMPTY;
    }
    *item = q->arr[q->head];
    if (q->tail == q->head)
    {
    q->tail = -1;
    q->head = -1;
    }
    else 
    {
        if (q->head == QUEUE_ARRAY_EL_NUM - 1)
        q->head = 0;
        else
         q->head +=1;
    }
    return ERR_OK;
}

void queue_array_destroy(queue_array_t *q)
{
    free(q);
}

void queue_array_print(FILE *f, queue_array_t *q, void (*printer)(FILE *, const void *))
{
    queue_array_t *q_1 = queue_array_create();
    while (!queue_array_is_empty(q))
    {
        object_t o;
        queue_array_pop(q, &o);
        queue_array_push(q_1, &o);
    }
    while (!queue_array_is_empty(q_1))
    {
        object_t o;
        queue_array_pop(q_1, &o);
        printer(f, &o);
        queue_array_push(q, &o);
    }
}

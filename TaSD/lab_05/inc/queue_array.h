#ifndef QUEUE_ARRAY_H__
#define QUEUE_ARRAY_H__
#define QUEUE_ARRAY_EL_NUM 1500

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "error.h"
#include "object.h"

// Очередь - статический массив
typedef struct
{
    object_t arr[QUEUE_ARRAY_EL_NUM]; // Массив элмеентов очереди
    int head; // Индекс первого элемента очереди
    int tail; // Индекс последнего элемента очереди
}queue_array_t;

queue_array_t *queue_array_create(void);

void queue_array_destroy(queue_array_t *q);


void queue_array_make_empty(queue_array_t *q);

bool queue_array_is_empty(const queue_array_t *q);

bool queue_array_is_full(const queue_array_t *q);

int queue_array_push(queue_array_t *q, object_t *item);

int queue_array_pop(queue_array_t *q, object_t *item);

void queue_array_print(FILE *f, queue_array_t *q, void printer(FILE *f, const void *item));

#endif // !queue_array_ARRAY_H__

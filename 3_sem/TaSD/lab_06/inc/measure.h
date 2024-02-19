#ifndef MEASURE_H__
#define MEASURE_H__

#include "tree.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

// Замерный эксперимент
typedef struct
{
    double time_by_name; // Время удаление в дереве по имени
    double time_by_date; // Время удаления в дереве по дате
    size_t n;            // Количество элементов в дереве
} measure_t;

int measure(void);

#endif // !MEASURE_H__

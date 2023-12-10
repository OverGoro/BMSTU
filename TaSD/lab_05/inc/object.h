#ifndef OBJECT_H__
#define OBJECT_H__

#include <stdio.h>
#include <stddef.h>

typedef struct 
{
    double adding_time;     // Время добавления в очередь
    double processing_time; // Время обработки в аппарате
} object_t;

/**
* @brief Вывод информации
*
* @param f[in] Файловый поток
* @param o[in] Объект
*/
void object_print(FILE *f, const void *o);

#endif // !OBJECT_H__

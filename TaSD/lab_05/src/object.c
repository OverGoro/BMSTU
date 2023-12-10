#include "../inc/object.h"
#include <stdio.h>

void object_print(FILE *f, const void *o)
{
    object_t *ob = (object_t *)o;
    fprintf(f, "%lf %lf\n", ob->adding_time, ob->processing_time);
}


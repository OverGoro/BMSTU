#include "prompt.h"

void empty_prompt(FILE *f, char *s)
{
    (void)(f);
    (void)(s);
}

void normal_prompt(FILE *f, char *s)
{
    fprintf(f, "%s", s);
}


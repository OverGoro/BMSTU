#include "../inc/hash_func.h"

size_t hash_func(char *s, size_t m)
{
    size_t hash = 0;
    size_t prime = 31;

    for (size_t i = 0; s[i] != '\0'; i++)
    {
        hash = (hash * prime + s[i]) % m;
    }

    return hash;
}


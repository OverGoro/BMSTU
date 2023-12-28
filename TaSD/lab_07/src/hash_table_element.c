#include "../inc/hash_table_element.h"
#include <string.h>

int element_set_content(element_t *e, char *name, char *manual)
{
    int rc = ERR_OK;
    if (!rc)
        e->name = strdup(name);
    if (!rc && e->name == NULL)
        rc = ERR_MEM;
    if (!rc)
        e->manual = strdup(manual);
    if (!rc && e->manual == NULL)
        rc = ERR_MEM;
    if (rc)
        element_free_content(e); 
    return rc;
}
void element_free_content(element_t *e)
{
    free(e->name);
    e->name = NULL;
    free(e->manual);
    e->manual = NULL;
}

int element_read(FILE *f, element_t *e)
{
    char *name = NULL, *manual = NULL;
    int rc = ERR_OK;
    int name_len, manual_len;
    size_t read = 0;

    // Чтение name
    if ((name_len = getline(&name, &read, f)) == -1 || name_len <= 1)
    {
        rc = ERR_IO;
    }
    else
    {
        name[--name_len] = '\0';
        if (name_len == 0)
            rc = ERR_RANGE;
    }
    // Чтение manual
    if (rc == ERR_OK && ((manual_len = getline(&manual, &read, f)) == -1 || manual_len <= 1))
    {
        rc = ERR_IO;
    }
    else if (rc == ERR_OK)
    {
        manual[--manual_len] = '\0';
        if (manual_len == 0)
            rc = ERR_RANGE;
    }

    if (!rc)
    {
        e->name = name;
        e->manual = manual;
    }
    return rc;
}

size_t element_get_size(element_t *e)   
{
    if (e == NULL)
        return 0;
    size_t s = sizeof(element_t);
    if (e->name != NULL) s += sizeof(char) * strlen(e->name);
    if (e->manual != NULL) s += sizeof(char) * strlen(e->manual);
    return s;
}


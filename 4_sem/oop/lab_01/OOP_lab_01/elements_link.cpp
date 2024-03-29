#include "elements_link.h"

static int link_read_id(size_t &id, FILE *file)
{
    int rc = OK;
    if (fscanf(file, "%lu", &id) != 1)
        rc = ERR_IO;
    return rc;
}

int link_read(link_t &link, FILE *f)
{
    int rc = OK;
    rc = link_read_id(link.i_1, f);
    if (!rc)
        rc = link_read_id(link.i_2, f);
    return rc;
}

int link_print(FILE *file, const link_t &link)
{
    fprintf(file, "%lu %lu\n", link.i_1, link.i_2);
    return OK;
}

int link_validate(const link_t &link, size_t target_array_size)
{
    if (link.i_1 >= target_array_size || link.i_2 >= target_array_size)
    {
        return ERR_RANGE;
    }
    return OK;
}

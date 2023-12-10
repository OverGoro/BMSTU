#define _GNU_SOURCE
#include "list.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "polynome.h"

int main(void)
{
    int rc = ERR_OK;
    char *cmnd = NULL;
    int len;
    size_t read = 0;

    // Чтение команды
    if ((len = getline(&cmnd, &read, stdin)) == -1 || len <= 1)
    {
        rc = ERR_IO;
    }
    else
    {
        cmnd[--len] = '\0';
        if (len == 0)
            rc = ERR_RANGE;
    }

    node_t *polynome = NULL;
    if (!rc && strcmp(cmnd, "ddx") == 0)
    {
        rc = polynome_input(stdin, &polynome);
        if (!rc)
        {
            node_t *polynome_d = polynome_get_derivative(polynome);
            polynome_print(stdout, polynome_d);
            polynome_free(&polynome_d);
        }
    }
    else if (!rc && strcmp(cmnd, "val") == 0)
    {
        int x, res;
        rc = polynome_input(stdin, &polynome);
        if (!rc && fscanf(stdin, "%d", &x) != 1)
            rc = ERR_IO;
        if (!rc)
        {
            rc = polynome_count(polynome, x, &res);
            printf("%d\n", res);
        }
    }
    else if (!rc && strcmp(cmnd, "sum") == 0)
    {
        node_t *polynome_1 = NULL, *polynome_2 = NULL;
        rc = polynome_input(stdin, &polynome_1);
        if (!rc)
            rc = polynome_input(stdin, &polynome_2);
        if (!rc)
        {
            polynome = polynome_summ(polynome_1, polynome_2);
            polynome_print(stdout, polynome);
        }
        polynome_free(&polynome_1);
        polynome_free(&polynome_2);
    }
    else if (!rc && strcmp(cmnd, "dvd") == 0)
    {
        node_t *polynome_1 = NULL, *polynome_2 = NULL;
        rc = polynome_input(stdin, &polynome);
        if (!rc)
        {
            polynome_devide(&polynome, &polynome_1, &polynome_2);
            polynome_print(stdout, polynome_1);
            polynome_print(stdout, polynome_2);
        }
        polynome_free(&polynome_1);
        polynome_free(&polynome_2);
    }
    else if (!rc)
    {
        rc = ERR_ARGS_VALUE;
    }
    polynome_free(&polynome);
    free(cmnd);
    return rc;
}

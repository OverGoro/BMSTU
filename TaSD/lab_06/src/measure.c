#include "../inc/measure.h"
#include "../inc/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define START_N 100
#define DELTA_N 100
#define END_N 5000

double get_time(void) 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

void measure_print(FILE *f, measure_t *measure)
{
    fprintf(f, "%lu %lf %lf\n", measure->n, measure->time_by_name, measure->time_by_date);
}

int measure(void)
{
    FILE *f_out = fopen("measures/data.txt", "w");
    if (f_out == NULL)
        return ERR_FILE;
    for (size_t i = START_N; i < END_N; i += DELTA_N)
    {
        printf("measuring %lu\n", i);
        measure_t m = {0, 0, 0};
        for (size_t n = 0; n < 25; n++)
        {
            srand(0);
            tree_t *tree = NULL;
            for (size_t j = 0; j <= i; j++)
            {
                char name[4];
                name[0] = 'A' + rand() % 24;
                name[1] = 'A' + rand() % 24;
                name[2] = 'A' + rand() % 24;
                name[3] = '\0';
                time_t date = (time_t)(rand() % 2);
                tree_t *node = tree_node_create(date, name);
                if (node == NULL)
                {
                    tree_destroy(&tree);
                    return ERR_MEM;
                }
                tree = tree_insert_node(tree, node, tree_node_cmp_name);
            }
            tree_t *tree_date = NULL;
            if (tree_rebuild(&tree_date, tree, tree_node_cmp_date))
            {
                tree_destroy(&tree);
                tree_destroy(&tree_date);
            }
            tree_t *node = tree_node_create(0, "a");
            if (node == NULL)
            {
                tree_destroy(&tree);
                tree_destroy(&tree_date);
                return ERR_MEM;
            }
            double time = get_time();
            tree_remove_by_cmp(&tree_date, node, tree_node_cmp_date, tree_node_cmp_name);
            m.time_by_date += (get_time() - time) / 25;

            time = get_time();
            tree_remove_by_cmp(&tree, node, tree_node_cmp_date, tree_node_cmp_name);
            m.time_by_name += (get_time() - time) / 25;

            m.n = i;
        }
        measure_print(f_out, &m);
    }
    fclose(f_out);
    system("gnuplot graph.gpi");
    return ERR_OK;
}


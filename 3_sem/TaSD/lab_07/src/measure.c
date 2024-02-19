#define _GNU_SOURCE
#include "../inc/measure.h"
#include "../inc/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
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

static double measure_hash_search_all(tree_t *tree, hash_table_t *ht)
{

    double res = 0;
    if (tree != NULL && tree->name != NULL)
    {
        double t = get_time();
        ht_get_manual(ht, tree->name);
        res += get_time() - t;
        res += measure_hash_search_all(tree->left, ht);
        res += measure_hash_search_all(tree->right, ht);
    }
    return res;
}

static double measure_closed_hash_search_all(tree_t *tree, closed_hash_table_t *cht)
{

    double res = 0;
    if (tree != NULL && tree->name != NULL)
    {
        double t = get_time();
        cht_get_manual(cht, tree->name);
        res += get_time() - t;
        res += measure_closed_hash_search_all(tree->left, cht);
        res += measure_closed_hash_search_all(tree->right, cht);
    }
    return res;
}

static double measure_tree_search_all(tree_t *root_tree, tree_t *tree)
{

    double res = 0;
    if (tree != NULL && tree->name != NULL)
    {
        double t = get_time();
        tree_find(root_tree, tree->name);
        res += get_time() - t;
        res += measure_tree_search_all(root_tree, tree->left);
        res += measure_tree_search_all(root_tree, tree->right);
    }
    return res;
}

static double measure_avl_tree_search_all(avl_tree_t *root_tree, tree_t *tree)
{

    double res = 0;
    if (tree != NULL && tree->name != NULL)
    {
        double t = get_time();
        avl_tree_find(root_tree, tree->name);
        res += get_time() - t;
        res += measure_avl_tree_search_all(root_tree, tree->left);
        res += measure_avl_tree_search_all(root_tree, tree->right);
    }
    return res;
}


static int measure_fill_search(tree_t **tree, 
                               avl_tree_t **avl_tree, 
                               hash_table_t *ht, 
                               closed_hash_table_t *cht, 
                               size_t num)
{
    tree_destroy(tree);
    avl_tree_destroy(avl_tree);
    cht_free_content(cht);
    ht_free_content(ht);
    size_t seed = (size_t)get_time();
    srand(seed);
    int rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && i < num; i++)
    {
        char name[5];
        for (size_t j = 0; j < sizeof(name); j++)
            name[j] = 1 + (char)rand() % 250;
        name[4] = 0;
        tree_t *el = tree_node_create(name, "a");
        if (el == NULL) rc = ERR_MEM;
        if (!rc) *tree = tree_insert_node(*tree, el, tree_node_cmp_name);
    }
    srand(seed);
    for (size_t i = 0; rc == ERR_OK && i < num; i++)
    {
        char name[5];
        for (size_t j = 0; j < sizeof(name); j++)
            name[j] = 1 + (char)rand() % 250;
        name[4] = 0;
        avl_tree_t *el = avl_tree_node_create(name, "a");
        if (el == NULL) rc = ERR_MEM;
        if (!rc) *avl_tree = avl_tree_insert_node(*avl_tree, el, tree_node_cmp_name);
    }

    srand(seed);
    for (size_t i = 0; rc == ERR_OK && i < num; i++)
    {
        char name[5];
        for (size_t j = 0; j < sizeof(name); j++)
            name[j] = 1 + (char)rand() % 250;
        name[4] = 0;
        rc = ht_insert(ht, name, "a",4);
    }

    srand(seed);
    for (size_t i = 0; rc == ERR_OK && i < num; i++)
    {
        char name[5];
        for (size_t j = 0; j < sizeof(name); j++)
            name[j] = 1 + (char)rand() % 250;
        name[4] = 0;
        rc = cht_insert(cht, name, "a", 3);
    }
    if (rc)
    {
        tree_destroy(tree);
        avl_tree_destroy(avl_tree);
        ht_free_content(ht);
        cht_free_content(cht);
    }
    return rc;
}

static int fill_hash(tree_t **tree, hash_table_t *ht, closed_hash_table_t *cht, size_t num, double max_collision)
{
    cht_free_content(cht);
    ht_free_content(ht);
    tree_destroy(tree);

    size_t seed = (size_t)get_time();
    int rc = ERR_OK;
    srand(seed);
    for (size_t i = 0; rc == ERR_OK && i < num; i++)
    {
        char name[6];
        for (size_t j = 0; j < sizeof(name); j++)
            name[j] = 1 + (char)rand() % 250;
        name[5] = 0;
        rc = ht_insert(ht, name, "a", max_collision);
    }

    srand(seed);
    for (size_t i = 0; rc == ERR_OK && i < num; i++)
    {
        char name[6];
        for (size_t j = 0; j < sizeof(name); j++)
            name[j] = 1 + (char)rand() % 250;
        name[5] = 0;
        rc = cht_insert(cht, name, "a", max_collision);
    }

    srand(seed);
    for (size_t i = 0; rc == ERR_OK && i < num; i++)
    {
        char name[6];
        for (size_t j = 0; j < sizeof(name); j++)
            name[j] = 1 + (char)rand() % 250;
        name[5] = 0;
        tree_t *el = tree_node_create(name, "a");
        if (el == NULL) rc = ERR_MEM;
        if (!rc) *tree = tree_insert_node(*tree, el, tree_node_cmp_name);
    }
    if (rc)
    {
        tree_destroy(tree);
        ht_free_content(ht);
        cht_free_content(cht);
    }
    return rc;
}


static int measure_hash(void)
{
    FILE *f = fopen("measures/hash.txt", "w");
    closed_hash_table_t cht = {0,0};
    hash_table_t ht = {0,0};
    tree_t *tree = NULL;

    int rc = ERR_OK;
    for (size_t i = 50; rc == ERR_OK && i <= 2000; i += 50)
    {
        printf("measuring %lu collisions\n", i);
        double time_ht = 0;
        double time_cht = 0;
        for (size_t j = 0; j < 5; j++)
        {
            rc = fill_hash(&tree, &ht, &cht, 2000, i);
            if (!rc)
            {
                time_ht += ht_get_average_collision(&ht);
                time_cht += cht_get_average_collision(&cht);
            }
        }
        fprintf(f, "%lu %lf %lf\n", i, time_ht / 5, time_cht / 5);
    }
    fclose(f);
    return rc;
}

static int measure_search(void)
{
    FILE *f = fopen("measures/find.txt", "w");
    FILE *f_size = fopen("measures/find_size.txt", "w");
    if (f == NULL || f_size == NULL)
        return ERR_FILE;

    tree_t *tree = NULL;
    avl_tree_t *avl_tree = NULL;
    closed_hash_table_t cht = {0,0};
    hash_table_t ht = {0,0};

    double time_tree = 0, time_avl = 0, time_ht = 0, time_cht = 0;

    int rc = ERR_OK;
    for (size_t n = 100; rc == ERR_OK && n <= 1000; n += 100)
    {
        printf("measuring %lu elements search\n", n);
        time_tree = 0;
        time_avl = 0;
        time_ht = 0;
        time_cht = 0;
        for (size_t i = 0; rc == ERR_OK && i < 10; i++)
        {
            rc = measure_fill_search(&tree, &avl_tree, &ht, &cht, n);
            if (!rc)
            {
                time_tree += measure_tree_search_all(tree, tree) / 10;

                time_avl += measure_avl_tree_search_all(avl_tree, tree) / 10;

                time_ht += measure_hash_search_all(tree, &ht) / 10;

                time_cht += measure_closed_hash_search_all(tree, &cht);
            }
        }
        fprintf(f, "%lu %lf %lf %lf %lf\n", n, time_tree, time_avl, time_ht, time_cht);
        fprintf(f_size, "%lu %lu %lu %lu %lu\n", n, tree_get_size(tree), 
                avl_tree_get_size(avl_tree),
                ht_get_size(&ht),
                cht_get_size(&cht));
    }
    tree_destroy(&tree);
    avl_tree_destroy(&avl_tree);
    cht_free_content(&cht);
    ht_free_content(&ht);

    fclose(f);
    fclose(f_size);

    return rc;
}

int measure(void)
{
    int rc = measure_search();
    if (!rc) rc = measure_hash();
    if (!rc) system("gnuplot graph.gpi");
    return rc;
}


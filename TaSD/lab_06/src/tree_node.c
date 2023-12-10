#define _GNU_SOURCE
#include "../inc/tree_node.h"

int tree_node_cmp_name(void *l, void *r)
{
    tree_t *l_n = l, *r_n = r;
    return strcmp(l_n->name, r_n->name);
}

int tree_node_cmp_date(void *l, void *r)
{
    tree_t *l_n = l, *r_n = r;
    if (l_n->date > r_n->date)
        return 1;
    else if (l_n->date == r_n->date)
        return 0;
    else
        return -1;
}


tree_t *tree_node_create(time_t date, char *name)
{
    tree_t *node = malloc(sizeof(tree_t));
    int rc = ERR_OK;
    if (node != NULL)
    {
        if (!rc)
            node->name = strdup(name);
        if (!rc && node->name == NULL)
            rc = ERR_MEM;
        if (!rc)
        {
            node->date = date;
            node->left = NULL;
            node->right = NULL;
        }
    }
    if (rc)
        tree_node_destroy(&node);
    return node;
}

tree_t *tree_node_copy(const tree_t *node)
{
    if (node == NULL)
        return NULL;
    tree_t *node_copy = malloc(sizeof(tree_t));
    if (node_copy != NULL)
        node_copy->name = strdup(node->name);
    if (node_copy != NULL && node_copy->name == NULL)
        tree_node_destroy(&node_copy);
    if (node_copy != NULL)
    {
        node_copy->date = node->date;
        node_copy->left = NULL;
        node_copy->right = NULL;
    }

    return node_copy;
}

void tree_node_clear(tree_t *tree)
{
    if (tree != NULL)
    {
        free(tree->name);
        tree->name = NULL;
    }
}

void tree_node_print_children(tree_t *node, void *file_arg)
{
    if (file_arg == NULL || node == NULL)
        return;
    FILE *f = file_arg;
    const char *time_n = strdup(ctime(&node->date));
    const char *time_l = NULL;
    const char *time_r = NULL;
    if (node->left != NULL)
        time_l = strdup(ctime(&node->left->date));
    if (node->right != NULL)
        time_r = strdup(ctime(&node->right->date));

    fprintf(f, "\"%s\n%s\";\n", node->name, time_n);
    if (time_l != NULL)
    {
        fprintf(f, "\"%s\n%s\" -> \"%s\n%s\";\n", node->name, time_n, node->left->name, time_l);
    }
    if (node->right != NULL)
    {
        fprintf(f, "\"%s\n%s\" -> \"%s\n%s\";\n", node->name, time_n, node->right->name, time_r);
    }
}

void tree_node_print_children_name(tree_t *node, void *file_arg)
{
    if (file_arg == NULL)
        return;
    FILE *f = file_arg;
    if (node->left != NULL)
        fprintf(f, "%s -> %s;\n", node->name, node->left->name);
    if (node->right != NULL)
        fprintf(f, "%s -> %s;\n", node->name, node->right->name);
}

void tree_node_print_children_date(tree_t *node, void *file_arg)
{
    if (file_arg == NULL)
        return;
    FILE *f = file_arg;
    if (node->left != NULL)
        fprintf(f, "\"%s\" -> \"%s\";\n", ctime(&node->date), ctime(&node->left->date));
    if (node->right != NULL)
        fprintf(f, "\"%s\" -> \"%s\";\n", ctime(&node->date), ctime(&node->right->date));
}

void tree_node_print_simple(tree_t *node, void *file_arg)
{
    if (file_arg == NULL)
        return;
    FILE *f = file_arg;
    if (node != NULL)
        fprintf(f, "%s\n", node->name);
}

void tree_node_destroy(tree_t **tree)
{
    if (tree != NULL)
    {
        tree_node_clear(*tree);
        free(*tree);
        *tree = NULL;
    }
}

int tree_node_read(FILE *f_in, FILE *f_out, tree_t *node)
{
    if (node == NULL)
        return ERR_EMPTY_NODE;
    char *name = NULL;
    time_t date = 0;
    int rc = ERR_OK;
    int len_name;
    size_t read = 0;

    // Чтение name
    fprintf(f_out, "Введите имя файла: ");
    if ((len_name = getline(&name, &read, f_in)) == -1 || len_name <= 1)
    {
        rc = ERR_IO;
    }
    else
    {
        name[--len_name] = '\0';
        if (len_name == 0)
            rc = ERR_RANGE;
    }
    
    // Чтение date
    if (rc == ERR_OK)
    {
        fprintf(f_out, "Введите дату изменения (в секундах с 1970 года): ");
        if (fscanf(f_in, "%ld", &date) != 1)
        {
            rc = ERR_IO;
            char c = 0;
            while ((c = fgetc(f_in)) != '\n' && c != '\0');
        }
    }

    if (rc == ERR_OK)
    {
        free(node->name);
        node->date = date;
        node->name = name;
    }

    return rc;
}


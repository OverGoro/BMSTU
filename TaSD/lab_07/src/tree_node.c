#define _GNU_SOURCE
#include "../inc/tree_node.h"

int tree_node_cmp_name(void *l, void *r)
{
    tree_t *l_n = l, *r_n = r;
    return strcmp(l_n->name, r_n->name);
}

tree_t *tree_node_create(char *name, char *manual)
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
            node->manual = strdup(manual);
        if (!rc && node->manual == NULL)
            rc = ERR_MEM;
        if (!rc)
        {
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
        node_copy->manual = strdup(node->manual);
    if (node_copy != NULL && node_copy->manual == NULL)
        tree_node_destroy(&node_copy);

    if (node_copy != NULL)
    {
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
        free(tree->manual);
        tree->manual = NULL;
    }
}

void tree_node_print_children(tree_t *node, void *file_arg)
{
    if (file_arg == NULL || node == NULL)
        return;
    FILE *f = file_arg;

    fprintf(f, "\"%s\n%s\";\n", node->name, node->manual);

    if (node->left)
        fprintf(f, "\"%s\n%s\" -> \"%s\n%s\";\n", node->name, node->manual, node->left->name, node->left->manual);

    if (node->right)
        fprintf(f, "\"%s\n%s\" -> \"%s\n%s\";\n", node->name, node->manual, node->right->name, node->right->manual);
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

void tree_node_print_children_manual(tree_t *node, void *file_arg)
{
    if (file_arg == NULL)
        return;
    FILE *f = file_arg;
    if (node->left != NULL)
        fprintf(f, "\"%s\" -> \"%s\";\n", node->manual, node->left->manual);
    if (node->right != NULL)
        fprintf(f, "\"%s\" -> \"%s\";\n", node->manual, node->right->manual);
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

    char *name = NULL, *manual = NULL;
    int len_name, len_manual;

    int rc = ERR_OK;
    size_t read = 0;

    // Чтение name
    if(f_out != NULL) fprintf(f_out, "Введите слово: ");
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
    
    // Чтение manual
    if (rc == ERR_OK)
    {
        if(f_out != NULL) fprintf(f_out, "Введите описание: ");
        if ((len_manual = getline(&manual, &read, f_in)) == -1 || len_manual <= 1)
        {
            rc = ERR_IO;
        }
        else
        {
            manual[--len_manual] = '\0';
            if (len_manual == 0)
                rc = ERR_RANGE;
        }
    }

    if (rc == ERR_OK)
    {
        free(node->name);
        node->manual = manual;
        node->name = name;
    }

    return rc;
}


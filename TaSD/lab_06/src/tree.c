#include "../inc/tree.h"
#include <stdio.h>
#include <stdlib.h>


tree_t *tree_insert_node(tree_t *tree, tree_t *node, int comporator(void *l, void *r))
{
    int cmp;
    if (node == NULL)
        return tree;

    if (tree == NULL)
        return node;

    cmp = comporator(node, tree);
    
    if (cmp < 0)
        tree->left = tree_insert_node(tree->left, node, comporator);
    else
        tree->right = tree_insert_node(tree->right, node, comporator);

    return tree;
}

void tree_traversal(tree_t *tree, void func(tree_t *node, void *arg), void *arg)
{
    if (tree == NULL)
        return;
    func(tree, arg);
    tree_traversal(tree->left, func, arg);
    tree_traversal(tree->right, func, arg);
}

void tree_traversal_back(tree_t *tree, void func(tree_t *node, void *arg), void *arg)
{
    if (tree == NULL)
        return;
    tree_traversal_back(tree->left, func, arg);
    tree_traversal_back(tree->right, func, arg);
    func(tree, arg);
}

void tree_traversal_left(tree_t *tree, void func(tree_t *node, void *arg), void *arg)
{
    if (tree == NULL)
        return;
    tree_traversal_left(tree->left, func, arg);
    func(tree, arg);
    tree_traversal_left(tree->right, func, arg);
}


void tree_remove_node(tree_t **tree, tree_t **node, int comporator(void *l, void *r))
{
    if (node == NULL || tree == NULL || *tree == NULL)
        return;

    tree_t *left = (*node)->left;
    tree_t *right = (*node)->right;
    tree_node_destroy(node);
    *tree = tree_insert_node(*tree, left, comporator);
    *tree = tree_insert_node(*tree, right, comporator);

}

void tree_remove_by_cmp(tree_t **tree, tree_t *prototype, int del_cmp(void *l, void *r), int tree_cmp(void *l, void *r))
{
    if (tree == NULL || *tree == NULL || prototype == NULL)
        return;
    tree_remove_by_cmp(&(*tree)->left, prototype, del_cmp, tree_cmp);
    if (*tree != NULL)
        tree_remove_by_cmp(&(*tree)->right, prototype, del_cmp, tree_cmp);
    if (*tree != NULL && del_cmp(*tree, prototype) <= 0)
        tree_remove_node(tree, tree, tree_cmp);
        
}

int tree_rebuild(tree_t **tree_copy, tree_t *tree, int comporator(void *l, void *r)) 
{
    if (tree == NULL)
        return ERR_OK;
    tree_t *node_copy = tree_node_copy(tree);
    if (node_copy == NULL)
        return ERR_MEM;
    *tree_copy = tree_insert_node(*tree_copy, node_copy, comporator);
    int rc = tree_rebuild(tree_copy, tree->left, comporator);
    if (rc != ERR_OK)
        return rc;
    rc = tree_rebuild(tree_copy, tree->right, comporator);

    return rc;
}

int tree_draw(const char *file_name, tree_t *tree)
{
    FILE *f = fopen(file_name, "w");
    if (f == NULL)
        return ERR_FILE;

    fprintf(f, "digraph tree {\n");
    tree_traversal(tree, tree_node_print_children, f);
    fprintf(f, "}");
    fclose(f);
    size_t command_len = strlen(file_name) * 2 + 29;
    char *command = malloc(command_len);
    if (command == NULL)
        return ERR_MEM;
    else
        command[0] = 0;

    command = strcat(command, "dot -T png -O ");
    if (command == NULL)
        return ERR_MEM;
    command = strcat(command, file_name);
    if (command == NULL)
        return ERR_MEM;
    command = strcat(command, " && open ");
    if (command == NULL)
        return ERR_MEM;
    command = strcat(command, file_name);
    if (command == NULL)
        return ERR_MEM;
    command = strcat(command, ".png");
    system(command);
    free(command);

    return ERR_OK;
}

void tree_destroy(tree_t **tree)
{
    if (*tree == NULL)
        return;
    tree_destroy(&(*tree)->left);
    tree_destroy(&(*tree)->right);
    tree_node_destroy(tree);
}


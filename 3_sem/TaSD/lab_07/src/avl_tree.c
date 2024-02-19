#include "../inc/avl_tree.h"
#include <string.h>

#define MAX(a,b) ((a > b) ? a : b)


static int height(avl_tree_t *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

static int get_balance(avl_tree_t *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

static avl_tree_t *right_rotate(avl_tree_t *y) {
    if (y == NULL) {
        return NULL;
    }
    avl_tree_t *x = y->left;
    if (x == NULL) {
        return y;
    }
    avl_tree_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + MAX(height(y->left), height(y->right));
    x->height = 1 + MAX(height(x->left), height(x->right));

    return x;
}

static avl_tree_t *left_rotate(avl_tree_t *x) {
    if (x == NULL) {
        return NULL;
    }
    avl_tree_t *y = x->right;
    if (y == NULL) {
        return x;
    }
    avl_tree_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + MAX(height(x->left), height(x->right));
    y->height = 1 + MAX(height(y->left), height(y->right));

    return y;
}
avl_tree_t *avl_tree_insert_node(avl_tree_t *avl_tree, avl_tree_t *node, int comparator(void *l, void *r)) {
    if (avl_tree == NULL)
        return node;

    if (comparator(node, avl_tree) < 0)
        avl_tree->left = avl_tree_insert_node(avl_tree->left, node, comparator);
    else if (comparator(node, avl_tree) > 0)
        avl_tree->right = avl_tree_insert_node(avl_tree->right, node, comparator);
    else
        return avl_tree;

    avl_tree->height = 1 + MAX(height(avl_tree->left), height(avl_tree->right));

    int balance = get_balance(avl_tree);

    if (balance > 1 && comparator(node, avl_tree) < 0)
        return right_rotate(avl_tree);

    if (balance < -1 && comparator(node, avl_tree->right) > 0)
        return left_rotate(avl_tree);

    if (balance > 1 && comparator(node, avl_tree->left) > 0) {
        avl_tree->left = left_rotate(avl_tree->left);
        return right_rotate(avl_tree);
    }

    if (balance < -1 && comparator(node, avl_tree->right) < 0) {
        avl_tree->right = right_rotate(avl_tree->right);
        return left_rotate(avl_tree);
    }

    return avl_tree;
}


void avl_tree_traversal(avl_tree_t *avl_tree, void func(avl_tree_t *node, void *arg), void *arg)
{
    if (avl_tree == NULL)
        return;
    func(avl_tree, arg);
    avl_tree_traversal(avl_tree->left, func, arg);
    avl_tree_traversal(avl_tree->right, func, arg);
}

void avl_tree_traversal_back(avl_tree_t *avl_tree, void func(avl_tree_t *node, void *arg), void *arg)
{
    if (avl_tree == NULL)
        return;
    avl_tree_traversal_back(avl_tree->left, func, arg);
    avl_tree_traversal_back(avl_tree->right, func, arg);
    func(avl_tree, arg);
}

void avl_tree_traversal_left(avl_tree_t *avl_tree, void func(avl_tree_t *node, void *arg), void *arg)
{
    if (avl_tree == NULL)
        return;
    avl_tree_traversal_left(avl_tree->left, func, arg);
    func(avl_tree, arg);
    avl_tree_traversal_left(avl_tree->right, func, arg);
}


void avl_tree_remove_node(avl_tree_t **avl_tree, avl_tree_t **node, int comporator(void *l, void *r))
{
    if (node == NULL || avl_tree == NULL || *avl_tree == NULL)
        return;

    avl_tree_t *left = (*node)->left;
    avl_tree_t *right = (*node)->right;
    avl_tree_node_destroy(node);
    *avl_tree = avl_tree_insert_node(*avl_tree, left, comporator);
    *avl_tree = avl_tree_insert_node(*avl_tree, right, comporator);

}

void avl_tree_remove_by_cmp(avl_tree_t **avl_tree, avl_tree_t *prototype, int del_cmp(void *l, void *r), int avl_tree_cmp(void *l, void *r))
{
    if (avl_tree == NULL || *avl_tree == NULL || prototype == NULL)
        return;
    avl_tree_remove_by_cmp(&(*avl_tree)->left, prototype, del_cmp, avl_tree_cmp);
    if (*avl_tree != NULL)
        avl_tree_remove_by_cmp(&(*avl_tree)->right, prototype, del_cmp, avl_tree_cmp);
    if (*avl_tree != NULL && del_cmp(*avl_tree, prototype) <= 0)
        avl_tree_remove_node(avl_tree, avl_tree, avl_tree_cmp);
        
}

int avl_tree_rebuild(avl_tree_t **avl_tree_copy, avl_tree_t *avl_tree, int comporator(void *l, void *r)) 
{
    if (avl_tree == NULL)
        return ERR_OK;
    avl_tree_t *node_copy = avl_tree_node_copy(avl_tree);
    if (node_copy == NULL)
        return ERR_MEM;
    *avl_tree_copy = avl_tree_insert_node(*avl_tree_copy, node_copy, comporator);
    int rc = avl_tree_rebuild(avl_tree_copy, avl_tree->left, comporator);
    if (rc != ERR_OK)
        return rc;
    rc = avl_tree_rebuild(avl_tree_copy, avl_tree->right, comporator);

    return rc;
}

int avl_tree_draw(const char *file_name, avl_tree_t *avl_tree)
{
    FILE *f = fopen(file_name, "w");
    if (f == NULL)
        return ERR_FILE;

    fprintf(f, "digraph avl_tree {\n");
    avl_tree_traversal(avl_tree, avl_tree_node_print_children, f);
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

void avl_tree_destroy(avl_tree_t **avl_tree)
{
    if (*avl_tree == NULL)
        return;
    avl_tree_destroy(&(*avl_tree)->left);
    avl_tree_destroy(&(*avl_tree)->right);
    avl_tree_node_destroy(avl_tree);
}

int avl_tree_read(avl_tree_t **tree, char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return ERR_FILE;
    int rc = ERR_OK;
    while (rc == ERR_OK)
    {
        avl_tree_t *node = avl_tree_node_create("", "");
        if (node == NULL) rc = ERR_MEM;
        if (!rc) rc = avl_tree_node_read(f, NULL, node);
        if (!rc) *tree = avl_tree_insert_node(*tree, node, avl_tree_node_cmp_name);
    }
    if (feof(f))
        rc = ERR_OK;
    fclose(f);
    return rc;
}

const char *avl_tree_find(avl_tree_t *tree, const char *name)
{
    if (tree == NULL)
        return NULL;
    int rc = strcmp(name, tree->name);
    if (rc == 0)
        return tree->manual;

    const char *manual = avl_tree_find(tree->left, name);
    if (!manual)
        manual = avl_tree_find(tree->right, name);
    return manual;
}

size_t avl_tree_get_size(avl_tree_t *avl_tree)  
{
    size_t s = 0;
    if (avl_tree == NULL)
        return s;
    s += sizeof(avl_tree_t);

    if (avl_tree->name != NULL) s += sizeof(char) * strlen(avl_tree->name);
    if (avl_tree->manual != NULL) s += sizeof(char) * strlen(avl_tree->manual);
    
    s += avl_tree_get_size(avl_tree->left);
    s += avl_tree_get_size(avl_tree->right);
    return s;
}


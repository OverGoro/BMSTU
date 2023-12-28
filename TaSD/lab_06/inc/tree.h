#ifndef TREE_H__
#define TREE_H__

#include "tree_node.h"

/**
* @brief Отрисовка дерева
*
* @param file_name[in] Имя файла с данными
* @param tree[in] Дерево
*
* @return Код ошибки
*/
int tree_draw(const char *file_name, tree_t *tree);

/**
* @brief Добавление узла в дерево
*
* @param tree[in, out] Дерево
* @param node[in] Узел
* @param comporator[in] Компоратор, по которому определяется положение узла в дереве
*
* @return Указатель на новый корень дерева
*/
tree_t *tree_insert_node(tree_t *tree, tree_t *node, int comporator(void *l, void *r));

/**
* @brief Перестроение дерева по новому компоратору 
*
* @param tree_copy [in, out] Новое дерево
* @param tree [in] Старое дерево
*
* @return Код ошибки
*/
int tree_rebuild(tree_t **tree_copy, tree_t *tree, int comporator(void *l, void *r));
/**
* @brief Обход дерева
*
* @param tree[in, out] Дерево
* @param func[in] Функция, применяющаяся к каждому узлу
* @param arg[in] аргумент функции
*/
void tree_traversal(tree_t *tree, void func(tree_t *node, void *arg), void *arg);
void tree_traversal_back(tree_t *tree, void func(tree_t *node, void *arg), void *arg);
void tree_traversal_left(tree_t *tree, void func(tree_t *node, void *arg), void *arg);

/**
* @brief Удаление узла из дерева
*
* @param treeх[in, out] Дерево
* @param node[in] Узел
* @param comporator[in] Компоратор, по которому построено дерево
*/
void tree_remove_node(tree_t **tree, tree_t **node, int comporator(void *l, void *r));

/**
* @brief Удаление узлов из дерева по прототипу и компоратору
*
* @param treeх[in, out] Дерево
* @param prototype[in] Прототип
* @param del_cmp[in] Компоратор по которому удалять элемента, если равны прототипу
* @param tree_cmp[in] Компоратор, по которому построено дерево
*/
void tree_remove_by_cmp(tree_t **tree, tree_t *prototype, int del_cmp(void *l, void *r), int tree_cmp(void *l, void *r));

/**
* @brief Уничтожает дерево
*
* @param tree[in, out] Дерево
*/
void tree_destroy(tree_t **tree);

#endif // !TREE_H__

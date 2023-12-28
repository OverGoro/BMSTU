#ifndef AVL_TREE_H__
#define AVL_TREE_H__

#include "avl_tree_node.h"

/**
* @brief Отрисовка дерева
*
* @param file_name[in] Имя файла с данными
* @param avl_tree[in] Дерево
*
* @return Код ошибки
*/
int avl_tree_draw(const char *file_name, avl_tree_t *avl_tree);

/**
* @brief Добавление узла в дерево
*
* @param avl_tree[in, out] Дерево
* @param node[in] Узел
* @param comporator[in] Компоратор, по которому определяется положение узла в дереве
*
* @return Указатель на новый корень дерева
*/
avl_tree_t *avl_tree_insert_node(avl_tree_t *avl_tree, avl_tree_t *node, int comporator(void *l, void *r));

/**
* @brief Перестроение дерева по новому компоратору 
*
* @param avl_tree_copy [in, out] Новое дерево
* @param avl_tree [in] Старое дерево
*
* @return Код ошибки
*/
int avl_tree_rebuild(avl_tree_t **avl_tree_copy, avl_tree_t *avl_tree, int comporator(void *l, void *r));
/**
* @brief Обход дерева
*
* @param avl_tree[in, out] Дерево
* @param func[in] Функция, применяющаяся к каждому узлу
* @param arg[in] аргумент функции
*/
void avl_tree_traversal(avl_tree_t *avl_tree, void func(avl_tree_t *node, void *arg), void *arg);
void avl_tree_traversal_back(avl_tree_t *avl_tree, void func(avl_tree_t *node, void *arg), void *arg);
void avl_tree_traversal_left(avl_tree_t *avl_tree, void func(avl_tree_t *node, void *arg), void *arg);

/**
* @brief Удаление узла из дерева
*
* @param avl_tree[in, out] Дерево
* @param node[in] Узел
* @param comporator[in] Компоратор, по которому построено дерево
*/
void avl_tree_remove_node(avl_tree_t **avl_tree, avl_tree_t **node, int comporator(void *l, void *r));

/**
* @brief Удаление узлов из дерева по прототипу и компоратору
*
* @param avl_tree[in, out] Дерево
* @param prototype[in] Прототип
* @param del_cmp[in] Компоратор по которому удалять элемента, если равны прототипу
* @param avl_tree_cmp[in] Компоратор, по которому построено дерево
*/
void avl_tree_remove_by_cmp(avl_tree_t **avl_tree, avl_tree_t *prototype, int del_cmp(void *l, void *r), int avl_tree_cmp(void *l, void *r));

/**
* @brief Уничтожает дерево
*
* @param avl_tree[in, out] Дерево
*/
void avl_tree_destroy(avl_tree_t **avl_tree);

int avl_tree_read(avl_tree_t **tree, char *file_name);

const char *avl_tree_find(avl_tree_t *tree, const char *name);

size_t avl_tree_get_size(avl_tree_t *avl_tree);

#endif // !avl_tree_H__

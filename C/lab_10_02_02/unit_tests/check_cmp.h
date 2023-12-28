#ifndef CHECK_CMP_H__
#define CHECK_CMP_H__

#include "node.h"

/**
* @brief Сравнение 2 списков
*
* @param head_1[in] Список 1
* @param head_2[in] Список 2
*
* @return 0 - равны, не 0 - не равны
*/
int cmp_list(node_t *head_1, node_t *head_2);

/**
* @brief Компоратор адресов
*
* @param l[in] Адрес 1
* @param r[in] Адрес 2
*
* @return Результат сравнения
*/
int cmp_addr(const void *l, const void *r);

#endif // !CHECK_CMP_H__

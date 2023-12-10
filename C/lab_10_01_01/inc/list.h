#ifndef LIST_H__
#define LIST_H__

#include <stdio.h>
#include "automobile.h"
#include "error.h"
#include "node.h"

/**
* @brief Добавление узла в конец списка
*
* @param head[in] Голова списка
* @param pnode[in] Узел
*
* @return Новая голова списка
*/
node_t *list_add_tail(node_t *head, node_t *pnode);

/**
* @brief Формирование списка на основе массива
*
* @param head[in, out] Голова списка
* @param arr[in] Массив
* @param n[in] Количество элементов в массиве
*
* @return Код ошибки
*/
int list_form_by_arr(node_t **head, automobile_t *arr, size_t n);

/**
* @brief Вывод списка в файловый поток 
*
* @param f[in, out] Файловый поток
* @param head[in] Голова списка
* @param printer[in] Функция вывод элементов
*/
void list_print(FILE *f, node_t *head, void printer(FILE *f, const void *node));

/**
* @brief Удаление узла из списка
*
* @param head[in, out] Голова списка
* @param node[in] Адрес удаляемого узла
*/
void remove_node(node_t **head, node_t *node);

/**
* @brief Удаление дубикатов из списка
*
* @param head[in, out] Голова списка
* @param comporator[in] Компаратор
*/
void remove_duplicates(node_t **head, int(*comporator)(const void *, const void *));

/**
* @brief Обращение списка
*
* @param head[in] Голова списка
*
* @return Новая голова спсика
*/
node_t *reverse(node_t *head);

/**
* @brief Разделение списка на 2
*
* @param head Голова первого списка
* @param back Голова второго списка
*/
void front_back_split(node_t *head, node_t **back);

/**
* @brief Слияние 2 отсортированных списков
*
* @param head_a[in] Отсортированный список
* @param head_b[in] Отсортированный список
* @param comparator[in] Компаратор
*
* @return Список после слияния
*/
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));


/**
* @brief Сортировка списка
*
* @param head[in, out] Голова списка
* @param comparator[in] Компоратор
*
* @return Новая голова
*/
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

/**
* @brief Получение данных и удаление головы списка
*
 *Список должен быть не пустой
*
* @param head[in, out] Голова списка
*
* @return Данные
*/
void *pop_front(node_t **head);

/**
* @brief Получение данных и удаление конца списка
*
 *Список должен быть не пустой
*
* @param head[in, out] Голова списка
*
* @return Данные
*/
void *pop_back(node_t **head);


/**
* @brief Освобождение памяти под список
*
* @param head[in] голова списка
*/
void list_free(node_t **head);

#endif // !LIST_H__

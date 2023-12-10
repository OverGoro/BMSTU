#ifndef address_list_H__
#define address_list_H__

#include <stdio.h>
#include "error.h"
#include "address_node.h"
/**
* @brief Проверка фрагментации
*
* @param head Список адресов
* @param element_size Размер элемента
*
* @return true/false
*/
bool address_list_check_frag(address_node_t *head, long element_size);

/**
* @brief Прибавление использованного адреса
*
* @param head[in] Голова списка адресов
* @param adr[in] Использованный адрес
*
* @return Новая голова
*/
address_node_t *addres_list_plus(address_node_t *head, void *adr);
/**
* @brief Добавление узла в конец списка
*
* @param head[in] Голова списка
* @param pnode[in] Узел
*
* @return Новая голова списка
*/
address_node_t *address_list_add_tail(address_node_t *head, address_node_t *pnode);


/**
* @brief Вывод списка в файловый поток 
*
* @param f[in, out] Файловый поток
* @param head[in] Голова списка
*/
void address_list_print(FILE *f, address_node_t *head);

/**
* @brief Разделение списка на 2
*
* @param head Голова первого списка
* @param back Голова второго списка
*/
void front_back_split(address_node_t* head, address_node_t** back);

/**
* @brief Слияние 2 отсортированных списков
*
* @param head_a[in] Отсортированный список
* @param head_b[in] Отсортированный список
* @param comparator[in] Компаратор
*
* @return Список после слияния
*/
address_node_t* sorted_merge(address_node_t** head_a, address_node_t** head_b, int (*comparator)(const void*, const void*));


/**
* @brief Сортировка списка
*
* @param head[in, out] Голова списка
* @param comparator[in] Компоратор
*/
void address_sort(address_node_t** head, int (*comparator)(const void*, const void*));

/**
* @brief Получение данных и удаление головы списка
*
* Список должен быть не пустой
*
* @param head[in, out] Голова списка
*
* @return Данные
*/
void* pop_front(address_node_t **head);

/**
* @brief Получение данных и удаление конца списка
*
* Список должен быть не пустой
*
* @param head[in, out] Голова списка
*
* @return Данные
*/
void* pop_back(address_node_t **head);


/**
* @brief Освобождение памяти под список
*
* @param head[in] голова списка
*/
void address_list_free(address_node_t **head);

#endif // !address_list_H__

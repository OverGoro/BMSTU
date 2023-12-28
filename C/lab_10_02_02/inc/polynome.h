#ifndef POLYNOME_H__
#define POLYNOME_H__

#include "list.h"

/**
* @brief Ввод коэффициентов полинома 
*
* @param f[in, out] йловый поток
* @param polynome[in, out] Полином
*
* @return Код ошибки
*/
int polynome_input(FILE *f, node_t **polynome);

/**
* @brief Освобождение памяти
*
* @param polynome[in, out] Полином 
*/
void polynome_free(node_t **polynome);

/**
* @brief Вывод коэффициентов полинома
*
* @param f[in, out] Файловый поток
* @param polynome[in] Полином
*/
void polynome_print(FILE *f, node_t *polynome);

/**
* @brief Вычисление значения полинома
*
* @param polynome[in] Полином
* @param x[in] Значение переменной
*/
int polynome_count(node_t *polynome, int x, int *r);

/**
* @brief Расчет производной полинома
*
* @param polynome[in] Исходный полином
*
* @return Полином-производная или NULL, 
* если посчитать производную невозможно
*/
node_t *polynome_get_derivative(node_t *polynome);

/**
* @brief Суммирование 2 полиномов
*
* @param polynome_1[in] Первый полином
* @param polynome_2[in] Второй полином
*
* @return Новый полином = сумме 2 переданных 
* или NULL, если оба полинома пустые
*/
node_t *polynome_summ(const node_t *polynome_1, const node_t *polynome_2);

/**
* @brief Деление полинома на полиномы четных и нечетных степеней
*
* @param polynome[in, out] Полином
* @param polynome_even[in, out] Полином четных степеней
* @param polynome_odd[in, out] Полином нечетных степеней
*/
void polynome_devide(node_t **polynome, node_t **polynome_even, node_t **polynome_odd);
#endif // !POLYNOME_H__

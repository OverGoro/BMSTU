#ifndef __NUM_H__
#define __NUM_H__

#define FLOAT_DIGITS_LEN 30 // Максимальная длина мантиссы дробного числа
#define INT_DIGITS_LEN 40 // Максимальная длина мантиссы целого числа
#define RESULT_DIGITS_LEN 40 // Максимальная длина мантиссы результата
#define MAX_DIGITS_LEN 40
#define MAX_ORDER 99999 // Максимальное значение порядка

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

// Режимы работы с числом
enum 
{
    INTEGER_MODE, // Работа с целым числом
    FLOAT_MODE,   // Работа с дробным числом
    RESULT_MODE   // Работа с результатом
};


// Дробное число
typedef struct {
    bool digits_sign; // Знак мантиссы
    int digits[MAX_DIGITS_LEN]; // Мантисса числа
    size_t digits_len; // Длина числа
    int order;   // Порядок числа
} float_num_t;

/**
* @brief Чтение числа из файлового потока
*
* @param f[in] Файловый поток
* @param pnum[out] Число
*
* @param mode[in] Режим ввода
* Возможные значения:
* INTEGER_MODE - ввод целого числа
* FLOAT_MODE - ввод дробного числа
*
* @return Код ошибки
*/
int num_read(FILE *f, float_num_t *pnum, int mode);


/**
* @brief Вывод числа в файовый поток
*
* @param f[in] Файловый поток
* @param pnum[in] Число
*/
void print_num(FILE *f, const float_num_t *pnum);


/**
* @brief Умножение целого числа на вещественное
*
* @param num_i[in] целое число
* @param num_f[in] вещественное число
* @param num_r[out] результат(вещественное число)
*
* @return Код ошибки
*/
int multiply_nums(const float_num_t *num_i, const float_num_t *num_f, float_num_t *num_r);

#endif


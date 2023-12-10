#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>

#define ERR_OK 0    // Успех
#define ERR_IO 1    // Ошибка ввода
#define ERR_RANGE 2 // Ошибка диапазона данных
#define ERR_MODE 3  // Ошибка: неверный режим работы
#define ERR_DIGITS_NUM 4 // Ошибка: превышение количества цифр числа
#define ERR_ORDER_DIGITS 5 // Ошибка: превышение количества цифр порядка при вводе
#define ERR_ORDER_OVERFLOW 6 // Ошибка6 превышение порядка после умножения

#endif


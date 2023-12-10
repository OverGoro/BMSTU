#ifndef AUTOMOBILE_H__
#define AUTOMOBILE_H__

#define _GNU_SOURCE

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
typedef struct automobile automobile_t;

// Автомобиль
struct automobile
{
    char *vin; // VIN номер
    size_t mileage; // Пробег
    size_t price; // Стоимость
};

/**
* @brief Сравнение автомобилей по VIN
*
* @param a_l[in] Указатель на 1-й автомобиль
* @param a_r[in] Укаазатель на 2-й автомобиль
*
* @return 0 - равны
* < 0 1-й "меньше" 2-го
* > 0 1-й "больше" 2-го
*/
int automobile_vin_cmp(const void *a_l, const void *a_r);

/**
* @brief Сравнение автомобилей по цене
*
* @param a_l[in] Указатель на 1-й автомобиль
* @param a_r[in] Укаазатель на 2-й автомобиль
*
* @return 0 - равны
* < 0 1-й "меньше" 2-го
* > 0 1-й "больше" 2-го
*/
int automobile_mileage_cmp(const void *a_l, const void *a_r);

/**
* @brief Сравнение автомобилей по цене
*
* @param a_l[in] Указатель на 1-й автомобиль
* @param a_r[in] Укаазатель на 2-й автомобиль
*
* @return 0 - равны
* < 0 1-й "меньше" 2-го
* > 0 1-й "больше" 2-го
*/
int automobile_price_cmp(const void *a_l, const void *a_r);

/**
* @brief Сравнение автомобилей по всем параметрам
*
* @param a_l[in] Указатель на 1-й автомобиль
* @param a_r[in] Укаазатель на 2-й автомобиль
*
* @return 0 - равны
* < 0 1-й "меньше" 2-го
* > 0 1-й "больше" 2-го
*/
int automobile_cmp(const void *a_l, const void *a_r);

/**
* @brief Осовобождение памяти под поля структуры
*
* @param a[in, out] Автомобиль
*/
void automobile_free_content(automobile_t *a);

/**
* @brief Выделение динамической памяти под автомобиль
*
* @return Указатель на выделенную область памяти
*/
automobile_t *automobile_create(void);

/**
* @brief Инициализация полей структуры
*
* @param a[out] Автомобиль
* @param vin[in] VIN
* @param mileage[in] Пробег
* @param price[in] Стоимость
*
* @return Код ошибки
*/
int automobile_init_content(automobile_t *a, char *vin, size_t mileage, size_t price);

/**
* @brief Чтение параметров автомобиля из файлового потока
*
* @param f[in, out] Файловый поток
* @param a[out] Автомобиль
*
* @return Код ошибки
*/
int automobile_read(FILE *f, automobile_t *a);

/**
* @brief Вывод информации об автомобиле в файловый поток
*
* @param f[in, out] Файловый поток
* @param p[in] Автомобиль
*/
void automobile_print(FILE *f, const void *p);

#endif // !automobile_H__

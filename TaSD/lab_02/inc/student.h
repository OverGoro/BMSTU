#ifndef STUDENT_H__
#define STUDENT_H__

#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

#define STREET_LEN 10
#define SURNAME_LEN 10
#define NAME_LEN 10
#define GROUP_LEN 10

typedef int (*cmp_t)(const void *l, const void *r);


// Типы жилья
enum
{
    HOUSE, // Дом
    DORMITORY, // Общежитие
    RENTAL // Съемное жилье
};

// Дом
typedef struct
{
    char sreet[STREET_LEN + 1]; // Улица
    unsigned int house_number;  // Номер дома
    unsigned int flat_number;   // Номер квартиры
} house_t;

// Общежитие
typedef struct
{
    unsigned int dormitory_number; // Номер общежития
    unsigned int room_number;      // Номер комнаты
} dormitory_t;

// Съемное жилье
typedef struct
{
    char sreet[STREET_LEN + 1]; // Название улицы
    unsigned int house_number;  // Номер дома
    unsigned int flat_number;   // Номер квартиры
    double cost;                // Стоимость
} rental_t;

// Студент
typedef struct
{
    size_t n;                     // Номер строки
    unsigned int housing_type;    // Тип жилья(Дом, общежитие, съемное жилье)
    char surname[SURNAME_LEN +1]; // Фамилия
    char name[NAME_LEN + 1];      // Имя
    char group[GROUP_LEN + 1];    // Группа
    unsigned int sex;             // Пол (м,ж - 1, 0)
    unsigned int age;             // Возраст
    double average_mark;          // Средний былл за сессию
    unsigned int entry_date;      // Год поступления
    union                         // Место проживания
    {
        house_t house;            // Дом
        dormitory_t dormitory;    // Общежитие
        rental_t rental;          // Съемное жилье
    } housing;
} student_t;


int cmp_mark(const void *student_l, const void *student_r);

/**
* @brief Проверка равенства studet_t по массиву компараторов
*
* @param student_l[in] Указатель на первого студента
* @param student_r[in] Указатель на второго студента
* @param cmp[in] Количество компараторов в массиве
*
* @return Результат сравнения
* <0 student_l < student_r
* 0 student_l = student_r
* >0 student_l > student_r
*/
int student_cmp(const void *student_l, const void *student_r, cmp_t cmp);

/**
* @brief Сравнение по типу жилья
*
* @param student_l[in] Указатель на первого студента
* @param student_r[in] Указатель на второго студента
*
* @return Результат сравнения
* <0 student_l < student_r
* 0 student_l = student_r
* >0 student_l > student_r
*/
int cmp_housing_type(const void *student_l, const void *student_r);

/**
* @brief Сравнение по дате поступления
*
* @param student_l[in] Указатель на первого студента
* @param student_r[in] Указатель на второго студента
*
* @return Результат сравнения
* <0 student_l < student_r
* 0 student_l < student_r
* >0 student_l < student_r
*/
int cmp_entry_date(const void *student_l, const void *student_r);

#endif


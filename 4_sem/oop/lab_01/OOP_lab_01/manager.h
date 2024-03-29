#ifndef MANAGER_H
#define MANAGER_H

#include "drawer.h"
#include "error.h"
#include "figure.h"

typedef enum
{
    COMMAND_READ,           // Чтение файла с точкам
    COMMAND_SAVE,           // Сохранение файла с точками
    COMMAND_MOVE,           // Сдвиг точек
    COMMAND_ROTATE,         // Поворот точек
    COMMAND_SCALE,          // Масштабировние точек
    COMMAND_DRAW,           // Отрисовка объектов
    COMMAND_EXIT            // Выход из программы
} manager_command_t;

typedef struct
{
    // Параметры отрисовщика
    drawer_params_t         drawer_params;  // Параметры отрисовщика
    // Параметры операций над точками
    point_t                 center;         // Центр операций
    move_coefficients_t     move_params;    // Параметры переноса
    rotate_coefficients_t   rotation_angle; // Угол поворота
    scale_coefficients_t    scale_params;   // Параметры масштабирования
    const char              *filename;      // Имя файла с данными точек
} manager_params_t;

/**
 * @brief manage Обработчик запросов
 * @param params[in]    Параметры запроса
 * @param command[in]   Запрашиваемая команда
 * @return Код ошибки
 */
int manage(const manager_params_t &params, manager_command_t command);

#endif // MANAGER_H

#ifndef ERROR_H
#define ERROR_H

enum
{
    OK,                     // Успех
    ERR_SAME_POINT,         // Ошибка: точки совпадают
    ERR_PARALLEL_LINES,     // Ошибка: линии параллельны
    ERR_NULL_LINE_EQUATION, // Ошибка: уравнение прямой задано неверно (0х + 0y + c)
    ERR_INDEX_OUT_OF_RANGE, // Ошибка: индекс за пределами
    ERR_INCORRECT_TRIANGLE, // Ошибка: треугольник задан неверно
};

#endif // ERROR_H

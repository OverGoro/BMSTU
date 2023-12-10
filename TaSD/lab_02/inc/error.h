#ifndef ERROR_H__
#define ERROR_H__
enum
{
    ERR_OK, // Ошибок нет
    ERR_IO, // Ошибка ввода-вывода
    ERR_RANGE, // Ошибка: Неверный диапазон значений
    ERR_FILE, // Ошибка открытия файла
    ERR_EMPTY_ARR, // Ошибка: пустой массив
    ERR_MEMORY // Ошибка выделения памяти
};
#endif


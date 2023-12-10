#ifndef ERRORS_H__
#define ERRORS_H__

enum
{
    ERR_OK, // Ошибок нет
    ERR_IO, // Ошибка ввода/вывода
    ERR_RANGE, // Неверный диапазон данных
    ERR_OVERFLOW, // Переполнение массива
    ERR_ARGS_NUM, // Неправильное количество ключей вызова программы
    ERR_ARGS_VALUE, // Неправильное значение ключей вызова программы
    ERR_FILE, // Ошибка работы с файлом
    ERR_MEMORY, // Ошибка выделения памяти
    ERR_EMPTY_ARR // Пустой массив
};

#endif


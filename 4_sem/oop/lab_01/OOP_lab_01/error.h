#ifndef ERROR_H
#define ERROR_H

#include <errno.h>

enum
{
    OK,                 // Успешное завершение
    ERR_IO,             // Ошибка ввода/вывода
    ERR_RANGE,          // Ошибка диапазона данных
    ERR_FILE,           // Стандартная ошибка работы с файлом
    ERR_FILE_NOT_EXIST, // Файл не существует
    ERR_FILE_ACCESS,    // Нет доступа к файлу
    ERR_MEM,            // Ошибка работы с памятью
    ERR_UNKNOWN_COMMAND // Ошибка: неизвестная команда
};

int error_get_file_error();

#endif // ERROR_H

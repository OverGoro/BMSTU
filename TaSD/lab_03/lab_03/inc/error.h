#ifndef ERROR_H__
#define ERROR_H__

enum 
{
    ERR_OK, // Ошибок нет
    ERR_RANGE, // Ошибка диапазона данных
    ERR_IO, // Ошибка ввода-вывода
    ERR_EL_OVERWRITE, // Ошибка: по заданным координатам уже считывался элемент
    ERR_FILE, // Ошибка работы с файлом
    ERR_MEM, // Ошибка работы с дианамической памятью 
    ERR_EMPTY_ARR, // Пустой массив
};

#endif // !ERROR_H__

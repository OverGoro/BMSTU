#include "../headers/error.hpp"

void handle_rc(int rc)
{
    if (rc == OK)
        std::cout << "Операция завершена\n";
    else if (rc == ERR_IO)
        std::cout << "Ошибка ввода/вывода\n";
    else if (rc == ERR_FILE)
        std::cout << "Ошибка работы с файлом\n";
    else if (rc == ERR_RANGE)
        std::cout << "Ошибка диапазона данных\n";
    else if (rc == ERR_UNKNOWN_COMMAND)
        std::cout << "Ошибка: неизвестная команда\n";
    else
        std::cout << "Неизвестная ошибка\n";
};

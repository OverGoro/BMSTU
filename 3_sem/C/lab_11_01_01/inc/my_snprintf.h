#ifndef MY_SNPRINTF_H__

#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

/**
* @brief Аналог snprintf
*
* @param str_buffer[in, out] Буфер
* @param buffer_size[in] Размер буфера
* @param format[in] Форматная строка
* @param ... Параметры
*
* @return -1 или количество записанных байт
*/
int my_snprintf(char *str_buffer, size_t buffer_size, const char *format, ...);

#endif // !MY_SNPRINTF_H__


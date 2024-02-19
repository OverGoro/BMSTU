#include "my_snprintf.h"
#include <stdbool.h>

#define OCT_BASE 8
#define OCT_BUF_SIZE 7

/**
* @brief Запись строки в буфер
*
* @param str_buffer[in, out] Буфер
* @param buffer_size[in] Размер буфера
* @param s[in] Строка
* @param wrote_bytes[in, out] Количество записанных байт
*/
static void print_s(char *str_buffer, size_t buffer_size, const char *s, size_t *wrote_bytes)
{
    for (const char *cur_char = s; *cur_char != 0; cur_char++, (*wrote_bytes)++)
    {
        if (*wrote_bytes < buffer_size)
            str_buffer[*wrote_bytes] = *cur_char;
    }
}

/**
* @brief Запись unsigned short в восьмеричном виде в буфер
*
* @param str_buffer[in, out] Буфер
* @param buffer_size[in] Размер буфера
* @param num[in] Число
* @param wrote_bytes[in, out] Количество записанных байт
*/
static void print_ho(char *str_buffer, size_t buffer_size, unsigned short num, size_t *wrote_bytes)
{
    char buf[OCT_BUF_SIZE + 1];

    unsigned short tmp_num = num;
    size_t num_len = 0;

    do
    {
        num_len++;
        tmp_num /= OCT_BASE;
    } while (tmp_num > 0);

    buf[num_len] = 0;
    size_t cur_i = num_len - 1;
    do 
    {
        buf[cur_i] = '0' + num % OCT_BASE;
        num /= OCT_BASE;
        cur_i--;
    } while (num > 0);
    print_s(str_buffer, buffer_size, buf, wrote_bytes);
}

int my_snprintf(char *str_buffer, size_t buffer_size, const char *format, ...)
{
    if ((str_buffer == NULL && buffer_size != 0) || format == NULL)
        return -1;

    va_list vl;
    char *s;
    unsigned short num;
    size_t wrote_bytes = 0;

    bool right_spec = true;

    va_start(vl, format);
    for (const char *f_char = format; *f_char != 0 && right_spec; f_char++)
    {
        if (*f_char == '%')
        {
            if (*(++f_char) == 's')
            {
                s = va_arg(vl, char *);
                print_s(str_buffer, buffer_size, s, &wrote_bytes);
            }
            else if (*f_char == 'h' && *(++f_char) == 'o')
            {
                num = va_arg(vl, int);
                print_ho(str_buffer, buffer_size, num, &wrote_bytes);
            }
            else
                right_spec = false;
        }
        else if (wrote_bytes < buffer_size)
        {
            str_buffer[wrote_bytes] = *f_char;
            wrote_bytes++;
        }
        else
            wrote_bytes++;
    }
    va_end(vl);

    if (wrote_bytes < buffer_size)
    {
        str_buffer[wrote_bytes] = 0;
    }
    else if (buffer_size != 0)
    {
        str_buffer[buffer_size - 1] = 0;
    }

    if (!right_spec)
        return -1;

    return wrote_bytes;
}


#include "num.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
// Режимы ввод текущей части числа
enum {
    DIGITS_SIGN_MODE,  // Ввод знака числа
    INT_DIGITS_MODE,   // Ввод цифр целой части числа
    FLOAT_DIGITS_MODE, // Ввод цифр дробной части числа
    ORDER_SIGN_MODE,   // Ввод знака порядка
    ORDER_MODE         // Ввод цифр порядка
};



/**
* @brief Сортирует массиа в обратном порядке
*
* @param arr[out] массив
* @param n[in] число элементов
*/
void reverse_arr(int *arr, size_t n)
{
    int *left = arr;
    int *right = arr + (n - 1);
    while (left < right)
    {
        int tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
}

int num_read(FILE *f, float_num_t *pnum, int mode)
{
    size_t max_digits_len; // Максимальнная длина мантиссы числа
    if (mode == INTEGER_MODE)
        max_digits_len = INT_DIGITS_LEN;
    else if (mode == FLOAT_MODE)
        max_digits_len = FLOAT_DIGITS_LEN;
    else
        return ERR_MODE;

    // текущий символ
    char c;
    // Текущий режим ввода
    int input_mode = DIGITS_SIGN_MODE; 
    // Знак мантиссы
    pnum->digits_sign = true;
    // Знак порядка
    bool order_sign = true;

    // Вводились ли какие либо цифры в число
    // Необходимо для записи нуля
    bool digits_flag = false;

    // order_value - добавочный порядок числа
    // если были числа до запятой в числе, то order_value > 0
    // в противном случае - order_value < 0
    int order_value = 0;

    // Изначально число пустое
    pnum->digits_len = 0; 
    pnum->order = 0;

    while ((c = fgetc(f)) != '\n' && c != '\0')
    {
        // Переход в режим ввода дробной части числа
        if (c == '.' && mode == FLOAT_MODE)
        {
            if (input_mode != DIGITS_SIGN_MODE && input_mode != INT_DIGITS_MODE )
                return ERR_IO;
            input_mode = FLOAT_DIGITS_MODE;
        }
        // Переход в режим ввода порядка числа
        else if ((c == 'E' || c == 'e') && mode == FLOAT_MODE)
        {
            // Если уже стоит режим ввода порядка
            if (input_mode != DIGITS_SIGN_MODE 
                && input_mode != INT_DIGITS_MODE 
                && input_mode != FLOAT_DIGITS_MODE)
            {
                return ERR_IO;
            }
            // Если не вводились цифры в мантиссу
            else if (!digits_flag)
                return ERR_IO;
            input_mode = ORDER_SIGN_MODE;
        }
        // Ввод знака
        else if (c == '+' || c == '-')
        {
            // Ввод знака числа
            if (input_mode == DIGITS_SIGN_MODE)
            {
                pnum->digits_sign = c == '+';
                input_mode = INT_DIGITS_MODE;
            }
            // Ввод знака порядка
            else if (input_mode == ORDER_SIGN_MODE)
            {
                order_sign = c == '+';
                input_mode = ORDER_MODE;
            }
            else
                return ERR_IO;
        }
        // Ввод цифры
        else if (isdigit(c))
        {
            digits_flag = true;
            // Если режим ввода знака, изменить на ввод соответсвующего значения
            if (input_mode == DIGITS_SIGN_MODE)
            {
                input_mode = INT_DIGITS_MODE;
            }
            else if(input_mode == ORDER_SIGN_MODE)
                input_mode = ORDER_MODE;

            // Ввод целой части числа
            // Если число уже имеет цифры или текущая цифра отлична от нуля, чтобы не хранить незначащие нули 
            if (input_mode == INT_DIGITS_MODE && (pnum->digits_len != 0 || c != '0')  && pnum->digits_len < max_digits_len)
            {
                pnum->digits[pnum->digits_len] = c - '0';
                pnum->digits_len++;
                order_value++;
            }
            // Ввод дробной части числа
            // Если не были введены цифры != 0 до текущего 0 в дробной части, уменьшать порядок без записи 0
            // Для ввода чисел аналогичных 0.00001, .0001, .003 e 2...
            else if (c == '0' && input_mode == FLOAT_DIGITS_MODE && pnum->digits_len == 0)
            {
                order_value--;
            }
            // Ввод дробной части числа
            else if (input_mode == FLOAT_DIGITS_MODE && pnum->digits_len < max_digits_len)
            {
                pnum->digits[pnum->digits_len] = c - '0';
                (pnum->digits_len)++;
            }
            // Ввод порядка числа
            else if (input_mode == ORDER_MODE)
            {
                pnum->order = pnum->order * 10 + c - '0';
                if (abs(pnum->order) > MAX_ORDER)
                    return ERR_ORDER_DIGITS;
            }
            // Если количество цифр в числе не 0, то произошла ошика переполнения
            else if (pnum->digits_len != 0)
            {
                return ERR_DIGITS_NUM;
            }
        }
        // Если введеден не пробел
        else if (!isspace(c))
        {
            return ERR_IO;
        }
    }
    // Если начался ввод порядка и не были введены цифры
    if (input_mode == ORDER_SIGN_MODE)
        return ERR_IO;

    // Если в число были введены только нули
    if (pnum->digits_len == 0 && digits_flag)
    {
        pnum->digits_len = 1;
        pnum->digits[0] = 0;
        pnum->order = 0;
        return ERR_OK;
    }
    // Если мантиссы не введено
    if (pnum->digits_len == 0)
        return ERR_IO;

    // Если вводился отрицательный порядок
    if (!order_sign)
        (pnum->order) *= -1;

    // Добавление порядка числа и проверка на переполнение порядка
    if (abs(pnum->order += order_value) > MAX_ORDER + (int)max_digits_len)
        return ERR_RANGE;
    // Очистка незначащих нулей
    for (int *i = &pnum->digits[pnum->digits_len - 1]; i > pnum->digits && *i == 0; i--)
    {
        (pnum->digits_len)--;
    }

    // Число считано правильно
    reverse_arr(pnum->digits, pnum->digits_len);
    return ERR_OK;
}

void print_num(FILE *f, const float_num_t *pnum)
{
    if (!(pnum->digits_sign))
        fprintf(f, "-");
    fprintf(f, "0.");
    for (int i = pnum->digits_len - 1; i >= 0; i--)
    {
        fprintf(f, "%d",  pnum->digits[i]);
    }
    if (pnum->order)
    {
        fprintf(f, " E %d", pnum->order); 
    }
    fprintf(f, "\n");
}


/**
* @brief Округляет на 1 знак
*
* @param digits[in, out] Мантисса
* @param digits_len[in] Длина мантиссы
*/
void move_nums(int *digits, int digits_len)
{
    if (digits_len > 1)
    {
        if (digits[0] >= 5)
            digits[1]++;
        // Сдвиг
        for (int i = 1; i < digits_len; i++)
        {
            digits[i] += digits[i - 1] / 10;
            digits[i - 1] = digits[i] % 10;
        }
        digits[digits_len - 1] = digits[digits_len - 2] / 10;
    }
}

int multiply_nums(const float_num_t *num_1, const float_num_t *num_2, float_num_t *num_r)
{

    num_r->order = 0;

    num_r->digits_len = 0;
    num_r->digits_sign = true;
    for (size_t i = 0; i < FLOAT_DIGITS_LEN; i++)
        num_r->digits[i] = 0;

    int digits_r[FLOAT_DIGITS_LEN + INT_DIGITS_LEN + 2];
    for (size_t i = 0; i < FLOAT_DIGITS_LEN + INT_DIGITS_LEN + 2; i++)
        digits_r[i] = 0;

    size_t digits_r_len = 0;
    size_t start_i = 0;
    int tmp = 0; // Для переноса при умножении
    
    // Вычисление полной мантиссы произведения
    for (size_t i_2 = 0; i_2 < num_2->digits_len; i_2++)
    {
        tmp = 0;
        for (size_t i_1 = 0; i_1 < num_1->digits_len; i_1++)
        {
            int num_r_digit = digits_r[start_i + i_1];
            digits_r[start_i + i_1] = (num_r_digit + num_1->digits[i_1] * num_2->digits[i_2] + tmp) % 10;
            tmp = (num_r_digit + num_1->digits[i_1] * num_2->digits[i_2] + tmp) / 10;
            if (start_i + i_1 + 1 > digits_r_len)
            {
                num_r->order++;
                digits_r_len = start_i + i_1 + 1 > digits_r_len ? start_i + i_1 + 1 : digits_r_len;
            }
        }
        while (tmp > 0)
        {
            for (size_t i = digits_r_len; i < FLOAT_DIGITS_LEN + INT_DIGITS_LEN + 2 && tmp > 0; i++)
            {
                int num_r_digit = digits_r[i];
                digits_r[i] = (num_r_digit + tmp) % 10;
                tmp = (num_r_digit + tmp) / 10;
                digits_r_len++;
                num_r->order++;
            }
        }
        start_i++;
    }
    
    // Очистка незначащих нулей
    for (size_t i = digits_r_len - 1; i > 0 && digits_r[i] == 0; i--)
        (digits_r_len)--;
    // Преобразование нулей на конце
    while (digits_r_len > 1 && digits_r[0] == 0)
    {
        move_nums(digits_r, digits_r_len);
        (digits_r_len)--;
        (num_r->order)++;
    }
    // Если 0
    if (digits_r_len == 1 && digits_r[0] == 0)
    {
        num_r->digits_len = 1;
        num_r->digits[0] = 0;
        num_r->order = 0;
        num_r->digits_sign = true;
        return ERR_OK;
    }
    // Запись мантиссы в num_r (в обратном порядке)
    int i = 0;
    for (i = digits_r_len - 1; i >= 0 && num_r->digits_len < RESULT_DIGITS_LEN; i--)
    {
        num_r->digits[num_r->digits_len] = digits_r[i];
        num_r->digits_len++;
    }
    // Разворот мантиссы в num_r
    for (int i_r = num_r->digits_len - 1; i_r >= (int)num_r->digits_len / 2; i_r--)
    {
        int r_digit = num_r->digits[i_r];
        num_r->digits[i_r] = num_r->digits[num_r->digits_len - i_r - 1];
        num_r->digits[num_r->digits_len - i_r - 1] = r_digit;
    }
    // Если полная мантисса записалась в num_r не полностью
    if (i >= 0)
    {
        tmp = digits_r[i];
        if (tmp >= 5)
            num_r->digits[0]++;
        int tmp = num_r->digits[0] / 10;
        for (size_t i_m = 1; i_m < num_r->digits_len; i_m++)
        {
            int r_digit = num_r->digits[i_m];
            num_r->digits[i_m] = (r_digit  + tmp) % 10;
            tmp = (r_digit + tmp) / 10;
        }
        if (tmp > 0)
        {
            move_nums(num_r->digits, num_r->digits_len);
            num_r->digits[num_r->digits_len - 1] = tmp;
            (num_r->order)++;
        }
    }
    while (num_r->digits_len > 1 && num_r->digits[0] == 0)
    {
        move_nums(num_r->digits, num_r->digits_len);
        (num_r->digits_len)--;
    }

    num_r->order +=  num_1->order + num_2->order - num_1->digits_len - num_2->digits_len;
    if (abs(num_r->order) > MAX_ORDER)
        return ERR_RANGE;
    num_r->digits_sign = (num_1->digits_sign == num_2->digits_sign);
    return ERR_OK;
}


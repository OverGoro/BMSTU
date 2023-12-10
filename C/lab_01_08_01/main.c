// Городский Юрий ИУ7-22Б
// Упаковка 4 байт в 1 число и распаковка их обратно
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define UINT32_BIT ((int)sizeof(uint32_t) * CHAR_BIT)

// Вывод числа в двоичном виде
// num - выводимое число
void print_bin(uint32_t num)
{
    for (int i = 0; i < UINT32_BIT; i++)
    {
        // num >> (UINT32_BIT - i - 1) - сдвиг числа так, что текущий бит становится последним
        // & 1 - получение значения последнего бита
        printf("%d", (num >> (UINT32_BIT - i - 1)) & 1);
    }
    printf("\n");
}

// Упаковка 4 байт в одно число
// num_1, num_2, num_3, num_4 - входные байты
uint32_t pack(uint8_t num_1, uint8_t num_2, uint8_t num_3, uint8_t num_4)
{
    uint32_t p_num_1, p_num_2, p_num_3, p_num_4;
    uint32_t packed_num;

    p_num_1 = num_1;
    p_num_2 = num_2;
    p_num_3 = num_3;
    p_num_4 = num_4;

    p_num_1 <<= 3 * CHAR_BIT;
    p_num_2 <<= 2 * CHAR_BIT;
    p_num_3 <<= 1 * CHAR_BIT;
    packed_num = p_num_1 + p_num_2 + p_num_3 + p_num_4;
    return packed_num;
}

// Распаковка числа в 4 байта
// num - число
// byte_num - номер байта для извлечения
uint8_t unpack(uint32_t num, uint8_t byte_num)
{
    int right_bytes_num;
    uint8_t u_num;

    right_bytes_num = sizeof(num) - byte_num;
    num >>= right_bytes_num * CHAR_BIT;
    u_num = num;

    return u_num;
}

int main(void)
{
    uint8_t num_1, num_2, num_3, num_4; // 4 байта с числами
    uint32_t packed_num; // Запакованное число
    uint8_t u_num_1, u_num_2, u_num_3, u_num_4; // Распакованные из числа 4 байта

    printf("Enter four bytes: ");
    if (scanf("%"SCNu8"%"SCNu8"%"SCNu8"%"SCNu8"", &num_1, &num_2, &num_3, &num_4) != 4)
    {
        printf("Error: input error\n");
        return ERR_IO;
    }

    packed_num = pack(num_1, num_2, num_3, num_4);

    u_num_1 = unpack(packed_num, 1);
    u_num_2 = unpack(packed_num, 2);
    u_num_3 = unpack(packed_num, 3);
    u_num_4 = unpack(packed_num, 4);

    printf("Result: ");
    print_bin(packed_num);

    printf("%"PRIu8"\n", u_num_1);
    printf("%"PRIu8"\n", u_num_2);
    printf("%"PRIu8"\n", u_num_3);
    printf("%"PRIu8"\n", u_num_4);

    return OK;
}


// Городский Юрий ИУ7-22Б
// Определение номера подъезда и этажа по номеру квартиры
#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define APARTMENTS_IN_ENTRANCE 36
#define APARTMENTS_ON_FLOOR 4
int main(void)
{
    int apartment;
    int entrance, floor;
    
    // Ввод
    printf("Input apartment num: ");
    scanf("%d", &apartment);
    // Определение подъезда
    entrance = (apartment - 1) / APARTMENTS_IN_ENTRANCE + 1;
    // Определение этажа
    floor = ((apartment - 1) - (entrance - 1) * APARTMENTS_IN_ENTRANCE) / APARTMENTS_ON_FLOOR + 1;

    printf("%d\n%d\n", entrance, floor);
    return OK;
}


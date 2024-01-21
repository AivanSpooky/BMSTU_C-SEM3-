#include <stdio.h>
#include <math.h>

#define OK 0
#define FLOORS 9
#define FLATS_PER_FLOOR 4

int main(void)
{
    int flat_num;
    
    printf("Введите номер квартиры:\n");
    scanf("%d", &flat_num);

    int entrance = ((flat_num - 1) / (FLOORS * FLATS_PER_FLOOR)) + 1;
    int floor = ((flat_num - (entrance - 1) * (FLOORS * FLATS_PER_FLOOR) - 1) / FLATS_PER_FLOOR) + 1;

    printf("Номер подъезда = %d \nЭтаж = %d \n", entrance, floor);

    return OK;
}
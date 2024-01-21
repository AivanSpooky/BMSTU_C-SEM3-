#include <stdio.h>
#include <math.h>

#define OK 0

int main(void)
{
    double v1, t1;
    double v2, t2;
    
    printf("Введите V1, T1, V2, T2:\n");

    scanf("%lf%lf%lf%lf", &v1, &t1, &v2, &t2);

    double v = v1 + v2;
    double t = (v1 * t1 + v2 * t2) / (v1 + v2);

    printf("Общий объем V = %f \nТемпература T = %f \n", v, t);

    return OK;
}
#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_WRONG_INPUT 2

double func_f(double x)
{
    return 1 / (sqrt(1 - (x * x)));
}

double func_s(double x, double eps)
{
    double n = 1;
    double x_n = 1;
    double result = 1;

    while (fabs(x_n) >= eps)
    {
        x_n *= n * x * x / (n + 1);
        n += 2;
        result += x_n;
    }
    return result;
}



int main(void)
{
    double x, eps;
    double func_real, func_eps, abs_err, rel_err;
    
    printf("Введите x и точность: \n");
    if (scanf("%lf%lf", &x, &eps) != 2)
    {
        printf("Неверный ввод!");
        return ERR_IO;
    }
    else if (eps <= 0 || eps > 1 || x >= 1 || x <= -1)
    {
        printf("Данные введены неверно!");
        return ERR_WRONG_INPUT;
    }

    func_real = func_f(x);
    func_eps = func_s(x, eps);
    abs_err = fabs(func_real - func_eps);
    rel_err = abs_err / fabs(func_real);

    printf("%f\n%f\n%f\n%f\n", func_real, func_eps, abs_err, rel_err);

    return OK;
}
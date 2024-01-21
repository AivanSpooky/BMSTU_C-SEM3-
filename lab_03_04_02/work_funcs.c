#include "work_funcs.h"

int find_num(int a[][M], size_t a_n, int *number)
{
    bool found = false;
    int max_elem;
    for (size_t i = 0; i < a_n; i++)
    {
        // начинаем счетчик j c (a_n - i), а не с (), т. к. мы не учитываем элементы, находящиеся
        // на самой побочной диагонали
        for (size_t j = (a_n - i); j < a_n; j++)
        {
            if ((a[i][j] % 10 == 5) || (a[i][j] % 10 == -5))
            {
                if (found == false)
                {
                    max_elem = a[i][j];
                    found = true;
                }
                if (a[i][j] > max_elem)
                {
                    max_elem = a[i][j];
                }
            }
        }
    }
    if (found == false)
        return ERR_NO_NUM;
    (*number) = max_elem;
    return OK;
}

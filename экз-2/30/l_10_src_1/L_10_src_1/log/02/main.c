#include <stdio.h>
#include "log.h"

void func_1(void)
{
    fprintf(log_get(), "func_1\n");
}

void func_2(int a)
{
    fprintf(log_get(), "func_2(%d)\n", a);
}

int main(void)
{
    if(log_init("test.log"))
    {
        fprintf(stderr, "Could not create log file\n");
        return -1;
    }

    func_1();
    func_2(5);

    log_close();

    return 0;
}

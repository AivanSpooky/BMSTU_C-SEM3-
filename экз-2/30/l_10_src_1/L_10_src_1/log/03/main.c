#include <stdio.h>
#include "log.h"

void func_1(void)
{
    log_message("%s\n", "func_1");
}

void func_2(int a)
{
    log_message("%s(%d)\n", "func_2", a);
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

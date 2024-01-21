#include <stdio.h>
#include <stddef.h>

struct inner
{
    int i;
    double d;
};

struct outer
{
    char c;
    int i;
    struct inner in;
    float f;
};

int main(void)
{
    struct outer out = {'a', 1, {2, 3.0}, 4.0};

    struct inner *pin = &out.in;
    struct outer *pout = NULL;

    long offset = (long) (&((struct outer*) 0)->in);

    printf("offset is %ld\n", offset);

    pout = (struct outer*) ((char*) pin - offset);

    printf("out %p, pout %p\n", &out, pout);

    pout = (struct outer*) ((char*) pin - offsetof(struct outer, in));

    printf("out %p, pout %p\n", &out, pout);

    return 0;
}

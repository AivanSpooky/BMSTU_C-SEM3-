#ifndef __PRODUCT_T_H__

#define __PRODUCT_T_H__

#include <stdint.h>
#include <stdio.h>

#include "consts.h"
#include "err_codes.h"

typedef struct
{
    char name[MAX_NAME_LEN];
    char manuf[MAX_MANUF_LEN];
    uint32_t price;
    uint32_t count;
} product_t;

int read_product(FILE *file, product_t *product);

#endif

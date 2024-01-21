#include "product_t.h"
#include <string.h>

int read_product(FILE *file, product_t *product)
{
    char name[MAX_NAME_LEN + 1];
    char manuf[MAX_MANUF_LEN + 1];
    uint32_t price;
    uint32_t count;

    char tmp[2];

    size_t len;

    if (!fgets(name, sizeof(name), file))
    {
        return ERR_FILE_READ;
    }
    len = strlen(name);
    if (name[len - 1] == '\n')
        name[--len] = '\0';
    if (!len || len >= MAX_NAME_LEN)
        return ERR_FILE_RANGE;
    
    if (!fgets(manuf, sizeof(manuf), file))
    {
        return ERR_FILE_READ;
    }
    len = strlen(manuf);
    if (manuf[len - 1] == '\n')
        manuf[--len] = '\0';
    if (!len || len >= MAX_MANUF_LEN)
        return ERR_FILE_RANGE;

    if (fscanf(file, "%u", &price) != ARG_READ)
        return ERR_DATA;
    if (fscanf(file, "%u", &count) != ARG_READ)
        return ERR_DATA;
    
    fgets(tmp, sizeof(tmp), file);

    strcpy(product->name, name);
    strcpy(product->manuf, manuf);
    product->price = price;
    product->count = count;
    return OK;
}

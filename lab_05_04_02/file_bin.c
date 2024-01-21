#include "file_bin.h"

void get_product_by_pos(FILE *file, size_t pos, product_t *product)
{
    pos *= sizeof(product_t);
    fseek(file, pos, SEEK_SET);
    fread(product, sizeof(product_t), 1, file);
}

void put_product_to_pos(FILE *file, size_t pos, product_t product)
{
    pos *= sizeof(product_t);
    fseek(file, pos, SEEK_SET);
    fwrite(&product, sizeof(product_t), 1, file);
}

int input_string(char *str, size_t max_len)
{
    char buf[MAX_NAME_LEN + 1];
    //buf[0] = '\0';
    //fprintf(stderr, "%zu\n", max_len);
    if (! fgets(buf, sizeof(buf), stdin))
        return ERR_DATA;
    size_t len = strlen(buf);
    //fprintf(stderr, "%zu\n", len);
    if (len > 0 && len < max_len && buf[len - 1] == '\n')
    {
        buf[len - 1] = '\0';
        len--;
    }
    else
        return ERR_DATA;
    strncpy(str, buf, max_len);
    return OK;
}


int add_product(FILE *file, size_t count)
{
    //printf("Enter information about the new product:\n");

    //printf("Name: ")
    //char tmp[2];
    product_t product;
    memset(&product, 0, sizeof(product_t));
    //fprintf(stderr, "1\n");
    if (input_string(product.name, MAX_NAME_LEN) != OK)
        return ERR_DATA;
    //fprintf(stderr, "1\n");
    //fgets(tmp, sizeof(tmp), file);
    //fprintf(stderr, "%s\n", product.name);
    if (input_string(product.manuf, MAX_MANUF_LEN) != OK)
        return ERR_DATA;
    //fprintf(stderr, "1\n");
    //fgets(tmp, sizeof(tmp), file);
    //fprintf(stderr, "%s\n", product.manuf);
    int price = 0;
    int cnt = 0;
    if (scanf("%d", &price) != ARG_READ)
        return ERR_DATA;
    if (price < 0)
        return ERR_DATA;
    //fprintf(stderr, "%u\n", product.price);
    if (scanf("%d", &cnt) != ARG_READ)
        return ERR_DATA;

    if (cnt < 0)
        return ERR_DATA;
    product.price = price;
    product.count = cnt;
    //fgets(tmp, sizeof(tmp), stdin);
    //fprintf(stderr, "1\n");
    //fprintf(stderr, "lmao\n");
    //rewind(file);
    size_t pos = 0;
    product_t product_tmp;
    memset(&product_tmp, 0, sizeof(product_t));
    for (size_t i = 0; i < count; i++)
    {
        get_product_by_pos(file, pos, &product_tmp);
        if ((product.price > product_tmp.price) || (product.price == product_tmp.price && product.count > product_tmp.count))
            break;
        pos++;
    }
    if (count != 0)
    {
        // Поставил тип int, так как цикл зацикливается, если в файле был изначально 1 элемент
        for (int i = (int)(count - 1); i >= (int)pos; i--)
        {
            get_product_by_pos(file, i, &product_tmp);
            put_product_to_pos(file, i + 1, product_tmp);
        }
    }
    put_product_to_pos(file, pos, product);
    return OK;
}

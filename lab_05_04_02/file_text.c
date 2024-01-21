#include "file_text.h"

// int get_line_to_data(FILE *file, char *line, size_t len)
// {
//     if (fgets(line, sizeof(line), file) == NULL)
//         return ERR_FILE;
//     size_t lenth = strlen(line);
    
//     // else
//     // {
//     //     size_t line_len = strlen(line);
        
//     //     if (line_len && line[line_len - 1] == '\n')
//     //     {
//     //         line[line_len - 1] = '\0';
//     //         line_len--;
//     //     }
//     // }
//     return OK;
// }

int fill_parray(FILE *file, product_t *products, size_t *cnt)
{
    rewind(file);

    (*cnt) = 0;
    product_t product;
    while (read_product(file, &product) == OK)
    {
        products[(*cnt)++] = product; 
    }
    if ((*cnt) == 0)
        return ERR_FILE_RANGE;
    // rewind(file);
    // size_t tmp_n = 0;

    // char tmp[2];
    // while (get_line_to_data(file, products[tmp_n].name, MAX_NAME_LEN) == OK)
    // {
    //     if (get_line_to_data(file, products[tmp_n].manuf, MAX_MANUF_LEN) != OK)
    //         return ERR_DATA;
    //     if (fscanf(file, "%" SCNu32, &products[tmp_n].price) != ARG_READ)
    //         return ERR_DATA;
    //     if (fscanf(file, "%" SCNu32, &products[tmp_n].count) != ARG_READ)
    //         return ERR_DATA;
    //     fgets(tmp, sizeof(tmp), file);

    //     tmp_n++;
    // }
    // if (tmp_n == 0)
    //     return ERR_FILE_RANGE;
    // (*cnt) = tmp_n;
    return OK;
}

bool check_end(char *name, char *substr)
{
    int len_name = strlen(name) - 1;
    int len_substr = strlen(substr) - 1;
    if (len_substr > len_name)
        return false;
    while (len_substr >= 0)
    {
        //fprintf(stderr, "%c %c\n", name[len_name], substr[len_substr]);
        if (name[len_name] != substr[len_substr])
            return false;
        len_name--;
        len_substr--;
    }
    return true;
    // size_t len = strlen(name);
    // char *real_end = (name + len) - strlen(substr);
    // // char *name_end = name;
    // // while ((size_t)((name + len) - name_end) > strlen(substr))
    // // {
    // //     name_end++;
    // // }
    // if (strcoll(real_end, substr) == 0)
    // {
    //     //fprintf(stderr, "%s|%s|%s\n", name_end, real_end, substr);
    //     return true;
    // }
    // return false;
}

int print_products(product_t *products, size_t count, char *substr)
{
    //printf("Products whose name ends with '%s':\n", substr);
    int rc = ERR_DATA;
    for (size_t i = 0; i < count; i++)
    {
        //fprintf(stderr, "%s|%s|\n", strstr(products[i].name, substr), products[i].name + strlen(products[i].name) - strlen(substr));
        //fprintf(stderr, "%d\n", check_end(products[i].name, substr));
        if (check_end(products[i].name, substr) == true)
        {
            fprintf(stdout, "%s\n%s\n", products[i].name, products[i].manuf);
            fprintf(stdout, "%" PRIu32 "\n%" PRIu32 "\n", products[i].price, products[i].count);
            rc = OK;
        }
    }
    return rc;
}

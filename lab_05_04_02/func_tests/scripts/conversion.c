#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../product_t.h"

void binary_to_text(const char *binary_filename, const char *text_filename)
{
    FILE *binary_file = fopen(binary_filename, "rb");
    if (binary_file == NULL)
    {
        printf("Failed to open binary file %s for reading\n", binary_filename);
        return;
    }

    FILE *text_file = fopen(text_filename, "w");
    if (text_file == NULL)
    {
        printf("Failed to open text file %s for writing\n", text_filename);
        fclose(binary_file);
        return;
    }

    product_t product;
    while (fread(&product, sizeof(product_t), 1, binary_file) != 0)
    {
        fprintf(text_file, "%s %s %u %u\n", product.name, product.manuf, product.price, product.count);
    }

    //printf("Binary file %s converted to text file %s\n", binary_filename, text_filename);
    fclose(binary_file);
    fclose(text_file);
}

void text_to_binary(const char *text_filename, const char *binary_filename)
{
    FILE *text_file = fopen(text_filename, "r");
    if (text_file == NULL)
    {
        printf("Failed to open text file %s for reading\n", text_filename);
        return;
    }

    FILE *binary_file = fopen(binary_filename, "wb");
    if (binary_file == NULL)
    {
        printf("Failed to open binary file %s for writing\n", binary_filename);
        fclose(text_file);
        return;
    }

    char name[MAX_NAME_LEN];
    char manufacturer[MAX_MANUF_LEN];
    uint32_t price;
    uint32_t quantity;
    while (fscanf(text_file, "%s %s %u %u\n", name, manufacturer, &price, &quantity) == 4)
    {
        product_t product;
        strncpy(product.name, name, MAX_NAME_LEN);
        strncpy(product.manuf, manufacturer, MAX_MANUF_LEN);
        product.price = price;
        product.count = quantity;

        fwrite(&product, sizeof(product_t), 1, binary_file);
    }

    //printf("Text file %s converted to binary file %s\n", text_filename, binary_filename);
    fclose(text_file);
    fclose(binary_file);
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("cnv.exe [b2t|t2b] [input filename] [output filename]\n");
        return 1;
    }

    char *mode = argv[1];
    char *input_filename = argv[2];
    char *output_filename = argv[3];

    if (strcmp(mode, "b2t") == 0)
    {
        binary_to_text(input_filename, output_filename);
    }
    else if (strcmp(mode, "t2b") == 0)
    {
        text_to_binary(input_filename, output_filename);
    }
    else
    {
        printf("Invalid mode. Must be 'b2t' or 't2b'.\n");
        return 1;
    }

    return 0;
}
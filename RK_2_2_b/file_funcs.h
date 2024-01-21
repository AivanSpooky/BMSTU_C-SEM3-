#ifndef __FILE_FUNCS_H__
#define __FILE_FUNCS_H__

#include <stdio.h>

#include "consts.h"
#include "err_codes.h"

int fill_file(FILE *file);

int print_file(FILE *file);

int union_files(FILE *file1, FILE *file2);

#endif

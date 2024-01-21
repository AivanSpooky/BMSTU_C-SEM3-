#ifndef CHECK_SORT_H__

#define CHECK_SORT_H__

#include <check.h>

Suite *sort_suite(void);

typedef void (*asserttype)(void *l, void *r);

#endif
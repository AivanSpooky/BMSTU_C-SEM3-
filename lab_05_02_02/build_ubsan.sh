#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=undefined -fno-omit-frame-pointer -g main.c work_funcs.c -o app.exe

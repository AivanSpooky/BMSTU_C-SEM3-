#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wvla -c ./*.c

gcc -o app.exe ./*.o -lm

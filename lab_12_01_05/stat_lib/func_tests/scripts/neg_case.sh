#!/bin/bash

if [ $# -ne 4 ]; then
	exit 1
fi

ok="0"
fail="1"
fail_val="123"

bin_file=$1
args_test=$2

mode=$3
val=$4

tmp_out="tmp_out.txt"
command="./app.exe "

if [ $# -eq 4 ]; then
	command="$command $(cat "$args_test")"
fi

if [[ $mode != "b" ]]; then
    if [[ $val -eq 1 ]]; then
        valgrind --leak-check=full --error-exitcode=123 $command > "tmp_out.txt" 2>&1
        if [ $? -eq 123 ]; then
            exit "$fail_val"
        fi
    fi
    $command > "$tmp_out"
    error="$?"
    if [[ $error -ne 0 ]]; then
        exit "$fail"
    fi
else
    $command < "$bin_file"
    error="$?"
    if [[ $error -ne 0 ]]; then
        exit "$fail"
    fi
fi

exit "$ok"

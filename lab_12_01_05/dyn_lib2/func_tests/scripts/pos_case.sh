#!/bin/bash

ok="0"
fail="1"
fail_val="123"

if [ $# -ne 6 ]; then
	exit "$fail"
fi

bin_file=$1

out_test=$2
args_test=$3

mode=$4
number=$5
val=$6

command="./app.exe "

if [ $# -eq 6 ]; then
	command="$command $(cat "$args_test")"
fi

if [[ $mode == "t" ]]; then
    if [ $val -eq 1 ]; then
        valgrind --leak-check=yes --error-exitcode=1 $command > "tmp_out.txt" 2>&1
        if [ $? -ne 0 ]; then
            exit "$fail_val"
        fi
    fi
    $command
    tmp_out="func_tests/data/pos_""$number""_tmpout.txt"
    error="$?"
    if [[ $error -ne 0 ]]; then
        exit "$fail"
    fi
    #
    ./func_tests/scripts/comparator.sh "$tmp_out" "$out_test"
    return_code="$?"
    rm "$tmp_out"
elif [[ $mode == "b" ]]; then
    $command < "$bin_file"
    error="$?"
    if [[ $error -ne 0 ]]; then
        exit "$fail"
    fi
    text_out="bin_out.txt"
    ./cnv.exe "b2t" """$bin_file"".tmp" "$text_out"
    ./func_tests/scripts/comparator.sh "$text_out" "$out_test"
    return_code="$?"
else
    exit "$fail"
fi


if [[ return_code -eq 0 ]]; then
    exit "$ok"
else
    exit "$fail"
fi

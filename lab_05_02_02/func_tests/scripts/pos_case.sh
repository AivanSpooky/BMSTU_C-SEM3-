#!/bin/bash

ok="0"
fail="1"

if [ $# -ne 3 ]; then
	exit "$fail"
fi

out_test=$2
args_test=$3

tmp_out="tmp_out.txt"
command="../../app.exe "

if [ $# -eq 3 ]; then
	command="$command $(cat "$args_test")"
fi

$command > "$tmp_out"
error="$?"

if [[ $error -ne 0 ]]; then
    exit "$fail"
fi

./comparator.sh "$tmp_out" "$out_test"
return_code="$?"

if [[ return_code -eq 0 ]]; then
    exit "$ok"
else
    exit "$fail"
fi

#!/bin/bash

if [ $# -ne 2 ]; then
	exit 1
fi

ok="0"
fail="1"
args_test=$2

tmp_out="tmp_out.txt"
command="../../app.exe "

if [ $# -eq 2 ]; then
	command="$command $(cat "$args_test")"
fi

$command > "$tmp_out"
error="$?"

if [[ $error -ne 0 ]]; then
    exit "$ok"
else
    exit "$fail"
fi

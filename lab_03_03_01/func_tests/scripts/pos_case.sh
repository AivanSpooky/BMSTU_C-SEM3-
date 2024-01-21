#!/bin/bash

ok="0"
fail="1"

if [ $# -ne 2 ]; then
	exit "$fail"
fi

in_test=$1
out_test=$2
tmp_out="tmp_out.txt"
command="../../app.exe"

$command < "$in_test" > "$tmp_out"
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

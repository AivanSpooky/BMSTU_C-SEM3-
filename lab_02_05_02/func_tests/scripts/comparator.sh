#!/bin/bash

if [ $# -ne 2 ]; then
    exit 1
fi

f1=$1
f2=$2


mask="[0-9]+"


clean_out_prog=$(grep -Eo "$mask" "$f1")
clean_out_test=$(grep -Eo "$mask" "$f2")

if [ "$clean_out_prog" != "$clean_out_test" ]; then
    exit 1
fi

exit 0

#!/bin/bash

cd ./func_tests/scripts/ || exit 1
mode="b"
./func_tests.sh "$mode"
cd ../../

#!/bin/bash

test_ok="0"
files_count=0
count_errors=0

files="../data/pos_??_in.txt"
for file_in in $files; do
	if [ -f "$file_in" ]; then
		number=$(echo "$file_in" | grep -o "[0-9]*")
	else
		echo "No positive tests"
		continue
	fi
	number=$(echo "$file_in" | grep -o "[0-9]*")

	file_out="../data/pos_""$number""_out.txt"

	if [ -f "$file_out" ]; then
		./pos_case.sh "$file_in" "$file_out"
        error="$?"
	else
		echo "pos_""$number""_in"": FAIL (No Output File)"
		count_errors=$((count_errors + 1))
		files_count=$((files_count + 1))
		continue
	fi

	if [ "$error" -eq "$test_ok" ]; then
		echo "pos_""$number""_in"": PASS"
	else
		echo "pos_""$number""_in"": FAIL"
		count_errors=$((count_errors + 1))
	fi
	files_count=$((files_count + 1))
done

echo
files="../data/neg_??_in.txt"
for file_in in $files; do
	if [ -f "$file_in" ]; then
		number=$(echo "$file_in" | grep -o "[0-9]*")
	else
		echo "No negative tests"
		continue
	fi
	
    ./neg_case.sh "$file_in"
    error="$?"

	if [ "$error" -eq "$test_ok" ]; then
		echo "neg_""$number""_in"": PASS"
	else
		echo "neg_""$number""_in"": FAIL"
		count_errors=$((count_errors + 1))
	fi
	files_count=$((files_count + 1))
done

percentage=$(echo "scale=9; ($files_count-$count_errors)/$files_count*100" | bc )
echo
echo "Tests passed (in %): "
echo "$percentage" | awk '{printf "%.0f\n",$1}'
exit "$count_errors"

#!/bin/bash

str=""
str21=""

result() {
    if [ "$str" == "$str21" ]
    then
	    echo 'Success!'
    else
	    echo 'Fail!'
    fi
}

file_1="test_1.txt"
file_2="test_2.txt"

echo -ne 'test   : '
str=$(cat $file_1 $file_2)
str21=$(./my_cat $file_1 $file_2)
result

for flag in -b -e -n -s -t -v; do
    echo -ne 'test '$flag': '
    str=$(cat $flag $file_1 $file_2)
    str21=$(./my_cat $flag $file_1 $file_2)
    result
done

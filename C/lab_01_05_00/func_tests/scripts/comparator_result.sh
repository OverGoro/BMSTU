#!/bin/bash
if [ $# -ne 2 ]
then
    exit 2
fi

# Cодержимое двух файлов
file1=$(cat "$1")
file2=$(cat "$2")

# Текст после "Result: "
result1=${file1//*Result: /}
result2=${file2//*Result: /}

# Сравниваем содержимое двух файлов
if [[ "$result1" == "$result2" ]]
then
    exit 0
else
    exit 1
fi

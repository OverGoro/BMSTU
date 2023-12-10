#!/bin/bash

# Корректность вызова
if [ $# -ne 2 ]
then
    exit 1
fi

real_out=$1 # Файл с выходнами данными программы
expected_out=$2 # Файл с ожидаемыми выходными данными

sed -i '0,/^Result: / s///' "$real_out"
sed -i '0,/^Result: / s///' "$expected_out"
if ! cmp -s "$real_out" "$expected_out"
then
    exit 1
fi

exit 0

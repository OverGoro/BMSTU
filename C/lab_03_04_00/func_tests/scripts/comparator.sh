#!/bin/bash

# Корректность вызова
if [ $# -ne 2 ]
then
    exit 1
fi

real_out=$1 # Файл с выходнами данными программы
expected_out=$2 # Файл с ожидаемыми выходными данными

# Маска для вычленения информации из всего вывода
data_mask="[+-]?[0-9][0-9]*.?[0-9]*"

data_real_out=$(grep -Eo "$data_mask" "$real_out"  | sed 's/^[ \t\n]*//;s/[ \t\n]*$//')
data_expected_out=$(grep -Eo "$data_mask" "$expected_out"  | sed 's/^[ \t\n]*//;s/[ \t\n]*$//')
if [ "$data_expected_out" != "$data_real_out" ]
then
    exit 1
fi
exit 0
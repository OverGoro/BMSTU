#!/bin/bash

# Корректность вызова
if [ $# -ne 2 ]
then
    exit 1
fi

real_out=$1 # Файл с выходнами данными программы
expected_out=$2 # Файл с ожидаемыми выходными данными

# Маска для вычленения информации из всего вывода
data_mask="[[:graph:]]+"

# Считывание чисел из файлов
real_data=$(grep -oE "$data_mask" "$real_out")
expected_data=$(grep -oE "$data_mask" "$expected_out")
if [[ "$real_data" == "$expected_data" ]]; then
    exit 0
else
    exit 1
fi


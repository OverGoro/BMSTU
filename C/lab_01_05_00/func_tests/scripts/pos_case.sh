#!/bin/bash

# Корректность вызова
if [ $# -ne 2 ]
then
    exit 1
fi

inp_data_file=$1 # Файл с входными данными
expected_out_file=$2 # Файл с выходными данными
program="../../app.exe" # Программа
prog_out_file="prog_out.txt" # Файл с выходными данными программы

file_data=$(cat "$inp_data_file")

echo "$file_data" | "$program" > "$prog_out_file"

program_exit_code=$? # Код завершения программы

if [ "$program_exit_code" -ne 0 ]
then
    # Если в ходе выполнения программы возникла ошибка
    exit 2 
fi

# Сравнение ожидаемых и выходных данных
./comparator_result.sh "$prog_out_file" "$expected_out_file"
exit $?
#!/bin/bash

# Корректность вызова
if [ $# -eq 1 ]
then

    input_file=$1 # Файл с входнами данными программы
    prog_out_file="prog_out.txt"
    program="../../app.exe"

    file_data=$(cat "$input_file")
    echo "$file_data" | "$program" > "$prog_out_file"

    program_exit_code=$?
    if [ $program_exit_code -eq 0 ]
    then
        exit 1
    else
        exit 0
    fi

elif [ $# -eq 2 ]
then
    inp_data_file=$1 # Файл с входными данными
    expected_out_file=$2 # Файл с выходными данными
    program="../../app.exe" # Программа
    prog_out_file="prog_out.txt" # Файл с выходными данными программы

    file_data=$(cat "$inp_data_file")

    echo "$file_data" | "$program" > "$prog_out_file"

    program_exit_code=$? # Код завершения программы

    if [ "$program_exit_code" -eq 0 ]
    then
        # Если в ходе выполнения программы возникла ошибка
        exit 2 
    fi

    # Сравнение ожидаемых и выходных данных
    ./comparator.sh "$prog_out_file" "$expected_out_file"
    exit $?
fi
exit 3
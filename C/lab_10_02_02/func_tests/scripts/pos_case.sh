#!/bin/bash

# Корректность вызова
if [ $# -lt 3 ]
then
    exit 1
fi

inp_data_file=$1 # Файл с входными данными

expected_out_file=$2 # Файл с выходными данными
program="../../app.exe" # Программа

keys_file=$3 # Файл с ключами программы

is_valgrind=0

if [ $# -eq 4 ]
then
    is_valgrind=1
fi

mod_prog_out_file="prog_out.txt" # Файл с вызодными данными в текстовом формате 
program_keys=""
if [ -e "$keys_file" ]
then
    echo "Args file were found"
    program_keys=$(cat "$keys_file") # Строка с ключами для запуска программы
fi


program_exit_code=0 # Код завершения программы
valgrind_out=""
if [ $is_valgrind -eq 0 ]
then
    if [ -e "$keys_file" ]
    then
        echo "RUNNING: $program $program_keys" # Выполнение программы с ключами
        eval "$program $program_keys" # Выполнение программы с ключами
    else 
        echo "RUNNING: cat $inp_data_file | $program" # Выполнение программы без ключей
        eval "cat $inp_data_file | $program > $mod_prog_out_file" # Выполнение программы без ключей
    fi
else
    if [ -e "$keys_file" ]
    then
        echo "RUNNING: valgrind --leak-check=yes --quiet --log-file=$mod_prog_out_file $program $program_keys" # Выполнение с ключами
        eval "valgrind --leak-check=yes --quiet --log-file=$mod_prog_out_file $program $program_keys" # Выполнение с ключами
    else 
        echo "RUNNING: cat $inp_data_file | valgrind --leak-check=yes --quiet --log-file=$mod_prog_out_file $program" # выполнение без ключей
        eval "cat $inp_data_file | valgrind --leak-check=yes --quiet --log-file=$mod_prog_out_file $program > $mod_prog_out_file" # выполнение без ключей
    fi
fi
    
program_exit_code=$? # Код завершения программы
if [ $program_exit_code -ne 0 ]
then
    echo "Exit code $program_exit_code"
    # Если в ходе выполнения программы возникла ошибка
    exit 2 
fi
# Сравнение ожидаемых и выходных данных
./comparator.sh "$mod_prog_out_file" "$expected_out_file"
comparator_result=$?
if [ $comparator_result -ne 0 ]
then
    diff "$expected_out_file" "$mod_prog_out_file"
fi
exit $comparator_result

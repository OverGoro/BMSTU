#!/bin/bash

# Корректность вызова
if [ $# -lt 3 ]
then
    exit 1
fi

script_dir="$(dirname "$(readlink -f "$0")")"
cd "$script_dir" || exit 1


inp_data_file="$(readlink -f "$1")" # Файл с входными данными

expected_out_file="$(readlink -f "$2")" # Файл с выходными данными
program="$(readlink -f "../../app.exe")" # Программа

keys_file="$(readlink -f $3)" # Файл с ключами программы

is_valgrind=0

if [ $# -eq 4 ]
then
    is_valgrind=1
fi

mod_prog_out_file=$(readlink -f "../data/prog_out.txt") # Файл с вызодными данными в текстовом формате 

program_keys=$(cat "$keys_file") # Строка с ключами для запуска программы


app_dir=$(dirname "$program")
cd "$app_dir" || exit 1

program_exit_code=0 # Код завершения программы
valgrind_out=""
if [ $is_valgrind -eq 0 ]
then
    eval \"$program\" $program_keys # Выполнение программы с ключами
else
    eval "valgrind --leak-check=yes --quiet --log-file=\"$mod_prog_out_file\" \"$program\" $program_keys"
    
fi

program_exit_code=$? # Код завершения программы

cd "$script_dir" || exit 1

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

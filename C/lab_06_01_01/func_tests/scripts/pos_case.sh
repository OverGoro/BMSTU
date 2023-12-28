#!/bin/bash

# Корректность вызова
if [ $# -ne 3 ]
then
    exit 1
fi

inp_data_file=$1 # Файл с входными данными

expected_out_file=$2 # Файл с выходными данными
program="../../app.exe" # Программа

keys_file=$3 # Файл с ключами программы

mod_prog_out_file="prog_out.txt" # Файл с вызодными данными в текстовом формате 


program_keys=$(cat "$keys_file") # Строка с ключами для запуска программы


program_exit_code=0 # Код завершения программы

eval "$program ../../$program_keys" > "$mod_prog_out_file" # Выполнение программы с ключами
    
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

exit $comparator_result

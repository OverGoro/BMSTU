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

program_keys=""
if [ -e "$keys_file" ]
then 
    program_keys=$(cat "$keys_file") # Строка с ключами для запуска программы
fi


program_exit_code=0 # Код завершения программы

if [[ "$program_keys" == "" ]]
then 
    eval "cat $inp_data_file | $program " > "$mod_prog_out_file" # Выполнение программы с ключами
else
    eval "cat $inp_data_file | $program $program_keys " > "$mod_prog_out_file"
fi
    
program_exit_code=$? # Код завершения программы

if [ $program_exit_code -ne 0 ]
then    
    echo "Exit code $program_exit_code"
    diff "$mod_prog_out_file" "$expected_out_file"
    # Если в ходе выполнения программы возникла ошибка
    exit 2 
fi


# Сравнение ожидаемых и выходных данных
./comparator.sh "$mod_prog_out_file" "$expected_out_file"
comparator_result=$?
if [[ $comparator_result -ne 0 ]]
then
    diff "$mod_prog_out_file" "$expected_out_file"
fi
exit $comparator_result

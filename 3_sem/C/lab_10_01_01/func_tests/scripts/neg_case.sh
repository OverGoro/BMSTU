#!/bin/bash
# Корректность вызова
if [ $# -eq 2 ] # Вызов с 1 файлом (без выходных данных)
then

    inp_data_file=$1 # Файл с входными данными
    mod_data_file="./temp_in.bin" # Файл с входными данными в двоичном формате

    program="../../app.exe" # Программа

    keys_file=$2 # Файл с ключами программы
    program_keys=$(cat "$keys_file") # Строка с ключами для запуска программы


    prog_out_file="prog_out.bin" # Файл с выходными данными программы
    mod_prog_out_file="prog_out.txt" # Файл с вызодными данными в текстовом формате 

    
    program_exit_code=0 # Код завершения программы
    
    eval "$program $program_keys" > "$mod_prog_out_file" # Выполнение программы с ключами

    program_exit_code=$?
    echo "Exit code: $program_exit_code"

    if [[ $program_exit_code -ne 0 ]]
    then
        exit 0 # В ходе выполнения программы возникла ошибка - ОК
    else
        exit 2 # В ходе выполнения программы не возникла ошибка - FAILED
    fi

elif [ $# -eq 3 ] && [[ "$3" == "--valgrind" ]] # Вызов с valgrind
then
    inp_data_file=$1 # Файл с входными данными
    mod_data_file="./temp_in.bin" # Файл с входными данными в двоичном формате

    program="../../app.exe" # Программа

    keys_file=$2 # Файл с ключами программы
    program_keys=$(cat "$keys_file") # Строка с ключами для запуска программы


    prog_out_file="prog_out.bin" # Файл с выходными данными программы
    mod_prog_out_file="prog_out.txt" # Файл с вызодными данными в текстовом формате 

    
    program_exit_code=0 # Код завершения программы
    valgrind_out=$(eval "valgrind --leak-check=yes --quiet $program $program_keys" > $mod_prog_out_file) # Выполнение программы с ключами
    
    program_exit_code=$?
    echo "Exit code: $program_exit_code"

    if [[ $program_exit_code -eq 0 ]] || [[ -s "$mod_prog_out_file" ]]
    then
        exit 2
    else
        exit 0
    fi
elif [ $# -eq 3 ] # Вызов c 2 файлами
then
    inp_data_file=$1 # Файл с входными данными
    mod_data_file="./temp_in.bin" # Файл с входными данными в двоичном формате

    expected_out_file=$2 # Файл с выходными данными
    program="../../app.exe" # Программа

    keys_file=$3 # Файл с ключами программы
    program_keys=$(cat "$keys_file") # Строка с ключами для запуска программы


    prog_out_file="prog_out.bin" # Файл с выходными данными программы
    mod_prog_out_file="prog_out.txt" # Файл с вызодными данными в текстовом формате 

    program_exit_code=0 # Код завершения программы

    eval "$program $program_keys" > "$mod_prog_out_file" # Выполнение программы с ключами

    program_exit_code=$? # Код завершения программы

    if [ "$program_exit_code" -eq 0 ]
    then    
        # Если в ходе выполнения программы не возникла ошибка - FAILED
        exit 2 
    fi
    # Сравнение ожидаемых и выходных данных
    ./comparator.sh "$mod_prog_out_file" "$expected_out_file"
    comparator_result=$?
    exit $comparator_result
elif [ $# -eq 4 ] # Вызов c 2 файлами и valgrind
then
    inp_data_file=$1 # Файл с входными данными
    mod_data_file="./temp_in.bin" # Файл с входными данными в двоичном формате

    expected_out_file=$2 # Файл с выходными данными
    program="../../app.exe" # Программа

    keys_file=$3 # Файл с ключами программы
    program_keys=$(cat "$keys_file") # Строка с ключами для запуска программы


    prog_out_file="prog_out.bin" # Файл с выходными данными программы
    mod_prog_out_file="prog_out.txt" # Файл с вызодными данными в текстовом формате 

    program_exit_code=0 # Код завершения программы

    eval "valgrind --leak-check=yes --quiet $program $program_keys" > "$mod_prog_out_file" # Выполнение программы с ключами

    program_exit_code=$? # Код завершения программы

    if [ "$program_exit_code" -eq 0 ] || [[ -s "$mod_prog_out_file" ]]
    then    
        # Если в ходе выполнения программы не возникла ошибка - FAILED
        exit 2 
    fi
    # Сравнение ожидаемых и выходных данных
    ./comparator.sh "$mod_prog_out_file" "$expected_out_file"
    comparator_result=$?
    exit $comparator_result
fi

exit 3

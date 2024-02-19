#!/bin/bash
if [ $# -eq 0 ]; then
    echo "Использование: $0 <number> [-n | -pi | -po]"
    exit 1
fi

number=$1
shift

if [ "$1" == "-n" ]; then
    file_name="./func_tests/data/neg_0${number}_in.txt"
elif [ "$1" == "-pi" ]; then
    file_name="./func_tests/data/pos_0${number}_in.txt"
elif [ "$1" == "-po" ]; then
    file_name="./func_tests/data/pos_0${number}_out.txt"
else
    echo "Неиверный ключ: $1"
    exit 1
fi

echo "Числа ('e' для завершения):"
while read input; do
    if [ "$input" == "e" ]; then
        break
    fi
    echo $input >> $file_name
done

echo "Создан файл $file_name"
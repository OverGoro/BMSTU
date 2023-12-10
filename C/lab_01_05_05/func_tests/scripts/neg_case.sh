#!/bin/bash

# Корректность вызова
if [ $# -ne 1 ]
then
    exit 1
fi

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
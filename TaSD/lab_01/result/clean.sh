#!/bin/bash

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

# Очистка временных файлов
files="*.exe *.o *.out *.gcno *.gcda *.gcov"

for file in $files; do
	if [ -f "$file" ]
	then
		rm "$file" 
	fi
done

cd ./func_tests/scripts || exit 1
files="*.bin *.txt "

for file in $files; do
	if [ -f "$file" ]
	then
		rm "$file" 
	fi
done

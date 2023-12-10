#!/bin/bash

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

# Удаление предыдущих файлов, если таковые существуют

make clean
make coverage


# Тестирование с выводом
./func_tests/scripts/func_tests.sh -v

# Определение и вывод покрытия
percent=$(gcov ./out/*.o | tail -n 1 | grep -Eo "[0-9]+\.[0-9]+")
echo "======================"
echo "Coverage: $percent%"
echo "======================"
rm  *.gcov out/*.gcda


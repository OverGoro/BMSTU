#!/bin/bash

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

# Удаление предыдущих файлов, если таковые существуют
if [ -f "main.gcda" ]
then
    rm "main.gcda"
fi

if [ -f "main.gcdo" ]
then
    rm "main.gcdo"
fi

./build_coverage.sh


# Тестирование с выводом
./func_tests/scripts/func_tests.sh -v

# Определение и вывод покрытия
percent=$(gcov ./*.c | tail -n 1 | grep -Eo "[0-9]+\.[0-9]+")
echo "======================"
echo "Coverage: $percent%"
echo "======================"


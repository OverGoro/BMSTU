#!/bin/bash

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

# Компиляция в объектные файлы
clang -g -O0 -Wall -Wextra -Wpedantic -Werror -c ./*.c

# Компоновка
clang -o app.exe ./*.o -lm
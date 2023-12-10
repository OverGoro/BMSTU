#!/bin/bash

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

# Компиляция в объектные файлы
clang -O3 -fsanitize=address -Wall -Wextra -Wpedantic -Werror -c ./*.c

# Компоновка
clang -fsanitize=address -o app.exe ./*.o -lm

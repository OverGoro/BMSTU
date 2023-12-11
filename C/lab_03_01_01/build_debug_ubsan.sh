#!/bin/bash

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

# Компиляция в объектные файлы
clang -std=c99 -g3 -O0 -fsanitize=undefined -fno-omit-frame-pointer -Wall -Wextra -Wpedantic -Werror -c ./*.c

# Компоновка
clang -fsanitize=undefined -o app.exe ./*.o -lm

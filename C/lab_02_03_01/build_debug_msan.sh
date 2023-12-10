#!/bin/bash

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

# Компиляция в объектные файлы
clang -std=c99 -g3 -O0 -fsanitize=memory -fno-omit-frame-pointer -Wall -Wextra -Wpedantic -Werror -c main.c

# Компоновка
clang -fsanitize=memory -o app.exe main.o -lm
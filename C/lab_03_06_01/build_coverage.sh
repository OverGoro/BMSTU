#!/bin/bash
# Компиляция в объектные файлы
gcc -O0 -Wall -Wextra -Wpedantic -Werror --coverage -c ./*.c

# Компоновка
gcc --coverage -o app.exe ./*.o -lm 
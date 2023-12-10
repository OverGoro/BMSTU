#!/bin/bash

# Переменная, хранящая путь к папке с .sh файлами
folder_path="$(dirname "$0")"

# Перебираем все .sh файлы в папке с помощью цикла for
for file in "$folder_path"/*.sh
do
    # Проверяем каждый файл с помощью shellcheck
    shellcheck "$file"
done

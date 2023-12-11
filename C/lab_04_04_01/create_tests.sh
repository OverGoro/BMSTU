#!/bin/bash
i=1
while IFS=$' ' read -r input output; do
  # создаем входной файл
  if [[ $i -lt 10 ]]; then
    printf -v num "0%d" $i
  else
    num=$i
  fi
  echo "$input" > "./func_tests/data/pos_${num}_in.txt"
  # создаем выходной файл
  echo "$output" > "./func_tests/data/pos_${num}_out.txt"
  ((i++))
done < "table.txt"

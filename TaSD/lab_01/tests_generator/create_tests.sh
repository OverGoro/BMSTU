#!/bin/bash

cat ./input.txt | python3 ./python_tests.py > ./output.txt
cat ./output.txt | ./normalizer.exe > ./normalized_output.txt
python3 ./tabler.py
cat ./table.txt
i=1
test_type="pos"
rm ../func_tests/data/*.txt
echo "# Позитивные тесты:"
while IFS=$'|' read -r args input output comment; do
    if [[ "$args" != "-" && "${args:0:1}" != "#" ]] ; then
        if [[ "$i" -lt 10 ]]; then
        printf -v num "0%d" $i
        else
            num=$i
        fi
        input=$(echo "$input" | sed 's/ /\n/g')
        input=$(echo "$input" | sed 's/_/ /g')
        output=$(echo "$output" | sed 's/ /\n/g')
        output=$(echo "$output" | sed 's/_/ /g')
        if [[ "$args" != "" ]]
        then
            printf "%s" "$args" > "../func_tests/data/${test_type}_${num}_args.txt"
        fi
        printf "%s" "$input" > "../func_tests/data/${test_type}_${num}_in.txt"
        echo "" >> "../func_tests/data/${test_type}_${num}_in.txt"
        if [[ "$output" != "" || $test_type == "pos" ]]
        then
            echo "$output" > "../func_tests/data/${test_type}_${num}_out.txt"
        fi
        echo "$i. $comment" 
        ((i++))
    elif [[ "${args:0:1}" == "#" ]]
    then 
        echo "$args"
    else
        test_type="neg"
        i=1
        echo "# Негативные тесты:"
    fi
done < "table.txt"

#!/bin/bash
i=1
p_i=1
n_i=1
test_type="pos"
rm ./func_tests/data/*.txt
echo "Сумма матриц"
echo "# Позитивные тесты:"
while IFS=$'|' read -r args input_a input_b output comment; do
    if [[ "$args" != "-" ]]
    then
        if [[ "$i" -lt 10 ]]; then
        printf -v num "0%d" $i
        else
            num=$i
        fi
        input_a=$(echo "$input_a" | sed 's/ /\n/g')
        input_a=$(echo "$input_a" | sed 's/_/ /g')
        input_b=$(echo "$input_b" | sed 's/ /\n/g')
        input_b=$(echo "$input_b" | sed 's/_/ /g')
        output=$(echo "$output" | sed 's/ /\n/g')
        output=$(echo "$output" | sed 's/_/ /g')

        printf "$args" > "./func_tests/data/${test_type}_${num}_args.txt"
        printf "$input_a" > "./func_tests/data/${test_type}_${num}_a_in.txt"
        printf "$input_b" > "./func_tests/data/${test_type}_${num}_b_in.txt"
        if [[ "$output" != "" || $test_type == "pos" ]]
        then
            echo "$output" > "./func_tests/data/${test_type}_${num}_out.txt"
        fi
        echo "$i. $comment" 
        ((i++))
    else
        ((i++))
        p_i=$i
        i=$n_i
        test_type="neg"
        echo "# Негативные тесты:"
    fi
done < "table_summ.txt"

echo ""
n_i=$i
i=$p_i
test_type="pos"

echo "Произведение матриц"
echo "# Позитивные тесты:"
while IFS=$'|' read -r args input_a input_b output comment; do
    if [[ "$args" != "-" ]]
    then
        if [[ "$i" -lt 10 ]]; then
        printf -v num "0%d" $i
        else
            num=$i
        fi
        input_a=$(echo "$input_a" | sed 's/ /\n/g')
        input_a=$(echo "$input_a" | sed 's/_/ /g')
        input_b=$(echo "$input_b" | sed 's/ /\n/g')
        input_b=$(echo "$input_b" | sed 's/_/ /g')
        output=$(echo "$output" | sed 's/ /\n/g')
        output=$(echo "$output" | sed 's/_/ /g')

        printf "$args" > "./func_tests/data/${test_type}_${num}_args.txt"
        printf "$input_a" > "./func_tests/data/${test_type}_${num}_a_in.txt"
        printf "$input_b" > "./func_tests/data/${test_type}_${num}_b_in.txt"
        if [[ "$output" != "" || $test_type == "pos" ]]
        then
            echo "$output" > "./func_tests/data/${test_type}_${num}_out.txt"
        fi
        echo "$i. $comment" 
        ((i++))
    else
        ((i++))
        p_i=$i
        i=$n_i
        test_type="neg"
        echo "# Негативные тесты:"
    fi
done < "table_mult.txt"

echo ""
n_i=$i
i=$p_i
test_type="pos"

echo "Решения СЛАУ методом Гаусса"
echo "# Позитивные тесты:"
while IFS=$'|' read -r args input output comment; do
    if [[ "$args" != "-" ]]
    then
        if [[ "$i" -lt 10 ]]; then
        printf -v num "0%d" $i
        else
            num=$i
        fi
        input=$(echo "$input" | sed 's/ /\n/g')
        input=$(echo "$input" | sed 's/_/ /g')
        output=$(echo "$output" | sed 's/ /\n/g')
        output=$(echo "$output" | sed 's/_/ /g')

        printf "$args" > "./func_tests/data/${test_type}_${num}_args.txt"
        printf "$input" > "./func_tests/data/${test_type}_${num}_in.txt"
        if [[ "$output" != "" || $test_type == "pos" ]]
        then
            echo "$output" > "./func_tests/data/${test_type}_${num}_out.txt"
        fi
        echo "$i. $comment" 
        ((i++))
    else
        ((i++))
        p_i=$i
        i=$n_i
        test_type="neg"
        echo "# Негативные тесты:"
    fi
done < "table_slae.txt"

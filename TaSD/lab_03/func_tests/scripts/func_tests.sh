#!/bin/bash

# Тихий режим - 1, режим с выводом - 0
print_mode=1
if [ "$1" = "-v" ]
then
    print_mode=0
fi

is_valgrind=0
if [ "$2" = "--valgrind" ]
then
    is_valgrind=1
fi

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

# Маска для входных файлов позитивных случаев
pos_file_input_regexp="pos_*_in.txt"
# Маска для выходных файлов позитивных случаев
pos_file_output_regexp="pos_*_out.txt"
# Маска для входных файлов негативных случаев
neg_file_input_regexp="neg_*_in.txt"
# Маска для выходных файлов негативных случаев
neg_file_output_regexp="neg_*_out.txt"

# Определение путей к файлам
pos_input_files=$(find ../data/ -name "$pos_file_input_regexp" | sort)
pos_output_files=$(find ../data/ -name "$pos_file_output_regexp" | sort)
neg_input_files=$(find ../data/ -name "$neg_file_input_regexp" | sort)
neg_output_files=$(find ../data/ -name "$neg_file_output_regexp" | sort)

# Определение количества позитивных и негативных тестов
pos_tests_num=$(echo "$pos_input_files" | wc -w)
neg_tests_num=$(echo "$neg_input_files" | wc -w)


# Количество пройденых позитивных тестов
pos_tests_completed=0
# Количество проваленных тестов
failed_tests=0

if [ "$pos_tests_num" != "0" ]
then
    if [ "$print_mode" = "0" ]
    then
        echo "======================"
        echo "Started positive tests"
        echo "----------------------"
    fi
    for i in $pos_input_files
    do
        i_num=${i//[^0-9]/}

        # Выполнение программы
        if [ "$is_valgrind" -eq 0 ]
        then
            ./pos_case.sh "$i" "../data/pos_${i_num}_out.txt" "../data/pos_${i_num}_args.txt"
        else
            ./pos_case.sh "$i" "../data/pos_${i_num}_out.txt" "../data/pos_${i_num}_args.txt" "--valgrind"
        fi
        # Результат программы
        test_result=$?
        # Сообщение для вывода
        message=""
        if [ "$test_result" -eq 0 ]
        then
            # Тест пройден
            message="\033[92mPassed\033[39m\n"
            pos_tests_completed=$((pos_tests_completed + 1))
        elif [ "$test_result" -eq 1 ]
        then
            # Тест провален
            failed_tests=$((failed_tests + 1))
            message="\033[31mNot passed\033[39m\n"
        else
            # Произошла ошибка
            failed_tests=$((failed_tests + 1))
            message="\033[31mError\033[39m\n"
        fi
        if [ "$print_mode" = "0" ]
        then
                f=${i//..\/data\//}
                echo -e "Test $f: $message"
            fi
            continue 2
        if [ "$print_mode" = "0" ]
        then
            # Если для текущего файла с входными данными нет файла с выходными
            message="\033[31mNo output file\033[39m\n"
            f=${i//..\/data\//}
            echo -e "Test $f: $message"
        fi
    done
    # Определение процента пройденных тестов
    pos_tests_completed=$((pos_tests_completed * 100))

    pos_tests_result=$(bc<<< "scale=1;$pos_tests_completed/$pos_tests_num" )

    if [ "${pos_tests_result//.[0-9]*/}" = "" ]
    then
        pos_tests_result="0$pos_tests_result"
    fi

    # Вывод рузьтата тестов
    if [ "$print_mode" = "0" ]
    then
        echo "----------------------"
        if [ "$pos_tests_result" = "100.0" ]
        then
            printf "Passed positive %%: \033[92m$pos_tests_result%%\033[39m\n"
        else
            printf "Passed positive %%: \033[31m$pos_tests_result%%\033[39m\n"
        fi
        echo "======================"
        printf "\n\n"
    fi
else
    # Если нет позитивных тестов
    if [ "$print_mode" = "0" ]
    then
        echo "======================"
        echo -e "\033[31mNo positive tests\033[39m\n"
        echo "======================"
    fi
fi

if [ "$neg_tests_num" -ne "0" ]
then
    if [ "$print_mode" = "0" ]
    then
        echo "======================"
        echo "Started negative tests"
        echo "----------------------"
    fi
    # Количестов пройденных негативных тестов
    neg_tests_completed=0
    for i in $neg_input_files
    do
        neg_out_file=""
        i_num=${i//[^0-9]/}
        if [[ -e "../data/neg_${i_num}_out.txt" ]]
        then
            neg_out_file="../data/neg_${i_num}_out.txt"
        fi
        test_result=""
        if [ "$neg_out_file" == "" ]
        then
            if [ "$is_valgrind" -eq 0 ]
            then
                ./neg_case.sh "$i" "../data/neg_${i_num}_args.txt"
            else
                ./neg_case.sh "$i" "../data/neg_${i_num}_args.txt" "--valgrind"
            fi
            test_result=$?
        else
            if [ "$is_valgrind" -eq 1 ]
            then
                ./neg_case.sh "$i" "$neg_out_file" "../data/neg_${i_num}_args.txt"
            else
                ./neg_case.sh "$i" "$neg_out_file" "../data/neg_${i_num}_args.txt" "--valgrind"
            fi


            test_result=$?
        fi
        
        # Сообщение для вывода
        message=""

        if [ "$test_result" -ne 0 ]
        then
            # Тест провален
            failed_tests=$((failed_tests + 1))
            message="\033[31mNot passed\033[39m\n"
        else
            # Тест пройден
            neg_tests_completed=$((neg_tests_completed + 1))
            message="\033[92mPassed\033[39m\n"
        fi
        if [ "$print_mode" = "0" ]
        then
            f=${i//..\/data\//}
            echo -e "Test $f: $message"
        fi
        continue
    done

    # Определение процента пройденных тестов
    neg_tests_completed=$((neg_tests_completed * 100))
    neg_tests_num=$((neg_tests_num))

    neg_tests_result=$(bc<<< "scale=1;$neg_tests_completed/$neg_tests_num" )

    if [ "${pos_tests_result//.[0-9]*/}" = "" ]
    then
        pos_tests_result="0$neg_tests_result"
    fi
    
    # Вывод результатов тестов
    if [ "$print_mode" = "0" ]
    then
        echo "----------------------"
        if [ "$neg_tests_result" = "100.0" ]
        then
            printf "Passed negative %%: \033[92m%s%%\033[39m\n" "$neg_tests_result"
        else
            printf "Passed negative %%: \033[31m%s%%\033[39m\n" "$neg_tests_result"
        fi
        echo "======================"
        printf "\n\n"
    fi
else
    # Если нет негативных тестов
    if [ "$print_mode" = "0" ]
    then
        echo "======================"
        printf "\033[31mNo negative tests\033[39m\n"
        echo "======================"
    fi
fi

exit "$failed_tests"

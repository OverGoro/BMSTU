#!/bin/bash

# Тихий режим - 1, режим с выводом - 0
print_mode=1
if [ "$1" = "-v" ]
then
    print_mode=0
fi

script_dir="$(dirname "$0")"
cd "$script_dir" || exit 1

# Маска для входных файлов позитивных случаев
pos_file_input_regexp="pos_*_in.txt"
# Маска для выходных файлов позитивных случаев
pos_file_output_regexp="pos_*_out.txt"
# Маска для входных файлов негативных случаев
neg_file_input_regexp="neg_*_in.txt"


# Определение путей к файлам
pos_input_files=$(find ../data/ -name "$pos_file_input_regexp" | sort)
pos_output_files=$(find ../data/ -name "$pos_file_output_regexp" | sort)
neg_input_files=$(find ../data/ -name "$neg_file_input_regexp" | sort)

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
        for o in $pos_output_files
        do
            o_num=${o//[^0-9]/}
            if [ "$o_num" = "$i_num" ]
            then
                # Выполнение программы
                ./pos_case.sh "$i" "$o"
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
            fi
        done        
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
        ./neg_case.sh "../data/$i"
        test_result=$?
        
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
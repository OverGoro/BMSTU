#include "error.h"
#include "measure.h"
#include "menu.h"
#include "student.h"
#include "student_array.h"
#include "student_filter.h"
#include "student_sort.h"
#include "student_keys.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_NAME_LEN 50

int main(void)
{
    student_t *arr_beg = NULL;
    student_t *arr_end = NULL;
    student_t *tmp_arr_beg = NULL;
    student_t *tmp_arr_end = NULL;
    student_key_t *ka_beg = NULL;
    student_key_t *ka_end = NULL;
    while (true)
    {
        // Вывод меню
        menu_print();
        // Ввод команды
        printf("\033[93mВведите команду: \033[0m");
        size_t command;
        char cur_char = '\0';
        int rc = scanf("%lu", &command);
        while ( rc != 1 || command == 0 || command > EXIT)
        {
            printf("\033[91mНеверная команда\033[0m\n");
            printf("\033[93mВведите команду: \033[0m");
            while ((cur_char = getchar()) != '\n' && cur_char != '\0');
            rc = scanf("%lu", &command);
        }
        while ((cur_char = getchar()) != '\n' && cur_char != '\0');
        
        // Выполнение комманд
        switch (command) 
        {
            // Считывание из файла
            case READ_FILE:
            {
                // Ввод имени файла
                printf ("\033[93mВведите имя файла (длина названия до %d символов): \033[0m", FILE_NAME_LEN);
                char file_name[FILE_NAME_LEN + 1];
                if (input_str(stdin, FILE_NAME_LEN, file_name) == ERR_OK)
                {
                    if (file_name[strlen(file_name) - 1] == '\n')
                        file_name[strlen(file_name) - 1] = '\0';
                }
                else 
                {
                    printf("\033[91mОшибка: не удалось считать имя файла\033[0m\n");
                    break;
                }

                // Работа с файлом
                // Открытие файла
                FILE *f = fopen(file_name, "r");
                if (f == NULL)
                {
                    printf("\033[91mНе удалось открыть файл\033[0m\n");
                    break;
                }
                // Считывание данных из файла
                int rc = sa_input(f, &arr_beg, &arr_end, empty_prompt);
                if (rc == ERR_IO)
                    printf("\033[91mНеправильный формат файла\033[0m\n");
                else if (rc == ERR_MEMORY)
                    printf("\033[91mНеудалось выделить память под таблицу\033[0m\n");
                else if (rc == ERR_EMPTY_ARR)
                    printf("\033[91mФайл пуст\033[0m\n");
                else if (rc != ERR_OK)
                    printf("\033[91mНепредвиденная ошибка\033[0m\n");
                fclose(f); 
                if (rc != ERR_OK)
                    break;
                // if (rc != ERR_OK)
                // {
                //     while ((cur_char = getchar()) != '\n' && cur_char != '\0');
                // }
                    
                if (sa_copy(arr_beg, arr_end, &tmp_arr_beg, &tmp_arr_end) != ERR_OK)
                    printf("\033[91mНе удалось создать буффер таблицы\033[0m\n");
                if (ka_create(&ka_beg, &ka_end, arr_beg, arr_end) != ERR_OK)
                    printf("\033[91mНе удалось выделить память для массива ключей\033[0m\n");
                printf("\033[92mТаблица загружена\033[0m\n");
                break;
            }

            // Вывод таблицы на экран
            case PRINT_TABLE:
            {
                if (tmp_arr_beg == tmp_arr_end)
                    printf("\033[92mПустая таблица\033[0m\n");
                else
                    sa_output(stdout, tmp_arr_beg, tmp_arr_end, true);
                break;
            }
            // Ручное добавление записи в таблицу
            case ADD_ENTRY:
            {
                printf("\033[93mВведите новую запись:\033[0m\n");
                int rc = sa_keyboard_append(&tmp_arr_beg, &tmp_arr_end);
                if (rc != ERR_OK)
                {
                    printf("\033[91mЗначение не добавлено\033[0m\n");
                    while ((cur_char = getchar()) != '\n' && cur_char != '\0');
                }
                else
                    printf("\033[92mЗначение добавлено\033[0m\n");
                if (ka_create(&ka_beg, &ka_end, tmp_arr_beg, tmp_arr_end) != ERR_OK)
                    printf("\033[91mНе удалось выделить память для массива ключей\033[0m\n");
                break;
            }
            
            // Загрузка исходной таблицы в буфер
            case LOAD_BUF:
            {
                if (sa_copy(arr_beg, arr_end, &tmp_arr_beg, &tmp_arr_end) != ERR_OK)
                    printf("\033[91mНе удалось создать буффер таблицы\033[0m\n");
                if (ka_create(&ka_beg, &ka_end, tmp_arr_beg, tmp_arr_end) != ERR_OK)
                    printf("\033[91mНе удалось выделить память для массива ключей\033[0m\n");
                 printf("\033[92mТаблица загружена\033[0m\n");

                break;
            }
            // Ручное удаление записи из таблицы
            case DELETE_ENTRY:
            {
                printf("\033[93mВведите номер(n) записи:\033[0m\n");
                size_t n = 0;
                if (scanf("%lu", &n) != 1)
                {
                    while ((cur_char = getchar()) != '\n' && cur_char != '\0');
                    printf("\033[91mn введено неверно\033[0m\n");
                    break;
                }
                int rc = sa_delete(&tmp_arr_beg, &tmp_arr_end, n);
                if (rc == ERR_MEMORY)
                   printf("\033[91mОшибка: удаление не удалось выделить память для изменной таблицы\033[0m\n"); 
                else if (rc == ERR_EMPTY_ARR)
                   printf("\033[91mТаблица уже пуста\033[0m\n"); 
                else if(rc == ERR_RANGE)
                    printf("\033[91mЗначение n выходит за границы таблицы\033[0m\n");
                else 
                {
                    if (ka_create(&ka_beg, &ka_end, tmp_arr_beg, tmp_arr_end) != ERR_OK)
                        printf("\033[91mНе удалось выделить память для массива ключей\033[0m\n");
                    printf("\033[92mУдаление совершено\033[0m\n");
                }
                break;
            }
            // Быстрая сортировка таблицы
            case QSORT_TABLE:
            {
                sa_quicksort(tmp_arr_beg, tmp_arr_end - tmp_arr_beg, sizeof(student_t), cmp_mark);
                size_t n = 0;
                for (student_t *pcur = tmp_arr_beg; pcur < tmp_arr_end; pcur++)
                {
                    pcur->n = n;
                    n++;
                }
                printf("\033[92mСортировка завершена\033[0m\n");
                if (ka_create(&ka_beg, &ka_end, tmp_arr_beg, tmp_arr_end) != ERR_OK)
                    printf("\033[91mНе удалось выделить память для массива ключей\033[0m\n");
                break;
            }
            // Быстрая сортировка массива ключей
            //
            case QSORT_ARR:
            {
                sa_quicksort(ka_beg, ka_end - ka_beg, sizeof(student_key_t), ka_cmp_marks);
                printf("\033[92mСортировка завершена\033[0m\n");
                break;
            }
            case BUBBLE_SORT_TABLE:
            {
                sa_bubble_sort(tmp_arr_beg, tmp_arr_end - tmp_arr_beg, sizeof(student_t), cmp_mark);
                size_t n = 0;
                for (student_t *pcur = tmp_arr_beg; pcur < tmp_arr_end; pcur++)
                {
                    pcur->n = n;
                    n++;
                }
                printf("\033[92mСортировка завершена\033[0m\n");
                if (ka_create(&ka_beg, &ka_end, tmp_arr_beg, tmp_arr_end) != ERR_OK)
                    printf("\033[91mНе удалось выделить память для массива ключей\033[0m\n");
                break;
            }
            // Сортировка массива ключей пузырьком
            case BUBBLE_SORT_ARR:
            {
                sa_bubble_sort(ka_beg, ka_end - ka_beg, sizeof(student_key_t), ka_cmp_marks);
                printf("\033[92mСортировка завершена\033[0m\n");
                break;
            }
            case PRINT_ARR:
            {
                if (ka_beg < ka_end)
                    ka_print(stdout, ka_beg, ka_end, true);
                else
                    printf("\033[92mПустой массив\033[0m\n");
                break;
            }
            case PRINT_TABLE_BY_ARR:
            {
                if (ka_beg < ka_end)
                    ka_print_table(stdout, tmp_arr_beg, ka_beg, ka_end);
                else
                    printf("\033[92mПустая таблица\033[0m\n");
                break;
            }
            case TIME_EXPERIMENT:
            {
                int rc = conduct_experiment(1000, 10000, 1000);
                if (rc != ERR_OK)
                    printf("\033[91mНе удалось провести замерный эксперимент\033[0m\n");
                else
                    printf("\033[92mУдалось провести замерный эксперимент\033[0m\n");
                break;
            }

            case SEARCH:
            {
                size_t year;
                printf("\033[93mВведите год поступления: \033[0m");
                if (scanf("%lu", &year) != 1)
                {
                    printf("\033[91mГод указан неверно\033[0m\n");
                    break;
                }
                student_t prototype;
                prototype.housing_type = RENTAL;
                prototype.entry_date = year;

                cmp_t cmp_arr[] = {cmp_housing_type, cmp_entry_date};
                int rc = sa_filter(&prototype, tmp_arr_beg, tmp_arr_end, &tmp_arr_beg, &tmp_arr_end, cmp_arr, 2);
                if (rc == ERR_OK)
                {
                    sa_output(stdout, tmp_arr_beg, tmp_arr_end, true);
                    if (ka_create(&ka_beg, &ka_end, tmp_arr_beg, tmp_arr_end) != ERR_OK)
                        printf("\033[91mНе удалось выделить память для массива ключей\033[0m\n");
                }
                else if (rc == ERR_MEMORY)
                    printf("\033[91mОшибка: не удалось выделить память под новый массив\033[0m\n");
                else if (rc == ERR_EMPTY_ARR)
                    printf("\033[92mПодходящих элементов нет\033[0m\n");
                else
                    printf("\033[91mПроизошла непредвиденная ошибка\033[0m\n");

                break;
            }
        
            case SAVE:
            {
                // Ввод имени файла
                printf ("\033[93mВведите имя файла: \033[0m");
                char file_name[FILE_NAME_LEN + 1];
                if (fgets(file_name, FILE_NAME_LEN, stdin) != NULL)
                {
                    if (file_name[strlen(file_name) - 1] == '\n')
                        file_name[strlen(file_name) - 1] = '\0';
                }
                else 
                {
                    printf("\033[91mОшибка: не удалось считать имя файла\033[0m\n");
                    break;
                }
                FILE *f = fopen(file_name, "w");
                if (f == NULL)
                {
                    printf("\033[91mНе удалось открыть файл\033[0m\n");
                    break;
                }
                sa_output(f, tmp_arr_beg, tmp_arr_end, false);
                printf("\033[92mТаблица сохранена\033[0m\n");
                fclose(f);
                break;
            }
            case EXIT:
            {
                break;
            }
        }
        if (command == EXIT)
            break;
    }
    if (!arr_beg)
        free(arr_beg);
    if (!tmp_arr_beg)
        free(tmp_arr_beg);
    return ERR_OK;
}

#include "error.h"
#include "vec_io.h"
#include "menu.h"
#include "measure.h"
#include "sparse_matrix_operations.h"
#include "sparse_matrix_io.h"
#include <bits/types/FILE.h>
#include <stdio.h>
int main(void)
{
    sparse_t matrix = { 0, 0, 0, NULL, NULL, NULL };
    vector_t vec = {NULL, NULL, 0, 0};
    vector_t vec_r = {NULL, NULL, 0, 0};

    int **matrix_normal = NULL;
    int **vec_normal = NULL;

    while (true)
    {
        menu_commands_print();
        // Ввод команды
        printf("\033[93mВведите команду: \033[0m");
        size_t command;
        char cur_char = '\0';
        int rc = scanf("%lu", &command);
        while ( rc != 1 || command > MEASURE)
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
            case INPUT_MAT:
                menu_input_matrix(&matrix_normal, &matrix);
                break;
            case INPUT_VEC:
                menu_input_vector(&vec_normal, &vec);
                break;
            case PRINT_MAT:
                menu_print_matrix(&matrix);
                break;
            case PRINT_VEC:
                menu_print_vector(&vec);
                break;
            case MULT:
                menu_mult(&vec, &matrix, &vec_r);
                break;
            case MULT_NORM:
                menu_mult_normal(&vec, &matrix, &vec_r);
                break;
            case MEASURE:
            {
                int rc = ERR_OK;
                FILE *f_normal = NULL, *f_sparse = NULL;
                f_normal = fopen("./measures/normal.txt", "w");

                if (f_normal == NULL)
                    rc = ERR_FILE;

                if (!rc)
                    f_sparse = fopen("./measures/sparse.txt", "w");
                if (!rc && f_sparse == NULL)
                    rc = ERR_FILE;
                if (!rc)
                    rc = menu_measure(stdout, f_normal, f_sparse);
                break;
            }
        }
        if (command == EXIT)
            break;
    }
}


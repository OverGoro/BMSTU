#include <stdbool.h>
#define _GNU_SOURCE
#include "../inc/menu.h"
#include <stdio.h>

void handle_err(int err)
{
    switch (err) 
    {
    case ERR_OK:
        printf("\033[92mОперация завершена\033[0m\n");
        break;
    case ERR_IO:
        printf("\033[91mОшибка ввода\033[0m\n");
        break;
    case ERR_RANGE:
        printf("\033[91mОшибка диапазона данных\033[0m\n");
        break;
    case ERR_MEM:
        printf("\033[91mОшибка работы с динамической памятью\033[0m\n");
        break;
    case ERR_EMPTY:
        printf("\033[91mОшибка: пусто\033[0m\n");
        break;
    case ERR_FILE:
        printf("\033[91mОшибка работы с файлом\033[0m\n");
        break;
    default:
        printf("\033[91mНеизвестная ошибка: %d\033[0m\n", err);
        break;
    }
}
void menu_print_text(void)
{
    printf(MENU_TEXT);
}

int menu_read(graph_t ***graph_nodes, size_t *n)
{
    char *file_name = NULL;
    int len_file_name;

    int rc = ERR_OK;
    size_t read = 0;

    // Чтение file_name
    fprintf(stdout, "\nВведите имя файла: ");
    if ((len_file_name = getline(&file_name, &read, stdin)) == -1 || len_file_name <= 1)
    {
        rc = ERR_IO;
    }
    else
    {
        file_name[--len_file_name] = '\0';
        if (len_file_name == 0)
            rc = ERR_RANGE;
    }

    FILE *f_in = NULL;
    if (!rc) f_in = fopen(file_name, "r");
    if (!rc && f_in == NULL) rc = ERR_FILE;
    if (!rc) rc = graph_read(f_in, graph_nodes, n);
    if (f_in) fclose(f_in);
    return rc;
}

int menu_print(graph_t **graph_nodes, size_t n)
{
    return graph_draw("graph.gv", graph_nodes, n);
}

int menu_find(graph_t **graph_nodes, size_t n)
{
    size_t id;
    int max_weight;
    printf("Идентификатор начального узла: ");
    if (scanf("%lu", &id) != 1)
        return ERR_IO;
    printf("Максимальная стоимость пути: ");
    if (scanf("%d", &max_weight) != 1)
        return ERR_IO;

    graph_t **available_nodes = NULL;
    size_t available_n = 0;
    
    graph_t *start_node = graph_arr_get_by_id(graph_nodes, n, id);
    if (start_node == NULL)
        return ERR_RANGE;

    graph_set_visit(graph_nodes, n, false);
    int rc = graph_get_avialable(start_node, &available_nodes, &available_n, max_weight);

    if (!rc) rc = graph_print(stdout, available_nodes, available_n);
    free(available_nodes);
    graph_set_visit(graph_nodes, n, false);
    return rc;
}


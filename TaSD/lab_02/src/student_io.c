#include "student_io.h"
#include "str_io.h"
#include "student.h"
#include <stdio.h>

void empty_prompt(FILE *f, char *s)
{
    (void)(f);
    (void)(s);
}

void normal_prompt(FILE *f, char *s)
{
    fprintf(f, "%s", s);
}

int house_input(FILE *f, house_t *house)
{
    int rc = input_str(f, STREET_LEN, house->sreet);
    if (rc != ERR_OK)
        return rc;
    if (fscanf(f, "%u", &house->house_number) != 1)
        return ERR_IO;
    fgetc(f); // Чтение \n
    if (fscanf(f, "%u", &house->flat_number) != 1)
        return ERR_IO;
    fgetc(f); // Чтение \n
    return ERR_OK;
}

void house_print(FILE *f, const house_t *house, bool is_table)
{
    if (!is_table)
        fprintf(f, "%s\n%u\n%u\n", house->sreet, house->house_number, house->flat_number);
    else
    {
        char *tmp_s = "";
        // Дом
        fprintf(f, "%*s | ", STREET_LEN, house->sreet);
        fprintf(f, "%*u | ", HOUSE_WIDTH, house->house_number);
        fprintf(f, "%*u | ", FLAT_WIDTH, house->flat_number);
        // Общежитие
        fprintf(f, "%*s | ", DORMITORY_NUM_WITH, tmp_s);
        fprintf(f, "%*s | ", ROOM_NUM_WIDTH, tmp_s);
        // Съемное
        fprintf(f, "%*s | ", STREET_LEN, tmp_s);
        fprintf(f, "%*s | ", HOUSE_WIDTH, tmp_s);
        fprintf(f, "%*s | ", FLAT_WIDTH, tmp_s);
        fprintf(f, "%*s | ", COST_WIDTH, tmp_s);
    }
}

int dormitory_input(FILE *f, dormitory_t *dormitory)
{
    if (fscanf(f, "%u", &dormitory->dormitory_number) != 1)
        return ERR_IO;
    fgetc(f); // Чтение \n
    
    if (fscanf(f, "%u", &dormitory->room_number) != 1)
        return ERR_IO;
    return ERR_OK;
    fgetc(f); // Чтение \n
}

void dormitory_print(FILE *f, const dormitory_t *dormitory, bool is_table)
{
    if (!is_table)
        fprintf(f, "%u\n%u\n", dormitory->dormitory_number, dormitory->room_number);
    else
    {
        char *tmp_s = "";
        // Дом
        fprintf(f, "%*s | ", STREET_LEN, tmp_s);
        fprintf(f, "%*s | ", HOUSE_WIDTH, tmp_s);
        fprintf(f, "%*s | ", FLAT_WIDTH, tmp_s);
        // Общежитие
        fprintf(f, "%*u | ", DORMITORY_NUM_WITH, dormitory->dormitory_number);
        fprintf(f, "%*u | ", ROOM_NUM_WIDTH, dormitory->room_number);
        // Съемное
        fprintf(f, "%*s | ", STREET_LEN, tmp_s);
        fprintf(f, "%*s | ", HOUSE_WIDTH, tmp_s);
        fprintf(f, "%*s | ", FLAT_WIDTH, tmp_s);
        fprintf(f, "%*s | ", COST_WIDTH, tmp_s);

    }
}

int rental_input(FILE *f, rental_t *rental)
{
    int rc = input_str(f, STREET_LEN, rental->sreet);
    if (rc != ERR_OK)
        return rc;
    if (fscanf(f, "%u", &rental->house_number) != 1)
        return ERR_IO;
    fgetc(f); // Чтение \n
    if (fscanf(f, "%u", &rental->flat_number) != 1)
        return ERR_IO;
    fgetc(f); // Чтение \n
    if (fscanf(f, "%lf", &rental->cost) != 1)
        return ERR_IO;
    fgetc(f); // Чтение \n
    return ERR_OK;
}

void rental_print(FILE *f, const rental_t *rental, bool is_table)
{
    if (!is_table)
    {
        fprintf(f, "%s\n%u\n%u\n%lf\n", rental->sreet, rental->house_number,
            rental->flat_number, rental->cost);
    }
    else
    {
        char *tmp_s = "";
        // Дом
        fprintf(f, "%*s | ", STREET_LEN, tmp_s);
        fprintf(f, "%*s | ", HOUSE_WIDTH, tmp_s);
        fprintf(f, "%*s | ", FLAT_WIDTH, tmp_s);
        // Общежитие
        fprintf(f, "%*s | ", DORMITORY_NUM_WITH, tmp_s);
        fprintf(f, "%*s | ", ROOM_NUM_WIDTH, tmp_s);
        // Съемное
        fprintf(f, "%*s | ", STREET_LEN, rental->sreet);
        fprintf(f, "%*u | ", HOUSE_WIDTH, rental->house_number);
        fprintf(f, "%*u | ", FLAT_WIDTH, rental->flat_number);
        fprintf(f, "%*.2lf | ", COST_WIDTH, rental->cost);

    }
}

int student_input(FILE *f, student_t *student, prompt_t prompt)
{
    prompt(stdout,"\033[93mТип жилья\033[0m\n");
    prompt(stdout,"\033[93m0 - дом\033[0m\n");
    prompt(stdout,"\033[93m1 - общежитие\033[0m\n");
    prompt(stdout,"\033[93m2 - съемное жилье\033[0m\n");
    prompt(stdout,"\033[93m: \033[0m");
    if (fscanf(f, "%u", &student->housing_type) != 1)
    {
        prompt(stdout,"\033[91mНеудалось считать тип\033[0m\n");
        return ERR_IO;    
    }
    if (student->housing_type >= 3)
    {
        prompt(stdout,"\033[91mНеверное значение типа\033[0m\n");
        return ERR_RANGE;
    }
    fgetc(f); // Чтение \n

    prompt(stdout,"\033[93mФамилия (до 10 символов): \033[0m");
    int rc = input_str(f, SURNAME_LEN, student->surname);
    if (rc != ERR_OK)
    {
        prompt(stdout,"\033[91mНеудалось считать фамилию\033[0m\n");
        return rc;
    }

    prompt(stdout,"\033[93mИмя (до 10 символов): \033[0m");
    rc = input_str(f, NAME_LEN, student->name);
    if (rc != ERR_OK)
    {
        prompt(stdout,"\033[91mНеудалось считать имя\033[0m\n");
        return ERR_IO;
    }

    prompt(stdout,"\033[93mГруппа (до 10 символов): \033[0m");
    rc = input_str(f, GROUP_LEN, student->group);
    if (rc != ERR_OK)
    {
        prompt(stdout,"\033[91mНеудалось считать группу\033[0m\n");
        return ERR_IO;
    }

    prompt(stdout,"\033[93mПол\033[0m\n");
    prompt(stdout,"\033[93m0 - Ж\033[0m\n");
    prompt(stdout,"\033[93m1 - М\033[0m\n");
    prompt(stdout,"\033[93m: \033[0m");
    if (fscanf(f, "%u", &student->sex) != 1)
    {
        prompt(stdout,"\033[91mНеудалось считать пол\033[0m\n");
        return ERR_IO;
    }
    else if (student->sex != 1 && student->sex != 0)
    {
        prompt(stdout,"\033[91mНеверное значение пола\033[0m\n");
        return ERR_RANGE;
    }
    fgetc(f); // Чтение \n

    prompt(stdout,"\033[93mВозраст: \033[0m\n");
    if (fscanf(f, "%u", &student->age) != 1)
    {
        prompt(stdout,"\033[91mНеудалось считать возраст\033[0m\n");
        return ERR_IO;
    }
    fgetc(f); // Чтение \n

    prompt(stdout,"\033[93mСредняя оценка за сессию [1 - 5]: \033[0m");
    if (fscanf(f, "%lf", &student->average_mark) != 1)
    {
        prompt(stdout,"\033[91mНеудалось считать оценку\033[0m\n");
        return ERR_IO;
    }
    fgetc(f); // Чтение \n


    prompt(stdout,"\033[93mГод поступления: \033[0m");
    if (fscanf(f, "%ud", &student->entry_date) != 1)
    {
        prompt(stdout,"\033[91mНеудалось считать год поступления\033[0m\n");
        return ERR_IO; 
    }
    fgetc(f); // Чтение \n

    if (student->housing_type == HOUSE)
    {
        prompt(stdout,"\033[93mВведите значения через enter\033[0m\n");
        prompt(stdout,"\033[93mУлица (до 10 символов), номер дома, номер квартиры: \033[0m\n");
        rc = house_input(f, &student->housing.house);
        if (rc != ERR_OK)
        {
            prompt(stdout,"\033[91mНеправильно введены параметры\033[0m\n");
            return rc;
        }
    }
    if (student->housing_type == DORMITORY)
    {
        prompt(stdout,"\033[93mВведите значения через enter\033[0m\n");
        prompt(stdout,"\033[93mНомер общежития, номер комнаты: \033[0m\n");

        rc = dormitory_input(f, &student->housing.dormitory);
        if (rc != ERR_OK)
        {
            prompt(stdout,"\033[91mНеправильно введены параметры\033[0m\n");
            return rc;
        }
    }
    if (student->housing_type == RENTAL)
    {
        prompt(stdout,"\033[93mВведите значения через enter\033[0m\n");
        prompt(stdout,"\033[93mУлица (до 10 символов), номер дома, номер квартиры, стоимость аренды: \033[0m\n");

        rc = rental_input(f, &student->housing.rental);
        if (rc != ERR_OK)
        {
            prompt(stdout,"\033[91mНеправильно введены параметры: \033[0m\n");
            return rc;
        }
    }
    return ERR_OK;
}

void student_print(FILE *f, const student_t *student, bool is_table)
{
    if (!is_table)
    {
        fprintf(f, "%d\n", (int)student->housing_type);
        fprintf(f, "%s\n", student->surname);
        fprintf(f, "%s\n", student->name);
        fprintf(f, "%s\n", student->group);
        fprintf(f, "%u\n", student->sex);
        fprintf(f, "%u\n", student->age);
        fprintf(f, "%lf\n", student->average_mark);
        fprintf(f, "%u\n", student->entry_date);
        if (student->housing_type == HOUSE)
            house_print(f, &student->housing.house, is_table);
        else if(student->housing_type == DORMITORY)
            dormitory_print(f, &student->housing.dormitory, is_table);
        else if(student->housing_type == RENTAL)
            rental_print(f, &student->housing.rental, is_table);
    }
    else
    {
        fprintf(f, "%-*lu | ",N_WIDTH, student->n);

        if (student->housing_type == HOUSE)
            printf("%-*s | ", HOUSING_WIDTH, "house");
        else if(student->housing_type == DORMITORY)
            printf("%-*s | ", HOUSING_WIDTH, "dormitory");
        else
            printf("%-*s | ", HOUSING_WIDTH, "rental");

        fprintf(f, "%-*s | ", SURNAME_LEN, student->surname);
        fprintf(f, "%-*s | ", NAME_LEN, student->name);
        fprintf(f, "%-*s | ", GROUP_LEN, student->group);
        fprintf(f, "%-*u | ", SEX_WIDTH, student->sex);
        fprintf(f, "%-*u | ", AGE_WIDTH, student->age);
        fprintf(f, "%-.*lf | ", MARK_WIDTH, student->average_mark);
        fprintf(f, "%-*u | ", DATE_WIDTH, student->entry_date);
        if (student->housing_type == HOUSE)
            house_print(f, &student->housing.house, is_table);
        else if(student->housing_type == DORMITORY)
            dormitory_print(f, &student->housing.dormitory, is_table);
        else if(student->housing_type == RENTAL)
            rental_print(f, &student->housing.rental, is_table);
        fprintf(f, "\n");
    }
}


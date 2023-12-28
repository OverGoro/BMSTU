#ifndef __STRIO_H__
#define __STRIO_H__
#include "errors.h"
#include "constants.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/// @brief Считывание сроки
/// @param buff Буффер 
/// @param buff_size Размер буффера
/// @return Код ошибки
int input_string(char *buff, size_t buff_size);
#endif

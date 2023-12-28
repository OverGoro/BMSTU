#ifndef __FUNCS_H__
#define __FUNCS_H__
#include <stddef.h>

/// @brief Функция выполняет поиск первого вхождения в строку string1 любого из символов строки string2.
/// @param string1 Строка для поиск вхождений
/// @param string2 Входящая строка
/// @return указатель на первое вхождение в string1 найденного символа, или — пустой указатель,
/// если нет ни одного совпадения. Поиск не учитывает завершающий нуль-символ
char *my_strpbrk(const char *string1, const char *string2);

/// @brief поиск символов строки string2 в строке string1
/// @param string1 Строка, в которой выполняется поиск
/// @param string2 Строка с искомыми символами
/// @return Длина начального участка строки string1, содержащего только символы строки string2.
/// Если все символы строки string1 входят в строку string2, функция возвращает длину всей строки string1.
/// Если первый символ в string1 не входит в строку string2, функция возвращает ноль
size_t my_strspn(const char *string1, const char *string2);

/// @brief Поиск первого вхождения любого символа из string2 в string1
/// @param[in] string1 Строка
/// @param[in] string2 Строка с искомыми символами
/// @return Количество символов до найденного первого вхождения
size_t my_strcspn(const char *string1, const char *string2);

/// @brief Поиск первого вхождения символа в строку
/// @param[in] string Строка
/// @param[in] symbol Символ
/// @return Указатель на найденный символ
char *my_strchr(const char *string, const int symbol);

/// @brief Поиск последнего вхождения символа в строку
/// @param[in] string Строка
/// @param[in] symbol Символ
/// @return Уаказаетль на найденный символ
char *my_strrchr(const char *string, const int symbol);

#endif

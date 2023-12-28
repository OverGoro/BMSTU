#include "matrix.h"
/// @brief Проверка четности числа
/// @param[in] a Число
/// @return Четность
bool is_even(int a)
{
    if (a % 2 != 0)
    {
        return false;
    }
    return true;
}
int find_min_element(int mat[][M], size_t mat_size, int *min_el)
{
    if (mat_size == 1)
    {
        return ERROR_NO_UNDER_DIAG_ELEMENTS;
    }
    
    int el = mat[1][0];
    for (size_t i = 0; i < mat_size; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (is_even(mat[i][j]) == false && (is_even(el) == true || el > mat[i][j]))
            {
                el = mat[i][j];
            }
        }
    }
    if (is_even(el) == true)
    {
        return ERROR_ONLY_EVEN;
    }
    *min_el = el;
    return OK;    
}

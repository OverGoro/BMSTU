#include "check_cmp.h"

int cmp_arr_int(int *parr, size_t n_arr, int *ans, size_t n_ans)
{
    int rc = 0;
    if (n_ans != n_arr)
        rc = 1;
    for (size_t i = 0; rc == 0 && i < n_arr; i++)
    {
        if (parr[i] != ans[i])
            rc = 1;
    }
    return rc;
}

